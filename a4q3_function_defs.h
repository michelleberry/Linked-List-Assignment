/*function declarations for assignment 4 question 3 (a4q3.c)*/
void print_fract_command(Sorted_List * list, char *string); 

void print_fract_sort_command(Sorted_List * list, char * string);

void print_fract(Sorted_List * list, int mode); 

int set_fraction (Fraction * fract, long long num, long long denom);

int set_mode( char * string); 

void set_mode_str (char * string, int mode);

void sum_command(Sorted_List * list, char * string);

void fract_filt_command(Sorted_List * list, char * line);

void whole_num_filt_command(Sorted_List * list, char * line);

void rem_mixed_filt_command(Sorted_List * list, char * line);

Sorted_List * filter( Sorted_List * list, int(*filter_fn)(value_type)); 