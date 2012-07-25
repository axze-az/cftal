include ../Rules.make
ifeq ($(INSTALLDIR),)
INSTALLDIR=$(HOME)
endif

# Name  of the library
LIBNAME=cftal
MAJOR=0#
MINOR=1#

SLDFLAGS:= $(SLDFLAGS) 
#ARCH=#-march=bdver1 -mxop #-march=bdver1 #-mdispatch-scheduler
ARCH+=#-no-sse3
CXXFLAGS+=-I.. -I../stlex -I../thread  -I../sysio -march=native

CSRCS=heap_array.cc x86vec_ops_1.cc x86vec_test.cc emuvec.cc

all: lib tests

lib: lib$(LIBNAME).so.$(MAJOR).$(MINOR) lib$(LIBNAME).a lib$(LIBNAME)-g.a

install: install-static install-shared install-debug install-header

###########################################################################
# Installation of the header files
install-header:
	mkdir -p $(INSTALLDIR)/include/cftal
	for i in *.h ; \
	do \
		if [ -f $$i ] ; then \
			$(INSTALL) -c -m 0644 $$i $(INSTALLDIR)/include/cftal	 ; \
		fi ; \
	done

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


###########################################################################
# Shared library
lib$(LIBNAME).so.$(MAJOR).$(MINOR): $(PICOBJS)
	$(SLD) -Wl,-hlib$(LIBNAME).so.$(MAJOR) \
$(SHAREDLIBS) $(SLDFLAGS) \
-Wl,-Map -Wl,lib$(LIBNAME).map \
-o $@ $(PICOBJS) -lm
	-$(RM) lib$(LIBNAME).so
	-ln -sf lib$(LIBNAME).so.$(MAJOR).$(MINOR) ./lib$(LIBNAME).so.$(MAJOR)
	-ln -sf lib$(LIBNAME).so.$(MAJOR) lib$(LIBNAME).so

install-shared: lib$(LIBNAME).so.$(MAJOR).$(MINOR)
	mkdir -p $(INSTALLDIR)/lib
	$(INSTALL) -m 0755 lib$(LIBNAME).so.$(MAJOR).$(MINOR) $(INSTALLDIR)/lib
	cd $(INSTALLDIR)/lib && \
ln -sf lib$(LIBNAME).so.$(MAJOR).$(MINOR) lib$(LIBNAME).so.$(MAJOR)
	cd $(INSTALLDIR)/lib && \
ln -sf lib$(LIBNAME).so.$(MAJOR) lib$(LIBNAME).so

emuvec.ol: CXXFLAGS-ol +=-fno-tree-vectorize -mtune=atom
emuvec.os: CXXFLAGS-os +=-fno-tree-vectorize -mtune=atom
emuvec.od: CXXFLAGS-od +=-fno-tree-vectorize -mtune=atom
emuvec.s: CXXFLAGS-os +=-fno-tree-vectorize -mtune=atom

TESTPROGS=hackx86vec genx86vec hackx86vec_g rcp_div rcp_div_g
tests: $(TESTPROGS)

testfpvec: testfpvec.ol
	$(LD) -o $@ $< $(LDFLAGS) -lstdc++

genx86vec: genx86vec.ol x86vec_test.ol
	$(LD) -o $@ $^ $(LDFLAGS) -lstdc++

hackx86vec: hackx86vec.ol x86vec_test.ol
	$(LD) -o $@ $^ $(LDFLAGS) -L. -Wl,-rpath=. -l$(LIBNAME) -lstdc++

hackx86vec_g: hackx86vec.od x86vec_test.od lib$(LIBNAME)-g.a
	$(LD) -o $@ $^ $(LDFLAGS) -g -L. -l$(LIBNAME)-g -lstdc++

rcp_div: rcp_div.ol x86vec_test.ol
	$(LD) -o $@ $^ $(LDFLAGS) -L. -Wl,-rpath=. -l$(LIBNAME) -lstdc++

rcp_div_g: rcp_div.od x86vec_test.od lib$(LIBNAME)-g.a
	$(LD) -o $@ $^ $(LDFLAGS) -g -L. -l$(LIBNAME)-g -lstdc++


# Full tests
all-tests: all \
check-00/testx86vec-00 \
check-01/testx86vec-01 \
check-02/testx86vec-02
	./check-00/testx86vec-00
	./check-01/testx86vec-01
	./check-02/testx86vec-02

check-00/testx86vec-00: all
	$(MAKE) -C check-00

check-01/testx86vec-01: all
	$(MAKE) -C check-01

check-02/testx86vec-02: all
	$(MAKE) -C check-02


#################################################################
# cleanup
clean:
	-$(RM) -rf *.i *.o* *.so.*  *.a *.so *.map *.s testx86vec
	-$(RM) -rf $(TESTPROGS)
	$(MAKE) -C check-00 $@
	$(MAKE) -C check-01 $@
	$(MAKE) -C check-02 $@

distclean: clean
	-$(RM) -rf .depend .*.dep* *~
	$(MAKE) -C check-00 $@
	$(MAKE) -C check-01 $@
	$(MAKE) -C check-02 $@

#######################################################################
# dependencies
ifneq ($(wildcard ./.*.dep*),)
include $(wildcard ./.*.dep*)
endif
