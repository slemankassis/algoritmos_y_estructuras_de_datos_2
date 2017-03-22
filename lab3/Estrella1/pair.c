
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

#include "pair.h"
#include "data.h"
#include "index.h"

struct _pair_t {

    index_t first;
    data_t second;

};

pair_t pair_from_index_data(index_t index, data_t data) {

    assert(index != NULL && data != NULL);
    pair_t pair = NULL;

    pair = calloc(1, sizeof(struct _pair_t));
    pair->first = index;
    pair->second = data;

    assert(pair != NULL && pair_fst(pair) == index && pair_snd(pair) == data);
    return pair;

}

pair_t pair_destroy(pair_t pair) {

    pair->first = index_destroy(pair_fst(pair));
    pair->second = data_destroy(pair_snd(pair));
    free(pair);
    pair = NULL;

    return pair;

}

index_t pair_fst(pair_t pair) {

    assert(pair != NULL);

    index_t fst = NULL;
    fst = pair->first;

    assert(fst != NULL);
    return fst;

}

data_t pair_snd(pair_t pair) {

    assert(pair != NULL);

    data_t snd = NULL;
    snd = pair->second;

    assert(snd != NULL);
    return snd;

}

bool pair_is_equal(pair_t pair, pair_t other) {

    assert(pair != NULL && other != NULL);
    return (index_is_equal(pair_fst(pair), pair_fst(other)) &&
            data_is_equal(pair_snd(pair), pair_snd(other)));

}

pair_t pair_copy(pair_t pair) {

    assert(pair != NULL);

    pair_t other = NULL;
    other = pair_from_index_data(index_copy(pair_fst(pair)),
                                 data_copy(pair_snd(pair)));

    assert(other != NULL && pair_is_equal(pair, other));
    return other;

}