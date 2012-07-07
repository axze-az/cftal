include ../Rules.make
ifeq ($(INSTALLDIR),)
INSTALLDIR=$(HOME)
endif

# Name  of the library
LIBNAME=cftal
MAJOR=0#
MINOR=1#

SLDFLAGS:= $(SLDFLAGS) -L../sysio -lsysio++ -L../thread -lthread++
#ARCH=#-march=bdver1 -mxop #-march=bdver1 #-mdispatch-scheduler
ARCH+=#-mno-sse4
CXXFLAGS+=-I.. -I../stlex -I../thread  -I../sysio -march=native

#CSRCS=solver_stats.cc exception.cc ex_overflow.cc ex_div_by_zero.cc	\
#ex_invalid_op.cc real16.cc real8.cc real4.cc fpvec.cc
CSRCS=fpvec.cc x86vec_ops_1.cc x86vec_test.cc

all: lib tests

lib: lib$(LIBNAME).so.$(MAJOR).$(MINOR) lib$(LIBNAME).a lib$(LIBNAME)-g.a

install: install-static install-shared install-debug install-header

###########################################################################
# Installation of the header files
install-header:
	mkdir -p $(INSTALLDIR)/include
	for i in *.h ; \
	do \
		if [ -f $$i ] ; then \
			$(INSTALL) -c -m 0644 $$i $(INSTALLDIR)/include ; \
		fi ; \
	done
	mkdir -p $(INSTALLDIR)/include/inlines
	for i in ./inlines/* ; \
	do \
		if [ -f $$i ] ; then \
			$(INSTALL) -c -m 0644 $$i  $(INSTALLDIR)/include/inlines ; \
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


tests: hackx86vec genx86vec hackx86vec_g


testfpvec: testfpvec.ol
	$(LD) -o $@ $< $(LDFLAGS) -lstdc++

genx86vec: genx86vec.ol x86vec_test.ol
	$(LD) -o $@ $^ $(LDFLAGS) -lstdc++

hackx86vec: hackx86vec.ol x86vec_test.ol
	$(LD) -o $@ $^ $(LDFLAGS) -lstdc++

hackx86vec_g: hackx86vec.od x86vec_test.od
	$(LD) -o $@ $^ $(LDFLAGS) -g -lstdc++

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
	-$(RM) -rf *.i *.o* *.so.*  *.a *.so *.map *.s testfpvec testx86vec
	-$(RM) -rf genx86vec hackx86vec
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
