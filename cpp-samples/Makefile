all:
	g++ -Wall --std=c++0x cast_test.cpp -o cast_test
	gcc -Wall -c function.c -o function.o 
	g++ -Wall use_c_function.cpp function.o -o use_c_function
clean:
	rm -f cast_test
	rm -f function.o 
	rm -f use_c_function 

