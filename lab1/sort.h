#ifndef _SORT_H
#define _SORT_H

#include <stdbool.h>

struct sorting_stats {
	unsigned long int comps;
	unsigned long int swaps;
};

bool array_is_sorted(int *a, unsigned int length);
/*
    Returns true if the array is ascending sorted, and false if not.
    The array 'a' must have exactly 'length' elements.

*/


struct sorting_stats selection_sort(int *a, unsigned int length);
/*
    Sort the array 'a' using the Selection sort algorithm. The resulting sort
    will be ascending.

    The array 'a' must have exactly 'length' elements.

*/
struct sorting_stats insertion_sort(int *a, unsigned int length);
/*
    Sort the array 'a' using the Insertion sort algorithm. The resulting sort
    will be ascending.

    The array 'a' must have exactly 'length' elements.

*/

struct sorting_stats quick_sort(int *a, unsigned int length);
/*
    Sort the array 'a' using the Quick sort algorithm. The resulting sort
    will be ascending.

    The array 'a' must have exactly 'length' elements.

*/
struct sorting_stats bubble_sort(int *a,unsigned int length);


struct sorting_stats rand_quick_sort(int *a,unsigned int length);

#endif
