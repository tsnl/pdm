Rather than use a separate `pd-task.json` file per-task,
consider consolidating tasks into a single file.

Thus, 2 different kinds of JSON files are recognized by the compiler:
1. `pandemonium-index.json`: aka package index files.
2. `pandemonium-tasks.json`: aka task files.

An example of `pandemonium-tasks.json` is enclosed at the end of this file, but note that the two systems are 
independent of each other.

Although task files cannot extend one another, 
each index file maps field names to `LoadOrder` expressions,
one of which can be to execute a task using a task file.

This would help integrate tasks into a package's compilation.
Although the below example does not use this facility, `server` may 
rely on a different `client` package. The `client` index file may then 
use a task to embed its WASM output as field in an `exports` module
(not compiler-defined, up to the API).

**IDEA:** an executable file or a WASM file is just a value... why not 
treat generating program output as a special case of generating fields from an
index file?
- The problem with this is that a generated executable's data segment must contain a copy of the executable, creating an
  infinite-size file.
- Instead, perhaps index files can also define tasks whose value output can be accessed in-language using 
  `package::tasks::task_name` such that these values are somehow erased at run-time.
- Alternatively, we can introduce 'HugeConstants' which are paged out (to a persistent file, to heap memory).
  - since indices and arrays help emulate indirection on a compact set
  - use paths and the FS to emulate indirection

`pandemonium-tasks.json`
```json
{
  "build-server": {
    "actions": [
      {
        "type": "build",
        "dir": "./build/server/",
        "name": "server",
        "input": {
          "path": "./index.pd-pkg",
          "module": "server_main::app1"
        }
      }
    ],
    "after": [
      "build-client"
    ]
  },
  "build-client": {
    "type": "WEB_BROWSER_APP",
    "actions": [
      {
        "type": "build",
        "path": "./build/client/",
        "name": "client",
        "input": {
          "path": "./index.pd-pkg",
          "module": "client_main::app1"
        }
      }
    ]
  }
}
```