# Packages

A `package` is a directory that contains one or more hub files. **Each file exposes one app or library target for package consumers.**
To augment these targets, a package may also contain the following optional directories.
- **doc**: contains human-readable text documentation that is excluded release distributions.
- **res**: contains all file resources accessible to code
  - Auto-mounted to the VFS
  - The compiler should tree-shake/validate the 'res' directory for each release target
  - Can include source code in other languages too
  - Can include binaries to link
- **src**: contains any additional source code for all targets.
  - Explicit imports still required from drivers.
  - Single shared namespace, like Go packages.
- **hub-output**: the output directory for the compiler.
  - **bin**: contains all executables.
  - **web**: contains all web output (HTML/JS/CSS).
  - **log**: <build>-log-<timestamp>.json: a JSON file containing all information about a specified build, including errors and ASTs. (?)
    - Extremely verbose, but data-rich.
    - Catch code breakage across time => really good compiler error messages relying on correlation.
- **tmp**: an intermediate directory for the compiler

NOTE
- If the package contains any other files in the root directory, they will be ignored unless explicitly mounted to the VFS.
- If the `hub` tool is run on a single file, the file's parent automatically becomes the package used.
  - This results in the creation of an `hub-output` directory

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
See `./out/bin` for (4) output executables.
See `./out/web` for (1) output web [HTML/JS/CSS] applications.

$ hub d .
Building target "dev.app.hub"... Done. (0e/0w/0i)
Building target "demo-sept-2019.app.hub"... Done. (0e/0w/0i)
Building target "demo-oct-2020.app.hub"... Done. (0e/0w/0i)
Building target "release.app.hub"... Done. (0e/0w/0i)
Building target "engine.lib.hub"... Done. (0e/0w/0i)
Built [5/5] targets with (0e/0w/0i) total.
See `./out/dist/bin` for (4) output executables.
See `./out/dist/web` for (1) output web [HTML/JS/CSS] applications.
```