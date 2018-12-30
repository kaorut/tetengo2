# Automake Settings
# Copyright (C) 2007-2019 kaoru
# $Id$

SOURCE_SUBDIRS = include src

SUBDIRS = $(SOURCE_SUBDIRS)

EXTRA_DIST = \
    tetengo2_detail.vcxproj tetengo2_detail.vcxproj.filters

lint-iwyu:
	for d in $(SOURCE_SUBDIRS); do (cd $$d && $(MAKE) lint-iwyu); done

lint-iwyu-extra:
	for d in $(SOURCE_SUBDIRS); do (cd $$d && $(MAKE) lint-iwyu-extra); done

format:
	for d in $(SOURCE_SUBDIRS); do (cd $$d && $(MAKE) format); done
