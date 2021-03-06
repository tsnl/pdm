# JSON Schema - Executables

The schema links modules together for target platforms.

But what about entry points? How do we turn a tangled mass of emitted code into an executable application?

The key is that there is no difference between a library and application: in either case, some other application calls
a specific function.

**IDEA:** define type-classes on modules for different applications.

**IDEA:** specify modules as entry points from `pandemonium-targets.json`
- simplest interface: 'main' for 'CONSOLE_APP_WITHOUT_ARGS'
- interface with args: 'main' for 'CONSOLE_APP'
- can add another interface for web applications in due time
- can add more complex interfaces for cross-platform GUI applications
- ALSO specify output path for each target relative to this file.

**IDEA:** specify 'task' objects using JSON
- no running involved, just file transformations
- can create executable LLVM IR (using `lli`) or WASM (further output up to user)
- can specify `after` property to order execution of tasks.
- each `task` is just a `.pd-task.json` file.

NOTE: everything always bundled into a single file, enormous as it may be.
- This lets us make the most of compiler optimization on known assets
- This allows next-level verification since input files are fed to the compiler
    - compiler error <=> assert guaranteed to fail
    - more input => more assertions guaranteed to fail => better compiler checks

E.g.:

`server.pd-task.json`

```json
{
  "kind": "build-app-executable",
  "app-kind": "CONSOLE_APP_WITH_ARGS",
  "output": {
    "path": "./server.ll",
    "type": "llvm-ir"
  },
  "input": {
    "node": "./index.pd-pkg-node",
    "module": "server_main::app1"
  },
  "after": [
    "./client.pd-task.json"
  ]
}
```

`client.pd-task.json`

```json
{
  "kind": "build-app-executable",
  "app-kind": "CHROMIUM_APP",
  "output": {
    "path": "./client.wasm",
    "type": "wasm"
  },
  "input": {
    "node": "./index.pd-pkg-node",
    "module": "client_main::app1"
  }
}
```