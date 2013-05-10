include ../../Rules.make
ifeq ($(INSTALLDIR),)
INSTALLDIR=$(HOME)
endif

# Name  of the library
LIBNAME=checkx86vec-03
MAJOR=0#
MINOR=1#

SLDFLAGS:= $(SLDFLAGS) -L../sysio -lsysio++ -L../thread -lthread++
CXXFLAGS+=-I. -I.. -I../.. -I../stlex -I../thread  -I../sysio -march=native
CSRCS=$(wildcard ./x86vec_test_*.cc ./bitops_test.cc d_int8_test.cc)

all: testx86vec-03 

debug: testx86vec-03-g

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
	$(LD) -o $@ $< $(OPT) $(LDFLAGS) -L. -l$(LIBNAME) -L .. -Wl,-Bstatic -lcftal -Wl,-Bdynamic -lstdc++

testx86vec-03-g: testx86vec-03.od lib$(LIBNAME)-g.a ../libcftal-g.a
	$(LD) -o $@ $< $(DEB) $(LDFLAGS) -L. -l$(LIBNAME)-g -L .. -Wl,-Bstatic -lcftal-g -Wl,-Bdynamic -lstdc++

# rcp_div: rcp_div.ol lib$(LIBNAME).so.$(MAJOR).$(MINOR)
# 	$(LD) -o $@ $< $(LDFLAGS) -L. -Wl,-rpath=. -l$(LIBNAME) -lstdc++

# rcp_div_g: rcp_div.od lib$(LIBNAME)-g.a
# 	$(LD) -o $@ $< $(LDFLAGS) -g -L. -l$(LIBNAME)-g -lstdc++

# rcp_div_64: rcp_div_64.ol lib$(LIBNAME).so.$(MAJOR).$(MINOR)
# 	$(LD) -o $@ $< $(LDFLAGS) -L. -Wl,-rpath=. -l$(LIBNAME) -lstdc++

# rcp_div_64_g: rcp_div_64.od lib$(LIBNAME)-g.a
# 	$(LD) -o $@ $< $(LDFLAGS) -g -L. -l$(LIBNAME)-g -lstdc++

test-sin: testx86vec-03
	./$< <sin.testdata

test-cos: testx86vec-03
	./$< <cos.testdata

test-tan: testx86vec-03
	./$< <tan.testdata

test-exp: testx86vec-03
	./$< <exp.testdata

test-exp-native: testx86vec-03
	./$< --use-native  <exp.testdata

test-exp-fma: testx86vec-03
	sde64 -mix -ast -- ./$< <exp.testdata

test-exp-native-fma: testx86vec-03
	sde64 -mix -ast -- ./$< --use-native <exp.testdata

test-cosh: testx86vec-03
	./$< <cosh.testdata

test-log: testx86vec-03
	./$< <log.testdata

test-log-fma: testx86vec-03
	sde64 -mix -ast -- ./$< <log.testdata

test-asin: testx86vec-03
	./$< <asin.testdata

test-acos: testx86vec-03
	./$< <acos.testdata

test-atan: testx86vec-03
	./$< <atan.testdata


#################################################################
# cleanup 
clean:
	-$(RM) -rf *.i *.o* *.so.*  *.a *.so *.map *.s 
	-$(RM) testx86vec-03 testx86vec-03-g

distclean: clean
	-$(RM) -rf .depend .*.dep* *~


#######################################################################
# dependencies
ifneq ($(wildcard ./.*.dep*),)
include $(wildcard ./.*.dep*)
endif
