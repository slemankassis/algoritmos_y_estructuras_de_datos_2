#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include "list.h"
#include "dict.h"
#include "data.h"
#include "index.h"

struct _dict_t {
	unsigned int length;
	list_t list;
};

dict_t dict_empty(void){
	dict_t dict = NULL;
	dict = calloc(1,sizeof(struct _dict_t));

	dict->list = list_empty();
	dict->length = 0;

	assert(dict != NULL && dict_length(dict) == 0);
	return dict;
}

dict_t dict_destroy(dict_t dict){
	dict->list = list_destroy(dict->list);
	dict->length = 0;

	free(dict);
	dict = NULL;

	return dict;
}

unsigned int dict_length(dict_t dict){
	assert(dict != NULL);
	return (dict->length);
}

bool dict_is_equal(dict_t dict, dict_t other){
	assert(dict != NULL && other != NULL);
	return (list_is_equal(dict->list, other->list) && dict_length(dict) == dict_length(other));
}

bool dict_exists(dict_t dict, word_t word){
	assert(dict != NULL && word != NULL);

	bool exists = true;
	index_t w = index_from_string(word);

	if(list_search(dict->list, w) == NULL){
		exists = false;
	}
	w = index_destroy(w);
	free(w);
	w = NULL;

	return exists;
}

def_t dict_search(dict_t dict, word_t word){
	assert(dict != NULL && word != NULL && dict_exists(dict, word));

	def_t def;
	data_t data = NULL;

	index_t w = index_from_string(word);
	data = list_search(dict->list, w);
	def = data_to_string(data);

	w = index_destroy(w);
	free(w);
	w = NULL;

	assert(def != NULL);
	return def;
}

dict_t dict_add(dict_t dict, word_t word, def_t def){
	assert(dict != NULL && word != NULL && def != NULL);

	dict->list = list_append(dict->list, index_from_string(word), data_from_string(def));
	dict->length = dict_length(dict)+1;

	assert(dict_length(dict) == list_length(dict->list));
	return dict;
}

dict_t dict_remove(dict_t dict, word_t word){
	assert(dict != NULL && word != NULL && dict_exists(dict, word));

	index_t w = index_from_string(word);
	dict->list = list_remove(dict->list, w);
	dict->length = dict_length(dict)-1;

	w = index_destroy(w);

	assert(dict_length(dict) == list_length(dict->list));
	return dict;
}

dict_t dict_copy(dict_t dict){
	dict_t other = NULL;

	if(dict!=NULL){
		other = calloc(1,sizeof(struct _dict_t));
		other->list = list_copy(dict->list);
		other->length = dict_length(dict);

		assert(dict_is_equal(other, dict));
	}
	return other;
}

void dict_dump(dict_t dict, FILE * fd){
	assert(dict != NULL);
	
	list_dump(dict->list, fd);
	dict = NULL;
}