#include "var.hh"

#include <string>
#include <iostream>
#include <algorithm>

#include "pdm/core/bitsets.hh"
#include "pdm/ast/node.hh"
#include "pdm/printer/printer.hh"

#include "pdm/feedback/feedback.hh"
#include "pdm/feedback/note.hh"
#include "pdm/feedback/letter.hh"
#include "pdm/feedback/manager.hh"

#include "var-archetype.hh"
#include "var-invariant.hh"
#include "typeop-result.hh"

namespace pdm::types {
    inline Var::Var(
        std::string&& name, ast::Node* opt_client_ast_node, VarArchetype archetype,
        SolveResult initial_solve_iter_result
    )
    :   m_name(std::move(name)),
        m_opt_client_ast_node(opt_client_ast_node),
        m_var_archetype(archetype),
        m_assumed_common_invariants(),
        m_assumed_kind_dependent_invariants(),
        m_invalid_assumed_kind_dependent_invariants(),
        m_assumed_kind(Kind::META_Unknown),
        m_assumed_sub_var_edges(),
        m_assumed_super_var_edges(),
        m_sp2_last_flushed_sub_var_count(0),
        m_sp2_last_flushed_kd_invariant_count(0),
        m_sp2_last_flushed_super_var_count(0),
        m_initial_solve_iter_result(initial_solve_iter_result),
        m_prev_solve_iter_result(initial_solve_iter_result),
        m_kdvs(nullptr),
        m_opt_type_soln(nullptr),
        m_finish_result(FinishResult::Plastic)
    {}

    SolveResult Var::assume_invariant_holds(VarInvariant* invariant) {
        return assume_invariant_holds_impl(invariant, false);
    }
    SolveResult Var::assume_invariant_holds_overwrite_fixed(VarInvariant* invariant) {
        return assume_invariant_holds_impl(invariant, true);
    }
    SolveResult Var::equals_by_induction(Var* var) {
        SolveResult res1 = help_assume_sub_var(this, var, true);
        SolveResult res2 = help_assume_sub_var(var, this, true);
        return result_and(res1, res2);
    }
    SolveResult Var::sub_var_by_induction(Var* var) {
        return help_assume_sub_var(this, var, true);
    }

