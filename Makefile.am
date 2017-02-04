# Automake Settings
# Copyright (C) 2007-2017 kaoru
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
	$(DOXYGEN) $(top_srcdir)/Doxyfile

.PHONY: clean-doc
clean-doc:
	-rm -rf $(top_builddir)/doc

distclean-local: clean-doc
