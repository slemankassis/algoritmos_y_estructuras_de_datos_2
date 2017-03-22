#include <assert.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include "union_find.h"

struct _union_find_t {
    int *array;
    uint lenght;
};

union_find_t union_find_create(uint max_size) {

    union_find_t uf = NULL;
    uf = calloc(1, sizeof(struct _union_find_t));

    assert(uf != NULL);

    uf->array = calloc(max_size, sizeof(unsigned int));
    uf->lenght = max_size;

    for (uint i = 0; i < max_size; i++) {

        uf->array[i] = -1;

    }

    return uf;

}

bool is_rep(union_find_t uf, uint elem) {

    return (uf->array[elem] < 0);

}

uint union_find_find(union_find_t uf, uint elem) {

    uint k = 0;
    uint r = 0;
    uint j = elem;

    while (!is_rep(uf, j)) {
        j = uf->array[j];
    }

    r = j;
    j = elem;

    while (!is_rep(uf, j)) {
        k = uf->array[j];
        uf->array[j] = r;
        j = k;
    }

    return r;

}

void union_find_union(union_find_t uf, uint elem1, uint elem2) {

    assert(is_rep(uf, elem1) && is_rep(uf, elem2));

    if (elem1 != elem2) {

        if (uf->array[elem2] >= uf->array[elem1]) {

            uf->array[elem1] = uf->array[elem1] + uf->array[elem2];
            uf->array[elem2] = elem1;

        } else {

            uf->array[elem2] = uf->array[elem1] + uf->array[elem2];
            uf->array[elem1] = elem2;
        }
    }
}

bool union_find_connected(union_find_t uf, uint elem1, uint elem2) {

    return (union_find_find(uf, elem1) == union_find_find(uf, elem2));

}

uint union_find_count(union_find_t uf) {

    uint count = 0;

    for (unsigned int i = 0; i < uf->lenght; i++) {

        if (uf->array[i] < 0) {

            count++;

        }

    }

    return count;

}

union_find_t union_find_destroy(union_find_t uf) {

    free(uf->array);
    uf->array = NULL;

    free(uf);
    uf = NULL;

    return uf;

}