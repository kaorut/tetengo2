# Automake Settings
# Copyright (C) 2007-2012 kaoru
# $Id$

headers = \
    test_bobura.model.type_list.h

extra_headers =

sources = \
    master.cpp \
    test_bobura.model.message.timetable_observer_set.cpp \
    test_bobura.model.serializer.bzip2_reader.cpp \
    test_bobura.model.serializer.bzip2_writer.cpp \
    test_bobura.model.serializer.json_reader.cpp \
    test_bobura.model.serializer.json_writer.cpp \
    test_bobura.model.serializer.reader.cpp \
    test_bobura.model.serializer.reader_selector.cpp \
    test_bobura.model.serializer.reader_set.cpp \
    test_bobura.model.serializer.writer.cpp \
    test_bobura.model.serializer.writer_selector.cpp \
    test_bobura.model.serializer.writer_set.cpp \
    test_bobura.model.station.cpp \
    test_bobura.model.station_info.grade.cpp \
    test_bobura.model.timetable.cpp \
    test_bobura.model.timetable_info.station_interval_calculator.cpp \
    test_bobura.model.timetable_info.station_location.cpp \
    test_bobura.model.timetable_info.train_kind_list.cpp \
    test_bobura.model.train.cpp \
    test_bobura.model.train_info.stop.cpp \
    test_bobura.model.train_info.time.cpp \
    test_bobura.model.train_info.time_span.cpp \
    test_bobura.model.train_kind.cpp

extra_sources =

BUILT_SOURCES = $(PRECOMPILE_BUILT_SOURCES)

check_PROGRAMS = bobura_model.test
EXTRA_DIST = $(extra_headers) $(extra_sources)

TESTS = bobura_model.test

bobura_model_test_CPPFLAGS = \
    $(PRECOMPILE_CPPFLAGS) \
    $(BOOST_CPPFLAGS) \
    -I$(top_srcdir)/bobura_model/include \
    -I$(top_srcdir)/tetengo2/include \
    -I$(top_srcdir)/tetengo2_detail/include
bobura_model_test_LDFLAGS = $(BOOST_LDFLAGS)
bobura_model_test_LDADD = \
    $(BOOST_FILESYSTEM_LIB) \
    $(BOOST_IOSTREAMS_LIB) \
    $(BOOST_PROGRAM_OPTIONS_LIB) \
    $(BOOST_SYSTEM_LIB) \
    $(BOOST_THREAD_LIB) \
    $(BOOST_UNIT_TEST_FRAMEWORK_LIB)
bobura_model_test_SOURCES = $(headers) $(sources)

$(top_srcdir)/precompiled/precompiled.h.gch: $(top_srcdir)/precompiled/precompiled.h
	pushd $(top_srcdir)/precompiled; $(MAKE) all; popd

