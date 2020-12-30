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
