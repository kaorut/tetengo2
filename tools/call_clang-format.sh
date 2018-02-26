#!/bin/sh
# Calls clang-format.
# Copyright (C) 2007-2018 kaoru
# $Id$

CLANGFORMAT=$1
FILE=$2

"$CLANGFORMAT" -style=file "$FILE" > "$FILE.tmp"
mv -f "$FILE.tmp" "$FILE"
#!/bin/sh
# Calls clang-format.
# Copyright (C) 2007-2018 kaoru
# $Id$

CLANGFORMAT=$1
FILE=$2

echo formatting $FILE ...
"$CLANGFORMAT" -style=file "$FILE" > "$FILE.tmp"
mv -f "$FILE.tmp" "$FILE"
