CC=gcc

iut : sleefdp.c sleefsp.c iut.c
	$(CC) -Wall sleefdp.c sleefsp.c iut.c -o iut -lm

../tester/tester :
	cd ../tester; make tester

../tester/testeru1 :
	cd ../tester; make testeru1

../tester/testersp :
	cd ../tester; make testersp

test : iut ../tester/tester ../tester/testeru1
	../tester/tester ./iut
	../tester/testeru1 ./iut

testsp : iut ../tester/testersp
	../tester/testersp ./iut

clean :
	rm -f *~ *.o iut
