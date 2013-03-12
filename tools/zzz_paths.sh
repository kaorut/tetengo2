#!/bin/sh
# File path lister.
# Copyright (C) 2007-2013 kaoru
# $Id$

list_sources()
{
    find \
        $1/bobura/src \
        $1/bobura_model/include \
        $1/tetengo2/include \
        $1/tetengo2/src \
        $1/tetengo2_detail/include \
        $1/tetengo2_gui/include \
        -maxdepth 1 \
        -type f \
        -name '*.h' -or \
        -name '*.cpp'
}

list_test_sources()
{
    find \
        $1/bobura/test \
        $1/bobura_model/test \
        $1/tetengo2/test \
        $1/tetengo2_gui/test \
        -maxdepth 1 \
        -type f \
        -name '*.h' -or \
        -name '*.cpp';
}

