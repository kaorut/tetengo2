# Automake Settings
# Copyright (C) 2007-2018 kaoru
# $Id$

SOURCE_SUBDIRS = \
    tetengo2 \
    tetengo2_detail \
    tetengo2_gui

SUBDIRS = \
    docsrc \
    precompiled \
    $(SOURCE_SUBDIRS) \
    tools \
    vsprops

EXTRA_DIST = tetengo2.sln tetengo2_config.h-original TODO Doxyfile

.PHONY: lint
lint: lint-test-cases lint-type-list-type-duplication lint-iwyu

lint-test-cases:
	$(top_srcdir)/tools/check_test_cases.sh $(top_srcdir) silent

lint-type-list-type-duplication:
	$(top_srcdir)/tools/check_type_list_type_duplication.sh $(top_srcdir)

lint-iwyu:
	for d in $(SOURCE_SUBDIRS); do (cd $$d && $(MAKE) lint-iwyu); done

.PHONY: lint-iwyu-extra
lint-iwyu-extra:
	for d in $(SOURCE_SUBDIRS); do (cd $$d && $(MAKE) lint-iwyu-extra); done

.PHONY: format
format:
	for d in $(SOURCE_SUBDIRS); do (cd $$d && $(MAKE) format); done

.PHONY: doc
doc:
	cd $(top_srcdir) && $(DOXYGEN) Doxyfile
	if test "$(top_srcdir)" != "$(top_builddir)"; \
	then \
	    rm -rf $(top_builddir)/doc; \
	    mv $(top_srcdir)/doc $(top_builddir); \
	fi

.PHONY: clean-doc
clean-doc:
	-rm -rf $(top_builddir)/doc

distclean-local: clean-doc