    SolveResult Var::assume_invariant_holds_impl(VarInvariant* invariant, bool override_fixed) {
        // if this invariant was not intended for a Var of this VarKind, then meta-type error:
        if (var_archetype() != invariant->domain_var_archetype()) {
            // todo: intercept templates here-- get their ret_tv and type that instead.
            return SolveResult::TypingError;
        }

        // if constant/fixed and 'override_fixed' is not set, this Var is 'change_forbidden'
        // this means ONLY sub_var and supervar invariants are stored.
        // - use 'override_fixed=true' to setup fixed Vars
        // - then, use 'override_fixed=false' to setup everything else
        bool change_forbidden = is_constant() && !override_fixed;

        // if a kind-independent invariant, adding and applying immediately.
        KindIndependentVarInvariant* common_invariant = nullptr;
        if ((common_invariant = dynamic_cast<KindIndependentVarInvariant*>(invariant)) != nullptr) {
            m_assumed_common_invariants.push_back(common_invariant);

            // subtype:
            auto subtype_of_invariant = dynamic_cast<SubtypeOfInvariant*>(invariant);
            if (subtype_of_invariant != nullptr) {
                return help_assume_sub_var(this, subtype_of_invariant->supertype_tv(), false);
            }

            // subclass:
            auto subclass_of_invariant = dynamic_cast<SubclassOfInvariant*>(invariant);
            if (subclass_of_invariant != nullptr) {
                return help_assume_sub_var(this, subclass_of_invariant->superclass_cv(), false);
            }
        
            // class instanceship:
            auto classof_invariant = dynamic_cast<ClassOfInvariant*>(invariant);
            if (classof_invariant != nullptr) {
                return help_assume_sub_var(classof_invariant->member_tv(), this, false);
            }

            // is number: separate invariant channel
            auto is_number_invariant = dynamic_cast<IsNumberVarInvariant*>(invariant);
            if (is_number_invariant != nullptr) {
                auto old_invariant_it = std::find(
                    m_opt_force_number_invariants.begin(),
                    m_opt_force_number_invariants.end(),
                    is_number_invariant
                );
                if (old_invariant_it == m_opt_force_number_invariants.end()) {
                    m_opt_force_number_invariants.push_back(is_number_invariant);
                    return SolveResult::UpdatedOrFresh;
                } else {
                    return SolveResult::NoChange;
                }
            }

            // Unknown KindIndependentVarInvariant kind...
            assert(0 && "Unknown KindIndependentVarInvariant.");
        }

        // if a kind-dependent invariant, adding to a list and deferring for later.
        // - we defer because if a TypeVar is multi-kind, we already have an error, so we can halt with the simplest error message.
        // - before KindDependentInvariant
        // also adding a kind-invariant corresponding to the assumed kind.
        // - NOTE: if change forbidden => ignore ALL kind-dependent invariants.
        if (change_forbidden) {
            return SolveResult::NoChange;
        } else {
            KindDependentInvariant* kind_dependent_invariant = nullptr;
            if ((kind_dependent_invariant = dynamic_cast<KindDependentInvariant*>(invariant)) != nullptr) {
                // kind-dependent invariants deferred for later.
                auto existing_kdi = std::find(
                    m_assumed_kind_dependent_invariants.begin(),
                    m_assumed_kind_dependent_invariants.end(),
                    kind_dependent_invariant
                );
                if (existing_kdi == m_assumed_kind_dependent_invariants.end()) {
                    if (m_assumed_kind == Kind::META_Unknown) {
                        m_assumed_kind = kind_dependent_invariant->required_type_kind();
                        m_assumed_kind_dependent_invariants.push_back(kind_dependent_invariant);
                    } else {
                        if (m_assumed_kind != kind_dependent_invariant->required_type_kind()) {
                            m_invalid_assumed_kind_dependent_invariants.push_back(kind_dependent_invariant);
                        } else {
                            m_assumed_kind_dependent_invariants.push_back(kind_dependent_invariant);
                        }
                    }
                    return SolveResult::UpdatedOrFresh;
                } else {
                    return SolveResult::NoChange;
                }
            }
        }
        
        return SolveResult::TypingError;
    }

    //
    // Solution:
    //

    SolveResult Var::solve_iter() {
        return m_prev_solve_iter_result = solve_iter_impl();
    }

