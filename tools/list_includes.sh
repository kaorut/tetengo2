#!/bin/sh

# Standard library usage lister.
# $Id$
# Copyright (C) 2007-2008 kaoru

LANG=C
SOLUTIONDIR=`dirname $0`/..
. $SOLUTIONDIR/tools/paths.sh

for f in `list_sources $SOLUTIONDIR`;
do
    grep "^\#include <[a-z]\+>" $f;
done | sort | uniq

echo ''

for f in `list_sources $SOLUTIONDIR`;
do
    grep "^\#include <boost\/" $f;
done | sort | uniq
