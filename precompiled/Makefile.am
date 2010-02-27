# Automake Settings
# Copyright (C) 2007-2010 kaoru
# $Id$

EXTRA_DIST = precompiled.h precompiled.cpp

all-local: precompiled.gch

precompiled.gch: precompiled.h
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) $(BOOST_CPPFLAGS) $<

clean-local:
	-rm -f *.gch
