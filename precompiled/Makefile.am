# Automake Settings
# Copyright (C) 2007-2015 kaoru
# $Id$

EXTRA_DIST = precompiled.h precompiled.cpp

PRECOMPILE_OUTPUT = $(top_builddir)/precompiled/precompiled.h.gch

all-local: $(PRECOMPILE_OUTPUT)

PRECOMPILE_CXX = $(CXX) $(DEFS) $(DEFAULT_INCLUDES) $(INCLUDES) $(AM_CPPFLAGS) $(CPPFLAGS) $(AM_CXXFLAGS) $(CXXFLAGS)
$(PRECOMPILE_OUTPUT): precompiled.h
	test -z "$(PRECOMPILE_CPPFLAGS)" || $(PRECOMPILE_CXX) -o $(PRECOMPILE_OUTPUT) $<

clean-local:
	-test -z "$(PRECOMPILE_CPPFLAGS)" || rm -f $(PRECOMPILE_OUTPUT)
