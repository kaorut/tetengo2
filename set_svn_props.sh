#!/bin/sh

# Subversion svn:keywords property setter.
# Copyright (C) 2007 kaoru

LANG=C

for f in `find bobura tetengo2 docsrc -type f -name '*.h' -or -name '*.cpp' -or -name '*.page'`; \
do
    chmod 666 $f;
    svn propset svn:keywords 'Author Date Rev Id' $f; \
done
