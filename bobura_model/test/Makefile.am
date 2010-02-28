# Automake Settings
# Copyright (C) 2007-2010 kaoru
# $Id$

headers =

extra_headers =

sources = \
    master.cpp \
    test_bobura.model.station.cpp \
    test_bobura.model.station_info.grade.cpp \
    test_bobura.model.timetable.cpp \
    test_bobura.model.timetable_info.station_location.cpp \
    test_bobura.model.train.cpp \
    test_bobura.model.train_info.stop.cpp \
    test_bobura.model.train_info.time.cpp \
    test_bobura.model.train_info.time_span.cpp

extra_sources =

check_PROGRAMS = bobura_model.test
EXTRA_DIST = $(extra_headers) $(extra_sources)

TESTS = bobura_model.test

bobura_model_test_CPPFLAGS = \
    $(PRECOMPILE_CPPFLAGS) \
    $(BOOST_CPPFLAGS) \
    -I$(top_srcdir)/bobura_model/include \
    -I$(top_srcdir)/tetengo2/include
bobura_model_test_LDFLAGS = $(BOOST_LDFLAGS)
bobura_model_test_LDADD = \
    $(BOOST_FILESYSTEM_LIB) \
    $(BOOST_PROGRAM_OPTIONS_LIB) \
    $(BOOST_SIGNALS_LIB) \
    $(BOOST_SYSTEM_LIB) \
    $(BOOST_UNIT_TEST_FRAMEWORK_LIB)
bobura_model_test_SOURCES = $(headers) $(sources)
