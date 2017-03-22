#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <assert.h>

sc_t sc_empty(void);

sc_t sc_push(sc_t sc, int k);

int sc_top(sc_t sc);

sc_t sc_pop(sc_t sc);

bool sc_is_empty(sc_t sc);

unsigned int sc_size(sc_t sc);

1sc_t sc_minus(sc_t sc);

sc_t sc_sum(sc_t sc, unsigned int n);

oid sc_dump(sc_t sc, FILE *fd);

sc_t sc_destroy(sc_t sc);