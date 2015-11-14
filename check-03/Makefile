include ../../Rules.make
ifeq ($(INSTALLDIR),)
INSTALLDIR=$(HOME)
endif

# Name  of the library
LIBNAME=checkx86vec-03
MAJOR=0#
MINOR=1#

ifeq ($(CC),aarch64-linux-gnu-gcc-5)
ARCH=-march=armv8-a
else
ARCH+=-march=native #-mavx -mavx2 -mfma -mavx512f -mpopcnt -mavx2 -mfma
endif

EXEC=

SLDFLAGS:= $(SLDFLAGS) -L../sysio -lsysio++ -L../thread -lthread++
CXXFLAGS+=-I. -I.. -I../.. -I../stlex -I../thread  -I../sysio #-march=native
CSRCS=$(wildcard ./x86vec_test_*.cc ./bitops_test.cc d_int8_test.cc)

all: testx86vec-03 #testemuvec-03

debug: testx86vec-03-g #testemuvec-03

lib: lib$(LIBNAME).a 

install: 
	@echo nothing to do

tgt:
	echo $(CSRCS)

###########################################################################
# Static library
lib$(LIBNAME).a: $(STDOBJS)
	$(AR) $(ARFLAGS) $@ $?

install-static: lib$(LIBNAME).a 
	mkdir -p $(INSTALLDIR)/lib
	$(INSTALL) -c -m 0644 lib$(LIBNAME).a $(INSTALLDIR)/lib

###########################################################################
# Static Debug library
lib$(LIBNAME)-g.a: $(DEBOBJS)
	$(AR) $(ARFLAGS) $@ $?

install-debug: lib$(LIBNAME)-g.a 
	mkdir -p $(INSTALLDIR)/lib
	$(INSTALL) -c -m 0644 lib$(LIBNAME)-g.a $(INSTALLDIR)/lib

testx86vec-03: testx86vec-03.ol lib$(LIBNAME).a ../libcftal.a
	$(LD) -o $@ $< $(OPT) $(LDFLAGS) -L. -l$(LIBNAME) -L .. -Wl,-Bstatic -lcftal -Wl,-Bdynamic -lstdc++ -lm

testx86vec-03-g: testx86vec-03.od lib$(LIBNAME)-g.a ../libcftal-g.a
	$(LD) -o $@ $< $(DEB) $(LDFLAGS) -L. -l$(LIBNAME)-g -L .. -Wl,-Bstatic -lcftal-g -Wl,-Bdynamic -lstdc++ -lm

testemuvec-03: testemuvec-03.ol lib$(LIBNAME).a ../libcftal.a
	$(LD) -o $@ $< $(OPT) $(LDFLAGS) -L. -l$(LIBNAME) -L .. -Wl,-Bstatic -lcftal -Wl,-Bdynamic -lstdc++ -lm

testemuvec-03-g: testemuvec-03.od lib$(LIBNAME)-g.a ../libcftal-g.a
	$(LD) -o $@ $< $(DEB) $(LDFLAGS) -L. -l$(LIBNAME)-g -L .. -Wl,-Bstatic -lcftal-g -Wl,-Bdynamic -lstdc++ -lm

# rcp_div: rcp_div.ol lib$(LIBNAME).so.$(MAJOR).$(MINOR)
# 	$(LD) -o $@ $< $(LDFLAGS) -L. -Wl,-rpath=. -l$(LIBNAME) -lstdc++

# rcp_div_g: rcp_div.od lib$(LIBNAME)-g.a
# 	$(LD) -o $@ $< $(LDFLAGS) -g -L. -l$(LIBNAME)-g -lstdc++

# rcp_div_64: rcp_div_64.ol lib$(LIBNAME).so.$(MAJOR).$(MINOR)
# 	$(LD) -o $@ $< $(LDFLAGS) -L. -Wl,-rpath=. -l$(LIBNAME) -lstdc++

# rcp_div_64_g: rcp_div_64.od lib$(LIBNAME)-g.a
# 	$(LD) -o $@ $< $(LDFLAGS) -g -L. -l$(LIBNAME)-g -lstdc++

test-sin: testx86vec-03
	$(EXEC) ./$< <sin.testdata

test-sin-256: testx86vec-03
	$(EXEC) ./$< --bits-256 <sin.testdata

