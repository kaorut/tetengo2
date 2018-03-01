#!/bin/bash
# Calls clang-format.
# Copyright (C) 2007-2018 kaoru
# $Id$

UNIX2DOS=$1
CLANGFORMAT=$2
SRCDIR=$3
FILES=${@:4}

CORE_COUNT=`grep -c '^processor' /proc/cpuinfo`

function call_clangformat_iter()
{
    UNIX2DOS=$1
    CLANGFORMAT=$2
    FILE=$3

    "$UNIX2DOS" < "$FILE" > "$FILE.tmp"
    test $? -eq 0 && mv -f "$FILE.tmp" "$FILE"

    sed -e "s/ \+\(\r\?\)$/\1/g" < "$FILE" > "$FILE.tmp"
    test $? -eq 0 && mv -f "$FILE.tmp" "$FILE"

    "$CLANGFORMAT" -style=file -fallback-style=none "$FILE" > "$FILE.tmp"
    test $? -eq 0 && mv -f "$FILE.tmp" "$FILE"
}
export -f call_clangformat_iter

echo $FILES | tr ' ' '\n' | xargs -P $CORE_COUNT -n 1 -I {} bash -c "call_clangformat_iter $UNIX2DOS $CLANGFORMAT $SRCDIR/{}"
