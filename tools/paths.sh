#!/bin/sh

# File path lister.
# $Id$
# Copyright (C) 2007-2008 kaoru

list_sources()
{
    find \
        $1/bobura/src \
        $1/bobura_model/include \
        $1/tetengo2/include \
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
        -maxdepth 1 \
        -type f \
        -name '*.h' -or \
        -name '*.cpp';
    list_sources $1
}

list_precompiled_sources()
{
    find \
        $1/precompiled \
        -maxdepth 1 \
        -type f \
        -name '*.h' -or \
        -name '*.cpp'
}

list_document_sources()
{
    find \
        $SOLUTIONDIR/docsrc \
        -maxdepth 1 \
        -type f \
        -name '*.page'
}

list_projects()
{
    find \
        $SOLUTIONDIR \
        $SOLUTIONDIR/bobura \
        $SOLUTIONDIR/bobura_model \
        $SOLUTIONDIR/tetengo2 \
        -maxdepth 1 \
        -type f \
        -name '*.vcproj'
}

list_tools()
{
    find \
        $SOLUTIONDIR/tools \
        -maxdepth 1 \
        -type f \
        -name '*.sh' -or \
        -name '*.pl'
}
