#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define SUCCESS 1
#define FAILURE 0
#define INSERTED_ORDER 2
#define SORTED_ORDER 4

typedef int value_type; 
typedef double key_type; 

#include "Sorted_List_ADT.h"
#include "commands_a4q1b.h"
#include "a4q1b_func_defs.h"

/* Program: a4q1b.c
 * Author: Michelle Berry
 * Purpose: allow users to create and manipulate multiple linked lists and perform
 *          mathematical operations on them.
 */
int main (int argc, char * argv[]){

	Sorted_List * list_of_lists[10]; 
	/*create array of 10 sorted lists*/
	int i; 
	for(i=0; i<10; i++){
		/*malloc each list & initialize to null (w/in create_list)*/
		list_of_lists[i] = create_list(); 
	}

	char line[500]; 

	if(argc > 1){
		/*open file for reading*/
		FILE *ifp; 
		if((ifp = fopen(argv[1], "r")) == NULL){
			fprintf(stderr, "Input file failed to open.\n");
			exit(1); 
		}
		
		while(fgets(line, 500, ifp) != NULL){ /*check for each possible command using string compare*/

			if(strncmp(line, "rem_first", 9) == 0){
				rem_first_b(list_of_lists, &line[10]);

			} else if(strncmp(line, "rem_last", 8) == 0){
				rem_last_b(list_of_lists, &line[9]);

			} else if(strncmp(line, "rem_small", 9) == 0){
				rem_small_b(list_of_lists, &line[10]);

			} else if(strncmp(line, "rem_large", 9) == 0){
				rem_large_b(list_of_lists, &line[10]);

			} else if(strncmp(line, "empty", 5) == 0){
				empty_b(list_of_lists, &line[6]);
				
			} else if(strncmp(line, "size", 4) == 0){
				print_size_b(list_of_lists, &line[5]);
			
			} else if(strncmp(line, "print_all", 9) == 0){
				print_all_b(list_of_lists, &line[10]);

			} else if(strncmp(line, "print_sort", 10) == 0){
				print_sort_b(list_of_lists, &line[11]);

			} else if(strncmp(line, "a", 1) == 0){
				append_command_b(list_of_lists, &line[2]);

			} else if(strncmp(line, "p", 1) == 0){
				push_command_b(list_of_lists, &line[2]);

			} else if(strncmp(line, "sum|", 4) == 0){
				sum_command(list_of_lists, &line[4]);

			} else if(strncmp(line,"diff|", 5) == 0){
				diff_command(list_of_lists, &line[5]);

			} else if(strncmp(line, "square|", 7) == 0){
				square_command(list_of_lists, &line[7]);

			} else if(strncmp(line, "sum_sq_d|", 9) == 0){
				sum_sq_d_command(list_of_lists, &line[9]);

			}
		}
		/*close the file*/
		fclose(ifp); 
		
	} else {
		printf("Usage: ./a4q1b <filename>\n");
	}

	/*remember to free all lists before program exits*/
	int p; 
	for(p=0; p<10; p++){
		destroy_list(list_of_lists[p]);
	}

	return 0; 
}