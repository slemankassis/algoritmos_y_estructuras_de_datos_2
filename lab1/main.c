/* First, the standard lib includes, alphabetically ordered */
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

/* Then, this project's includes, alphabetically ordered */
#include "array_helpers.h"
#include "sort.h"

#define EXIT 'e'
#define INSERTION_SORT 'i'
#define SELECTION_SORT 's'
#define QUICK_SORT 'q'
#define BUBBLE_SORT 'b'
#define RAND_QUICK_SORT 'r'


void print_help(char *program_name) {
    /* Print the usage help of this program. */
    printf("Usage: %s <input file path>\n\n"
           "Sort an array given in a file in disk.\n"
           "\n"
           "The input file must have the following format:\n"
           " * The first line must contain only a positive integer,"
           " which is the length of the array.\n"
           " * The second line must contain the members of the array"
           " separated by one or more spaces. Each member must be an integer."
           "\n\n"
           "In other words, the file format is:\n"
           "<amount of array elements>\n"
           "<array elem 1> <array elem 2> ... <array elem N>\n\n",
           program_name);
}

char *parse_filepath(int argc, char *argv[]) {
    /* Parse the filepath given by command line argument. */
    char *result = NULL;

    if (argc < 2) {
        print_help(argv[0]);
        exit(EXIT_FAILURE);
    }

    result = argv[1];

    return (result);
}

char print_menu(void) {
    char result = '\0', discard = '\0';
    int scanf_result = 0;

    printf("Choose the sorting algorithm. Options are:\n"
           "\ts - selection sort\n\ti - insertion sort\n"
           "\tq - quick sort\n\tb - bubble sort\n\tr - rand quick sort\n\te - exit this program\n"
           "Please enter your choice: ");

    scanf_result = scanf("%c", &result);
    if (scanf_result != 1) {
        result = '\0';
    }

    /* Consume everything left in the stdin buffer */
    while (discard != '\n') {
        scanf_result = scanf("%c", &discard);
    }

    return (result);
}

bool is_valid_option(char option) {
    bool result = false;

    result = (option == EXIT ||
              option == INSERTION_SORT ||
              option == SELECTION_SORT || option == QUICK_SORT
|| option == BUBBLE_SORT || option == RAND_QUICK_SORT);

    return (result);
}

int main(int argc, char *argv[]) {
    char option = '\0';
    char *filepath = NULL;
    unsigned int length = 0;
    int *array = NULL;
    int *original_array = NULL;
	struct sorting_stats result;
    /* parse the filepath given in command line arguments */
    filepath = parse_filepath(argc, argv);

    /* parse the array given in the input file */
    array = array_from_file(filepath, &length);

    /* save a copy of array used to make some checks later */
    original_array = array_duplicate(array, length);

    /* print a simple menu and do the actual sorting */
    do {
        option = print_menu();
        switch (option) {
        case INSERTION_SORT:
            result=insertion_sort(array, length);
            break;
        case SELECTION_SORT:
            result=selection_sort(array, length);
            break;
        case QUICK_SORT:
            result=quick_sort(array, length);
            break;
	case BUBBLE_SORT:
            result=bubble_sort(array, length);
	    break;
	case RAND_QUICK_SORT:
	    result=rand_quick_sort(array, length);
	    break;
        case EXIT:
            printf("Exiting.\n");
            return (EXIT_SUCCESS);
        default:
            printf("\n\"%c\" is invalid. Please choose a valid option."
                   "\n\n", option);
        }
    } while (!is_valid_option(option));

    /* show the ordered array in the screen */
    array_dump(array, length);
    
    /* check if it is sorted */
    assert(array_is_sorted(array, length));

    /* check if it is a permutation of original */
    assert(array_is_permutation_of(array, original_array, length));

    /* destroy array */
    array_destroy(array);
    array_destroy(original_array);
	
	printf("Comps: %d \n",(int)result.comps);
	printf("Swaps: %d \n",(int)result.swaps);
	
    return (EXIT_SUCCESS);
}
