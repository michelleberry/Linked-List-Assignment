#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define SUCCESS 1
#define FAILURE 0
#define INSERTED_ORDER 2
#define SORTED_ORDER 4

/* HAD TO MAKE ALL NEW COMMAND FUNCTIONS FOR Q1B SO THEY WOULD PRINT WHICH LIST THEY WERE AFFECTING!!*/
/* There would be a more clever way to do this but it would make my main() for each program dirtier. So.*/
typedef int value_type; 
typedef double key_type; 

#include "Sorted_List_ADT.h"
#include "a4q1b_func_defs.h"

/*wrapper function calls remove list and prints results*/
/*removes first key value node in inserted list and shows what was removed*/
void rem_first_b(Sorted_List * lists[10], char * string){
	int index = 0; 
	value_type value; 
	key_type key; 
	sscanf(string, "%d", &index);
	if(size(lists[index]) == 0){
		printf("rem_first:  list = %d  could not remove - list already empty\n", index); 
	} else {
		remove_first(lists[index], &value, &key);
		printf("rem_first:  list = %d,  %.02f %d  \n", index, key, value);
		
	}
}

/*removes last key value node in inserted list and shows what was removed*/
void rem_last_b(Sorted_List * lists[10], char * string){
	int index = 0; 
	value_type value; 
	key_type key; 
	sscanf(string, "%d", &index);
	if(size(lists[index]) == 0){
		printf("rem_last:  list = %d  could not remove - list already empty\n", index); 
	} else {
		remove_last(lists[index], &value, &key);
		printf("rem_last:  list = %d, %.02f %d  \n", index, key, value);
	}

}

/*removes smallest key value node in list and shows what was removed*/
void rem_small_b(Sorted_List * lists[10], char * string){
	int index = 0; 
	value_type value; 
	key_type key; 
	sscanf(string, "%d", &index);
	if(size(lists[index]) == 0){
		printf("rem_small:  list = %d  could not remove - list already empty\n", index); 
	} else {
		remove_smallest_key(lists[index], &value, &key);
		printf("rem_small:  list = %d, %.02f %d  \n", index, key, value);
	}

}

/*removes largest key value node in list and shows what was removed*/
void rem_large_b(Sorted_List * lists[10], char * string){
	int index = 0; 
	value_type value; 
	key_type key; 
	sscanf(string, "%d", &index);
	if(size(lists[index]) == 0){
		printf("rem_large:  list = %d  could not remove - list already empty\n", index); 
	} else {
		remove_largest_key(lists[index], &value, &key);
		printf("rem_large:  list = %d, %.02f %d  \n", index, key, value);
	}
}

void print_size_b(Sorted_List * lists[10], char * string){
	int index = 0; 
	sscanf(string, "%d", &index);
	printf("size: list = %d, List size = %d\n", index, size(lists[index]));
}

void empty_b(Sorted_List * lists[10], char * string){
	int index = 0; 
	sscanf(string, "%d", &index);
	empty_list(lists[index]); 
	printf("empty: list = %d, List size = %d\n", index, size(lists[index])); 
}

void print_all_b(Sorted_List * lists[10], char * string){
	int index = 0; 
	sscanf(string, "%d", &index);
	printf("print_all:  list = %d, Insertion Order\n", index);
	print_all(lists[index]); 
}

void print_sort_b(Sorted_List * lists[10], char * string){
	int index = 0; 
	sscanf(string, "%d", &index);
	printf("print_sort:  list = %d, Key Sort Order\n", index);
	print_sort(lists[index]); 
}

/*invokes append function and prints record of what was appended*/
void append_command_b(Sorted_List * lists[10], char * string){
	int index = 0; 
	value_type value; 
	key_type key;

	sscanf(string, "%d %lf %d", &index, &key, &value); 
	append(lists[index], value, key);
	printf("a:\tlist = %d, %.02f %d\n", index, key, value);

}

/*invokes push function and prints record of what was pushed*/
void push_command_b(Sorted_List * lists[10], char * string){
	int index = 0;
	value_type value; 
	key_type key;

	sscanf(string, "%d %lf %d", &index, &key, &value);
	push(lists[index], value, key);
	printf("p:\tlist = %d, %.02f %d\n", index, key, value);

}

void sum_command(Sorted_List * lists[10], char *string ){
	int index = 0; 
	sscanf(string, "%d", &index);
	printf("sum: \t list = %d, result = %d\n", index, sum(lists[index]));
}

void diff_command(Sorted_List * lists[10], char *string){
	int index = 0; 
	int indexB = 0; 
	char order[25]; /*from input*/
	char orderStr[25]; /*to be used for printing*/
	sscanf(string, "%d:%d %s", &index, &indexB, order);

	/*get order*/
	int orderInt = get_order(order);
	set_order_str(orderStr, orderInt);
			
	if(size(lists[index]) == size(lists[indexB])){
		printf("diff: \t list1 = %d, list2 = %d, %s\n", index, indexB, orderStr);
		value_type * array = diff(lists[index], lists[indexB], orderInt);
		int q;
	for(q=0; q<(size(lists[index])) ; q++){
		printf("   %d\n", array[q]);
	}
	free(array); 
	} else {
		printf("diff:  list %d and list %d are not the same size\n", index, indexB );
	}
}

void square_command(Sorted_List * lists[10], char * string){
	int index = 0; 
	sscanf(string, "%d", &index);
	printf("square:  list = %d\n", index);
	Sorted_List * sqList = square(lists[index]);
	print_all(sqList); 
	destroy_list(sqList);
}

void sum_sq_d_command(Sorted_List * lists[10], char * string){
	int index = 0; 
	int indexB = 0; 
	char order[25]; /*from input*/
	char orderStr[25]; /*to be used for printing*/
	sscanf(string, "%d:%d %s", &index, &indexB, order);
	
	/*get order*/
	int orderInt = get_order(order);
	set_order_str(orderStr, orderInt);

	int result = sum_of_sq_diff(lists[index], lists[indexB], orderInt);
				
	if(size(lists[index]) != size(lists[indexB])){
		printf("sum_sq_d: lists are not same size\n");
	} else {
		printf("sum_sq_d: list1 = %d, list2 = %d, %s, result = %d\n", index, indexB, orderStr, result);
	}
}