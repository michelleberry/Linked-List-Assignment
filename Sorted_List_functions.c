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

/*creates the Sorted_List list*/
Sorted_List * create_list(){
	Sorted_List * new_list = malloc(sizeof(Sorted_List));
	if(new_list != NULL){
		new_list->next = NULL; 
		new_list->sort = NULL; 
		new_list->size = 0; 
	}
	return new_list; 
}

/*returns size. an implementation detail of the ADT*/
int size(Sorted_List * list){
	return list->size; 
}

/*finds last node in a linked list*/
Node * find_last(Sorted_List * head){
	Node * node = head->next; 
	if(node != NULL){
		while(node->next != NULL){
			node = node->next; 
		}
	}
	return node; 
}

/*inserts node to sort and prevsort links in the proper sorted order*/
int insert_sorted( Sorted_List * list, Node * new_node){
	key_type search; 
	if(list->sort == NULL){
		list->sort = new_node;
		new_node->prev_sorted = NULL;
		new_node->sort = NULL;   
	} else {
		search = new_node->key; 
		
		Node * node = list->sort; 
		Node * head = list->sort; 
		Node * insert_node = NULL; 
		/*look for the last node less than the value of the new node - we will insert new node after that*/
		while(node != NULL && (node->key != search) && (node->key < search)){
			insert_node = node; 
			node = node->sort; 
		} 

		if(insert_node == NULL){ /*if you must push the new node*/
			new_node->sort = head; 
			list->sort = new_node; 
			new_node->prev_sorted = NULL; 
			new_node->sort->prev_sorted = new_node;
		} else if(insert_node->sort == NULL){ /*if you are appending the new node*/
			insert_node->sort = new_node; 
			new_node->prev_sorted = insert_node; 
			new_node->sort = NULL; 
		} else {/*insert between insert node and insert_node->sort*/
			new_node->sort = insert_node->sort;
			insert_node->sort = new_node; 
			new_node->prev_sorted = insert_node; 
			new_node->sort->prev_sorted = new_node; 
		}	
		
	}
	return SUCCESS; 
}


Node * add_front(Sorted_List * list, Node ** head, value_type value, key_type key){
	Node * new_node = malloc(sizeof(Node)); 
	if(new_node != NULL){
		#ifdef INT 
			new_node->value = value; 
		#endif

		#ifdef CHAR 
			strcpy(new_node->value, value); 
		#endif

		#ifdef FRACT
			(new_node->value).num = value.num; 
			(new_node->value).denom = value.denom; 
		#endif
  
		new_node->key = key; 

		new_node->next = *head;
		/*double imp starts*/ 
		new_node->prev = NULL; 
		if(*head != NULL){
			(*head)->prev = new_node; 
		}
		/*end (remove inbetween to remove double links)*/
		*head = new_node; 
	}
	insert_sorted(list, new_node);
	return new_node; 
}

/*inserts node at head of list*/
int push( Sorted_List * list, value_type value, key_type key){
	Node * node = add_front(list, &(list->next), value, key);
	int result = (node != NULL); 
	if(result == SUCCESS){
		list->size++; 
	}
	return result; 
}

/*appends node to end of list*/
int append ( Sorted_List * list, value_type value, key_type key){
	int result = FAILURE; 
	if(list->next == NULL){ /*if the list is empty before appending*/
		Node * first = malloc(sizeof(Node)); 
		if(first != NULL){ result = SUCCESS; }
		/* copy the values into the new node*/
		#ifdef INT 
			first->value = value; 
		#endif

		#ifdef CHAR 
			strcpy(first->value, value); 
		#endif

		#ifdef FRACT
			(first->value).num = value.num; 
			(first->value).denom = value.denom; 
		#endif

		first->key = key; 

		list->next = first; 
		first->next = NULL;
		first->prev = NULL; 
		first->sort = NULL;
		first->prev_sorted = NULL; 
		insert_sorted(list, first);
	} else {
		Node * last = find_last(list); 
		Node * new_node = malloc(sizeof(Node));
		if(new_node != NULL){ result = SUCCESS;}
		/*copy the values into the new node*/
		#ifdef INT 
			new_node->value = value; 
		#endif

		#ifdef CHAR 
			strcpy(new_node->value, value); 
		#endif

		#ifdef FRACT
			(new_node->value).num = value.num; 
			(new_node->value).denom = value.denom; 
		#endif
		new_node->key = key;

		last->next = new_node; 
		new_node->next = NULL;
		new_node->prev = last; 
		new_node->sort = NULL;
		insert_sorted(list, new_node);
	}
	list->size++; 
	return result;
}

/*finds last node in sorted linked list*/
Node * find_highest(Sorted_List * head){
	Node * node = head->sort; 
	if(node != NULL){
		while(node->sort != NULL){
			node = node->sort; 
		}
	}
	return node; 
}

/*remove the node passed from the sorted order links of the list*/
void remove_from_sort_links(Sorted_List * list, Node * remove){
	/*I consider every position the node could be in 
	  relative to it's neighbor nodes - eg. are they null?*/
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
}