    bool Var::finish() {
        switch (m_finish_result)
        {
            case FinishResult::Finished_Ok:
            {
                return true;
            }
            case FinishResult::Finished_Broken_Typing:
            {
                return false;
            }
            case FinishResult::Finished_Broken_Compiler:
            {
                if (pdm::DEBUG) {
                    assert(0 && "Compiler error in Var::finish");
                }
                return false;
            }
            case FinishResult::Baking:
            {
                // no new information-- mid-cycle.
                // todo: return a promise?
                return true;
            }
            case FinishResult::Plastic:
            {
                // set 'baking' to true
                m_finish_result = FinishResult::Baking;

                // finishing:
                bool finish_ok = finish_impl();

                // parsing OK and returning/updating 'result' to fixed:
                if (finish_ok) {
                    m_finish_result = FinishResult::Finished_Ok;
                    return true;
                } else {
                    m_finish_result = FinishResult::Finished_Broken_Typing;
                    return false;
                }
            }
        }
    }
    bool Var::finish_impl() {
        // ignoring constant/fixed types:
        assert(!is_constant());

        // checking for type_kind mismatch:
        if (!m_invalid_assumed_kind_dependent_invariants.empty()) {
            // todo: print invalid assumed variants, rejected due to required_type_kind() mismatch.
            assert(
                0 &&
                "NotImplemented: printing invalid assumed constraints, rejected due to required_type_kind() mismatch."
            );
            return false;
        }

        // if this Var must solve to a number, ensure so:
        if (m_assumed_kind != Kind::META_Unknown) {
            if (!m_opt_force_number_invariants.empty()) {
                if (!is_number_type_kind(m_assumed_kind)) {
                    return false;
                }
            }
        }

        // checking latest solve_iter result:
        bool solve_ok = false;
        {
            SolveResult result = solve_iter();
            switch (result)
            {
                case SolveResult::TypingError:
                {
                    std::string headline = ("Could not solve type.");
                    std::string more = "";
                    std::vector<feedback::Note*> notes;
                    if (opt_client_ast_node() != nullptr) {
                        std::string desc0 = "see syntax element here...";
                        notes.push_back(new feedback::AstNodeNote(
                            std::move(desc0),
                            opt_client_ast_node()
                        ));
                    }
                    feedback::post(new feedback::Letter(
                        feedback::Severity::Error,
                        std::move(headline),
                        std::move(more),
                        std::move(notes)
                    ));
                    solve_ok = false;
                    break;
                }
                case SolveResult::CompilerError:
                {
                    std::string headline = (
                        "A compiler error occurred while solving a type."
                    );
                    std::string more = "";
                    std::vector<feedback::Note*> notes;
                    if (opt_client_ast_node() != nullptr) {
                        std::string desc0 = "see syntax element here...";
                        notes.push_back(new feedback::AstNodeNote(
                            std::move(desc0),
                            opt_client_ast_node()
                        ));
                    }
                    feedback::post(new feedback::Letter(
                        feedback::Severity::Error,
                        std::move(headline),
                        std::move(more),
                        std::move(notes)
                    ));
                    solve_ok = false;
                    break;
                }
                default:
                {
                    solve_ok = true;
                    break;
                }
            }
        }
        if (!solve_ok) {
            return false;
        }

        // solving for an algebraic type if required:
        if (VarArchetype::Type == var_archetype()) {
            bool reify_ok = false;
            {
                if (m_kdvs) {
                    m_opt_type_soln = m_kdvs->reify(this);
                    reify_ok = (m_opt_type_soln != nullptr);
                } else {
                    // todo: reject since insufficient information
                    // assert(0 && "NotImplemented: report insufficient information at Var::finish");
                    std::cout << "NotImplemented: report insufficient information at Var::finish" << std::endl;
                    reify_ok = false;
                }
            }
            if (!reify_ok) {
                // assert(0 && "NotImplemented: report !reify_ok in Var::finish");
                std::cout << "NotImplemented: report !reify_ok in Var::finish" << std::endl;
                return false;
            }

            if (!m_opt_type_soln->check_finite()) {
                // infinite type; error already posted.
                return false;
            }
        }

        // all ok!
        return true;
    }

    Type* Var::get_type_soln() {
        if (finish()) {
            return m_opt_type_soln;
        } else {
            return nullptr;
        }
    }

