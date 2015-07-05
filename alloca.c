#include <alloca.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char **argv) {
	char *buf;
	buf = alloca(strtoul(argv[1], NULL, 0));
	printf("%p\n", buf);

	return 0;
}
