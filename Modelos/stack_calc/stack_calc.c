#include "stack_calc.h"

struct sc_t {
	stack_calc sc;
};

struct stack_calc {
	int value;
	stack_calc next;
};

sc_t sc_empty(void) {
	c = NULL;
	return c;
}

sc_t sc_push(sc_t sc, int k) {
	struct sc_t q = calloc(1, sizeof(struct sc_t));
	q->value = k;
	q->next = c;
	c = q;
}

int sc_top(sc_t sc) {
	int k = c->value;
	return k;
}

sc_t sc_pop(sc_t sc) {
	sc_t q = c->next;
	free(c);
	return q;
}

bool sc_is_empty(sc_t sc) {
	return (c == NULL);
}

unsigned int sc_size(sc_t sc) {
	unsigned int lenght = 0;
	while (p != NULL) {
		lenght++;
		p = p->next;
	}
	return lenght;
}

1sc_t sc_minus(sc_t sc) {

}

sc_t sc_sum(sc_t sc, unsigned int n);

oid sc_dump(sc_t sc, FILE *fd);

sc_t sc_destroy(sc_t sc);