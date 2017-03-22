#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include "bst.h"
#include "dict.h"
#include "data.h"
#include "index.h"
#include "list.h"

struct _dict_t {
    unsigned int length;
    bst_t bst;
};

dict_t dict_empty(void) {

    dict_t dict = NULL;
    dict = calloc(1, sizeof(struct _dict_t));

    dict->bst = bst_empty();
    dict->length = 0;

    assert(dict != NULL && dict_length(dict) == 0);
    return dict;

}

dict_t dict_destroy(dict_t dict) {

    dict->bst = bst_destroy(dict->bst);
    dict->length = 0;

    free(dict);
    dict = NULL;

    return dict;

}

unsigned int dict_length(dict_t dict) {

    assert(dict != NULL);
    return (bst_length(dict->bst));

}

bool dict_is_equal(dict_t dict, dict_t other) {

    assert(dict != NULL && other != NULL);
    return (bst_is_equal(dict->bst, other->bst) &&
            dict_length(dict) == dict_length(other));

}

bool dict_exists(dict_t dict, word_t word) {

    assert(dict != NULL && word != NULL);

    bool exists = true;
    index_t index = index_from_string(word);

    if (bst_search(dict->bst, index) == NULL) {
        exists = false;
    }

    index = index_destroy(index);
    return exists;

}

def_t dict_search(dict_t dict, word_t word) {

    assert(dict != NULL && word != NULL && dict_exists(dict, word));

    index_t index = NULL;
    data_t data = NULL;
    def_t def = NULL;

    index = index_from_string(word);
    data = bst_search(dict->bst, index);
    def = data_to_string(data);

    index = index_destroy(index);
    assert(def != NULL);
    return def;

}

dict_t dict_add(dict_t dict, word_t word, def_t def) {

    assert(dict != NULL && word != NULL && def != NULL &&
           !dict_exists(dict, word));
    index_t index = NULL;
    data_t data = NULL;

    index = index_from_string(word);
    data = data_from_string(def);

    dict->bst = bst_add(dict->bst, index, data);
    dict->length = dict_length(dict) + 1;

    assert(dict_length(dict) == bst_length(dict->bst));
    return dict;

}

dict_t dict_remove(dict_t dict, word_t word) {

    assert(dict != NULL && word != NULL && dict_exists(dict, word));
    index_t index = NULL;

    index = index_from_string(word);
    dict->bst = bst_remove(dict->bst, index);
    dict->length = dict_length(dict) - 1;

    index = index_destroy(index);

    assert(dict_length(dict) == bst_length(dict->bst));
    return dict;

}

dict_t dict_copy(dict_t dict) {
    dict_t other = NULL;

    if (dict != NULL) {
        other = calloc(1, sizeof(struct _dict_t));
        other->bst = bst_copy(dict->bst);
        other->length = dict_length(dict);

        assert(dict_is_equal(other, dict));
    }

    return other;

}

void dict_dump(dict_t dict, FILE * fd) {

    assert(dict != NULL);
    list_t list = NULL;

    list = bst_to_list(dict->bst, list);

    assert(list_length(list) == bst_length(dict->bst));
    list_dump(list, fd);

    list = list_destroy(list);
    dict = NULL;

}