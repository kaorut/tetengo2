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
    tetengo2.detail.base.gui_fixture.cpp \
    tetengo2.detail.base.impl_set.cpp \
    tetengo2.detail.base.unit.cpp \
    tetengo2.detail.stub.alert.cpp \
    tetengo2.detail.stub.cursor.cpp \
    tetengo2.detail.stub.gui_fixture.cpp \
    tetengo2.detail.stub.impl_set.cpp \
    tetengo2.detail.stub.unit.cpp \
    tetengo2.detail.unixos.config.cpp \
    tetengo2.detail.unixos.encoding.cpp \
    tetengo2.detail.unixos.impl_set.cpp

extra_sources = \
    tetengo2.detail.windows.alert.cpp \
    tetengo2.detail.windows.config.cpp \
    tetengo2.detail.windows.cursor.cpp \
    tetengo2.detail.windows.direct2d.error_category.cpp \
    tetengo2.detail.windows.encoding.cpp \
    tetengo2.detail.windows.error_category.cpp \
    tetengo2.detail.windows.font.cpp \
    tetengo2.detail.windows.gdiplus.error_category.cpp \
    tetengo2.detail.windows.gdiplus.gui_fixture.cpp \
    tetengo2.detail.windows.gui_fixture.cpp \
    tetengo2.detail.windows.impl_set.cpp \
    tetengo2.detail.windows.unit.cpp

BUILT_SOURCES = $(PRECOMPILE_BUILT_SOURCES)

lib_LIBRARIES = libtetengo2_detail.a
EXTRA_DIST = $(extra_headers) $(extra_sources)

libtetengo2_detail_a_CPPFLAGS = \
    -I$(top_srcdir)/tetengo2/include \
    -I$(top_srcdir)/tetengo2_detail/include \
    -I$(top_srcdir)/tetengo2_gui/include
libtetengo2_detail_a_SOURCES = $(headers) $(sources)

lint-iwyu:
	for f in $(headers) $(sources); \
	do \
	    echo "iwyu: "$$f; \
	    $(IWYU) -Xiwyu --mapping_file=$(top_srcdir)/tools/iwyu_mappings.imp -Xiwyu --max_line_length=1024 -x c++ $(CPPFLAGS) $(libtetengo2_detail_a_CPPFLAGS) $(CXXFLAGS) $$f; \
	done

$(top_builddir)/precompiled/precompiled.h.$(PRECOMPILE_EXT): $(top_srcdir)/precompiled/precompiled.h
	pushd $(top_builddir)/precompiled; \
	$(MAKE) all; \
	popd
