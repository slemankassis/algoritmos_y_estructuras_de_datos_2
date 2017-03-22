#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <assert.h>
#include "expr.h"

struct expr_t
{
	unsigned int var;
	expr left;
	expr right;
};

expr var(unsigned int n) {
	expr g = NULL;
	g = calloc(1, sizeof(struct expr_t));
	g->var = n;
	g->left = NULL;
	g->right = NULL;
	return g;
}

expr op(expr e) {
	expr g = NULL;
	g = calloc(1, sizeof(struct expr_t));
	g->var = 0;
	g->left = e;
	g->right = NULL;
	return g;
}

expr suma(expr e, expr f) {
	expr g = NULL;
	g = calloc(1, sizeof(struct expr_t));
	g->var = 1;
	g->left = e;
	g->right = f;
	return g;
}

expr mult(expr e, expr f) {
	expr g = NULL;
	g = calloc(1, sizeof(struct expr_t));
	g->var = 2;
	g->left = e;
	g->right = f;
	return g;
}

expr Div(expr e, expr f) {
	expr g = NULL;
	g = calloc(1, sizeof(struct expr_t));
	g->var = 3;
	g->left = e;
	g->right = f;
	return g;
}


bool is_var(expr e) {
	return (e->left == NULL && e->right == NULL);
}

bool is_op(expr e) {
	return (e->left != NULL && e->right == NULL);
}

bool is_suma(expr e) {
	return (!is_var(e) && e->var == 1);
}

bool is_mult(expr e) {
	return (!is_var(e) && e->var == 2);
}

bool is_div(expr e) {
	return (!is_var(e) && e->var == 3);
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

unsigned int max_var(expr e) {
	unsigned int n;
	if(is_var(e)) {
		n = e->var;
	} else if(is_op(e)) {
		n = max_var(e->left);
	} else {
		n = maximo(max_var(e->left), max_var(e->right));
	}
	return n;
}


expr resta(expr e, expr f) {
	return (suma(e, op(f)));
}

expr mod(expr e, expr f) {
	return (resta(e, mult(Div(e, f), f)));
}


int eval(int *a, expr e) {
	int r;
	if (is_var(e)) {
		r = a[e->var];
	} else if (is_op(e)) {
		r = -eval(a, e->left);
	} else if (is_suma(e)) {
		r = eval(a, e->left) + eval(a, e->right);
	} else if (is_mult(e)) {
		r = eval(a, e->left) * eval(a, e->right);
	} else {
		r = eval(a, e->left) / eval(a, e->right);
	}
	return r;
}


void dump(int *a, expr e, FILE *fd) {//es necesario que vuelva a operar para imprimir //lo mismo que eval //recursivo
	if (is_var(e)) {
		fprintf(fd, "%i", eval(a, e));
	} else if (is_op(e)) {
		fprintf(fd, "-");
		dump(a, e->left, fd);
	} else if (is_suma(e)) {
		dump(a, e->left, fd);
		fprintf(fd, "+");
		dump(a, e->right, fd);
	} else if (is_mult(e)) {
		dump(a, e->left, fd);
		fprintf(fd, "*");
		dump(a, e->right, fd);
	} else if (is_div(e)) {
		dump(a, e->left, fd);
		fprintf(fd, "/");
		dump(a, e->right, fd);
	}
}

/*
void dump(prop p, FILE *fd) {
	if (is_var(p)) {
  		fprintf(fd, "%d\n", p->var);
 	} else if (is_not(p)) {
 		fprintf(fd, "not ");
		prop_dump(p->left, fd);
	} else if (is_and(p)) {
  		prop_dump(p -> left, fd);
		fprintf(fd, " and ");
  		prop_dump(p->right, fd);
  	}
}
*/

void destroy(expr e) {
	if (e != NULL) {
	if (!is_var(e)) {
		if (is_op(e)) {
			destroy(e->left);
			e->left = NULL;
		} else {
			destroy(e->left);
			e->left = NULL;
			destroy(e->right);
			e->right = NULL;
		}
	}
	free(e);
	e = NULL;

}}
