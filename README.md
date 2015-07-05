# CFI and Safe Stack

Some binaries to play around with the new LLVM exploit mitigations. I figure not everyone wants to complile llvm from svn. Binaries are just a basic 64-bit write-what-where loop with standard exploit mitigations enabled (relro, pie, cookies, nx).

If there's anything you want me to add/remove, let me know and I'll try to hook it up.
 
The tarball contains everything.

Some notes:
* -fsanitize=safe-stack seems to remove -fstack-protector
* -fsanitize=cfi requires a LLVMgold.so which seems to require a current binutils
* -fsanitize=safe-stack adds quite a bit of code to the resulting binaries
