#!/bin/sh

# Subversion property setter.
# $Id$
# Copyright (C) 2007-2008 kaoru

LANG=C

for f in ` \
    find . bobura bobura_model tetengo2 precompiled docsrc \
        -type f \
        -name '*.h' -or \
        -name '*.cpp' -or \
        -name '*.page' -or \
        -name 'Doxyfile' -or \
        -name 'Doxyfile.test' -or \
        -name 'bobura_config.h-original' \
`; \
do
    echo 'Setting to '$f; \
    chmod 644 $f; \
    svn propdel -q svn:executable $f; \
    svn propset -q svn:keywords 'Author Date Rev Id' $f; \
done

for f in ` \
    find . bobura bobura_model tetengo2 \
        -type f \
        -name 'bobura.sln' -or \
        -name 'set_svn_props.sh'
`; \
do
    echo 'Setting to '$f; \
    chmod 755 $f; \
    svn propset -q svn:executable '*' $f; \
    svn propset -q svn:keywords 'Author Date Rev Id' $f; \
done
