iut : sleef.c iut.c
	gcc -Wall sleef.c iut.c -o iut -lm

../tester/tester :
	cd ../tester; make tester

../tester/testersp :
	cd ../tester; make testersp

test : iut ../tester/tester
	../tester/tester ./iut

testsp : iut ../tester/testersp
	../tester/testersp ./iut

clean :
	rm -f *~ *.o iut
