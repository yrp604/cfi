#include <sys/mman.h>

#include <stdio.h>
#include <stdlib.h>
#include <string.h>


class obj {
public:
	virtual void fp() { printf("[-] ?\n"); }
};

class thing : public obj {
public:
	virtual void fp() { printf("[-] :(\n"); }
};

class gadget : public thing  {
public:
	void fp() { printf("[-] !\n"); }
};

void doit_o(obj *o) {
	char buf[20];
	printf("%p\n", buf);
	o->fp();
}

void doit_t(thing *t) {
	puts("doit_t");
	t->fp();
}

void doit_g(gadget *g) {
	puts("doit_g");
	g->fp();
}

int main(int argc, char **argv) {
	char buf[20];
	void *code;
	unsigned int i = 0;
	unsigned long x, y, *write;
	thing *t;
	obj *o;
	gadget *g;

	code = mmap(NULL, 0x1000, PROT_EXEC | PROT_READ | PROT_WRITE, MAP_PRIVATE | MAP_ANONYMOUS, -1, 0);

	if (getenv("SHELLCODE"))
		strncpy((char *)code, getenv("SHELLCODE"), 0x1000);

	o = new obj;
	t = new thing;
	g = new gadget;

	printf("[+] main @ 0x%llx\n", main);
	printf("[+] printf @ 0x%llx\n", printf);
	printf("[+] buf @ 0x%llx\n", buf);
	printf("[+] code @ 0x%llx\n", code);
	printf("[+] t @ 0x%llx\n", t);

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
	printf("[+] Calling o->fp()...\n");
	doit_o(o);

	printf("[+] Calling t->fp()...\n");
	doit_o(t);
	doit_t(t);

	printf("[+] Calling g->fp()...\n");
	doit_o(g);
	doit_t(g);
	doit_g(g);
}
