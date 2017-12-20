# Automake Settings
# Copyright (C) 2007-2017 kaoru
# $Id$

headers =

extra_headers =

sources = \
    tetengo2.concurrent.progressive_future.cpp \
    tetengo2.config.cached_config.cpp \
    tetengo2.config.config_base.cpp \
    tetengo2.config.config_list.cpp \
    tetengo2.config.persistent_config.cpp \
    tetengo2.config.temporary_config.cpp \
    tetengo2.message.message_catalog.cpp \
    tetengo2.message.message_catalog_parser.cpp \
    tetengo2.message.messages.cpp \
    tetengo2.text.character_iterator.cpp \
    tetengo2.text.encoding.ascii.cpp \
    tetengo2.text.encoding.cp932.cpp \
    tetengo2.text.encoding.encoding.cpp \
    tetengo2.text.encoding.locale.cpp \
    tetengo2.text.encoding.polymorphic.cpp \
    tetengo2.text.encoding.utf8.cpp \
    tetengo2.text.grammar.grammar.cpp \
    tetengo2.text.grammar.json.cpp \
    tetengo2.text.pull_parser.cpp \
    tetengo2.text.push_parser.cpp

extra_sources =

BUILT_SOURCES = $(PRECOMPILE_BUILT_SOURCES)

lib_LIBRARIES = libtetengo2.a
EXTRA_DIST = $(extra_headers) $(extra_sources)

libtetengo2_a_CPPFLAGS = \
    -I$(top_srcdir)/tetengo2/include \
    -I$(top_srcdir)/tetengo2_detail/include
libtetengo2_a_SOURCES = $(headers) $(sources)

IWYU_OPTS += -Xiwyu --mapping_file=$(top_srcdir)/$(IWYU_IMP_PATH)

lint-iwyu:
	for f in $(headers) $(sources); \
	do \
	    echo "iwyu: "$$f; \
	    $(IWYU) $(IWYU_OPTS) $(CPPFLAGS) $(libtetengo2_a_CPPFLAGS) $(CXXFLAGS) $$f || test $$? -eq 2; \
	done

$(top_builddir)/precompiled/precompiled.h.$(PRECOMPILE_EXT): $(top_srcdir)/precompiled/precompiled.h
	pushd $(top_builddir)/precompiled; \
	$(MAKE) all; \
	popd
