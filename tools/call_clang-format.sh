#!/bin/bash
# Calls clang-format.
# Copyright (C) 2007-2018 kaoru
# $Id$

CLANGFORMAT=$1
FILES=${@:2}

CORE_COUNT=`grep -c '^processor' /proc/cpuinfo`

function call_clangformat_iter()
{
    CLANGFORMAT=$1
    FILE=$2
    
    echo "formatting $FILE ... "
    "$CLANGFORMAT" -style=file > "$FILE.tmp"
    mv -f "$FILE.tmp" "$FILE"
}
export -f call_clangformat_iter

echo $FILES | tr ' ' '\n' | xargs -P $CORE_COUNT -n 1 -I {} bash -c "call_clangformat_iter $CLANGFORMAT {}"

