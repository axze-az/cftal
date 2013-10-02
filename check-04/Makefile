include ../../Rules.make
ifeq ($(INSTALLDIR),)
INSTALLDIR=$(HOME)
endif

# Name  of the library
LIBNAME=checkx86vec-04
MAJOR=0#
MINOR=1#

SLDFLAGS:= $(SLDFLAGS) -L../sysio -lsysio++ -L../thread -lthread++
ARCH+=-march=native
CXXFLAGS+=-I. -I.. -I../.. -I../stlex -I../thread  -I../sysio -march=native
CSRCS=$(wildcard ./x86vec_test_*.cc)

all: testx86vec-04

debug: testx86vec-04-g

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

testx86vec-04: testx86vec-04.ol lib$(LIBNAME).a ../libcftal.a
	$(LD) -o $@ $< $(OPT) $(LDFLAGS) -L. -l$(LIBNAME) -L ..	\
-Wl,-Bstatic -lcftal -Wl,-Bdynamic -lstdc++ -lm

testx86vec-04-g: testx86vec-04.od lib$(LIBNAME)-g.a ../libcftal-g.a
	$(LD) -o $@ $< $(DEB) $(LDFLAGS) -L. -l$(LIBNAME)-g -L .. \
-Wl,-Bstatic -lcftal-g -Wl,-Bdynamic -lstdc++ -lm

# rcp_div: rcp_div.ol lib$(LIBNAME).so.$(MAJOR).$(MINOR)
# 	$(LD) -o $@ $< $(LDFLAGS) -L. -Wl,-rpath=. -l$(LIBNAME) -lstdc++

# rcp_div_g: rcp_div.od lib$(LIBNAME)-g.a
# 	$(LD) -o $@ $< $(LDFLAGS) -g -L. -l$(LIBNAME)-g -lstdc++

# rcp_div_64: rcp_div_64.ol lib$(LIBNAME).so.$(MAJOR).$(MINOR)
# 	$(LD) -o $@ $< $(LDFLAGS) -L. -Wl,-rpath=. -l$(LIBNAME) -lstdc++

# rcp_div_64_g: rcp_div_64.od lib$(LIBNAME)-g.a
# 	$(LD) -o $@ $< $(LDFLAGS) -g -L. -l$(LIBNAME)-g -lstdc++



#################################################################
# cleanup 
clean:
	-$(RM) -rf *.i *.o* *.so.*  *.a *.so *.map *.s 
	-$(RM) testfpvec testx86vec-04 testx86vec-04-g

distclean: clean
	-$(RM) -rf .depend .*.dep* *~


#######################################################################
# dependencies
ifneq ($(wildcard ./.*.dep*),)
include $(wildcard ./.*.dep*)
endif
