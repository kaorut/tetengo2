#!/bin/sh

# Standard library usage extractor.
# $Id$
# Copyright (C) 2007-2008 kaoru

LANG=C
SOLUTIONDIR=`dirname $0`/..

for f in ` \
    find \
        $SOLUTIONDIR/bobura/src \
        $SOLUTIONDIR/bobura/test \
        $SOLUTIONDIR/bobura_model/include \
        $SOLUTIONDIR/bobura_model/test \
        $SOLUTIONDIR/tetengo2/include \
        $SOLUTIONDIR/tetengo2/test \
        -maxdepth 1 \
        -type f \
        -name '*.h' -or \
        -name '*.cpp' \
`;
do
    echo '['$f']';
    $SOLUTIONDIR/tools/extract_stblib_usages.pl \
        $SOLUTIONDIR/tools/stdlib_headers.txt < $f;
    echo '';
done
