#ifndef PROP_H
#define PROP_H

typedef struct _prop *prop;

prop p_var(int n);

prop p_not(prop p);

prop p_and(prop p, prop q);

bool p_is_var(prop p);

bool p_is_not(prop p);

bool p_is_and(prop p);

int p_max_var(prop p);

prop p_or(prop p, prop q);

bool p_eval( ,prop p);

prop p_destroy(prop p);

#endif