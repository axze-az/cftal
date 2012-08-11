iut : iut.6 sleef.6
	6l -o iut iut.6

iut_std : iut_std.6 sleef.6
	6l -o iut_std iut_std.6

iut.6 : iut.go sleef.6
	6g iut.go

iut_std.6 : iut_std.go sleef.6
	6g iut_std.go

sleef.6 : sleef.go
	6g sleef.go

../tester/tester :
	cd ../tester; make tester

test : iut ../tester/tester
	../tester/tester ./iut

test_std : iut_std ../tester/tester
	../tester/tester ./iut_std

clean :
	rm -f *~ *.6 iut iut_std
