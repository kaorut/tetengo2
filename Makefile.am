# Automake Settings
# Copyright (C) 2007-2013 kaoru
# $Id$

SUBDIRS = \
     bobura bobura_model \
     docsrc \
     precompiled \
     samples \
     setup \
     tetengo2 tetengo2_detail tetengo2_gui

EXTRA_DIST = bobura.sln bobura_config.h-original TODO Doxyfile Doxyfile.test

.PHONY: lint
lint: lint-includes lint-test-cases lint-typedefs

lint-includes:
	$(top_srcdir)/tools/check_includes.sh '' silent

lint-test-cases:
	$(top_srcdir)/tools/check_test_cases.sh '' silent

lint-typedefs:
	$(top_srcdir)/tools/check_typedefs.sh '' silent

doc-all: doc doc-test

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

.PHONY: doc-test
doc-test:
	if test "$(top_srcdir)" != "$(top_builddir)"; \
	then \
	    test ! -e $(top_srcdir)/doc.test || rm -rf $(top_srcdir)/doc.test; \
	    test ! -e $(top_builddir)/doc.test || mv $(top_builddir)/doc $(top_srcdir)/doc.test; \
	    pushd $(top_srcdir); \
	fi
	$(DOXYGEN) $(top_srcdir)/Doxyfile.test
	if test "$(top_srcdir)" != "$(top_builddir)"; \
	then \
	    popd; \
	    test ! -e $(top_builddir)/doc.test || rm -rf $(top_builddir)/doc.test; \
	    test ! -e $(top_srcdir)/doc.test || mv -f $(top_srcdir)/doc $(top_builddir)/doc.test; \
	fi

clean-doc-all: clean-doc clean-doc-test

.PHONY: clean-doc
clean-doc:
	-rm -rf $(top_builddir)/doc

.PHONY: clean-doc-test
clean-doc-test:
	-rm -rf $(top_builddir)/doc.test

distclean-local: clean-doc-all
