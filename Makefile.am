# Automake Settings
# Copyright (C) 2007-2015 kaoru
# $Id$

SUBDIRS = \
     docsrc \
     precompiled \
     tetengo2 tetengo2_detail tetengo2_gui \
     tools \
     vsprops

EXTRA_DIST = tetengo2.sln tetengo2_config.h-original TODO Doxyfile

.PHONY: lint
lint: lint-includes lint-test-cases lint-type-list-type-duplication

lint-includes:
	$(top_srcdir)/tools/check_includes.sh $(top_srcdir)

lint-test-cases:
	$(top_srcdir)/tools/check_test_cases.sh $(top_srcdir) silent

lint-type-list-type-duplication:
	$(top_srcdir)/tools/check_type_list_type_duplication.sh $(top_srcdir)

.PHONY: doc
doc:
	if test "$(top_srcdir)" != "$(top_builddir)"; \
	then \
	    test ! -e $(top_srcdir)/doc || rm -rf $(top_srcdir)/doc; \
	    test ! -e $(top_builddir)/doc || mv $(top_builddir)/doc $(top_srcdir)/doc; \
	    pushd $(top_srcdir); \
	fi
	$(DOXYGEN) $(top_srcdir)/Doxyfile
	if test "$(top_srcdir)" != "$(top_builddir)"; \
	then \
	    popd; \
	    test ! -e $(top_builddir)/doc || rm -rf $(top_builddir)/doc; \
	    test ! -e $(top_srcdir)/doc || mv -f $(top_srcdir)/doc $(top_builddir)/doc; \
	fi

.PHONY: clean-doc
clean-doc:
	-rm -rf $(top_builddir)/doc

distclean-local: clean-doc
