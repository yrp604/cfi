# CFI and Safe Stack

Some binaries to play around with the new LLVM exploit mitigations. Binaries are just a basic 64-bit write8/read8/printf loop with standard exploit mitigations enabled (relro, pie, cookies, nx).

* alloca: non-exploitable binary with `-fsanitize=safe-stack` to show behavior of `alloca(3)`
* safe-stack: `-fsanitize=safe-stack`
* safe-stack-plain: Same binary, without `-fsanitize=safe-stack`
* control-flow: `-fsanitize=cfi`
* control-flow-safe-stack: `-fsanitize=cfi,safe-stack`
* control-flow-plain: Same binary, without either.

I'd suggest reading the Makefile.

If there's anything you want me to add/remove, let me know (@yrp604 or email) and I'll try to hook it up.
 
The tarball contains everything.

Some notes:
* `-fsanitize=safe-stack` seems to remove `-fstack-protector`
* `-fsanitize=cfi` requires a `LLVMgold.so` which seems to require a current binutils
* `-fsanitize=safe-stack` adds quite a bit of code to the resulting binaries
