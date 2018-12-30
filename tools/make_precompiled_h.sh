#/bin/sh
# Makes precompiled.h.
# Copyright (C) 2007-2019 kaoru
# $Id$

TOOLS_DIR=`dirname $0`
SOLUTION_DIR="$1"
test -n "$SOLUTION_DIR" || SOLUTION_DIR="$TOOLS_DIR/.."

INCLUDE_LIST="$SOLUTION_DIR/tools/zzz_include_list.txt"
PRECOMPILED_H="$SOLUTION_DIR/precompiled/precompiled.h"
PRECOMPILED_H_TMP=$PRECOMPILED_H".tmp"

LANG=C

. "$SOLUTION_DIR/tools/paths.sh"
for f in `list_sources $SOLUTION_DIR; list_test_sources $SOLUTION_DIR`;
do
    echo -n '.' 1>&2;
    grep "^#\s*include\s" $f | sed -e "s/\s\/\/.*$//" | sed -e "s/\r//";
done | sort | uniq > $INCLUDE_LIST
echo '' 1>&2


"$TOOLS_DIR/zzz_make_precompiled_h.py" \
  "$INCLUDE_LIST" \
  "$SOLUTION_DIR/tools/precompiled.template.h" \
  > $PRECOMPILED_H_TMP

mv $PRECOMPILED_H_TMP $PRECOMPILED_H
rm -f $INCLUDE_LIST
