#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define SUCCESS 1
#define FAILURE 0

#ifdef INT
	typedef int value_type; 
	typedef double key_type; 
#endif

#ifdef CHAR
	typedef char value_type[80]; 
	typedef int key_type; 
#endif

#ifdef FRACT
	typedef struct{
		long long num; 
		long long denom; 
	} Fraction; 

	typedef Fraction value_type; 
	typedef double key_type; 

#endif

#include "Sorted_List_ADT.h"

#ifdef FRACT
	#include "a4q3_function_defs.h"
#endif

#ifdef CHAR
int space_offset(char * string){
	int i=0; 
	while(string[i] == ' ' || string[i] == '\t'){
		i++; 
	}
	return i; 
}
#endif

/*wrapper function calls remove list and prints results*/
/*removes first key value node in inserted list and shows what was removed*/
void rem_first(Sorted_List * list){
	value_type value; 
	key_type key; 
	if(size(list) == 0){
		printf("rem_first:  could not remove - list already empty\n"); 
	} else {
		remove_first(list, &value, &key);
		#ifdef CHAR
			printf("rem_first:  %d %s \n", key, value);
		#endif

		#ifdef INT
			printf("rem_first:  %.02f %d  \n", key, value);
		#endif

		#ifdef FRACT
			printf("rem_first:  %.03f %lld/%lld  \n", key, value.num, value.denom);
		#endif
	}
}

/*removes last key value node in inserted list and shows what was removed*/
void rem_last(Sorted_List * list){
	value_type value; 
	key_type key; 
	if(size(list) == 0){
		printf("rem_last:  could not remove - list already empty\n"); 
	} else {
		remove_last(list, &value, &key);
		#ifdef CHAR
			printf("rem_last:  %d %s \n", key, value);
		#endif

		#ifdef INT
			printf("rem_last:  %.02f %d  \n", key, value);
		#endif

		#ifdef FRACT
			printf("rem_last:  %.03f %lld/%lld  \n", key, value.num, value.denom);
		#endif
	}

}

/*removes smallest key value node in list and shows what was removed*/
void rem_small(Sorted_List * list){
	value_type value; 
	key_type key; 
	if(size(list) == 0){
		printf("rem_small:  could not remove - list already empty\n"); 
	} else {
		remove_smallest_key(list, &value, &key);
		#ifdef CHAR
			printf("rem_small:  %d %s \n", key, value);
		#endif

		#ifdef INT
			printf("rem_small:  %.02f %d  \n", key, value);
		#endif

		#ifdef FRACT
			printf("rem_small:  %.03f %lld/%lld  \n", key, value.num, value.denom);
		#endif
	}

}

/*removes largest key value node in list and shows what was removed*/
void rem_large(Sorted_List * list){
	value_type value; 
	key_type key; 
	if(size(list) == 0){
		printf("rem_large:  could not remove - list already empty\n"); 
	} else {
		remove_largest_key(list, &value, &key);
		#ifdef CHAR
			printf("rem_large:  %d %s \n", key, value);
		#endif

		#ifdef INT
			printf("rem_large:  %.02f %d  \n", key, value);
		#endif

		#ifdef FRACT
			printf("rem_large:  %.03f %lld/%lld  \n", key, value.num, value.denom);
		#endif
	}
}

void print_size(Sorted_List * list){
	printf("size: List size = %d\n", size(list));
}

void empty(Sorted_List * list){
	empty_list(list); 
	printf("empty:   List size = %d\n", size(list));
}

void print_all_command(Sorted_List * list){
	printf("print_all:    Insertion Order\n");
	print_all(list); 
}

void print_sort_command(Sorted_List * list){
	printf("print_sort:    Key Sort Order\n");
	print_sort(list); 
}

/*invokes append function and prints record of what was appended*/
void append_command(Sorted_List * list, char * string){
	value_type value; 
	key_type key;

	#ifdef CHAR
		strcpy(value, string);
		int space = space_offset(value) + 1; 
		key = strlen(value)-space;
		append(list, value, key);
		printf("a:\t%d %s", key, value);
	#endif

	#ifdef INT
		sscanf(string, "%lf %d ", &key, &value); 
		append(list, value, key);
		printf("a:\t%.02f %d\n", key, value);
	#endif

	#ifdef FRACT
		long long num; long long denom; 
		sscanf(string, "%lld / %lld", &num, &denom);
		if(strchr(string, '/') == NULL){
			denom = 1; 
		}

		set_fraction(&value, num, denom);
		key = (long double)value.num/(long double)value.denom;
		append(list, value, key);

		if(value.denom == 1){
			printf("a:\t%.03f %lld\n", key, value.num);
		} else {
			printf("a:\t%.03f %lld/%lld\n", key, value.num, value.denom);
		}
	#endif
}

/*invokes push function and prints record of what was pushed*/
void push_command(Sorted_List * list, char * string){
	value_type value; 
	key_type key;

	#ifdef CHAR
	strcpy(value, string);
	int space = space_offset(value) + 1; 
	key = strlen(value)-space;
	push(list, value, key);
	printf("p:\t%d %s", key, value);
	#endif

	#ifdef INT
	sscanf(string, "%lf %d ", &key, &value); 
	push(list, value, key);
	printf("p:\t%.02f %d\n", key, value);
	#endif

	#ifdef FRACT
		long long num; long long denom; 
		sscanf(string, "%lld / %lld", &num, &denom);
		if(strchr(string, '/') == NULL){
			denom = 1; 
		}

		set_fraction(&value, num, denom);
		key = (long double)value.num/(long double)value.denom;
		push(list, value, key);

		if(value.denom == 1){
			printf("p:\t%.03f %lld\n", key, value.num);
		} else {
			printf("p:\t%.03f %lld/%lld\n", key, value.num, value.denom);
		}
	#endif

}
