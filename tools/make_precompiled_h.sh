#/bin/sh
# Makes precompiled.h.
# Copyright (C) 2007-2018 kaoru
# $Id$

TOOLS_DIR=`dirname $0`
SOLUTION_DIR="$1"
test -n "$SOLUTION_DIR" || SOLUTION_DIR="$TOOLS_DIR/.."

PRECOMPILED_H="$SOLUTION_DIR/precompiled/precompiled.h"
PRECOMPILED_H_TMP=$PRECOMPILED_H".tmp"

"$TOOLS_DIR/zzz_make_precompiled_h.pl" \
  "$SOLUTION_DIR/tools/stdlib_headers.txt" \
  "$SOLUTION_DIR/tools/precompiled.template.h" \
  > $PRECOMPILED_H_TMP

mv $PRECOMPILED_H_TMP $PRECOMPILED_H
