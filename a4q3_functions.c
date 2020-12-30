#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define SUCCESS 1 /*we use this for TRUE - same thing*/
#define FAILURE 0 /*we use this for FALSE - same thing*/
#define SIMPLE 10 
#define MIXED 20

typedef struct{
	long long num; 
	long long denom; 
} Fraction; 

typedef Fraction value_type; 
typedef double key_type; 

#include "Sorted_List_ADT.h"
#include "a4q2_function_defs.h"

/*sets the numerator and denominator in the fraction struct*/
int set_fraction (Fraction * fract, long long num, long long denom){
	if(denom == 0){
		return FAILURE; 
	} if (denom < 0){
		fract->denom = abs(denom); 
	} else {
		fract->denom = denom; 
	}
	fract->num = num; 
	return SUCCESS; 
}

/*sets mode based on information from user input string*/
int set_mode( char * string ){
	int mode = 0; 
	if(strncmp(string, "SIMPLE", 6) == 0){
		mode = SIMPLE; 
	} else if(strncmp(string, "MIXED", 5) == 0){
		mode = MIXED; 
	}
	return mode; 
}

/*sets string to be printed based on mode - simple or mixed*/
void set_mode_str (char * string, int mode){
	if(mode == SIMPLE){
		strcpy(string, "Simple Fractions");
	} else if(mode == MIXED){
		strcpy(string, "Mixed Fractions");
	}
}

/*simplifies fractions to lowest terms*/
void simplify(Fraction * fract){
	long g = gcd((long) fract->num , (long) fract->denom);
	fract->num = (fract->num)/g; 
	fract->denom = (fract->denom)/g;
}

/*convert a simple fraction to mixed fraction if necessary and print the contents of the node*/
void print_fract_mode(Fraction fract, int mode){
	int wholeNum, newNum; 
	simplify(&fract);
	if(mode == SIMPLE){ 
		printf("%lld/%lld\n", fract.num, fract.denom);
		
	} else if(mode == MIXED){
		if(fract.denom == 1){
			printf("%lld\n", fract.num); 
		} else if(fract.num < fract.denom){ 
			printf("%lld/%lld\n", fract.num, fract.denom);
		} else {
			wholeNum = fract.num / fract.denom; /*calculate the whole number and new mixed fraction*/
			newNum = fract.num % fract.denom; 
			if(newNum == 0){ /*if numerator is now zero don't bother to print 0/denom*/
				printf("%d\n", wholeNum);
			} else {
				printf("%d %d/%lld\n", wholeNum, newNum, fract.denom);
			}
		}
	}
}

/*print the list of fractions in insertion order*/
void print_fract(Sorted_List * list, int mode){
	Node * node = list->next;
	if(node != NULL){
		while(node->next != NULL){
			printf("   %.03f ", node->key); 
			print_fract_mode(node->value, mode);
			node = node->next; 
		}
		printf("   %.03f ", node->key);
		print_fract_mode(node->value, mode);
	}
}

/*invokes print_fract and also prints the command telling which mode was used*/
void print_fract_command(Sorted_List * list, char *string){
	char modestring[50]; 
	char modeStr[50]; 
	/*get mode from user input string*/
	sscanf(string, "%s", modestring);
	int mode = set_mode(modestring);
	set_mode_str(modeStr, mode); 
	/*invoke print*/
	printf("print_all:    %s, Insertion Order\n", modeStr);
	print_fract(list, mode);
}

/*print the list of fractions in key sort order*/
void print_sort_fract(Sorted_List * list, int mode){
	Node * node = list->sort;
	if(node != NULL){
		while(node->sort != NULL){
			printf("   %.03f ", node->key);
			print_fract_mode(node->value, mode);
			node = node->sort; 
		}
		printf("   %.03f ", node->key);
		print_fract_mode(node->value, mode);
	}

}

/*invokes print_sort_fract and also prints the command telling which mode was used*/
void print_fract_sort_command(Sorted_List * list, char * string){
	char modestring[50]; 
	char modeStr[50];
	/*get mode from user input string*/
	sscanf(string, "%s", modestring);
	int mode = set_mode(modestring);
	set_mode_str(modeStr, mode); 
	/*invoke print*/
	printf("print_sort:    %s, Key Sort Order\n", modeStr);
	print_sort_fract(list, mode);
}

value_type fract_reduce(Sorted_List * list, int (*reduce)(value_type *, value_type *, value_type *), value_type init){
	Node * node = list->next; 
	value_type result = init; 
	if(node->next != NULL){
		reduce( &result, &node->value, &node->next->value);
		node = node->next->next;
		int i; 
		for(i = 2; i < list->size; i++){
			/*sum and check for overflow errors*/
			if( reduce(&result, &node->value, &result) == FAILURE){
				printf("OVERFLOW ERROR - operation aborted\n"); 
				return init; 
			}
			node = node->next; 
		}
	} else {
		result = node->value; 
	}
	simplify(&result); 
	return result; 
}

