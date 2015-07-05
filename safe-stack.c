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

	printf("[+] main @ 0x%llx\n", main);
	printf("[+] printf @ 0x%llx\n", printf);
	printf("[+] buf @ 0x%llx\n", buf);
	printf("[+] code @ 0x%llx\n", code);

	write = (unsigned long *)buf;

	for (;;) {
		printf("[*] Read/Write #%u\n", i++);
		printf("[*] write8 index:\n");
		fgets(buf, sizeof(buf), stdin);
		x = strtoul(buf, NULL, 0);

		printf("[*] write8 value:\n");
		fgets(buf, sizeof(buf), stdin);
		y = strtoul(buf, NULL, 0);

		if (x == 0xdeadbeef && y == 0xdeadbeef)
			break;

		printf("[+] write8 *0x%llx = 0x%llx\n", &write[x], y);
		write[x] = y;

		printf("[*] read8 index:\n");
		fgets(buf, sizeof(buf), stdin);
		x = strtoul(buf, NULL, 0);
		printf("[+] read8 0x%llx: 0x%llx\n", &write[x], write[x]);

		printf("[*] print str:\n");
		fgets(buf, sizeof(buf), stdin);
		printf(buf);
	}

	printf("[+] Returning from main...\n");
}
