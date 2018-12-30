# Automake Settings
# Copyright (C) 2007-2019 kaoru
# $Id$

SOURCE_SUBDIRS = include src test

SUBDIRS = $(SOURCE_SUBDIRS)

EXTRA_DIST = \
    tetengo2_gui.vcxproj tetengo2_gui.vcxproj.filters \
    tetengo2_gui.test.vcxproj tetengo2_gui.test.vcxproj.filters

lint-iwyu:
	for d in $(SOURCE_SUBDIRS); do (cd $$d && $(MAKE) lint-iwyu); done

lint-iwyu-extra:
	for d in $(SOURCE_SUBDIRS); do (cd $$d && $(MAKE) lint-iwyu-extra); done

format:
	for d in $(SOURCE_SUBDIRS); do (cd $$d && $(MAKE) format); done
