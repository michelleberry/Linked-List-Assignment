This was the final assignment in my intermediate C programming course at the University of Guelph.
It involved creating an ADT/Abstract Data Type which is called Sorted_List and is a sorted doubly linked list. 
The file names are organized by question, which would be more helpful if i still had the outline of the assignment but I forgot to download it and lost it, whoops.
Here is a rough description of the file directory:

- a4q1a_char.c and a4q1a_int.c : parse user input commands
- commands_q1a.c : perform linked list operations such as print, append, remove, push, print, free/destroy a list

- a4q1b.c : creates an array of 10 sorted linked lists
- commands_a4q1b.c : perform linked list operations on an array of linked lists. had to write new functions instead of calling those from commands_q1a (which might have been a better program design) due to assignment restrictions

- a4q2.c : extended edition of a4q1a, allows file input from stdin or a file with scripted commands written. new commands include gcd which finds greatest common divisor of all integers within the list, and remove_nth which removes the node at the requested index n.
- a4q2_functions.c : perform linked list operations 

- a4q3.c : essentialy the same as q1a and q2, however now the content of the linked list are fractions which require an additional struct Fraction and specialized functions to implement. there are now special commands that will display the fractions as mixed numbers or improper fractions. 
- a4q3_functions.c : perform fraction linked list operations

Below is my original README handed in with my assignment. 

Here are instructions on how to compile and run the programs for Assignment 4 of CIS*2500.
Name: Michelle Berry
SN: 1082031

Question 1a:

	a4q1a_char:
	Compile: make a4q1a_char
	Execute: ./a4q1a_char <filename>

	a4q1a_int:
	Compile: make a4q1a_int
	Execute: ./a4q1a_int <filename>

	note - here the filename is optional as these programs also accept stdin input. 
	note2 - i wrote my own .c and .h files. 

Question 1b:

	Compile: make a4q1b
	Execute: ./a4q1b <filename>

	note - here filename is required 

Question 2:

	Compile: make a4q2
	Execute: ./a4q2 <filename>

	note - here filename is required
	note2 - Important!! - I have implemented a GCD command to test my gcd function. To use it, type "gcd a b" in your commands file where a and b are long integers. All of my recursive functions are in the file a4q2_functions.c, and the gcd function is at the bottom of this program. 
	My gcd function is tail recursive because it returns a reference to the function - i.e. it recurrs at the very end or 'tail' of the function. 
	I have added the -O2 flag to my makefile where a4q2 is compiled because i read online (https://gcc.gnu.org/onlinedocs/gcc/Optimize-Options.html) that it enables the command -foptimize-sibling-calls which optimizes sibling and tail recursive calls.

Question 3: 

	Compile: make a4q3
	Execute: ./a4q3 <filename>
	note - here filename is required
	note2 - my filter function can be found in the file a4q3_functions.c
