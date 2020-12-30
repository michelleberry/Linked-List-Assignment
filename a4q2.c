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
#include "a4q2_function_defs.h"
#include "commands_a4q1a.h"
#include "a4q1b_func_defs.h"

/* Program: a4q2.c
 * Author: Michelle Berry
 * Purpose: Allow user to create, view, add, and remove nodes from a dynamic linked list that is also kept sorted. 
 *          In this program, the content of the list are integers and doubles. Implement recursive functions. 
 */
int main (int argc, char * argv[]){

	char line[500]; 
	long a, b;    

	/*create list*/
	Sorted_List * myList = create_list();  

	if(argc > 1){
		/*open file for reading the commands from*/
		FILE *ifp; 
		if((ifp = fopen(argv[1], "r")) == NULL){
			fprintf(stderr, "Input file failed to open.\n");
			exit(1); 
		}
		
		/*loop through and read each line of the file*/
		while(fgets(line, 500, ifp) != NULL){
			a = 0; b = 0; 
			/*compare first n characters of each line with commands*/
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

			} else if(strncmp(line, "count_up", 8) == 0){
				count_up_command(&line[8]);

			} else if(strncmp(line, "count_down", 10) == 0){
				count_down_command(&line[10]);

			} else if(strncmp(line, "nth", 3) == 0){
				nth_command(myList, &line[3]);

			} else if(strncmp(line, "remove_nth", 10 ) == 0){
				remove_nth_command(myList, &line[10]);

			} else if(strncmp(line, "gcd", 3) == 0){
				sscanf(&line[3], "%ld %ld ", &a, &b);
				printf("gcd: The greatest common divisor of %ld and %ld is : %ld\n", a, b, gcd(a, b));

			}
		}
		fclose(ifp); 
	} else {
		/*if no filename inputted, instructions are provided*/
		printf("Usage: ./a4q2 <filename>\n");
	}


	/*if the list has not already been emptied, destroy it. Otherwise free the list*/
	if(size(myList) == 0){
		free(myList);
	} else {
		destroy_list(myList);
	}
	return 0; 
}