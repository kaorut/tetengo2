# Automake Settings
# Copyright (C) 2007-2012 kaoru
# $Id$

EXTRA_DIST = precompiled.h precompiled.cpp

all-local: precompiled.h.gch

precompiled.h.gch: precompiled.h
	test -z "$(PRECOMPILE_CPPFLAGS)" || $(CXX) $(CPPFLAGS) $(CXXFLAGS) $(BOOST_CPPFLAGS) $<

clean-local:
	-test -z "$(PRECOMPILE_CPPFLAGS)" || rm -f *.gch
