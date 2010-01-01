#! /bin/sh
# Bootstrap Script
# Copyright (C) 2007-2010 kaoru
# $Id$

aclocal -I autoconf-archive/m4 && \
autoheader && \
automake --add-missing --copy --gnu && \
autoconf
