#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <assert.h>
#include "prop.h"

struct _prop {
	unsigned int var;
	prop left;
	prop right;
};

prop p_var(unsigned int n) {
	prop p = calloc(1, sizeof(struct prop));
	p->var = n;
	p->left = NULL;
	p->right = NULL;
	return p;
}

prop p_not(prop p) {
	prop q = calloc(1, sizeof(struct prop));
	q->left = p;
	q->right = NULL;
	p = NULL;
	return q;
}

prop p_and(prop p, prop q) {
	prop r = calloc(1, sizeof(struct prop));
	r->left = p;
	r->right = q;
	return r;
}

bool p_is_var(prop p) {
	return (p->left = NULL && p->right = NULL);
}

bool p_is_not(prop p) {
	return (p->left != NULL && p->right = NULL);
}

bool p_is_and(prop p) {
	return (p->left != NULL && p->right != NULL);
}

unsigned int maximo(unsigned int a, unsigned int b) {
	unsigned int c;
	if (a <= b) {
		c = b;
	} else {
		c = a;
	}
	return c;
}

unsigned int p_max_var(prop p) {
	if (p_is_var(p)) {
		max = p->var;
	} else if (p_is_not(p)) {
		max = p_max_var(p->left);
	} else if (p_is_and(p)) {
		max = maximo(p_max_var(p->left), p_max_var(p->right));
	}
	return max;
}

prop p_or(prop p, prop q) {
	prop r = calloc(1, sizeof(struct prop));
	r = p_not(p_and(p_not(p), p_not(q)));
	return r;
}

bool p_eval(a, prop p) {
	bool result;
	if (p_is_var(p)) {
		result = a[p->left];
	} else if (p_is_not) {
		result = !eval(a, p->left);
	} else {
		result = eval(p->left) && eval(p->right);
	}
}

prop destroy(prop p){
    if (!p_is_var(p)){
        if (p_is_and(p)){
            p->left = destroy(p->left);
            p->right = destroy(p->right);
        } else {
        	p->left = destroy(p->left);
        }
    }
    free(p);
    p = NULL;
    return p;
}
