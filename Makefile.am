# Automake Settings
# Copyright (C) 2007-2009 kaoru
# $Id$

#### Subdirectories ####


#### Documentation ####

doc-all: doc doc-test

.PHONY: doc
doc:
	$(DOXYGEN) Doxyfile

.PHONY: doc-test
doc-test:
	$(DOXYGEN) Doxyfile.test

clean-doc-all: clean-doc clean-doc-test

.PHONY: clean-doc
clean-doc:
	-rm -rf doc

.PHONY: clean-doc-test
clean-doc-test:
	-rm -rf doc.test

distclean-local: clean-doc-all
