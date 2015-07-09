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
	void fp() { printf("[-] :(\n"); }
};

void __attribute__ ((noinline)) doit(obj *o) {
	o->fp();
}

int main(int argc, char **argv) {
	obj *o;
	thing *t;

	t = new thing;
	o = new obj;

	printf("[+] Calling o/t->fp()...\n");
	doit(o);
	doit(t);

	return 0;
}
