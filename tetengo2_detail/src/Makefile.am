# Automake Settings
# Copyright (C) 2007-2017 kaoru
# $Id$

headers =

extra_headers =

sources = \
    tetengo2.detail.base.alert.cpp \
    tetengo2.detail.base.config.cpp \
    tetengo2.detail.base.cursor.cpp \
    tetengo2.detail.base.encoding.cpp \
    tetengo2.detail.stub.alert.cpp \
    tetengo2.detail.stub.cursor.cpp \
    tetengo2.detail.unixos.config.cpp \
    tetengo2.detail.unixos.encoding.cpp

extra_sources = \
    tetengo2.detail.windows.alert.cpp \
    tetengo2.detail.windows.config.cpp \
    tetengo2.detail.windows.cursor.cpp \
    tetengo2.detail.windows.encoding.cpp

BUILT_SOURCES = $(PRECOMPILE_BUILT_SOURCES)

lib_LIBRARIES = libtetengo2_detail.a
EXTRA_DIST = $(extra_headers) $(extra_sources)

libtetengo2_detail_a_CPPFLAGS = \
    -I$(top_srcdir)/tetengo2/include \
    -I$(top_srcdir)/tetengo2_detail/include
libtetengo2_detail_a_SOURCES = $(headers) $(sources)

$(top_builddir)/precompiled/precompiled.h.$(PRECOMPILE_EXT): $(top_srcdir)/precompiled/precompiled.h
	pushd $(top_builddir)/precompiled; \
	$(MAKE) all; \
	popd
