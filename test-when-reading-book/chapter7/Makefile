GPP=g++ -g

all:
	$(GPP) this_test.cpp -o this_test
	$(GPP) construct_test.cpp -std=c++0x -o construct_test
	$(GPP) construct2_test.cpp -std=c++0x -o construct2_test
	$(GPP) friend_test.cpp -o friend_test
	$(GPP) class_test.cpp -std=c++0x -o class_test
	$(GPP) scope_test.cpp -o scope_test

clean:
	rm -f this_test
	rm -f construct_test
	rm -f construct2_test
	rm -f friend_test
	rm -f class_test
	rm -f scope_test