int add_fract(Fraction * result, Fraction * x, Fraction * y){
	simplify(x); simplify(y); 
	long long tempNum = (((x->num)*(y->denom))+((x->denom)*(y->num))); 
	long long tempDenom = (x->denom*y->denom);
	/*if overflow or underflow return FAILURE*/
	if((x->num > 0 && y->num > 0 && tempNum < 0)|| (x->num < 0 && y->num < 0 && tempNum > 0)){
		return FAILURE; 
	} /*else must have been successful*/
	result->num = tempNum; 
	result->denom = tempDenom; 
	simplify(result); 
	return SUCCESS; 
}

/*finds the summation of all the fractions in list and prints it in the desired mode*/
int fract_sum(Sorted_List * list, int mode){
	Fraction fract; 
	fract.num = 0; 
	fract.denom = 0;
	if(list->next == NULL){ 
		return FAILURE; 
	}
	print_fract_mode(fract_reduce(list, add_fract, fract), mode);
	return SUCCESS; 
}

/*checks for the fract filter conditions*/
int fract_filt(value_type fract){
	if(fract.denom != 1){
		return SUCCESS; 
	}
	return FAILURE; 
}

/*checks for the whole_num filter conditions*/
/* whole numbers only, no fractions*/
int whole_num(value_type fract){
	if (fract.denom == 1){
		return SUCCESS; 
	}
	return FAILURE; 
}

/*checks for the rem_mixed filter conditions - no mixed numbers, either whole or fractions < 1*/
int rem_mixed(value_type fract){
	if(fract.denom == 1){
		return SUCCESS; 
	} else if (fract.num > fract.denom){
		return FAILURE; 
	}
	return SUCCESS; 
}

/*the recursive helper function to filter. */
Sorted_List * filter_recurr( Sorted_List * new_list, Node * node, int(*filter_fn)(value_type)){
	if(node == NULL){
		return new_list; 
	} else if(filter_fn(node->value) == SUCCESS){
		append(new_list, node->value, node->key); 
	}
	return filter_recurr(new_list, node->next, filter_fn); /*tail recursive*/
}

/*maps a new list based on filter restrictions*/
Sorted_List * filter( Sorted_List * list, int(*filter_fn)(value_type)){
	Node * node = list->next; 
	Sorted_List * new_list = create_list();
	return (node == NULL)? new_list : filter_recurr(new_list, node, filter_fn); 
}

/*invokes sum function and prints the command*/
void sum_command(Sorted_List * list, char * string){
	char substring[50];
	/*get mode from input line*/
	sscanf(string, "%s", substring);
	int mode = set_mode(substring); 
	printf("sum: \tresult = ");
	if(fract_sum(list, mode) == FAILURE){
		printf("no result - list empty\n"); 
	}
}

/*invokes fract filter and prints the command details*/
void fract_filt_command(Sorted_List * list, char * line){
	char string[50];
	char modeStr[50]; 
	/*get mode from input line*/
	sscanf(line, "%s", string);
	int mode = set_mode(string);
	set_mode_str(modeStr, mode); 
	/*create filtered list, print, and then free*/
	Sorted_List * fract_list = filter(list, fract_filt);
	printf("fract:    %s, Insertion Order\n", modeStr);
	print_fract(fract_list, mode);
	destroy_list(fract_list);
}

/*invokes filter function for whole numbers and prints the command details*/
void whole_num_filt_command(Sorted_List * list, char * line){
	char string[50];
	char modeStr[50]; 
	/*get mode from input line*/
	sscanf(line, "%s", string);
	int mode = set_mode(string);
	set_mode_str(modeStr, mode);
	/*create filtered list, print, and then free*/ 
	Sorted_List * whole_num_list = filter(list, whole_num);
	printf("whole_num:    %s, Insertion Order\n", modeStr);
	print_fract(whole_num_list, mode);
	destroy_list(whole_num_list);
}

/*invokes filter function for rem_mixed and prints the command details*/
void rem_mixed_filt_command(Sorted_List * list, char * line){
	char string[50];
	char modeStr[50]; 
	/*get mode from input line*/
	sscanf(line, "%s", string);
	int mode = set_mode(string);
	set_mode_str(modeStr, mode); 
	/*create filtered list, print, and then free*/
	Sorted_List * rem_mixed_list = filter(list, rem_mixed);
	printf("rem_mixed:    %s, Insertion Order\n", modeStr);
	print_fract(rem_mixed_list, mode);
	destroy_list(rem_mixed_list);
}