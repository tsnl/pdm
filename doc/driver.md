# Implementing a test framework

- Finalize packages spec (done, see [packages.md](./packages.md))
- Load a package with no imports from the FS using the [`cxong/tinydir`](https://github.com/cxong/tinydir) dependency.
- Generate...
  - C output source code
  - Promela output source code (?)
- Run GCC and SPIN, integrating output as required.

- Finalize compiler installation spec, with the following requirements:
  - **site-packages**: contains cached versions of downloaded packages
- Load a package with imports from the FS
  - Hit the `site-packages` cache to check if a package has already been downloaded
    - if the package is not in the `site-packages`, download it
    - Consider using the BitTorrent protocol
  - Compile and attach the package before typing
    - Ensure C code can be linked (via extern or similar functionality) with specified compiler flags
    - Ensure file-paths are appropriately translated to refer to the right subdirectories of packages