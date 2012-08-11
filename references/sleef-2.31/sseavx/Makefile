iutsse2 : sleefsseavx.c helpersse2.h iut.c
	gcc -DENABLE_SSE2 -Wall -Wno-unused -O -msse2 iut.c sleefsseavx.c -o iutsse2 -lm

iutavx : sleefsseavx.c helperavx.h iut.c
	gcc -DENABLE_AVX -Wall -Wno-unused -O -mavx iut.c sleefsseavx.c -o iutavx -lm

../tester/tester :
	cd ../tester; make tester

../tester/testersp :
	cd ../tester; make testersp

test : iutsse2 iutavx ../tester/tester
	../tester/tester ./iutsse2
	../tester/tester ./iutavx

testsp : iutsse2 iutavx ../tester/testersp
	../tester/testersp ./iutavx
	../tester/testersp ./iutsse2

clean :
	rm -f *~ *.o *.s iutsse2 iutavx
