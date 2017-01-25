
run_test: test
	./test

test: odt.c odt.h test.c
	gcc -g odt.c test.c ezxml/libezxml.a -lzip -o test 


