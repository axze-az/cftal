## Makefile for the x86_64 directory of the libgcc-math library.
##
## Copyright (C) 2005
## Free Software Foundation, Inc.
##

# May be used by various substitution variables.
gcc_version := $(shell cat $(top_srcdir)/../gcc/BASE-VER)


noinst_LTLIBRARIES = libmv.la

libmv_la_SOURCES = \
  libm_util_amd.h \
  vrd2cos.s vrd2sincos.s vrd2exp.s vrd2sin.s vrd2log10.s vrd2log2.s vrd2log.s \
  vrd4log2.s vrd4log.s vrd4cos.s vrd4sin.s vrd4exp.s vrd4log10.s \
  vrs4log10f.s vrs4sincosf.s vrs4log2f.s vrs4sinf.s vrs4logf.s vrs4cosf.s \
  vrs4powf.s vrs4expf.s vrs4powxf.s \
  vrs8logf.s vrs8expf.s vrs8log10f.s vrs8log2f.s \
  remainder_piby2.c remainder_piby2d2f.c


# XXX hack alert
# From libffi/Makefile.am

# Work around what appears to be a GNU make bug handling MAKEFLAGS
# values defined in terms of make variables, as is the case for CC and
# friends when we are called from the top level Makefile.
AM_MAKEFLAGS = \
	"AR_FLAGS=$(AR_FLAGS)" \
	"CC_FOR_BUILD=$(CC_FOR_BUILD)" \
	"CFLAGS=$(CFLAGS)" \
	"CXXFLAGS=$(CXXFLAGS)" \
	"CFLAGS_FOR_BUILD=$(CFLAGS_FOR_BUILD)" \
	"CFLAGS_FOR_TARGET=$(CFLAGS_FOR_TARGET)" \
	"INSTALL=$(INSTALL)" \
	"INSTALL_DATA=$(INSTALL_DATA)" \
	"INSTALL_PROGRAM=$(INSTALL_PROGRAM)" \
	"INSTALL_SCRIPT=$(INSTALL_SCRIPT)" \
	"JC1FLAGS=$(JC1FLAGS)" \
	"LDFLAGS=$(LDFLAGS)" \
	"LIBCFLAGS=$(LIBCFLAGS)" \
	"LIBCFLAGS_FOR_TARGET=$(LIBCFLAGS_FOR_TARGET)" \
	"MAKE=$(MAKE)" \
	"MAKEINFO=$(MAKEINFO) $(MAKEINFOFLAGS)" \
	"PICFLAG=$(PICFLAG)" \
	"PICFLAG_FOR_TARGET=$(PICFLAG_FOR_TARGET)" \
	"SHELL=$(SHELL)" \
	"RUNTESTFLAGS=$(RUNTESTFLAGS)" \
	"exec_prefix=$(exec_prefix)" \
	"infodir=$(infodir)" \
	"libdir=$(libdir)" \
	"prefix=$(prefix)" \
	"includedir=$(includedir)" \
	"AR=$(AR)" \
	"AS=$(AS)" \
	"CC=$(CC)" \
	"CXX=$(CXX)" \
	"LD=$(LD)" \
	"LIBCFLAGS=$(LIBCFLAGS)" \
	"NM=$(NM)" \
	"PICFLAG=$(PICFLAG)" \
	"RANLIB=$(RANLIB)" \
	"DESTDIR=$(DESTDIR)"

MAKEOVERRIDES=

## ################################################################