    SolveResult Var::solve_iter_impl() {
        // before any solution, checking if an error occurred in a previous iter and returning early if so:
        {
            if (m_prev_solve_iter_result == SolveResult::TypingError) {
                return SolveResult::TypingError;
            }
            if (m_prev_solve_iter_result == SolveResult::CompilerError) {
                return SolveResult::CompilerError;
            }
        }
        assert(
            (m_prev_solve_iter_result == SolveResult::UpdatedOrFresh) ||
            (m_prev_solve_iter_result == SolveResult::NoChange)
        );

        // since the last update, there have been (1) new supervars, (2) new sub_vars, and (3) new invariants.
        // start by assuming no change has occurred. If any changes are applied, update 'result'.
        SolveResult result = SolveResult::NoChange;

        // Phase 1: checking that all related vars contain values of the same 'kind':
        {
            result = result_and(result, solve_iter_phase1());
        }

        // Phase 2: updating KDVSes
        if (!result_is_error(result)) {
            result = result_and(result, solve_iter_phase2());
        }

        return result;
    }
    SolveResult Var::solve_iter_phase1() {
        Kind super_var_kind = get_kind_from_edges(m_assumed_super_var_edges);
        Kind sub_var_kind = get_kind_from_edges(m_assumed_sub_var_edges);

        if (super_var_kind == Kind::META_GetKindFromEdgesError || sub_var_kind == Kind::META_GetKindFromEdgesError) {
            return SolveResult::TypingError;
        }

        SolveResult result = SolveResult::NoChange;

        if (super_var_kind != Kind::META_Unknown) {
            if (m_assumed_kind == Kind::META_Unknown) {
                m_assumed_kind = super_var_kind;
                result = SolveResult::UpdatedOrFresh;
            } else if (m_assumed_kind != super_var_kind) {
                std::string headline = "Type has inconsistent kinds vs. super-var";
                std::vector<feedback::Note*> notes;
                if (m_opt_client_ast_node) {
                    std::string desc = "See AST node here...";
                    notes.push_back(
                        new feedback::SourceLocNote(std::move(desc), m_opt_client_ast_node->loc())
                    );
                }
                feedback::post(new feedback::Letter(
                    feedback::Severity::Error,
                    std::move(headline), {},
                    std::move(notes)
                ));
                return SolveResult::TypingError;
            }
        }
        if (sub_var_kind != Kind::META_Unknown) {
            if (m_assumed_kind == Kind::META_Unknown) {
                m_assumed_kind = sub_var_kind;
                result = SolveResult::UpdatedOrFresh;
            } else if (m_assumed_kind != sub_var_kind) {
                std::string headline = "Type has inconsistent kinds vs. sub-var";
                std::vector<feedback::Note*> notes;
                if (m_opt_client_ast_node) {
                    std::string desc = "See AST node here...";
                    notes.push_back(
                        new feedback::SourceLocNote(std::move(desc), m_opt_client_ast_node->loc())
                    );
                }
                feedback::post(new feedback::Letter(
                    feedback::Severity::Error,
                    std::move(headline), {},
                    std::move(notes)
                ));
                return SolveResult::TypingError;
            }
        }

        return result;
    }
    Kind Var::get_kind_from_edges(std::vector<Var::Edge> const& edges) {
        Kind common_kind = Kind::META_Unknown;
        size_t edges_count = edges.size();
        for (size_t index = 0; index < edges_count; index++) {
            Var::Edge const& edge = edges[index];
            Kind edge_kind = edge.var->m_assumed_kind;
            if (edge_kind == Kind::META_Unknown) {
                continue;
            }
            if (common_kind == Kind::META_Unknown) {
                common_kind = edge_kind;
            } else if (common_kind != edge_kind) {
                // todo: report this error using Feedback
                return Kind::META_GetKindFromEdgesError;
            }
        }
        return common_kind;
    }

