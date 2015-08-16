include ../Rules.make
ifeq ($(INSTALLDIR),)
INSTALLDIR=$(HOME)
endif

# Name  of the library
LIBNAME=cftal
MAJOR=0#
MINOR=1#

SLDFLAGS:= $(SLDFLAGS) 
ARCH+=#-mavx -mpopcnt -mavx2 -mfma
CXXFLAGS+=-I.. -march=native #-mavx -mfma -mavx2 #-mavx -mfma -mavx2
CXXFLAGS+=-I.. -march=native -mavx512f -mavx512pf -mavx512er -mavx512cd 
CXXFLAGS+=-fstrict-aliasing -Wstrict-aliasing=1
OPT+=-fno-unroll-loops

CSRCS=mul_div_32.cc mul_div_64.cc d_real.cc math_func.cc x86_ops_1.cc	\
x86_v2f64.cc x86_v4f64.cc x86_v4f32.cc x86_v8f32.cc vec_traits.cc	\
x86_v8f64.cc

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

#emuvec.ol: CXXFLAGS-ol +=-fno-tree-vectorize -mtune=corei7
#emuvec.os: CXXFLAGS-os +=-fno-tree-vectorize -mtune=corei7
#emuvec.od: CXXFLAGS-od +=-fno-tree-vectorize -mtune=corei7
#emuvec.s: CXXFLAGS-os +=-fno-tree-vectorize -mtune=corei7

TESTPROGS=hackx86vec genx86vec hackx86vec_g 

tests: $(TESTPROGS)

testfpvec: testfpvec.ol
	$(LD) -o $@ $< $(LDFLAGS) -lstdc++

genx86vec: genx86vec.ol lib$(LIBNAME).so.$(MAJOR).$(MINOR)
	 $(LD) -o $@ $< $(LDFLAGS) -L. -Wl,-rpath=. -l$(LIBNAME) -lstdc++

#hackx86vec.ol: CXXFLAGS-ol += -fno-tree-vectorize

hackx86vec: hackx86vec.ol lib$(LIBNAME).so.$(MAJOR).$(MINOR)
	$(LD) -o $@ $< $(LDFLAGS) -L. -Wl,-rpath=. -l$(LIBNAME) -lstdc++ -lm

hackx86vec_g: hackx86vec.od lib$(LIBNAME)-g.a
	$(LD) -o $@ $< $(LDFLAGS) -g -L. -l$(LIBNAME)-g -lstdc++ -lm

#x.s: hackx86vec.s x86_v4f64.s x86_v2f64.s
x.s: hackx86vec.s
	c++filt < $< >$@ 
	-$(RM) $<

# Full tests
all-tests: all \
check-00/testx86vec-00 \
check-01/testx86vec-01 \
check-02/testx86vec-02 \
check-03/testx86vec-03
	./check-00/testx86vec-00
	./check-01/testx86vec-01
	./check-02/testx86vec-02
	./check-03/testx86vec-03

check-00/testx86vec-00: all
	$(MAKE) -C check-00

check-01/testx86vec-01: all
	$(MAKE) -C check-01

check-02/testx86vec-02: all
	$(MAKE) -C check-02

check-03/testx86vec-03: all
	$(MAKE) -C check-02


#################################################################
# cleanup
clean:
	-$(RM) -rf *.i *.o* *.so.*  *.a *.so *.map *.s testx86vec
	-$(RM) -rf $(TESTPROGS)
	$(MAKE) -C check-00 $@
	$(MAKE) -C check-01 $@
	$(MAKE) -C check-02 $@
	$(MAKE) -C check-03 $@

distclean: clean
	-$(RM) -rf .depend .*.dep* *~
	$(MAKE) -C check-00 $@
	$(MAKE) -C check-01 $@
	$(MAKE) -C check-02 $@
	$(MAKE) -C check-03 $@

#######################################################################
# dependencies
ifneq ($(wildcard ./.*.dep*),)
include $(wildcard ./.*.dep*)
endif