test-sin-fma: testx86vec-03
	sde64 -mix -ast -- ./$< <sin.testdata

test-sin-native: testx86vec-03
	$(EXEC) ./$< --use-native <sin.testdata

test-sin-native-fma: testx86vec-03
	sde64 -mix -ast -- ./$< --use-native <sin.testdata

test-cos: testx86vec-03
	$(EXEC) ./$< <cos.testdata

test-cos-256: testx86vec-03
	$(EXEC) ./$< --bits-256 <cos.testdata

test-cos-native: testx86vec-03
	$(EXEC) ./$< --use-native <cos.testdata

test-tan: testx86vec-03
	$(EXEC) ./$< <tan.testdata

test-tan-256: testx86vec-03
	$(EXEC) ./$< --bits-256 <tan.testdata

test-tan-native: testx86vec-03
	$(EXEC) ./$< --use-native <tan.testdata

test-exp: testx86vec-03
	$(EXEC) ./$< <exp.testdata

test-exp-256: testx86vec-03
	$(EXEC) ./$< --bits-256 <exp.testdata

test-exp-native: testx86vec-03
	$(EXEC) ./$< --use-native  <exp.testdata

test-exp-native-256: testx86vec-03
	$(EXEC) ./$< --use-native  --bits-256 <exp.testdata

test-exp-fma: testx86vec-03
	sde64 -mix -ast -- ./$< <exp.testdata

test-exp-native-fma: testx86vec-03
	sde64 -mix -ast -- ./$< --use-native <exp.testdata

test-expm1: testx86vec-03
	$(EXEC) ./$< <expm1.testdata

test-expm1-256: testx86vec-03
	$(EXEC) ./$< --bits-256 <expm1.testdata

test-expm1-native: testx86vec-03
	$(EXEC) ./$< --use-native  <expm1.testdata

test-expm1-fma: testx86vec-03
	sde64 -mix -ast -- ./$< <expm1.testdata

test-expm1-native-fma: testx86vec-03
	sde64 -mix -ast -- ./$< --use-native <expm1.testdata

test-pow: testx86vec-03
	$(EXEC) ./$< <pow.testdata

test-pow-256: testx86vec-03
	$(EXEC) ./$< --bits-256 <pow.testdata

test-pow-native: testx86vec-03
	$(EXEC) ./$< --use-native  <pow.testdata

test-pow-fma: testx86vec-03
	sde64 -mix -ast -- ./$< <pow.testdata

test-pow-native-fma: testx86vec-03
	sde64 -mix -ast -- ./$< --use-native <pow.testdata

test-sinh: testx86vec-03
	$(EXEC) ./$< <sinh.testdata

test-sinh-256: testx86vec-03
	$(EXEC) ./$< --bits-256 <sinh.testdata

test-sinh-native: testx86vec-03
	$(EXEC) ./$< --use-native  <sinh.testdata

test-sinh-fma: testx86vec-03
	sde64 -mix -ast -- ./$< <sinh.testdata

test-sinh-native-fma: testx86vec-03
	sde64 -mix -ast -- ./$< --use-native <sinh.testdata

test-cosh: testx86vec-03
	$(EXEC) ./$< <cosh.testdata

test-cosh-256: testx86vec-03
	$(EXEC) ./$< --bits-256 <cosh.testdata

test-log: testx86vec-03
	$(EXEC) ./$< <log.testdata

test-log-256: testx86vec-03
	$(EXEC) ./$< --bits-256 <log.testdata

test-log-fma: testx86vec-03
	sde64 -mix -ast -- ./$< <log.testdata

test-asin: testx86vec-03
	$(EXEC) ./$< <asin.testdata

test-acos: testx86vec-03
	$(EXEC) ./$< <acos.testdata

test-atan: testx86vec-03
	$(EXEC) ./$< <atan.testdata


#################################################################
# cleanup 
clean:
	-$(RM) -rf *.i *.o* *.so.*  *.a *.so *.map *.s 
	-$(RM) testx86vec-03 testx86vec-03-g
	-$(RM) testemuvec-03 testemuvec-03-g
	-$(RM) sde*.txt

distclean: clean
	-$(RM) -rf .depend .*.dep* *~


#######################################################################
# dependencies
ifneq ($(wildcard ./.*.dep*),)
include $(wildcard ./.*.dep*)
endif
