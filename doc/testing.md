# Implementing a test framework

- Finalize packages spec, possibly with the following directory structure:
  - **doc**: contains human-readable text documentation that is excluded from the release package.
  - **res**: contains all file resources accessible to code
    - The compiler should tree-shake/validate the 'res' directory for each release target
    - Can include source code in other languages too
    - Can include binaries to link
  - **src**: contains all source code to be compiled to an executable
  - **out**: the output directory for the compiler.

    Compiled executables go here, but so do assets, binaries, and compiler-generated JSON files like...
    - <build>-version.json: a JSON file containing version information about the specified build.
    - <build>-interface.json: a JSON file containing cross-platform interface information about the generated targets, specifying which targets are supported in each case.
    - (...)
  - **tmp**: an intermediate directory for the compiler
- Finalize compiler installation spec, with the following requirements:
  - **site-packages**: contains cached versions of downloaded packages
- Load a package with no imports from the FS using the [`cxong/tinydir`](https://github.com/cxong/tinydir) dependency.
- Generate...
  - C output source code
  - Promela output source code (?)
- Load a package with imports from the FS
  - Hit the `site-packages` cache to check if a package has already been downloaded
    - if the package is not in the `site-packages`, download it
    - Consider using the BitTorrent protocol
  - Compile and attach the package before typing
    - Ensure C code can be linked (via extern or similar functionality) with specified compiler flags
    - Ensure file-paths are appropriately translated to refer to the right subdirectories of packages