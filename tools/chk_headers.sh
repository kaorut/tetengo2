#!/bin/sh

# Standard library usage checker.
# $Id$
# Copyright (C) 2007-2008 kaoru

LANG=C
SOLUTIONDIR=`dirname $0`/..
. $SOLUTIONDIR/tools/paths.sh

for f in `list_sources $SOLUTIONDIR`;
do
    echo '['$f']';
    $SOLUTIONDIR/tools/extract_stblib_usages.pl \
        $SOLUTIONDIR/tools/stdlib_headers.txt < $f;
    echo '';
done
