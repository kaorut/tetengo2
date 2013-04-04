# Automake Settings
# Copyright (C) 2007-2013 kaoru
# $Id$

SUBDIRS = \
     bobura bobura_model \
     docsrc \
     precompiled \
     samples \
     tetengo2 tetengo2_detail tetengo2_gui

EXTRA_DIST = bobura.sln bobura_config.h-original TODO Doxyfile Doxyfile.test

doc-all: doc doc-test

.PHONY: doc
doc:
	pushd $(top_srcdir); \
	$(DOXYGEN) Doxyfile; \
	popd; \
	test "$(top_srcdir)" == "$(top_builddir)" || mv -f $(top_srcdir)/doc $(top_builddir)/doc

.PHONY: doc-test
doc-test:
	pushd $(top_srcdir); \
	$(DOXYGEN) Doxyfile.test; \
	popd; \
	test "$(top_srcdir)" == "$(top_builddir)" || mv -f $(top_srcdir)/doc.test $(top_builddir)/doc.test

clean-doc-all: clean-doc clean-doc-test

.PHONY: clean-doc
clean-doc:
	-rm -rf doc

.PHONY: clean-doc-test
clean-doc-test:
	-rm -rf doc.test

distclean-local: clean-doc-all
