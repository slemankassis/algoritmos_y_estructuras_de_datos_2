#ifndef EXPR_H
#define EXPR_H
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct expr_t *expr;//


expr var(unsigned int n);
expr op(expr e);
expr suma(expr e, expr f);
expr mult(expr e, expr f);
expr Div(expr e, expr f);

bool is_var(expr e);
bool is_op(expr e);
bool is_suma(expr e);
bool is_mult(expr e);
bool is_div(expr e);

unsigned int max_var(expr e);

expr resta(expr e, expr f);
expr mod(expr e, expr f);

int eval(int *a, expr e);

void dump(int *a, expr e, FILE *fd);
void destroy(expr e);


#endif