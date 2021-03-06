#!/bin/sh
# File path lister.
# Copyright (C) 2007-2019 kaoru
# $Id$

list_sources()
{
    find \
        $1/tetengo2/include \
        $1/tetengo2/src \
        $1/tetengo2_detail/include \
        $1/tetengo2_detail/src \
        $1/tetengo2_gui/include \
        $1/tetengo2_gui/src \
        -type f \
        -name '*.h' -or \
        -name '*.cpp'
}

list_test_sources()
{
    find \
        $1/tetengo2/test \
        $1/tetengo2_gui/test \
        -type f \
        -name '*.h' -or \
        -name '*.cpp';
}

