# Typer

This module visits each Script, creates `types::Rule` instances, and adds them to a type system as 
**assumptions.** These assumptions are specified by the typing rules of the language.

Note, then, that the typer implementation and type rules are totally separate.

The typer visitor...
- creates TVs on the 'pre' visit pass
- assume types::Relation on post visit pass