#! /bin/sh
# Bootstrap Script
# Copyright (C) 2007-2012 kaoru
# $Id$

aclocal && \
autoheader && \
automake --add-missing --copy --gnu && \
autoconf
