# Automake Settings
# Copyright (C) 2007-2018 kaoru
# $Id$

SOURCE_SUBDIRS = include src test

SUBDIRS = $(SOURCE_SUBDIRS) res.test

EXTRA_DIST = \
    tetengo2.vcxproj tetengo2.vcxproj.filters \
    tetengo2.test.vcxproj tetengo2.test.vcxproj.filters

lint-iwyu:
	for d in $(SOURCE_SUBDIRS); do (cd $$d && $(MAKE) lint-iwyu); done

lint-iwyu-extra:
	for d in $(SOURCE_SUBDIRS); do (cd $$d && $(MAKE) lint-iwyu-extra); done
