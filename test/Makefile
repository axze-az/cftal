include ../../Rules.make
ifeq ($(INSTALLDIR),)
INSTALLDIR=$(HOME)
endif

# Name  of the library
LIBNAME=cftal-test
MAJOR=0#
MINOR=1#

SLDFLAGS:= $(SLDFLAGS) 
CXXFLAGS+= -march=native -I../..
CSRCS=div.cc intops.cc signs.cc #$(wildcard ./test_vec*.cc)

TESTPRGS=gen-test-vec test-intops test-v2 test-v4f32 test-v4s32		\
test-v4u32 test-v8s16 test-v8u16 test-v4f64 test-v4s64 test-v4u64	\
test-v8f32 test-v8s32 test-v8u32
TESTPRGS-DEB=$(addsuffix -g, $(TESTPRGS))

all: $(TESTPRGS) #lib$(LIBNAME).a #testvec-01

debug: $(TESTPRGS-DEB)

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

gen-test-vec: gen-test-vec.ol lib$(LIBNAME).a ../libcftal.a
	$(LD) -o $@ $< $(OPT) $(LDFLAGS) -L. -l$(LIBNAME) -L .. -Wl,-Bstatic -lcftal -Wl,-Bdynamic -lstdc++
	./$@

# use pre compiled headers for the builds
of_vec_v2.h of_vec_v4.h of_vec_v8.h: gen-test-vec

of_vec_v2.h.gch: of_vec_v2.h
	$(CXX) $(CXXFLAGS-o) -c -o $@ $<

of_vec_v4.h.gch: of_vec_v4.h
	$(CXX) $(CXXFLAGS-o) -c -o $@ $<

of_vec_v8.h.gch: of_vec_v8.h
	$(CXX) $(CXXFLAGS-o) -c -o $@ $<

test-v2.ol: of_vec_v2.h.gch 
test-v4f32.ol: of_vec_v4.h.gch 
test-v4s32.ol: of_vec_v4.h.gch 
test-v4u32.ol: of_vec_v4.h.gch 

test-v4f64.ol: of_vec_v4.h.gch 
test-v4u64.ol: of_vec_v4.h.gch 
test-v4s64.ol: of_vec_v4.h.gch 

test-v8f32.ol: of_vec_v8.h.gch 
test-v8s32.ol: of_vec_v8.h.gch 
test-v8u32.ol: of_vec_v8.h.gch 

test-intops: test-intops.ol lib$(LIBNAME).a ../libcftal.a
	$(LD) -o $@ $< $(OPT) $(LDFLAGS) -L. -l$(LIBNAME) -L .. -Wl,-Bstatic -lcftal -Wl,-Bdynamic -lstdc++ 

test-v2: test-v2.ol lib$(LIBNAME).a ../libcftal.a
	$(LD) -o $@ $< $(OPT) $(LDFLAGS) -L. -l$(LIBNAME) -L .. -Wl,-Bstatic -lcftal -Wl,-Bdynamic -lstdc++

test-v2-g: test-v2.od lib$(LIBNAME)-g.a ../libcftal-g.a
	$(LD) -o $@ $< $(DEB) $(LDFLAGS) -L. -l$(LIBNAME)-g -L .. -Wl,-Bstatic -lcftal-g -Wl,-Bdynamic -lstdc++

test-v4f32: test-v4f32.ol lib$(LIBNAME).a ../libcftal.a 
	$(LD) -o $@ $< $(OPT) $(LDFLAGS) -L. -l$(LIBNAME) -L .. -Wl,-Bstatic -lcftal -Wl,-Bdynamic -lstdc++

test-v4f32-g: test-v4f32.od lib$(LIBNAME)-g.a ../libcftal-g.a
	$(LD) -o $@ $< $(DEB) $(LDFLAGS) -L. -l$(LIBNAME)-g -L .. -Wl,-Bstatic -lcftal-g -Wl,-Bdynamic -lstdc++

test-v4s32: test-v4s32.ol lib$(LIBNAME).a ../libcftal.a
	$(LD) -o $@ $< $(OPT) $(LDFLAGS) -L. -l$(LIBNAME) -L .. -Wl,-Bstatic -lcftal -Wl,-Bdynamic -lstdc++

test-v4s32-g: test-v4s32.od lib$(LIBNAME)-g.a ../libcftal-g.a
	$(LD) -o $@ $< $(DEB) $(LDFLAGS) -L. -l$(LIBNAME)-g -L .. -Wl,-Bstatic -lcftal-g -Wl,-Bdynamic -lstdc++

test-v4u32: test-v4u32.ol lib$(LIBNAME).a ../libcftal.a
	$(LD) -o $@ $< $(OPT) $(LDFLAGS) -L. -l$(LIBNAME) -L .. -Wl,-Bstatic -lcftal -Wl,-Bdynamic -lstdc++

test-v4u32-g: test-v4u32.od lib$(LIBNAME)-g.a ../libcftal-g.a
	$(LD) -o $@ $< $(DEB) $(LDFLAGS) -L. -l$(LIBNAME)-g -L .. -Wl,-Bstatic -lcftal-g -Wl,-Bdynamic -lstdc++

