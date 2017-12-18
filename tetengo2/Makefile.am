# Automake Settings
# Copyright (C) 2007-2017 kaoru
# $Id$

SUBDIRS = include res.test src test

EXTRA_DIST = \
    tetengo2.vcxproj tetengo2.vcxproj.filters \
    tetengo2.test.vcxproj tetengo2.test.vcxproj.filters

lint-iwyu:
	for d in include src test; do (cd $$d && $(MAKE) lint-iwyu); done
