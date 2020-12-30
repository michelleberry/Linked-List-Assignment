#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define SUCCESS 1
#define FAILURE 0

typedef char value_type[80]; 
typedef int key_type; 

#include "Sorted_List_ADT.h"
#include "commands_a4q1a.h"

/* Program: a4q1a_char.c
 * Author: Michelle Berry
 * Purpose: Allow user to create, view, add, and remove nodes from a dynamic linked list that is also kept sorted.
 *          in this program, the content of the list is strings <80 chars and their respective lengths.  
 */
int main (int argc, char * argv[]){

	char line[500];  
	/*create the list*/
	Sorted_List * myList = create_list();  

	if(argc > 1){
		/*open the file*/
		FILE *ifp; 
		if((ifp = fopen(argv[1], "r")) == NULL){
			fprintf(stderr, "Input file failed to open.\n");
			exit(1); 
		}
		/*loop through each line of file containing commands until end is reached*/
		while(fgets(line, 500, ifp) != NULL){
			/*check for each possible command*/
			if(strncmp(line, "rem_first", 9) == 0){
				rem_first(myList);

			} else if(strncmp(line, "rem_last", 8) == 0){
				rem_last(myList);

			} else if(strncmp(line, "rem_small", 9) == 0){
				rem_small(myList);

			} else if(strncmp(line, "rem_large", 9) == 0){
				rem_large(myList);

			} else if(strncmp(line, "empty", 5) == 0){
				empty(myList); 

			} else if(strncmp(line, "size", 4) == 0){
				print_size(myList); 

			} else if(strncmp(line, "print_all", 9) == 0){
				print_all_command(myList); 

			} else if(strncmp(line, "print_sort", 10) == 0){
				print_sort_command(myList); 

			} else if(strncmp(line, "a", 1) == 0){
				append_command(myList, &line[1]);

			} else if(strncmp(line, "p", 1) == 0){
				push_command(myList, &line[1]);
			}
		}
		fclose(ifp); 
	} else {
		/*if no input file loop through stdin*/
		while(fgets(line, 500, stdin) != NULL && (feof(stdin) != EOF)){
			if(strncmp(line, "rem_first", 9) == 0){
				rem_first(myList);

			} else if(strncmp(line, "rem_last", 8) == 0){
				rem_last(myList);

			} else if(strncmp(line, "rem_small", 9) == 0){
				rem_small(myList);

			} else if(strncmp(line, "rem_large", 9) == 0){
				rem_large(myList);

			} else if(strncmp(line, "empty", 5) == 0){
				empty(myList); 

			} else if(strncmp(line, "size", 4) == 0){
				print_size(myList); 

			} else if(strncmp(line, "print_all", 9) == 0){
				print_all_command(myList); 

			} else if(strncmp(line, "print_sort", 10) == 0){
				print_sort_command(myList); 

			} else if(strncmp(line, "a", 1) == 0){
				append_command(myList, &line[1]);

			} else if(strncmp(line, "p", 1) == 0){
				push_command(myList, &line[1]);

			}
		}
	}

	/*if list is not empty destroy it to free all memory*/
	if(size(myList) == 0){
		free(myList);
	} else {
		destroy_list(myList);
	}
	return 0; 
}