a4q1a_char: a4q1a_char.o Sorted_List_char_functions.o commands_q1a_char.o
	gcc -ansi -Wall -o a4q1a_char a4q1a_char.o Sorted_List_char_functions.o commands_q1a_char.o

a4q1a_char.o: a4q1a_char.c
	gcc -ansi -Wall -c a4q1a_char.c -DCHAR -o a4q1a_char.o

a4q1a_int: a4q1a_int.o Sorted_List_int_functions.o commands_q1a_int.o
	gcc -ansi -Wall -o  a4q1a_int a4q1a_int.o Sorted_List_int_functions.o commands_q1a_int.o

a4q1a_int.o: a4q1a_int.c
	gcc -ansi -Wall -c a4q1a_int.c -DINT -o a4q1a_int.o

a4q1b: a4q1b.o Sorted_List_int_functions.o a4q1b_functions.o commands_q1b.o
	gcc -ansi -Wall -o a4q1b a4q1b.o Sorted_List_int_functions.o a4q1b_functions.o commands_q1b.o

a4q1b.o: a4q1b.c
	gcc -ansi -Wall -c a4q1b.c -DINT -o a4q1b.o

a4q2: a4q2.o a4q2_functions.o Sorted_List_int_functions.o a4q1b_functions.o commands_q1a_int.o
	gcc -ansi -Wall -O2 -o a4q2 a4q2.o a4q2_functions.o Sorted_List_int_functions.o a4q1b_functions.o commands_q1a_int.o

a4q2.o: a4q2.c
	gcc -ansi -Wall -c a4q2.c -DINT -O2 -o a4q2.o

a4q3: a4q3.o a4q3_functions.o Sorted_List_fract_functions.o a4q1b_functions.o a4q2_functions.o commands_q1a_fract.o
	gcc -ansi -Wall -o a4q3 a4q3.o a4q3_functions.o Sorted_List_fract_functions.o a4q1b_functions.o a4q2_functions.o commands_q1a_fract.o

a4q3.o: a4q3.c
	gcc -ansi -Wall -c a4q3.c -lm -DFRACT -o a4q3.o

Sorted_List_char_functions.o: Sorted_List_functions.c
	gcc -ansi -Wall -c Sorted_List_functions.c -DCHAR -o Sorted_List_char_functions.o

Sorted_List_int_functions.o: Sorted_List_functions.c
	gcc -ansi -Wall -c Sorted_List_functions.c -DINT -o Sorted_List_int_functions.o

Sorted_List_fract_functions.o: Sorted_List_functions.c
	gcc -ansi -Wall -c Sorted_List_functions.c -DFRACT -o Sorted_List_fract_functions.o

commands_q1a_int.o: commands_q1a.c
	gcc -ansi -Wall -c commands_q1a.c -DINT -o commands_q1a_int.o

commands_q1a_char.o: commands_q1a.c
	gcc -ansi -Wall -c commands_q1a.c -DCHAR -o commands_q1a_char.o

commands_q1a_fract.o: commands_q1a.c
	gcc -ansi -Wall -c commands_q1a.c -DFRACT -o commands_q1a_fract.o

commands_q1b.o: commands_a4q1b.c
	gcc -ansi -Wall -c commands_a4q1b.c -o commands_q1b.o

a4q1b_functions.o: a4q1b_functions.c
	gcc -ansi -Wall -c a4q1b_functions.c

a4q2_functions.o: a4q2_functions.c
	gcc -ansi -Wall -c a4q2_functions.c

a4q3_functions.o: a4q3_functions.c
	gcc -ansi -Wall -c a4q3_functions.c 

