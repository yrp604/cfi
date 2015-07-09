#include <stdlib.h>

struct obj {
	void (*f)(int);
} *o;

int main() {
	o->f = exit;
	o->f(1);

	return 0;
}
