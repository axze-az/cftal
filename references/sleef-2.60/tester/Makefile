all : tester testersp

tester : tester.c
	gcc -Wall tester.c -lm -lmpfr -o tester

testersp : testersp.c
	gcc -Wall testersp.c -lm -lmpfr -o testersp

clean :
	rm -f *~ *.o tester testersp