/*removes the node passed from the insertion order links of the list passed*/
void remove_from_insert_links(Sorted_List * list, Node * remove){
	/*I consider every position the node could be in 
	  relative to it's neighbor nodes - eg. are they null?*/
	if (remove->prev == NULL && remove->next == NULL){
		list->next = NULL; 
	} else if(remove->prev == NULL){
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
}

/*removes first node (first regarding the inserted order).*/
int remove_first( Sorted_List * list, value_type * value, key_type * key){
	Node * remove = list->next; 
	if(remove != NULL){
		#ifdef INT 
			*value = remove->value; 
		#endif

		#ifdef CHAR 
			strcpy(*value, remove->value);  
		#endif 

		#ifdef FRACT
			value->num = (remove->value).num; 
			value->denom = (remove->value).denom; 
		#endif
		*key = remove->key; 

		remove_from_insert_links(list, remove); 
		remove_from_sort_links(list, remove);
 
	} else {
		return FAILURE;
	}

	(list->size)--; 
	free(remove);
	return SUCCESS;
	 
}

/*removes last node according to the insertion order*/
int remove_last( Sorted_List * list, value_type * value, key_type * key){
	Node * remove = find_last(list);
	if(remove != NULL){
		/*copy the values to return what was removed*/
		#ifdef INT 
			*value = remove->value; 
		#endif

		#ifdef CHAR 
			strcpy(*value, remove->value);  
		#endif 

		#ifdef FRACT
			value->num = (remove->value).num; 
			value->denom = (remove->value).denom; 
		#endif
		*key = remove->key; 
		/*remove from insertion order links*/
		remove_from_insert_links(list, remove); 
		remove_from_sort_links(list, remove); 
		 
	} else {
		return FAILURE;
	}
	/*update the list size and free the node that was removed*/
	(list->size)--; 
	free(remove); 
	return SUCCESS;
}

/*removes node with smallest key value*/
int remove_smallest_key(Sorted_List * list, value_type * value, key_type * key){
	Node * remove = list->sort; 
	if(remove != NULL){
		/*copy the values in order to return what was removed*/
		#ifdef INT 
			*value = remove->value; 
		#endif

		#ifdef CHAR 
			strcpy(*value, remove->value);  
		#endif 

		#ifdef FRACT
			value->num = (remove->value).num; 
			value->denom = (remove->value).denom;  
		#endif
		*key = remove->key; 
		/*remove from insert order list and sort order list*/
		remove_from_insert_links(list, remove); 
		remove_from_sort_links(list, remove);

	} else {
		return FAILURE;
	}
	/*update the list size and free the node that was removed*/
	(list->size)--; 
	free(remove); 
	return SUCCESS;
	 	 
}

/*finds largest key value and removes it from sorted list and insertion order list*/
int remove_largest_key(Sorted_List * list, value_type * value, key_type * key){
	Node * remove = find_highest(list);
	if(remove != NULL){
		#ifdef INT 
			*value = remove->value; 
		#endif

		#ifdef CHAR 
			strcpy(*value, remove->value);  
		#endif 

		#ifdef FRACT
			value->num = (remove->value).num; 
			value->denom = (remove->value).denom; 
		#endif
		*key = remove->key; 
		/*remove from insert order list*/
		remove_from_insert_links(list, remove); 
		remove_from_sort_links(list, remove);
			 
	} else {
		return FAILURE; 
	}
	/*update the list size and free the node that was removed*/
	(list->size)--; 
	free(remove); 
	return SUCCESS;
}

void print_key_value_pair(Node * node){
	#ifdef INT
		printf("   %.02f  %d\n", (node->key), (node->value));
	#endif

	#ifdef CHAR
		printf("%d  %s", (node->key), (node->value));
	#endif
}

/*prints entire list in insertion order*/
void print_all(Sorted_List * list){
	Node * head = list->next;
	if(head != NULL){
		while( head->next != NULL){
			print_key_value_pair(head); 
			/*traverse the list*/
			head = head->next; 
		}
		print_key_value_pair(head); 
	}  	
}

/*prints list in sorted order (ascending key values)*/
void print_sort(Sorted_List * list){
	Node * prNode = list->sort;
	if(prNode != NULL){
		while( prNode->sort != NULL){
			print_key_value_pair(prNode);
			prNode = prNode->sort; 
		}
		print_key_value_pair(prNode);
	}  
}

/*empties list by removing last node until list is empty*/
void empty_list( Sorted_List * list){ 
	int init_size = list->size; 
	int i = 0; 
	value_type value; /*dummy variables, needed to use remove last function*/
	key_type key; 
	int ret = SUCCESS; 
	while(ret != FAILURE && i < init_size){
		ret = remove_last(list, &value, &key);
		i++; 
	}
} 

/*empties and frees list*/
void destroy_list( Sorted_List * list){
	empty_list(list); 
	free(list); 
}
