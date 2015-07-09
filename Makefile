CFLAGS=-Wno-unused-result -Wno-format -fPIE -pie -fstack-protector -Wl,-z,now -Wl,-z,relro -D_FORTIFY_SOURCE=2 -O2

# Obviously this requires clang3.7
all: cast alloca safe-stack-plain safe-stack struct-call control-flow-plain control-flow \
	control-flow-simple control-flow-safe-stack ud2

ud2: ud2.c
	clang $(CFLAGS) -flto ud2.c -o ud2
cast: cast.c
	clang $(CFLAGS) -fsanitize=safe-stack cast.c -o cast
alloca: alloca.c
	clang $(CFLAGS) -fsanitize=safe-stack alloca.c -o alloca
safe-stack-plain: safe-stack.c
	clang $(CFLAGS) safe-stack.c -o safe-stack-plain
safe-stack: safe-stack.c
	clang $(CFLAGS) -fsanitize=safe-stack safe-stack.c -o safe-stack
struct-call: struct-call.c
	clang $(CFLAGS) -flto -fsanitize=cfi struct-call.c -o struct-call
control-flow-simple: cfi-simple.cpp
	clang++ $(CFLAGS) -flto -fsanitize=cfi cfi-simple.cpp -o control-flow-simple
control-flow-plain: cfi.cpp
	clang++ $(CFLAGS) -flto cfi.cpp -o control-flow-plain
control-flow: cfi.cpp
	clang++ $(CFLAGS) -flto -fsanitize=cfi cfi.cpp -o control-flow
control-flow-safe-stack: cfi.cpp
	clang++ $(CFLAGS) -flto -fsanitize=cfi,safe-stack cfi.cpp -o control-flow-safe-stack

tarball: all
	tar --exclude '.git' --exclude 'solutions' -vzcf ../cfi.tgz ../cfi
	mv ../cfi.tgz .

clean:
	rm -f cfi.tgz
	# These are toy binary to look at the disassembly
	rm -f alloca
	rm -f cast
	rm -f control-flow-simple
	rm -f struct-call
	rm -f ud2
	# These are exploity ones
	rm -f safe-stack-plain
	rm -f safe-stack
	rm -f control-flow-plain
	rm -f control-flow
	rm -f control-flow-safe-stack
