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

/*reduce a list to a single value using function provided*/
value_type reduce(Sorted_List * list, value_type (*reduce)(value_type, value_type), value_type init){
	Node * node = list->next; 
	value_type result = init; 
	int i; 
	for( i = 0; i < size(list); i++){
		result = reduce( node->value, result); 
		node = node->next; 
	}
	return result; 
}

/*adds two values and returns the sum*/
value_type add(value_type a, value_type b){
	return a + b; 
}

/*reduces a list by producing the summation*/
value_type sum(Sorted_List * list){
	if(list->next == NULL){
		return 0; 
	}
	return reduce(list, add, 0);
}


Sorted_List * map ( Sorted_List * list, value_type(*fn_ptr)(value_type)){
	Node * node = list->next; 
	Sorted_List * new_list = create_list(); 
	int i; 
	for (i = 0; i < size(list); i++){
		append(new_list, fn_ptr (node->value), node->key);
		node = node->next; 
	}

	return new_list; 
}

/*squares a value and returns the product*/
value_type square_values( value_type a ){
	return a*a; 
}

/*squares all values in a list and returns a list of these values*/
Sorted_List * square (Sorted_List * list){
	if(size(list) == 0){
		return create_list(); 
	}
	return map(list, square_values);
}

/*subtracts two values and returns the difference*/
value_type subtract ( value_type a, value_type b){
	return a - b; 
}

/*use this for diff*/
value_type * map_2_array( Sorted_List * list1, Sorted_List * list2, value_type(*fn_ptr)(value_type, value_type), int order){
	value_type * results = malloc(sizeof(value_type) * (size(list1)));

	Node * node1 = (order == SORTED_ORDER)? list1->sort : list1->next ; 
	Node * node2 = (order == SORTED_ORDER)? list2->sort : list2->next ;	
	
	int i; 
	for(i=0; i< (size(list1)) ; i++){
		results[i] = fn_ptr(node1->value, node2->value);
		node1 = (order == SORTED_ORDER)? node1->sort : node1->next; 
		node2 = (order == SORTED_ORDER)? node2->sort : node2->next; 
	}
	return results; 
} 

/*takes the difference of nodes in same position in each list*/
value_type * diff(Sorted_List * list1, Sorted_List * list2, int order){
	return map_2_array( list1, list2, subtract, order);
}

/*same as reduce but allows a mapping function*/
value_type map_reduce(Sorted_List * list, value_type(*map)(value_type), value_type (*reduce)(value_type, value_type), value_type init, value_type order ){
	Node * node = (order == SORTED_ORDER)? list->sort : list->next; 
	value_type result = init; 
	int i; 
	for( i = 0; i < size(list); i++){
		/*at each node, map with function and add to reduce accumulator*/
		result = reduce( map(node->value), result); 
		node = (order == SORTED_ORDER)? node->sort : node->next; 
	}
	destroy_list(list);
	return result;
}

/*map two functions into one list, then pass along to be mapped and reduced again*/
value_type map_2_reduce( Sorted_List * list1, Sorted_List * list2, value_type(*map)( value_type, value_type ), value_type (*reduce)(value_type, value_type), int order ){
	
	Node * node1 = (order == SORTED_ORDER)? list1->sort : list1->next;
	Node * node2 = (order == SORTED_ORDER)? list2->sort : list2->next;
	Sorted_List * new_list = create_list(); 
	int i; 
	for (i = 0; i < (size(list1)); i++){
		append(new_list, map(node1->value, node2->value), node1->key);
		node1 = (order == SORTED_ORDER)? node1->sort : node1->next;
		node2 = (order == SORTED_ORDER)? node2->sort : node2->next;
	}

	return map_reduce(new_list, square_values, add, 0, order);

} 

/*take differences of two lists, square all differences, then find their summation*/
value_type sum_of_sq_diff(Sorted_List * list1, Sorted_List * list2, int order){
	if(size(list1) != size(list2)){
		return FAILURE;
	}

	return map_2_reduce(list1, list2, subtract, add, order);
}

/*check if order is sorted or inserted*/
int get_order(char * string){
	if(strncmp(string, "SORTED_ORDER", 12) == 0){
		return SORTED_ORDER; 
	}
	return INSERTED_ORDER; 
}

/*set order string which will later print based on the order desired*/
void set_order_str( char * string, int order){
	if(order == INSERTED_ORDER){
		strcpy(string, "Insertion Order"); 
	} else if( order == SORTED_ORDER ){
		strcpy(string, "Key Sort Order");
	}
}