    SolveResult Var::solve_iter_phase2() {
        // first, checking that no invalid invariants have been assumed, in which case SP2 terminates with a typing
        // error:
        if (!m_invalid_assumed_kind_dependent_invariants.empty()) {
            return SolveResult::TypingError;
        }

        SolveResult result = SolveResult::NoChange;

        // creating the KDVS:
        if (m_kdvs == nullptr) {
            // invoking the KDVS submodule to make a KDVS:
            NewKDVS kdvs_create_info = try_new_kdvs_for(m_var_archetype, m_assumed_kind);
            switch (kdvs_create_info.result)
            {
                case KcResult::InsufficientInfo:
                {
                    // do nothing; kdvs stays at nullptr.
                    break;
                }
                case KcResult::Ok:
                {
                    // create a KDVS!
                    m_kdvs = kdvs_create_info.kdvs;
                    result = result_and(result, SolveResult::UpdatedOrFresh);
                    break;
                }
                case KcResult::Error_MixedKind:
                {
                    // error in kind-check above!
                    std::cout << "!!- Faulty kind-check detected in Var::update_kd_invariants_impl" << std::endl;
                    result = result_and(result, SolveResult::CompilerError);
                    break;
                }
            }
        } else {
            // KDVS already exists; still valid.
        }

        // flushing invariants to the KDVS:
        if (m_kdvs != nullptr && !m_assumed_kind_dependent_invariants.empty()) {
            size_t a = m_sp2_last_flushed_kd_invariant_count;
            size_t b = m_assumed_kind_dependent_invariants.size() - 1;
            for (size_t i = a; i <= b; i++) {
                KindDependentInvariant* kd_invariant = m_assumed_kind_dependent_invariants[i];
                m_kdvs->try_add_invariant(kd_invariant);
            }
            m_sp2_last_flushed_kd_invariant_count = b;
        }

        // flushing invariants to sub_vars:
        // - fresh sub_vars need all invariants, old and new.
        // - old sub_vars only need new invariants.
        // - after propagating updates, need to update bounds for next iter.
        {
            size_t old_invariant_count = m_sp2_last_flushed_kd_invariant_count;
            size_t old_sub_var_count = m_sp2_last_flushed_sub_var_count;

            // adding only new invariants to old sub_vars:
            for (size_t old_sub_var_index = 0; old_sub_var_index < old_sub_var_count; old_sub_var_index++) {
                Var* old_sub_var = m_assumed_sub_var_edges[old_sub_var_index].var;
                for (
                    size_t new_invariant_index = old_invariant_count;
                    new_invariant_index < m_assumed_kind_dependent_invariants.size();
                    new_invariant_index++
                    ) {
                    VarInvariant* new_invariant = m_assumed_kind_dependent_invariants[new_invariant_index];
                    result = result_and(result, old_sub_var->assume_invariant_holds(new_invariant));
                }
            }

            // adding all invariants to only new sub_vars:
            for (size_t new_sub_var_index = old_sub_var_count;
                 new_sub_var_index < m_assumed_sub_var_edges.size();
                 new_sub_var_index++) {
                Var* new_sub_var = m_assumed_sub_var_edges[new_sub_var_index].var;
                for (VarInvariant* invariant: m_assumed_kind_dependent_invariants) {
                    result = result_and(new_sub_var->assume_invariant_holds(invariant), result);
                }
            }

            // updating bounds for next iter:
            // assume all invariants and all sub_vars so far have been propagated.
            m_sp2_last_flushed_kd_invariant_count = m_assumed_kind_dependent_invariants.size();
            m_sp2_last_flushed_sub_var_count = m_assumed_sub_var_edges.size();
        }

        return result;
    }


    SolveResult Var::help_assume_sub_var(Var* sub_var, Var* super_var, bool is_second_order_invariant) {
        SolveResult assume_op_result = SolveResult::NoChange;

        {   // inserting super-var into sub-var:
            bool existing_super_var_matches_super_var = false;
            for (Var::Edge const& existing_super_var_edge: sub_var->m_assumed_super_var_edges) {
                Var* existing_super_var = existing_super_var_edge.var;
                if (existing_super_var == super_var) {
                    existing_super_var_matches_super_var = true;
                    break;
                }
            }
            if (!existing_super_var_matches_super_var) {
                sub_var->m_assumed_super_var_edges.push_back({super_var, is_second_order_invariant});
                assume_op_result = SolveResult::UpdatedOrFresh;
            }
        }

        {   // inserting sub-var into super-var:
            bool existing_sub_var_matches_sub_var = false;
            for (Var::Edge const& existing_sub_var_edge: super_var->m_assumed_sub_var_edges) {
                Var* existing_sub_var = existing_sub_var_edge.var;
                if (existing_sub_var == sub_var) {
                    existing_sub_var_matches_sub_var = true;
                    break;
                }
            }
            if (!existing_sub_var_matches_sub_var) {
                super_var->m_assumed_sub_var_edges.push_back({sub_var, is_second_order_invariant});
                assume_op_result = SolveResult::UpdatedOrFresh;
            }
        }
        
        return assume_op_result;
    }

    SolveResult TypeVar::initial_sp2_result_for_soln_bill(TypeVarSolnBill soln_bill) {
        switch (soln_bill) {
            case TypeVarSolnBill::Fixed: 
            {
                return SolveResult::NoChange;
            }
            case TypeVarSolnBill::Monotype:
            {
                return SolveResult::UpdatedOrFresh;
            }
        }
    }

