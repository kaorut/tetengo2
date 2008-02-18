#!/bin/sh

# Subversion property setter.
# $Id$
# Copyright (C) 2007-2008 kaoru

LANG=C

set_prop_for_ordinal()
{
    echo 'Setting for '$1; \
    chmod 644 $1; \
    svn propdel -q svn:executable $1; \
    svn propset -q svn:keywords 'Author Date Rev Id' $1; \
}

set_prop_for_executable()
{
    echo 'Setting for '$1; \
    chmod 755 $1; \
    svn propset -q svn:executable '*' $1; \
    svn propset -q svn:keywords 'Author Date Rev Id' $1; \
}

for f in ` \
    find \
        bobura/src bobura/test \
        bobura_model/include bobura_model/test \
        tetengo2/include tetengo2/test \
        precompiled \
        -maxdepth 1 \
        -type f \
        -name '*.h' -or \
        -name '*.cpp' \
`; \
do
    set_prop_for_ordinal $f;
done
for f in `find docsrc -maxdepth 1 -type f -name '*.page'`; \
do
    set_prop_for_ordinal $f;
done
set_prop_for_ordinal bobura_config.h-original
set_prop_for_ordinal Doxyfile
set_prop_for_ordinal Doxyfile.test

set_prop_for_executable bobura.sln
for f in ` \
    find . bobura bobura_model tetengo2 \
        -maxdepth 1 \
        -type f \
        -name '*.vcproj' \
`; \
do
    set_prop_for_executable $f;
done
set_prop_for_executable set_svn_props.sh
