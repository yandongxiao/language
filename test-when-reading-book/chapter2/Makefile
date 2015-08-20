GPP=g++ -g

all:
	g++ buildins.cpp -std=c++0x -o buildins
	$(GPP) calculate_with_char.cpp -o calculate_with_char
	$(GPP) signed_to_unsigned.cpp -o signed_to_unsigned
	$(GPP) unsigned_to_signed.cpp -o unsigned_to_signed
	$(GPP) initialization.cpp -std=c++0x -o initialization
	$(GPP) refer_test.cpp -o refer_test
	$(GPP) ptr_test.cpp -std=c++0x -o ptr_test
	$(GPP) const_test.cpp -std=c++0x -o const_test
	$(GPP) auto_test.cpp -std=c++0x -o auto_test
	$(GPP) decltype_test.cpp -std=c++0x -o decltype_test

clean:
	rm -f buildins
	rm -f calculate_with_char
	rm -f signed_to_unsigned
	rm -f unsigned_to_signed
	rm -f inunsigned_to_signed
	rm -f refer_test
	rm -f ptr_test
	rm -f const_test
	rm -f auto_test
	rm -f decltype_test
	rm -f initialization
