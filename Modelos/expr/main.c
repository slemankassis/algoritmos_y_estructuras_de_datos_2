#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <assert.h>
#include "expr.h"

int main(void) {
	expr p = var(0);
	expr q = var(1);
	expr w = suma(p, q);
	expr e = suma(w, q);
	destroy(e);
	return 0;
}