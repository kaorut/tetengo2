# Automake Settings
# Copyright (C) 2007-2013 kaoru
# $Id$

EXTRA_DIST = precompiled.h precompiled.cpp

all-local: $(top_srcdir)/precompiled/precompiled.h.gch

$(top_srcdir)/precompiled/precompiled.h.gch: precompiled.h
	test -z "$(PRECOMPILE_CPPFLAGS)" || $(CXX) $(CPPFLAGS) $(CXXFLAGS) $(BOOST_CPPFLAGS) $<

clean-local:
	-test -z "$(PRECOMPILE_CPPFLAGS)" || rm -f $(top_srcdir)/precompiled/precompiled.h.gch
