#include <sys/mman.h>

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char **argv) {
	char buf[20];
	void *code;
	unsigned int i = 0;
	unsigned long x, y, *write;

	code = mmap(NULL, 0x1000, PROT_EXEC | PROT_READ | PROT_WRITE, MAP_PRIVATE | MAP_ANONYMOUS, -1, 0);

	if (getenv("SHELLCODE"))
		strncpy((char *)code, getenv("SHELLCODE"), 0x1000);

	printf("[+] main @ %llx\n", main);
	printf("[+] printf @ %llx\n", printf);
	printf("[+] buf @ %llx\n", buf);
	printf("[+] code @ %llx\n", code);

	write = (unsigned long *)buf;

	for (;;) {
		printf("[*] Write #%u\n", i++);
		printf("[*] x:\n");
		fgets(buf, sizeof(buf), stdin);
		x = strtoul(buf, NULL, 0);

		printf("[*] y:\n");
		fgets(buf, sizeof(buf), stdin);
		y = strtoul(buf, NULL, 0);

		if (x == 0xdeadbeef && y == 0xdeadbeef)
			break;

		write[x] = y;
	}

	printf("[+] Returning from main...\n");
}
