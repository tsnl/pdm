TODO: explain how the VFS mounts certain directories to gain access to the real FS
- All file-resources must either be...
  - specified at compile-time, or
  - loaded **through the VFS at run-time**
- The VFS provides uniform sandboxing and caching, providing the same interface across native and browser scripts.