# Automake Settings
# Copyright (C) 2007-2017 kaoru
# $Id$

SUBDIRS = tetengo2

headers = \
    tetengo2.h

include_HEADERS = $(headers)

iwyu_CPPFLAGS = \
    -I$(top_srcdir)/tetengo2/include \
    -I$(top_srcdir)/tetengo2_detail/include

lint-iwyu:
	for f in $(headers); \
	do \
	    echo $$f; \
	    iwyu -x c++ $(CPPFLAGS) $(iwyu_CPPFLAGS) $(CXXFLAGS) $$f; \
	done
	for d in $(SUBDIRS); do (cd $$d && $(MAKE) lint-iwyu); done
