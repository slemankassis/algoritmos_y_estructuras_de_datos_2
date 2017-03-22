#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

#include "list.h"
#include "data.h"
#include "index.h"
#include "pair.h"

struct _node_t {
	pair_t elem;
	list_t next;
};

list_t list_empty(void){
	list_t list = NULL;

	assert(list_length(list) == 0);
	return list;	
}

list_t list_destroy(list_t list){
	list_t aux1 = NULL;
	list_t aux2 = NULL;

	aux1 = list;
	while(aux1 != NULL){
		pair_destroy(aux1->elem);

		if(aux1->next != NULL){
			aux2 = aux1;
			aux1 = aux1->next;

			aux2->next = NULL;
			free(aux2);
			aux2 = NULL;
		} else {
			free(aux1);
			aux1 = NULL;
		}
	}
	list = aux1;

	return list;
}

unsigned int list_length(list_t list){
	unsigned int length = 0;

	while(list != NULL){
		length++;
		list = list->next;
	}
	return length;
}

bool list_is_equal(list_t list, list_t other){
	bool result = (list_length(list) == list_length(other));

	while(result && list != NULL && other != NULL){
		result = (pair_is_equal(list->elem, other->elem));

		list = list->next;
		other = other->next;
	}

	return result;
}

data_t list_search(list_t list, index_t index){
	bool lost = true;
	data_t data = NULL;

	while(list != NULL && lost){
		if(index_is_equal(pair_fst(list->elem), index)){
			data = pair_snd(list->elem);
			lost = false;
		} else {
			list = list->next;
		}
	}

	return data;
}

list_t list_append(list_t list, index_t index, data_t data){
	list_t curr = NULL;
	list_t prev = NULL;
	list_t newnode = NULL;

	curr = list;
	if(list == NULL){
		list = calloc(1,sizeof(struct _node_t));
		list->elem = pair_from_index_data(index, data);
		list->next = NULL;

	} else {
		while(curr != NULL){
			prev = curr;
			curr = curr->next;
		}

		newnode = calloc(1,sizeof(struct _node_t));
		newnode->elem = pair_from_index_data(index, data);
		newnode->next = NULL;

		prev->next = newnode;
	}
	return list;
}

list_t list_remove(list_t list, index_t index){
	bool removed = false;
	list_t aux = NULL;
	list_t curr =NULL;

	aux = list;
	curr = list;

	if(list!=NULL){
		if(!index_is_equal(pair_fst(list->elem), index)){
			curr = list->next;

			while(!removed && curr != NULL){
				if(index_is_equal(pair_fst(curr->elem), index)){
					aux->next = curr->next;
					curr->elem = pair_destroy(curr->elem);
					free(curr);
					curr = NULL;
					removed = true;
				}
				else
				{
					curr = curr->next;
					aux = aux->next;
				}
			}
		} else {
			list = list->next;
			curr->elem = pair_destroy(curr->elem);
			free(curr);
			curr = NULL;
			aux = NULL;
		}
	}
	return list;
}

list_t list_copy(list_t list){
	list_t newlist = NULL;
	list_t aux1 = NULL;
	list_t listoriginal = NULL;

	listoriginal = list;
	if(list!=NULL){
		newlist = calloc(1,sizeof(struct _node_t));
		newlist->elem = pair_copy(list->elem);
		newlist->next = NULL;
		aux1 = newlist;

		list = list->next;

		while(list != NULL){	
			newlist->next = calloc(1,sizeof(struct _node_t));
			newlist = newlist->next;
			newlist->elem = pair_copy(list->elem);
			newlist->next = NULL;

			list = list->next;
		}
		newlist = aux1;
		aux1 = NULL;
	}

	free(list);
	list = NULL;

	assert(list_is_equal(listoriginal, newlist));
	return newlist;
}

void list_dump(list_t list, FILE * fd){
	
	while(list != NULL){
		index_t indexx = pair_fst(list->elem);
		data_t dataa = pair_snd(list->elem);
		char *i=index_to_string(indexx);
		char *d=data_to_string(dataa);
		fprintf(fd, "%s : %s\n", i, d);
		list = list->next;
		free(i);
		free(d);
		i = NULL;
		d = NULL;
		dataa = NULL;
		indexx = NULL;
	}	
}