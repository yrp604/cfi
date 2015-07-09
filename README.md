# CFI and Safe Stack

Some binaries to play around with the new LLVM exploit mitigations. Binaries are just a basic 64-bit write8/read8/printf loop with standard exploit mitigations enabled (relro, pie, cookies, nx).

* cast: simple example of trying to cast a stack pointer onto the fake stack
* ud2: example of `-flto` turning use of un-initialized memory to a `ud2` instruction
* alloca: non-exploitable binary with `-fsanitize=safe-stack` to show behavior of `alloca(3)`
* safe-stack: `-fsanitize=safe-stack`
* safe-stack-plain: Same binary, without `-fsanitize=safe-stack`
* struct-call: `-fsanitize=cfi` applied to a C function pointer
* control-flow-simple: Basic `-fsanitize=cfi` binary to look at guards
* control-flow: `-fsanitize=cfi`
* control-flow-safe-stack: `-fsanitize=cfi,safe-stack`
* control-flow-plain: Same binary, without either.

I'd suggest reading the Makefile.

If there's anything you want me to add/remove, let me know (@yrp604 or email) and I'll try to hook it up.
 
Some notes:
* `-fsanitize=safe-stack` adds quite a bit of code to the resulting binaries
* `-fsanitize=cfi` requires a `LLVMgold.so` which seems to require a current binutils
* More detailed `safe-stack` notes [here](https://gist.github.com/yrp604/70bd281dd04a982b0397).
* More detailed `cfi` notes [here](https://gist.github.com/yrp604/2e1b13f76c18186ea203)
