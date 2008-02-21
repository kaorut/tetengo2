#!/bin/sh

# Subversion property setter.
# $Id$
# Copyright (C) 2007-2008 kaoru

LANG=C
SOLUTIONDIR=`dirname $0`/..

set_prop_for_ordinal()
{
    echo 'Setting for '$1
    chmod 644 $1
    svn propdel -q svn:executable $1
    svn propset -q svn:keywords 'Author Date Rev Id' $1
}

set_prop_for_executable()
{
    echo 'Setting for '$1
    chmod 755 $1
    svn propset -q svn:executable '*' $1
    svn propset -q svn:keywords 'Author Date Rev Id' $1
}

for f in ` \
    find \
        $SOLUTIONDIR/bobura/src \
        $SOLUTIONDIR/bobura/test \
        $SOLUTIONDIR/bobura_model/include \
        $SOLUTIONDIR/bobura_model/test \
        $SOLUTIONDIR/tetengo2/include \
        $SOLUTIONDIR/tetengo2/test \
        $SOLUTIONDIR/precompiled \
        -maxdepth 1 \
        -type f \
        -name '*.h' -or \
        -name '*.cpp' \
`;
do
    set_prop_for_ordinal $f;
done
for f in ` \
    find \
        $SOLUTIONDIR/docsrc \
        -maxdepth 1 \
        -type f \
        -name '*.page' \
`;
do
    set_prop_for_ordinal $f;
done
set_prop_for_ordinal $SOLUTIONDIR/bobura_config.h-original
set_prop_for_ordinal $SOLUTIONDIR/Doxyfile
set_prop_for_ordinal $SOLUTIONDIR/Doxyfile.test

set_prop_for_executable $SOLUTIONDIR/bobura.sln
for f in ` \
    find \
        $SOLUTIONDIR \
        $SOLUTIONDIR/bobura \
        $SOLUTIONDIR/bobura_model \
        $SOLUTIONDIR/tetengo2 \
        -maxdepth 1 \
        -type f \
        -name '*.vcproj' \
`;
do
    set_prop_for_executable $f;
done
set_prop_for_executable $SOLUTIONDIR/tools/set_svn_props.sh
