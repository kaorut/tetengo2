# Automake Settings
# Copyright (C) 2007-2017 kaoru
# $Id$

headers =

extra_headers =

sources = \
    tetengo2.gui.alert.cpp \
    tetengo2.gui.cursor.cursor_base.cpp \
    tetengo2.gui.cursor.system.cpp \
    tetengo2.gui.dimension.cpp \
    tetengo2.gui.fixture.cpp \
    tetengo2.gui.position.cpp \
    tetengo2.gui.unit.em.cpp \
    tetengo2.gui.unit.pixel.cpp \
    tetengo2.gui.unit.point.cpp

extra_sources =

BUILT_SOURCES = $(PRECOMPILE_BUILT_SOURCES)

lib_LIBRARIES = libtetengo2_gui.a
EXTRA_DIST = $(extra_headers) $(extra_sources)

libtetengo2_gui_a_CPPFLAGS = \
    -I$(top_srcdir)/tetengo2/include \
    -I$(top_srcdir)/tetengo2_detail/include \
    -I$(top_srcdir)/tetengo2_gui/include
libtetengo2_gui_a_SOURCES = $(headers) $(sources)

IWYU_OPTS += -Xiwyu --mapping_file=$(top_srcdir)/$(IWYU_IMP_PATH)

lint-iwyu:
	for f in $(headers) $(sources); \
	do \
	    echo "iwyu: "$(srcdir)/$$f; \
	    $(IWYU) $(IWYU_OPTS) $(CPPFLAGS) $(libtetengo2_gui_a_CPPFLAGS) $(CXXFLAGS) $(srcdir)/$$f || test $$? -eq 2; \
	done

lint-iwyu-extra:
	for f in $(extra_headers) $(extra_sources); \
	do \
	    echo "iwyu: "$(srcdir)/$$f; \
	    $(IWYU) $(IWYU_OPTS) $(CPPFLAGS) $(libtetengo2_gui_a_CPPFLAGS) $(CXXFLAGS) $(srcdir)/$$f || test $$? -eq 2; \
	done

$(top_builddir)/precompiled/precompiled.h.$(PRECOMPILE_EXT): $(top_srcdir)/precompiled/precompiled.h
	pushd $(top_builddir)/precompiled; \
	$(MAKE) all; \
	popd
