#!/bin/sh

# Subversion property setter.
# Copyright (C) 2007-2008 kaoru

LANG=C

for f in ` \
    find bobura bobura_model tetengo2 precompiled docsrc \
    -type f -name '*.h' -or -name '*.cpp' -or -name '*.page' \
`; \
do
    echo 'Setting to '$f
    chmod 666 $f;
    svn propdel -q svn:executable $f; \
    svn propset -q svn:keywords 'Author Date Rev Id' $f; \
done
