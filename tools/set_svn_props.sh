#!/bin/sh

# Subversion property setter.
# $Id$
# Copyright (C) 2007-2009 kaoru

LANG=C
SOLUTIONDIR=`dirname $0`/..
. $SOLUTIONDIR/tools/paths.sh

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
    list_sources $SOLUTIONDIR; \
    list_test_sources $SOLUTIONDIR; \
    list_precompiled_sources $SOLUTIONDIR; \
    list_document_sources $SOLUTIONDIR \
`;
do
    set_prop_for_ordinal $f;
done
set_prop_for_ordinal $SOLUTIONDIR/bobura_config.h-original
set_prop_for_ordinal $SOLUTIONDIR/Doxyfile
set_prop_for_ordinal $SOLUTIONDIR/Doxyfile.test
set_prop_for_ordinal $SOLUTIONDIR/start_vc_config.txt-original
set_prop_for_ordinal $SOLUTIONDIR/tools/stdlib_headers.txt

for f in ` \
  list_projects $SOLUTIONDIR; \
  list_tools $SOLUTIONDIR \
`;
do
    set_prop_for_executable $f;
done
set_prop_for_executable $SOLUTIONDIR/bobura.sln
