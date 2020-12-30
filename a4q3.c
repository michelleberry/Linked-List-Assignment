#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define SUCCESS 1
#define FAILURE 0
#define SIMPLE 10 
#define MIXED 20

typedef struct{
	long long num; 
	long long denom; 
} Fraction; 

typedef Fraction value_type; 
typedef double key_type; 

#include "Sorted_List_ADT.h"
#include "a4q3_function_defs.h"
#include "commands_a4q1a.h"

/* Program: a4q3.c
 * Author: Michelle Berry
 * Purpose: Allow user to create, view, add, and remove nodes from a dynamic linked list that is also kept sorted. 
 *          In this program, the content of the list are fractions. 
 */
int main (int argc, char * argv[]){

	char line[500]; 

	/*create list*/
	Sorted_List * myList = create_list();   

	if(argc > 1){
		/*open input file for reading*/
		FILE *ifp; 
		if((ifp = fopen(argv[1], "r")) == NULL){
			fprintf(stderr, "Input file failed to open.\n");
			exit(1); 
		}
		
		/*loop through input file line by line comparing each line for possible commands*/
		while(fgets(line, 500, ifp) != NULL){
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
				print_fract_command(myList, &line[9]);

			} else if(strncmp(line, "print_sort", 10) == 0){
				print_fract_sort_command(myList, &line[10]);

			} else if(strncmp(line, "a", 1) == 0){
				append_command(myList, &line[1]);
				
			} else if(strncmp(line, "p", 1) == 0){
				push_command(myList, &line[1]);

			} else if(strncmp(line, "sum", 3) == 0){
				sum_command(myList, &line[3]);

			} else if(strncmp(line, "fract", 5) == 0){
				fract_filt_command(myList, &line[5]);

			} else if(strncmp(line, "whole_num", 9) == 0){
				whole_num_filt_command(myList, &line[9]);

			} else if(strncmp(line, "rem_mixed", 9) == 0){
				rem_mixed_filt_command(myList, &line[9]);

			}

		}
		fclose(ifp); 

	} else {
		printf("Usage: ./a4q3 <filename>\n");
	}

	/*if the list has not already been emptied, destroy it. Otherwise free the list*/
	if(size(myList) == 0){
		free(myList);
	} else {
		destroy_list(myList);
	}
	return 0; 
}