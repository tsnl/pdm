# Scripts

*Like Python, each source file is designed to be wholly local.*

A `script` refers to a single source file. It is the modular unit of source code. 

Scripts may use file resources that are **static** or **dynamic**
- static resources: unchanging files always used by a script at a fixed location
  - will be copied/managed by the compiler
  - may be optimized by the compiler, bundled with other static resources
  - imported files are a kind of static resource
- dynamic resources: files used by a script that may change during run-time or may not be used.
  - requires use of the VFS to mount, load, open, and check file access

# Example

*The 'dev.app.hub' program below prints `(...)\n\n` to stdout.*

```
$ tree .
demo_package
├── demo-sept-2019.app.hub
├── demo-oct-2020.app.hub
├── dev.app.hub
├── release.app.hub
├── engine.lib.hub
├── src
│   ├── math.hub
│   ├── render.hub
│   └── oogl.hub
└── doc/

$ hub r .
No target specified, please select one of...
[1] demo-sept-2019.app.hub
[2] demo-oct-2020.app.hub
[3] dev.app.hub
[4] release.app.hub
[5] engine.lib.hub
> 3
Building target "dev.app.hub"... Done. (0e/0w/0i)
Running target "dev.app.hub"...
(...)

$ hub r dev.app.hub
Building target "dev.app.hub"... Done. (0e/0w/0i)
Running target "dev.app.hub"...
(...)

$ hub b .
Building target "dev.app.hub"... Done. (0e/0w/0i)
Building target "demo-sept-2019.app.hub"... Done. (0e/0w/0i)
Building target "demo-oct-2020.app.hub"... Done. (0e/0w/0i)
Building target "release.app.hub"... Done. (0e/0w/0i)
Building target "engine.lib.hub"... Done. (0e/0w/0i)
Built [5/5] targets with (0e/0w/0i) total.

$ hub d .
Building target "dev.app.hub"... Done. (0e/0w/0i)
Building target "demo-sept-2019.app.hub"... Done. (0e/0w/0i)
Building target "demo-oct-2020.app.hub"... Done. (0e/0w/0i)
Building target "release.app.hub"... Done. (0e/0w/0i)
Building target "engine.lib.hub"... Done. (0e/0w/0i)
Built [5/5] targets with (0e/0w/0i) total.
```