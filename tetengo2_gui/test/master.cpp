/*! \file
    \brief The master test suite for tetengo2_gui.

    Copyright (C) 2007-2019 kaoru

    $Id$
*/

#define BOOST_TEST_MODULE test_tetengo2_gui
#include <boost/test/unit_test.hpp> // IWYU pragma: keep

#include <tetengo2/detail/base/gui_impl_set.h>
#include <tetengo2/detail/stub/gui_impl_set.h>


namespace {
    struct set_detail_impl
    {
        set_detail_impl()
        {
            tetengo2::detail::set_gui_detail_impl_set(tetengo2::detail::stub::gui_impl_set::instance());
        }
    };
}


BOOST_GLOBAL_FIXTURE(set_detail_impl);
