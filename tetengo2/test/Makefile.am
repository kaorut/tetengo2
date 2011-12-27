# Automake Settings
# Copyright (C) 2007-2011 kaoru
# $Id$

headers =

extra_headers =

sources = \
    master.cpp \
    test_tetengo2.concurrent.channel.cpp \
    test_tetengo2.concurrent.consumer.cpp \
    test_tetengo2.concurrent.producer.cpp \
    test_tetengo2.gui.common_dialog.file_open.cpp \
    test_tetengo2.message.messages.cpp \
    test_tetengo2.message.message_catalog.cpp \
    test_tetengo2.message.message_catalog_parser.cpp \
    test_tetengo2.meta.assoc_list.cpp \
    test_tetengo2.operators.cpp \
    test_tetengo2.text.cpp \
    test_tetengo2.text.encoder.cpp \
    test_tetengo2.text.encoding.encoding.cpp \
    test_tetengo2.text.encoding.ascii.cpp \
    test_tetengo2.text.encoding.locale.cpp \
    test_tetengo2.text.encoding.utf8.cpp \
    test_tetengo2.text.grammar.json.cpp \
    test_tetengo2.text.pull_parser.cpp \
    test_tetengo2.text.push_parser.cpp \
    test_tetengo2.unique.cpp

extra_sources =

BUILT_SOURCES = $(PRECOMPILE_BUILT_SOURCES)

check_PROGRAMS = tetengo2.test
EXTRA_DIST = $(extra_headers) $(extra_sources)

TESTS = tetengo2.test

tetengo2_test_DEPENDENCIES = \
    messages.test
tetengo2_test_CPPFLAGS = \
    $(PRECOMPILE_CPPFLAGS) \
    $(BOOST_CPPFLAGS) \
    -I$(top_srcdir)/tetengo2/include \
    -I$(top_srcdir)/tetengo2_detail/include
tetengo2_test_LDFLAGS = $(BOOST_LDFLAGS)
tetengo2_test_LDADD = \
    $(BOOST_DATE_TIME_LIB) \
    $(BOOST_FILESYSTEM_LIB) \
    $(BOOST_PROGRAM_OPTIONS_LIB) \
    $(BOOST_SYSTEM_LIB) \
    $(BOOST_THREAD_LIB) \
    $(BOOST_UNIT_TEST_FRAMEWORK_LIB)
tetengo2_test_SOURCES = $(headers) $(sources)

messages.test:
	cp -r $(top_srcdir)/tetengo2/res.test/messages.test .

clean-local:
	-rm -rf messages.test

$(top_srcdir)/precompiled/precompiled.h.gch: $(top_srcdir)/precompiled/precompiled.h
	pushd $(top_srcdir)/precompiled; $(MAKE) all; popd

