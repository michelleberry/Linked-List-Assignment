
/*for help calculating key values when value_type is char*/
int space_offset(char * string); 

/*"wrapper" functions that implement each command:*/
void rem_first(Sorted_List * list);

void rem_last(Sorted_List * list);

void rem_large(Sorted_List * list);

void rem_small(Sorted_List * list); 

void print_size(Sorted_List * list); 

void empty(Sorted_List * list);

void print_all_command(Sorted_List * list);

void print_sort_command(Sorted_List * list);

void append_command(Sorted_List * list, char * string);

void push_command(Sorted_List * list, char * string); 