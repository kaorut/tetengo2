#! /bin/sh
# Bootstrap Script
# Copyright (C) 2007-2016 kaoru
# $Id$

aclocal && \
autoheader && \
automake --add-missing --copy --gnu && \
autoconf
