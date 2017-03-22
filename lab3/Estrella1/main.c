#include "dict.h"
#include "dict_helpers.h"
#include <assert.h>

#define PATH_TO_DICT "input/small.dic"
#define PATH_TO_COPY "input/copy.dic"

int main(void) {
    dict_t dict = NULL;
    dict_t copy = NULL;

    dict = dict_from_file(PATH_TO_DICT);
    dict_to_file(dict, PATH_TO_COPY);
    copy = dict_from_file(PATH_TO_COPY);

    assert(dict_is_equal(dict, copy));
    dict = dict_destroy(dict);
    copy = dict_destroy(copy);
    return (0);
}