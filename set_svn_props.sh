#!/bin/sh

# Subversion svn:keywords property setter.
# Copyright (C) 2007 kaoru

find bobura tetengo2 docsrc -type f -name '*.h' -or -name '*.cpp' -or -name '*.page' \
| xargs svn propset svn:keywords 'Author Data Rev Id'
