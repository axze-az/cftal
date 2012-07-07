include ../../Rules.make
ifeq ($(INSTALLDIR),)
INSTALLDIR=$(HOME)
endif

# Name  of the library
LIBNAME=checkx86vec-00
MAJOR=0#
MINOR=1#

SLDFLAGS:= $(SLDFLAGS) -L../sysio -lsysio++ -L../thread -lthread++
CXXFLAGS+=-I. -I.. -I../stlex -I../thread  -I../sysio -march=native
CSRCS=$(wildcard ./x86vec_test*.cc)

all: testx86vec-00

debug: testx86vec-g

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

testx86vec-00: testx86vec-00.ol lib$(LIBNAME).a
	$(LD) -o $@ $< $(OPT) $(LDFLAGS) -L. -l$(LIBNAME) -L .. -Wl,-Bstatic -lmath++ -Wl,-Bdynamic -lstdc++

testx86vec-00-g: testx86vec-00.od lib$(LIBNAME)-g.a
	$(LD) -o $@ $< $(DEB) $(LDFLAGS) -L. -l$(LIBNAME)-g -L .. -Wl,-Bstatic -lmath++-g -Wl,-Bdynamic -lstdc++


#################################################################
# cleanup 
clean:
	-$(RM) -rf *.i *.o* *.so.*  *.a *.so *.map *.s 
	-$(RM) testfpvec testx86vec-00 testx86vec-00-g

distclean: clean
	-$(RM) -rf .depend .*.dep* *~


#######################################################################
# dependencies
ifneq ($(wildcard ./.*.dep*),)
include $(wildcard ./.*.dep*)
endif
