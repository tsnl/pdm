Expanding on these packages as 1-1 scripts, each field of this JSON document maps to a `LoadOrder`.

Every LoadOrder exp **must** have a `kind` field specifying what to expect in the rest of the fields.

Every LoadOrder exp **may** have an `about` field with human-readable information.

Every LoadOrder exp **may** have an `also` field with any data, so other tools and extensions may stuff data here.

Initially, a small set of LoadOrders can be provided, including the ability to execute a file at compile-time. 
Over time, custom LoadOrders can be provided, likely using `"custom/?"`.

The `kind` field can be used to customize loaded data. 
- `wrapped-c-unit`: a C source unit 
- `pd-node`: a single PD source file
- `pd-pkg-node`: a PD package node (i.e. a directory containing a `pd-pkg-index.json` file)

`pd-pkg-index.json`

```json
{
  "sdl2": {
    "kind": "wrapped-c-unit",
    "about": {
      "version": "0.0.0",
      "author": "Nikhil Tony Idiculla",
      "wrapped-info": {
        "name": "SDL2",
        "version": "2.1.0",
        "language": "C-99",
        "author": "Sam Latinga"
      }
    },
    "link-args": {
      "include_dirs": [
        "./dep/include/"
      ],
      "defines": {
        "SDL_BUILD_STATIC": "(1)"
      }
    },
    "platform-dependent-link-args": {
      "win32-x64": {
        "static-libs": [
          "./dep/win32/lib/SDL2/SDL2main.lib",
          "./dep/win32/lib/SDL2/SDL2.lib"
        ]
      },
      "linux-x64": {
        "static-libs": [
          "./dep/linux-x86/lib/SDL2/SDL2main.a",
          "./dep/linux-x86/lib/SDL2/SDL2.a"
        ]
      },
      "macos-x64": {
        "static-libs": [
          "./dep/macos-x86/lib/SDL2/SDL2main.a",
          "./dep/macos-x86/lib/SDL2/SDL2.a"
        ]
      },
      "chromium": {}
    }
  },
  "sdl2_helpers": {
    "kind": "pd-node",
    "path": "./sdl2-helpers.pd-node"
  },
  "sdl2_extra": {
    "kind": "pd-pkg-node",
    "path": "./sdl2-extra.pd-pkg-node"
  }
}
```