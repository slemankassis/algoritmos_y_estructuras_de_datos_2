#include <stdio.h>
#include <stdbool.h>
#include <assert.h>
#include <stdlib.h>
#include "list.h"
#include "pair.h"
#include "bst.h"

struct _tree_node_t {

    pair_t elem;
    bst_t left;
    bst_t right;

};

bst_t bst_empty(void) {

    bst_t bst = NULL;
    return bst;

}

bst_t bst_destroy(bst_t bst) {

    if (bst != bst_empty()) {
        bst->left = bst_destroy(bst->left);
        bst->right = bst_destroy(bst->right);
        bst->elem = pair_destroy(bst->elem);

        bst->left = NULL;
        bst->right = NULL;
        free(bst);
        bst = NULL;
    }

    return bst;

}

unsigned int bst_length(bst_t bst) {

    unsigned int length = 0;
    if (bst != NULL) {
        length = bst_length(bst->left) + bst_length(bst->right) + 1;
    }

    return length;

}

bool bst_is_equal(bst_t bst, bst_t other) {

    bool result = true;

    if (bst != NULL && other != NULL) {
        if (pair_is_equal(bst->elem, other->elem)) {
            result = bst_is_equal(bst->right, other->right) &&
                bst_is_equal(bst->left, other->left)
        } else {
            result = false;
        }
    } else if ((bst != NULL && other == NULL) || (bst == NULL &&
                                                  other != NULL)) {
        result = false;
    }

    return result;

}

data_t bst_search(bst_t bst, index_t index) {

    data_t data = NULL;

    if (bst != NULL) {
        if (index_is_equal(pair_fst(bst->elem), index)) {
            data = pair_snd(bst->elem);

        } else if (index_is_less_than(pair_fst(bst->elem), index)) {
            data = bst_search(bst->right, index);
        } else {
            data = bst_search(bst->left, index);
        }
    }

    return data;

}

bst_t bst_add(bst_t bst, index_t index, data_t data) {

    bst_t newnode = NULL;

    if (bst != NULL) {

        if (index_is_less_than(pair_fst(bst->elem), index)) {
            bst->right = bst_add(bst->right, index, data);
        } else {
            bst->left = bst_add(bst->left, index, data);
        }
    } else {
        newnode = calloc(1, sizeof(struct _tree_node_t));
        newnode->left = NULL;
        newnode->right = NULL;
        newnode->elem = pair_from_index_data(index, data);

        bst = newnode;
        newnode = NULL;
    }

    return bst;

}

bst_t bstmax(bst_t bst) {

    bst_t max = NULL;
    if (bst != NULL) {

        if (bst->right != NULL) {
            max = bstmax(bst->right);
        } else {
            max = bst;
        }
    }

    return max;

}

bst_t deletemax(bst_t bst) {

    if (bst != NULL) {

        if (bst->right != NULL) {
            bst->right = deletemax(bst->right);
        } else {
            bst = bst->left;
        }
    }

    return bst;

}

bst_t bst_remove(bst_t bst, index_t index) {

    bst_t aux = NULL;
    if (bst != NULL && bst_search(bst, index) != NULL) {

        if (index_is_equal(pair_fst(bst->elem), index)) {

            if (bst->left != NULL) {
                bst->elem = pair_destroy(bst->elem);
                aux = bstmax(bst->left);
                bst->elem = pair_copy(aux->elem);
                bst->left = deletemax(bst->left);
                aux->left = NULL;
                aux = bst_destroy(aux);
            } else {
                aux = bst->right;
                bst->right = NULL;
                bst = bst_destroy(bst);
                bst = aux;
                aux = NULL;
            }
        } else if (index_is_less_than(pair_fst(bst->elem), index)) {
            bst->right = bst_remove(bst->right, index);
        } else {
            bst->left = bst_remove(bst->left, index);
        }

    }
    return bst;

}

bst_t bst_copy(bst_t bst) {

    bst_t newbst = NULL;
    if (bst != NULL) {
        newbst = calloc(1, sizeof(struct _tree_node_t));
        newbst->elem = pair_copy(bst->elem);
        newbst->right = bst_copy(bst->right);
        newbst->left = bst_copy(bst->left);
    }

    assert(bst_is_equal(bst, newbst));
    return newbst;

}

list_t bst_to_list(bst_t bst, list_t list) {

    index_t index = NULL;
    data_t data = NULL;

    if (bst != NULL) {
        list = bst_to_list(bst->left, list);
        index = index_copy(pair_fst(bst->elem));
        data = data_copy(pair_snd(bst->elem));
        list = list_append(list, index, data);
        list = bst_to_list(bst->right, list);
    }

    index = NULL;
    data = NULL;

    return list;

}