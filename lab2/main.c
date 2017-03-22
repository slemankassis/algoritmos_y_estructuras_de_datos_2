#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include "dict_helpers.h"
#include "helpers.h"
#include "dict.h"

#define SIZE 'z'
#define SEARCH 's'
#define ADD 'a'
#define DELETE 'd'
#define EMPTY 'e'
#define SHOW 'h'
#define DUPLICATE 'c'
#define LOAD 'l'
#define SAVE 'u'
#define QUIT 'q'

char print_menu(void){
    char result = '\0', discard = '\0';
    int scanf_result = 0;
    printf("\n\t************DICCIONARIO******************\n"
           "\t*   z - Tamaño del diccionario          *\n"
           "\t*   s - Buscar una palabra              *\n"
           "\t*   a - Agregar una palabra             *\n"
           "\t*   d - Eliminar una palabra            *\n"
           "\t*   e - Vaciar diccionario              *\n"
           "\t*   h - Mostrar diccionario             *\n"
           "\t*   c - Duplicar diccionario*           *\n"
           "\t*   l - Abrir diccionario desde archivo *\n"
           "\t*   u - Guardar diccionario             *\n"
           "\t*   q - Salir                           *\n"
           "\t*****************************************\n"
           "\t                                         \n"
           "-> Elija una opcion: ");
    scanf_result = scanf("%c", &result);
    if(scanf_result != 1){
        result = '\0';
    }
    while(discard != '\n'){
        scanf_result = scanf("%c", &discard);
    }
    return result;
}

int main(){
    char option = '\0';
   	dict_t dict = dict_empty();
   	word_t word = NULL;
   	def_t def = NULL;
    char *filename = '\0';

    dict_t other = NULL;

    while(true){
        option = print_menu();

        switch (option){

	        case SIZE:
	            printf("\t-> El tamaño es: %u\n", dict_length(dict));
	            break;

	        case SEARCH:
				printf("\t-> Buscar la palabra: ");
				word = readline_from_stdin();
	            if(dict_exists(dict, word) && dict_length(dict)!= 0){
	            	def = dict_search(dict, word);
	                printf("\t-> La definicion es: %s\n",def);
	            } else {
	                printf("\t-> La palabra no existe.\n");
	            }

	            if(word != NULL){
	        		free(word);
		  	 		word = NULL;
	        	}
	        	if(def != NULL){
	        		free(def);
		  	 		def = NULL;
	        	}
				break;

	        case ADD:
				printf("\t-> Palabra: ");
				word = readline_from_stdin();
				
		        if(dict_exists(dict, word)){
		            printf("\t-> La palabra ya existe en el diccionario.\n");
		        } else {
		            printf("\t-> Definicion: ");
		            def = readline_from_stdin();
		        	dict = dict_add(dict, word, def);
			        printf("\t-> La palabra fue agregada.\n");
		        }
		        
		        if(word != NULL){
	        		free(word);
		   			word = NULL;
	            }
		   		if(def != NULL){
		   			free(def);
		   			def = NULL;
		   		}
				break;

			case DELETE:
				printf("\t-> Palabra a borrar: ");
				word = readline_from_stdin();
				if(word != NULL){
		            if(dict_exists(dict, word)){
		                dict = dict_remove(dict, word);
		                printf("\t-> La palabra fue eliminada.\n");
		            } else {
		                printf("\t-> Palabra no existe en el diccionario o no es valida.\n");
		            }
		            if(word != NULL){
			        	free(word);
				  	 	word = NULL;
				    }
		        }
	            break;

			case EMPTY:
				dict = dict_destroy(dict);
			    dict = dict_empty();
			    printf("\t-> El diccionario fue vaciado.\n");
		    	break;

		    case SHOW:
	            printf("\n{\n");
		    	dict_dump(dict, stdout); 
	            printf("}\n");
		    	break;

		    case DUPLICATE:
		    	other = dict_copy(dict);
		    	dict = dict_destroy(dict);
		    	dict = other;
		    	other = NULL;
	            printf("\t-> El diccionario fue duplicado:\n");
	            printf("\n{\n");
	            dict_dump(dict, stdout); 
	            printf("}\n");
		    	break;

		    case LOAD:
	            printf("\t-> Ingrese diccionario: ");
	            filename = readline_from_stdin();
	            other = dict_from_file(filename);
			    if(other!=NULL){
			        printf("\t-> El diccionario fue cargado.\n");

			        dict = dict_destroy(dict);
			        dict = other;
			        other = NULL;
			    } else {
			        printf("\t-> No se pudo cargar.\n");
			    }

			    free(filename);
			    filename = NULL;
		    	break;

		    case SAVE:
		    	if(dict != NULL){
		            printf("\t-> Nombre del diccionario: \n");
		            filename = readline_from_stdin();

		            if(filename != NULL){
			    		dict_to_file(dict, filename);
			    		printf("\t-> El diccionario fue guardado.\n");
		            	
		            } else {
	            		printf("\t-> No se pudo guardar.\n");
	           		}
	           		free(filename);
		            filename = NULL;
		        } else {
	            	printf("\t-> No se pudo guardar.\n");
	            }
		    	break;

	        case QUIT:
	            printf("\t-> Saliendo.\n");
	            dict = dict_destroy(dict);
	            if(other != NULL){
	            	other = dict_destroy(other);
	            }
	            

	            return (EXIT_SUCCESS);

	        default:
	            printf("\n\"%c\" no es una opcion valida."
	                   "\n\n", option);
	        }
	    }
	    return (EXIT_SUCCESS);
}