    //
    // Printing:
    //

    void Var::print(printer::Printer* p) const {
        print_title(p);
        printer::print_c_str(p, " {");
        printer::print_newline_indent(p);
        {
            help_print_assumed_kind_bitset(p);
            printer::print_newline(p);
            help_print_assumed_common_invariants(p);
            printer::print_newline(p);
            help_print_assumed_kind_dependent_invariants(p);
            printer::print_newline(p);
            help_print_assumed_sub_vars(p);
            printer::print_newline(p);
            help_print_assumed_super_vars(p);
            printer::print_newline(p);
            help_print_opt_client_ast_node(p);
            printer::print_newline(p);
            help_print_kdvs(p);
            printer::print_newline(p);
            help_print_soln(p);
        }
        printer::print_newline_exdent(p);
        printer::print_c_str(p, "}");
        printer::print_newline(p);
    }

    void Var::print_title(printer::Printer* p) const {
        // printing a prefix denoting var_archetype():
        switch (var_archetype())
        {
            case VarArchetype::Type:
            {
                printer::print_c_str(p, "Type");
                break;
            }
            case VarArchetype::Class:
            {
                printer::print_c_str(p, "Class");
                break;
            }
            default:
            {
                printer::print_c_str(p, "Var(?)");
                break;
            }
        }
        printer::print_c_str(p, " ");

        // printing the var name:
        printer::print_str(p, name());

        // printing last kdr changed:
        switch (m_prev_solve_iter_result)
        {
            case SolveResult::UpdatedOrFresh:
            {
                printer::print_c_str(p, " (UpdatedOrFresh)");
                break;
            }
            case SolveResult::NoChange:
            {
                printer::print_c_str(p, " (NoChange)");
                break;
            }
            case SolveResult::TypingError:
            {
                printer::print_c_str(p, " (TypingError)");
                break;
            }
            case SolveResult::CompilerError:
            {
                printer::print_c_str(p, " (CompilerError)");
                break;
            }
        }

        // printing the var addr:
        printer::print_c_str(p, " @ ");
        printer::print_uint_hex(p, reinterpret_cast<u64>(this));
    }
    void Var::help_print_assumed_kind_bitset(printer::Printer* p) const {
        printer::print_c_str(p, "assume TypeKind: ");
        printer::print_c_str(p, type_kind_as_str(m_assumed_kind));
    }
    void Var::help_print_assumed_common_invariants(printer::Printer* p) const {
        printer::print_c_str(p, "assume CommonInvariants:");
        if (assumed_common_invariants().empty()) {
            printer::print_c_str(p, " None");
        } else {
            for (VarInvariant* invariant: assumed_common_invariants()) {
                printer::print_newline(p);
                printer::print_c_str(p, "- ");
                printer::print_str(p, invariant->name());
            }
        }
    }
    void Var::help_print_assumed_kind_dependent_invariants(printer::Printer* p) const {
        printer::print_c_str(p, "assume KindDependentInvariants:");
        if (assumed_kind_dependent_invariants().empty()) {
            printer::print_c_str(p, " None");
        } else {
            for (VarInvariant* invariant: assumed_kind_dependent_invariants()) {
                printer::print_newline(p);
                printer::print_c_str(p, "- ");
                printer::print_str(p, invariant->name());
            }
        }
    }
    void Var::help_print_assumed_sub_vars(printer::Printer* p) const {
        printer::print_c_str(p, "assume Sub-vars:");
        if (assumed_sub_var_edges().empty()) {
            printer::print_c_str(p, " None");
        } else {
            for (Var::Edge const& edge: m_assumed_sub_var_edges) {
                Var* assumed_sub_var = edge.var;
                printer::print_newline(p);
                printer::print_c_str(p, "- ");
                assumed_sub_var->print_title(p);
            }
        }
    }
    void Var::help_print_assumed_super_vars(printer::Printer* p) const {
        printer::print_c_str(p, "assume Super-vars:");
        if (assumed_super_var_edges().empty()) {
            printer::print_c_str(p, " None");
        } else {
            for (auto assumed_super_var_edge: m_assumed_super_var_edges) {
                printer::print_newline(p);
                printer::print_c_str(p, "- ");
                assumed_super_var_edge.var->print_title(p);
            }
        }
    }
    void Var::help_print_kdvs(printer::Printer* p) const {
        printer::print_c_str(p, "kdvs: ");
        if (m_kdvs != nullptr) {
            m_kdvs->print(p);
        } else {
            printer::print_c_str(p, "None");
        }
    }
    void Var::help_print_opt_client_ast_node(printer::Printer* p) const {
        printer::print_c_str(p, "client: ");
        if (m_opt_client_ast_node != nullptr) {
            printer::print_c_str(p, ast::kind_as_text(m_opt_client_ast_node->kind()));
            printer::print_c_str(p, " @ ");
            printer::print_uint_hex(p, reinterpret_cast<u64>(m_opt_client_ast_node));
        } else {
            printer::print_c_str(p, "N/A");
        }
    }
    void Var::help_print_soln(printer::Printer* p) const {
        printer::print_c_str(p, "soln: ");
        if (m_opt_type_soln) {
            m_opt_type_soln->print(p);
        } else if (var_archetype() != VarArchetype::Type) {
            printer::print_c_str(p, "N/A (Exempt-archetype)");
        } else {
            printer::print_c_str(p, "NULL");
        }
    }

