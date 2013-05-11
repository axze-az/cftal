CC=gcc
OPT=-O -Wall -Wno-unused -Wno-attributes
SDE=/opt/sde-bdw-external-5.38.0-2013-01-03-lin/sde

all : testsse2 testavx

iutsse2 : sleefsseavx.c helpersse2.h iut.c
	$(CC) $(OPT) -DENABLE_SSE2 -msse2 iut.c sleefsseavx.c -o iutsse2 -lm

iutavx : sleefsseavx.c helperavx.h iut.c
	$(CC) $(OPT) -DENABLE_AVX -mavx iut.c sleefsseavx.c -o iutavx -lm

iutavx2 : sleefsseavx.c helperavx2.h iut.c
	$(CC) $(OPT) -DENABLE_AVX2 -mavx2 -mfma iut.c sleefsseavx.c -o iutavx2 -lm

iutfma4 : sleefsseavx.c helperfma4.h iut.c
	$(CC) $(OPT) -DENABLE_FMA4 -mavx -mfma4 iut.c sleefsseavx.c -o iutfma4 -lm

../tester/tester :
	cd ../tester; make tester

../tester/testeru1 :
	cd ../tester; make testeru1

../tester/testersp :
	cd ../tester; make testersp

testsse2 : iutsse2 ../tester/tester ../tester/testersp
	../tester/tester ./iutsse2
	../tester/testeru1 ./iutsse2
	../tester/testersp ./iutsse2

testavx : iutavx ../tester/tester ../tester/testersp
	../tester/tester ./iutavx
	../tester/testeru1 ./iutavx
	../tester/testersp ./iutavx

testavx2 : iutavx2 ../tester/tester ../tester/testersp
	../tester/tester $(SDE) -- ./iutavx2
	../tester/testeru1 $(SDE) -- ./iutavx2
	../tester/testersp $(SDE) -- ./iutavx2

testfma4 : iutfma4 ../tester/tester ../tester/testersp
	../tester/tester ./iutfma4
	../tester/testeru1 ./iutfma4
	../tester/testersp ./iutfma4

clean :
	rm -f *~ *.o *.s iutsse2 iutavx iutavx2 iutfma4
