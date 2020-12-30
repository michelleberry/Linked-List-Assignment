#include <stdlib.h>
#include <stdio.h>
#define SUCCESS 1
#define FAILURE 0
#define INSERTED_ORDER 2
#define SORTED_ORDER 4

typedef int value_type; 
typedef double key_type; 

#include "Sorted_List_ADT.h"
#include "a4q1b_func_defs.h"

/*count from 0 to n by 1's*/
/*recursive function*/
int count_up ( int first, int last ){
	if(first == last){
		return last; 
	} 

	if(first+1 == last){
		printf("%d \n", first+1);
	} else {
		printf("%d, ", first+1);
	}

	return count_up(first+1, last);  /*as you can see it is tail recursive*/
}

/*count down by 2's from n to zero*/
int count_down (int num){
	if(num == 0){
		return 0; 
	}

	if(num-2 == 0){
		printf("%d \n", num-2);
	} else {
		printf("%d, ", num-2);
	}

	return count_down(num-2); 
}


int nth(Node * node, int current, int n){
	if(current == n){
		printf("   %.02f %d\n", node->key, node->value);
		return 1; 
	} else {
		node = node->next; 
		return nth(node, current+1, n);
	}

}

int nth_sorted(Node * node, int current, int n){
	if(current == n){
		printf("   %.02f %d\n", node->key, node->value);
		return 1; 
	} else {
		node = node->sort; 
		return nth_sorted(node, current+1, n);
	}
}

/*finds the nth to be removed RECURSIVELY*/
Node * remove_nth_sorted(Node * node, int current, int n){
	if(current == n){
		return node; 
	} else {
		node = node->sort; 
		return remove_nth_sorted(node, current+1, n);
	}
}

/*finds the nth to be removed RECURSIVELY*/
Node * remove_nth(Node * node, int current, int n){
	if(current == n){
		return node; 
	} else {
		node = node->next; 
		return remove_nth(node, current+1, n);
	}
}

/*remove nth node from list in specified order*/
int nth_remover(Sorted_List * list, int n, int order, value_type * value, key_type * key){

	Node * remove = (order == INSERTED_ORDER)? remove_nth(list->next, 0, n) : remove_nth_sorted(list->sort, 0, n); 
	*value = remove->value; 
	*key = remove->key; 

	/*remove from insert order list*/
	if (remove->prev == NULL && remove->next == NULL){
		list->next = NULL; 
	}else if(remove->prev == NULL){
		list->next = remove->next; 
		remove->next->prev = NULL; 
		remove->next = NULL; 
	} else if (remove->next == NULL){
		remove->prev->next = NULL; 
		remove->prev = NULL; 
	} else {
		remove->prev->next = remove->next; 
		remove->next->prev = remove->prev; 
		remove->prev = NULL; 
		remove->next = NULL; 
	}

	/*remove from sorted list*/
	if(remove->sort == NULL && remove->prev_sorted == NULL){
		list->sort = NULL; 
	} else if(remove->prev_sorted == NULL){
		list->sort = remove->sort; 
		remove->sort->prev_sorted = NULL;  
		remove->sort = NULL; 

	} else if(remove->sort == NULL){
		remove->prev_sorted->sort = NULL;  
		remove->prev_sorted = NULL;

	} else {
		remove->prev_sorted->sort = remove->sort; 
		remove->sort->prev_sorted = remove->prev_sorted; 
		remove->prev_sorted = NULL; 
		remove->sort = NULL;
	}

	(list->size)--; 
	free(remove); 
	return SUCCESS;

}

/* Compute GCD using Euclid's Algorithm*/
long gcd (long a, long b){

	if ( b < a ){
		long temp;
		temp = a;
		a = b;
		b = temp;
	}

	if(a == b){
		return a;
	} 
	/*else*/
	return gcd(a, b-a);
	
}

/*invokes the count up function and prints the command*/
void count_up_command(char * string){
	int n; 
	sscanf(string, "%d ", &n); 
	printf("count_up from 0 to %d\n     0, ", n);
	count_up(0, n);
}

/*invokes the count down function and prints the command*/
void count_down_command(char * string){
	int n; 
	sscanf(string, "%d ", &n);
	printf("count_down from %d to 0 by 2\n     %d, ", n*2, n*2);
	count_down(n*2); 
}

/*invokes recursive nth function that finds nth node and prints when it is found*/
void nth_command(Sorted_List * list, char * string){
	int n; 
	char substr[50];
	char orderStr[50];  
	sscanf(string, "%d %s", &n, substr);
	int order = get_order(substr);
	set_order_str(orderStr, order);

	printf("nth: \t n = %d, %s\n", n, orderStr);
	if(n > (list->size)-1){
		printf("    FAILED: n >= size where size = %d\n", list->size);
	} else {
		if (order == SORTED_ORDER){
			nth_sorted(list->sort, 0, n);

		} else if (order == INSERTED_ORDER){
			nth(list->next, 0, n);
		}
	}
}

/*invokes nth_remover function which invokes recursive functions that find the node and return it to be removed by nth remover*/
void remove_nth_command(Sorted_List * list, char * string){
	int n; 
	char substr[50];
	char orderStr[50];  
	sscanf(string, "%d %s", &n, substr);
	int order = get_order(substr);
	set_order_str(orderStr, order);

	printf("remove_nth: \t n = %d, %s\n", n, orderStr);
	if(n > (list->size)-1){
		printf("    FAILED: n >= size where size = %d\n", list->size);
	} else {
		value_type num; 
		key_type fnum; 
		nth_remover(list, n, order, &num, &fnum);
		printf("   %.02f %d\n", fnum, num);	
	}
}