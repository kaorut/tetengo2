# Automake Settings
# Copyright (C) 2007-2016 kaoru
# $Id$

headers = \
    test_tetengo2.detail_type_list.h \
    test_tetengo2.type_list.h

extra_headers =

sources = \
    master.cpp \
    test_tetengo2.concurrent.channel.cpp \
    test_tetengo2.concurrent.consumer.cpp \
    test_tetengo2.concurrent.producer.cpp \
    test_tetengo2.concurrent.progressive_future.cpp \
    test_tetengo2.concurrent.progressive_promise.cpp \
    test_tetengo2.config.cached_config.cpp \
    test_tetengo2.config.config_base.cpp \
    test_tetengo2.config.config_list.cpp \
    test_tetengo2.config.persistent_config.cpp \
    test_tetengo2.config.temporary_config.cpp \
    test_tetengo2.message.messages.cpp \
    test_tetengo2.message.message_catalog.cpp \
    test_tetengo2.message.message_catalog_parser.cpp \
    test_tetengo2.meta.assoc_list.cpp \
    test_tetengo2.observable_forward_iterator.cpp \
    test_tetengo2.text.cpp \
    test_tetengo2.text.encoder.cpp \
    test_tetengo2.text.encoding.encoding.cpp \
    test_tetengo2.text.encoding.ascii.cpp \
    test_tetengo2.text.encoding.cp932.cpp \
    test_tetengo2.text.encoding.locale.cpp \
    test_tetengo2.text.encoding.utf8.cpp \
    test_tetengo2.text.grammar.json.cpp \
    test_tetengo2.text.pull_parser.cpp \
    test_tetengo2.text.push_parser.cpp

extra_sources =

BUILT_SOURCES = $(PRECOMPILE_BUILT_SOURCES)

check_PROGRAMS = tetengo2.test
EXTRA_DIST = $(extra_headers) $(extra_sources)

TESTS = tetengo2.test

tetengo2_test_DEPENDENCIES = \
    $(top_builddir)/tetengo2/src/libtetengo2.a \
    messages.test
tetengo2_test_CPPFLAGS = \
    -I$(top_srcdir)/tetengo2/include \
    -I$(top_srcdir)/tetengo2_detail/include
tetengo2_test_LDFLAGS = \
    -L$(top_builddir)/tetengo2/src
tetengo2_test_LDADD = \
    -ltetengo2 \
    $(UNITTEST_LIBS)
tetengo2_test_SOURCES = $(headers) $(sources)

messages.test:
	cp -r $(top_srcdir)/tetengo2/res.test/messages.test $(top_builddir)/tetengo2/test

clean-local:
	-chmod -R u+w $(top_builddir)/tetengo2/test/messages.test
	-rm -rf $(top_builddir)/tetengo2/test/messages.test

$(top_builddir)/precompiled/precompiled.h.gch: $(top_srcdir)/precompiled/precompiled.h
	pushd $(top_builddir)/precompiled; \
	$(MAKE) all; \
	popd

$(top_builddir)/tetengo2/src/libtetengo2.a:
	pushd $(top_builddir)/tetengo2/src; \
	$(MAKE) all; \
	popd
