Given these changes, modules in-language can be made much better using `extends` statements.
- `extends` statements can check that an app satisfies a class. 
- `mod <struct-type-spec>` can approximate full mod expressions.
    - in the future, type and class fields can be added for subtype checks

```
import {
    io from "https://github.com/tsnl/std-io.pdm-pkg-node";
    vec from "https://github.com/tsnl/std-vec.pdm-pkg-node";
}

mod apps {
    CONSOLE_APP_WITHOUT_ARGS :: cls (Mod MODULE) {
        Mod :< mod {
            main () -> Int16
        };
    };
    CONSOLE_APP :: cls (Mod MODULE) {
        Mod :< mod {
            main (args vec[String]::Vec) -> Int16
        };
    };
};

mod server {
    mod app1 {
        extends apps::CONSOLE_APP_WITHOUT_ARGS;
    
        main :: () -> Int16 {
            io::print("Hello, world!");
            0
        };
    };
};
```
