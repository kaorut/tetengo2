# Automake Settings
# Copyright (C) 2007-2016 kaoru
# $Id$

headers =

extra_headers =

sources = \
    tetengo2.detail.base.config.cpp

extra_sources =

BUILT_SOURCES = $(PRECOMPILE_BUILT_SOURCES)

lib_LIBRARIES = libtetengo2_detail.a
EXTRA_DIST = $(extra_headers) $(extra_sources)

libtetengo2_detail_a_CPPFLAGS = \
    -I$(top_srcdir)/tetengo2/include
libtetengo2_detail_a_SOURCES = $(headers) $(sources)

$(top_builddir)/precompiled/precompiled.h.gch: $(top_srcdir)/precompiled/precompiled.h
	pushd $(top_builddir)/precompiled; \
	$(MAKE) all; \
	popd
