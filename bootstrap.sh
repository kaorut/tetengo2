#! /bin/sh
# Bootstrap Script
# Copyright (C) 2007-2017 kaoru
# $Id$

aclocal && \
autoheader && \
automake --add-missing --copy --gnu && \
autoconf
