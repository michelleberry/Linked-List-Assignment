typedef struct NODE {
	value_type value; 
	key_type key; 
	struct NODE * next; /* links to the next node in order of insertion*/
	struct NODE * sort; /* links to nodes in ascending order sorted by key*/
	struct NODE * prev; 
	struct NODE * prev_sorted; 
} Node; 

typedef struct LIST{
	int size; 
	struct NODE * next;
	struct NODE * sort;  /*points to the first node in the list (aka the head)*/
} Sorted_List; 

/*functions for Sorted_List datatype*/
Sorted_List * create_list(); 

int size( Sorted_List * list);

int push( Sorted_List * list, value_type value, key_type key);

int append( Sorted_List * list, value_type value, key_type key);

void print_all(Sorted_List * list); 

void print_sort(Sorted_List * list);

int remove_first( Sorted_List * list, value_type * value, key_type * key);

int remove_last( Sorted_List * list, value_type * value, key_type * key);

int remove_smallest_key(Sorted_List * list, value_type * value, key_type * key);

int remove_largest_key(Sorted_List * list, value_type * value, key_type * key);  

void empty_list( Sorted_List * list); 

void destroy_list( Sorted_List * list);
