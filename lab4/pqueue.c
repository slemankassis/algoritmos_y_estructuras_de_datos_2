#include <stdbool.h>
#include <stdlib.h>
#include <assert.h>
#include "edge.h"
#include "pqueue.h"

struct _pqueue_t {
    elem_t *elems;
    unsigned int size;
    unsigned int max_size;
};

pqueue_t pqueue_empty(unsigned int max_size) {

    pqueue_t pq = NULL;

    pq = calloc(1, sizeof(struct _pqueue_t));

    pq->elems = calloc(max_size + 1, sizeof(elem_t));
    pq->size = 0;
    pq->max_size = max_size;

    return pq;

}

bool pqueue_is_full(pqueue_t pq) {

    return (pq->size == pq->max_size);

}

bool pqueue_is_empty(pqueue_t pq) {

    return (pq->size == 0);

}

elem_t pqueue_fst(pqueue_t pq) {

    assert(!pqueue_is_empty(pq));

    elem_t elem = NULL;

    if (pq->size != 0) {

        elem = pq->elems[1];

    }

    return elem;

}

unsigned int pqueue_size(pqueue_t pq) {

    return pq->size;

}

unsigned int left(int i) {

    return (2 * i);

}

unsigned int right(int i) {

    return (2 * i + 1);

}

unsigned int parent(int i) {

    return (i / 2);

}

bool has_children(pqueue_t pq, unsigned int i) {

    return (left(i) <= pq->size);

}

bool has_parent(int i) {

    return (i != 1);

}

int min_child(pqueue_t pq, int i) {

    int j = 0;

    if (right(i) <= pq->size &&
        edge_lte(pq->elems[right(i)], pq->elems[left(i)])) {

        j = right(i);

    } else {

        j = left(i);

    }

    return j;

}

void swap(pqueue_t pq, int i, int j) {

    elem_t x = pq->elems[j];
    pq->elems[j] = pq->elems[i];
    pq->elems[i] = x;

    x = NULL;
}

void lift(pqueue_t pq, int i) {

    swap(pq, i, parent(i));

}

bool must_lift(pqueue_t pq, int i) {

    return (elem_lt(pq->elems[i], pq->elems[parent(i)]));

}

void floatt(pqueue_t pq) {

    unsigned int c = pq->size;

    while (has_parent(c) && must_lift(pq, c)) {

        lift(pq, c);
        c = parent(c);

    }

}

void sink(pqueue_t pq) {

    unsigned int p = 1;

    while (has_children(pq, p) && must_lift(pq, min_child(pq, p))) {

        p = min_child(pq, p);
        lift(pq, p);

    }

}

void pqueue_enqueue(pqueue_t pq, elem_t elem) {

    assert(!pqueue_is_full(pq));

    unsigned int size = pq->size + 1;

    pq->size = size;
    pq->elems[size] = elem;

    floatt(pq);

}

void pqueue_dequeue(pqueue_t pq) {

    assert(!pqueue_is_empty(pq));

    unsigned int size = pq->size - 1;

    pq->size = size;
    pq->elems[1] = edge_destroy(pq->elems[1]);
    pq->elems[1] = pq->elems[size + 1];

    sink(pq);

}

pqueue_t pqueue_destroy(pqueue_t pq) {

    for (unsigned int i = 1; i <= pq->size; i++) {

        pq->elems[i] = elem_destroy(pq->elems[i]);

    }

    free(pq->elems);
    free(pq);

    return NULL;

}