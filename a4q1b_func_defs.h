/*holds declarations of public (list math) functions needed for the A4 Q1b program*/

value_type sum(Sorted_List * list);

Sorted_List * square (Sorted_List * list);

value_type * diff(Sorted_List * list1, Sorted_List * list2, int order);

value_type sum_of_sq_diff(Sorted_List * list1, Sorted_List * list2, int order);

/*used for recieving user inputs about wheter the order should be INSERTED or SORTED order*/
void set_order_str( char * string, int order);

int get_order(char * string);