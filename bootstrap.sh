#! /bin/sh
# Bootstrap Script
# Copyright (C) 2007-2009 kaoru
# $Id$

aclocal -I m4 && \
autoheader && \
automake --add-missing --copy --gnu && \
autoconf
