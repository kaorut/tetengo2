# Automake Settings
# Copyright (C) 2007-2017 kaoru
# $Id$

SUBDIRS = tetengo2

headers = \
    tetengo2.detail.h

include_HEADERS = $(headers)

iwyu_CPPFLAGS = \
    -I$(top_srcdir)/tetengo2/include \
    -I$(top_srcdir)/tetengo2_detail/include \
    -I$(top_srcdir)/tetengo2_gui/include

lint-iwyu:
	for f in $(headers); \
	do \
	    echo "iwyu: "$$f; \
	    $(IWYU) -Xiwyu --mapping_file=$(top_srcdir)/tools/iwyu_mappings.imp -Xiwyu --max_line_length=1024 -x c++ $(CPPFLAGS) $(iwyu_CPPFLAGS) $(CXXFLAGS) $$f; \
	done; \
	for d in $(SUBDIRS); do (cd $$d && $(MAKE) lint-iwyu); done