test-v8s16: test-v8s16.ol lib$(LIBNAME).a ../libcftal.a
	$(LD) -o $@ $< $(OPT) $(LDFLAGS) -L. -l$(LIBNAME) -L .. -Wl,-Bstatic -lcftal -Wl,-Bdynamic -lstdc++

test-v8s16-g: test-v8s16.od lib$(LIBNAME)-g.a ../libcftal-g.a
	$(LD) -o $@ $< $(DEB) $(LDFLAGS) -L. -l$(LIBNAME)-g -L .. -Wl,-Bstatic -lcftal-g -Wl,-Bdynamic -lstdc++

test-v8u16: test-v8u16.ol lib$(LIBNAME).a ../libcftal.a
	$(LD) -o $@ $< $(OPT) $(LDFLAGS) -L. -l$(LIBNAME) -L .. -Wl,-Bstatic -lcftal -Wl,-Bdynamic -lstdc++

test-v8u16-g: test-v8u16.od lib$(LIBNAME)-g.a ../libcftal-g.a
	$(LD) -o $@ $< $(DEB) $(LDFLAGS) -L. -l$(LIBNAME)-g -L .. -Wl,-Bstatic -lcftal-g -Wl,-Bdynamic -lstdc++

test-v4f64: test-v4f64.ol lib$(LIBNAME).a ../libcftal.a
	$(LD) -o $@ $< $(OPT) $(LDFLAGS) -L. -l$(LIBNAME) -L .. -Wl,-Bstatic -lcftal -Wl,-Bdynamic -lstdc++

test-v4f64-g: test-v4f64.od lib$(LIBNAME)-g.a ../libcftal-g.a
	$(LD) -o $@ $< $(DEB) $(LDFLAGS) -L. -l$(LIBNAME)-g -L .. -Wl,-Bstatic -lcftal-g -Wl,-Bdynamic -lstdc++

test-v4s64: test-v4s64.ol lib$(LIBNAME).a ../libcftal.a
	$(LD) -o $@ $< $(OPT) $(LDFLAGS) -L. -l$(LIBNAME) -L .. -Wl,-Bstatic -lcftal -Wl,-Bdynamic -lstdc++

test-v4s64-g: test-v4s64.od lib$(LIBNAME)-g.a ../libcftal-g.a
	$(LD) -o $@ $< $(DEB) $(LDFLAGS) -L. -l$(LIBNAME)-g -L .. -Wl,-Bstatic -lcftal-g -Wl,-Bdynamic -lstdc++

test-v4u64: test-v4u64.ol lib$(LIBNAME).a ../libcftal.a
	$(LD) -o $@ $< $(OPT) $(LDFLAGS) -L. -l$(LIBNAME) -L .. -Wl,-Bstatic -lcftal -Wl,-Bdynamic -lstdc++

test-v4u64-g: test-v4u64.od lib$(LIBNAME)-g.a ../libcftal-g.a
	$(LD) -o $@ $< $(DEB) $(LDFLAGS) -L. -l$(LIBNAME)-g -L .. -Wl,-Bstatic -lcftal-g -Wl,-Bdynamic -lstdc++

test-v8f32: test-v8f32.ol lib$(LIBNAME).a ../libcftal.a
	$(LD) -o $@ $< $(OPT) $(LDFLAGS) -L. -l$(LIBNAME) -L .. -Wl,-Bstatic -lcftal -Wl,-Bdynamic -lstdc++

test-v8f32-g: test-v8f32.od lib$(LIBNAME)-g.a ../libcftal-g.a
	$(LD) -o $@ $< $(DEB) $(LDFLAGS) -L. -l$(LIBNAME)-g -L .. -Wl,-Bstatic -lcftal-g -Wl,-Bdynamic -lstdc++

test-v8s32: test-v8s32.ol lib$(LIBNAME).a ../libcftal.a
	$(LD) -o $@ $< $(OPT) $(LDFLAGS) -L. -l$(LIBNAME) -L .. -Wl,-Bstatic -lcftal -Wl,-Bdynamic -lstdc++

test-v8s32-g: test-v8s32.od lib$(LIBNAME)-g.a ../libcftal-g.a
	$(LD) -o $@ $< $(DEB) $(LDFLAGS) -L. -l$(LIBNAME)-g -L .. -Wl,-Bstatic -lcftal-g -Wl,-Bdynamic -lstdc++

test-v8u32: test-v8u32.ol lib$(LIBNAME).a ../libcftal.a
	$(LD) -o $@ $< $(OPT) $(LDFLAGS) -L. -l$(LIBNAME) -L .. -Wl,-Bstatic -lcftal -Wl,-Bdynamic -lstdc++

test-v8u32-g: test-v8u32.od lib$(LIBNAME)-g.a ../libcftal-g.a
	$(LD) -o $@ $< $(DEB) $(LDFLAGS) -L. -l$(LIBNAME)-g -L .. -Wl,-Bstatic -lcftal-g -Wl,-Bdynamic -lstdc++


#################################################################
# cleanup 
clean:
	-$(RM) -rf *.i *.o* *.so.*  *.a *.so *.map *.s *.gch
	-$(RM) $(TESTPRGS) $(TESTPRGS-DEB)

distclean: clean
	-$(RM) -rf .depend .*.dep* *~


#######################################################################
# dependencies
ifneq ($(wildcard ./.*.dep*),)
include $(wildcard ./.*.dep*)
endif
