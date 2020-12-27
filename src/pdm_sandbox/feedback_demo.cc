#include "feedback_demo.hh"

#include <string>
#include <iostream>

#include "pdm/feedback/feedback.hh"
#include "pdm/feedback/manager.hh"
#include "pdm/feedback/note.hh"
#include "pdm/feedback/letter.hh"

using namespace pdm;

namespace pdm_cli::feedback_demo {

    void demo1() {
        /* Letter(
            Severity severity, 
            std::string&& headline, 
            std::string&& about, 
            std::vector<Note*>&& notes
            )
        */

        std::vector<feedback::Note*> notes;
        notes.reserve(1);
        notes.push_back(new feedback::Note(std::move("whoopsie here #1")));
        notes.push_back(new feedback::Note(std::move("whoopsie here #2")));
        
        feedback::Manager* manager = feedback::new_manager();
        manager->post(new feedback::Letter(
            feedback::Severity::Info,
            std::move(std::string("Info Message #1")),
            std::move(std::string("Blah dee blah blah")),
            {}
        ));

        feedback::post(new feedback::Letter(
            feedback::Severity::Error,
            std::move(std::string("Error Message #1")),
            std::move(std::string("Before X, expected Y (have you tried adding a, b, or c?)")),
            std::move(notes)
        ));
        feedback::print_all(std::cout);

        manager->set_invisible();
        std::cout 
            << std::endl
            << "Info manager has been set as invisible." 
            << std::endl;
        
        feedback::print_all(std::cout);
    }

}