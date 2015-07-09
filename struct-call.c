#include <stdio.h>
#include <stdlib.h>

struct obj {
	int (*fp)(const char *);
} *o;

int main(int argc, char **argv) {
	//o = malloc(sizeof(struct obj));

	o->fp = puts;

	o->fp(argv[0]);

	return 0;
}
