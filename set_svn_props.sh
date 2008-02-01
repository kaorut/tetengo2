#!/bin/sh

# Subversion property setter.
# Copyright (C) 2007-2008 kaoru

LANG=C

for f in ` \
    find bobura bobura_model tetengo2 precompiled docsrc \
    -type f -name '*.h' -or -name '*.cpp' -or -name '*.page' \
`; \
do
    chmod 666 $f;
    svn propdel svn:executable $f; \
    svn propset svn:keywords 'Author Date Rev Id' $f; \
done