    //
    // Constant types:
    //
    // todo: implement constant Relations for these invariants to be applied from.

    FixedTypeVar::FixedTypeVar(std::string&& name, Type* fixed_soln)
    :   TypeVar("FixedType:" + std::move(name), fixed_soln, nullptr, TypeVarSolnBill::Fixed)
    {
        m_finish_result = FinishResult::Finished_Ok;
        m_opt_type_soln = fixed_soln;
    }
    
    VoidFixedTypeVar::VoidFixedTypeVar()
    :   FixedTypeVar(std::move(std::string("Void")), VoidType::get()) 
    {
        assume_invariant_holds_overwrite_fixed(new IsVoidInvariant(nullptr, VarArchetype::Type));
    }
    StringFixedTypeVar::StringFixedTypeVar()
    :   FixedTypeVar(std::move(std::string("String")), StringType::get())
    {
        assume_invariant_holds_overwrite_fixed(new IsStringInvariant(nullptr, VarArchetype::Type));
    }
    
    Int8FixedTypeVar::Int8FixedTypeVar()
    :   FixedTypeVar(std::move(std::string("Int8")), IntType::get_i8())
    {
        assume_invariant_holds_overwrite_fixed(new IsIntInvariant(nullptr, VarArchetype::Type, 8, 8, true));
    }
    Int16FixedTypeVar::Int16FixedTypeVar()
    :   FixedTypeVar(std::move(std::string("Int16")), IntType::get_i16())
    {
        assume_invariant_holds_overwrite_fixed(new IsIntInvariant(nullptr, VarArchetype::Type, 16, 16, true));
    }
    Int32FixedTypeVar::Int32FixedTypeVar()
    :   FixedTypeVar(std::move(std::string("Int32")), IntType::get_i32())
    {
        assume_invariant_holds_overwrite_fixed(new IsIntInvariant(nullptr, VarArchetype::Type, 32, 32, true));
    }
    Int64FixedTypeVar::Int64FixedTypeVar()
    :   FixedTypeVar(std::move(std::string("Int64")), IntType::get_i64())
    {
        assume_invariant_holds_overwrite_fixed(new IsIntInvariant(nullptr, VarArchetype::Type, 64, 64, true));
    }
    Int128FixedTypeVar::Int128FixedTypeVar()
    :   FixedTypeVar(std::move(std::string("Int128")), IntType::get_i128())
    {
        assume_invariant_holds_overwrite_fixed(new IsIntInvariant(nullptr, VarArchetype::Type, 128, 128, true));
    }

