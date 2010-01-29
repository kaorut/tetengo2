#!/bin/sh
# Checks the #include directives.
# Copyright (C) 2007-2010 kaoru
# $Id$

LANG=C
SOLUTIONDIR=`dirname $0`/..
. $SOLUTIONDIR/tools/paths.sh

for f in `list_sources $SOLUTIONDIR; list_test_sources $SOLUTIONDIR`;
do
    echo '['$f']';
done
