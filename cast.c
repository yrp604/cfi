#include <stdio.h>

int main() {
	char buf[20];
	unsigned long x;
	x = (unsigned long)buf;
	printf("%p\n", x);
	return 0;
}