    UInt1FixedTypeVar::UInt1FixedTypeVar()
    :   FixedTypeVar(std::move(std::string("UInt1")), IntType::get_u8())
    {
        assume_invariant_holds_overwrite_fixed(new IsIntInvariant(nullptr, VarArchetype::Type, 1, 1, false));
    }
    UInt8FixedTypeVar::UInt8FixedTypeVar()
    :   FixedTypeVar(std::move(std::string("UInt8")), IntType::get_u8())
    {
        assume_invariant_holds_overwrite_fixed(new IsIntInvariant(nullptr, VarArchetype::Type, 8, 8, false));
    }
    UInt16FixedTypeVar::UInt16FixedTypeVar()
    :   FixedTypeVar(std::move(std::string("UInt16")), IntType::get_u16())
    {
        assume_invariant_holds_overwrite_fixed(new IsIntInvariant(nullptr, VarArchetype::Type, 16, 16, false));
    }
    UInt32FixedTypeVar::UInt32FixedTypeVar()
    :   FixedTypeVar(std::move(std::string("UInt32")), IntType::get_u32())
    {
        assume_invariant_holds_overwrite_fixed(new IsIntInvariant(nullptr, VarArchetype::Type, 32, 32, false));
    }
    UInt64FixedTypeVar::UInt64FixedTypeVar()
    :   FixedTypeVar(std::move(std::string("UInt64")), IntType::get_u64())
    {
        assume_invariant_holds_overwrite_fixed(new IsIntInvariant(nullptr, VarArchetype::Type, 64, 64, false));
    }
    UInt128FixedTypeVar::UInt128FixedTypeVar()
    :   FixedTypeVar(std::move(std::string("UInt128")), IntType::get_u128())
    {
        assume_invariant_holds_overwrite_fixed(new IsIntInvariant(nullptr, VarArchetype::Type, 128, 128, false));
    }

    Float16FixedTypeVar::Float16FixedTypeVar()
    :   FixedTypeVar(std::move(std::string("Float16")), FloatType::get_f16())
    {
        assume_invariant_holds_overwrite_fixed(new IsFloatInvariant(nullptr, VarArchetype::Type, 16, 16));
    }
    Float32FixedTypeVar::Float32FixedTypeVar()
    :   FixedTypeVar(std::move(std::string("Float32")), FloatType::get_f32())
    {
        assume_invariant_holds_overwrite_fixed(new IsFloatInvariant(nullptr, VarArchetype::Type, 32, 32));
    }
    Float64FixedTypeVar::Float64FixedTypeVar()
    :   FixedTypeVar(std::move(std::string("Float64")), FloatType::get_f32())
    {
        assume_invariant_holds_overwrite_fixed(new IsFloatInvariant(nullptr, VarArchetype::Type, 64, 64));
    }
    
    //
    // Constant classes:
    //
    // todo: implement constant Relations for these invariants to be applied from.

    SignedIntFixedClassVar::SignedIntFixedClassVar()
    :   FixedClassVar(std::move(std::string("FixedClass:SignedInt")))
    {
        auto invariant = new IsIntInvariant(nullptr, VarArchetype::Class, -1, -1, true);
        auto result = assume_invariant_holds_overwrite_fixed(invariant);
        assert(result == SolveResult::UpdatedOrFresh);
    }
    UnsignedIntFixedClassVar::UnsignedIntFixedClassVar()
    :   FixedClassVar(std::move(std::string("FixedClass:UnsignedInt")))
    {
        auto invariant = new IsIntInvariant(nullptr, VarArchetype::Class, -1, -1, false);
        auto result = assume_invariant_holds_overwrite_fixed(invariant);
        assert(result == SolveResult::UpdatedOrFresh);
    }
    FloatFixedClassVar::FloatFixedClassVar()
    :   FixedClassVar(std::move(std::string("FixedClass:Float")))
    {
        auto invariant = new IsFloatInvariant(nullptr, VarArchetype::Class, -1, -1);
        auto result = assume_invariant_holds_overwrite_fixed(invariant);
        assert(result == SolveResult::UpdatedOrFresh);
    }
}