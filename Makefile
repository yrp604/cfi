CFLAGS=-Wno-format -fPIE -pie -fstack-protector -Wl,-z,now -Wl,-z,relro

# Obviously this requires clang3.7
all:
	clang $(CFLAGS) safe-stack.c -o safe-stack-plain
	clang $(CFLAGS) -fsanitize=safe-stack safe-stack.c -o safe-stack
	clang++ $(CFLAGS) -flto cfi.cpp -o control-flow-plain
	clang++ $(CFLAGS) -flto -fsanitize=cfi cfi.cpp -o control-flow
	clang++ $(CFLAGS) -flto -fsanitize=cfi,safe-stack cfi.cpp -o control-flow-safe-stack

tarball: all
	tar -vzcf ../cfi.tgz ../cfi
	mv ../cfi.tgz .

clean:
	rm -f cfi.tgz
	rm -f safe-stack-plain
	rm -f safe-stack
	rm -f control-flow-plain
	rm -f control-flow
	rm -f control-flow-safe-stack
