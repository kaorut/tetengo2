/*! \file
    \brief Test of class tetengo2::gui::icon.

    Copyright (C) 2007-2013 kaoru

    $Id$
*/

//#include <boost/mpl/at.hpp>
#include <boost/test/unit_test.hpp>

#include "tetengo2.detail.stub.icon.h"
#include "tetengo2.text.h"

#include "test_tetengo2.gui.type_list.h"

#include "tetengo2.gui.icon.h"


namespace
{
    typedef boost::mpl::at<test_tetengo2::gui::type_list, test_tetengo2::gui::type::path>::type path_type;

    typedef tetengo2::gui::icon<path_type, tetengo2::detail::stub::icon> icon_type;


}


BOOST_AUTO_TEST_SUITE(test_tetengo2)
BOOST_AUTO_TEST_SUITE(gui)
BOOST_AUTO_TEST_SUITE(icon)
    // test cases

    BOOST_AUTO_TEST_CASE(construction)
    {
        BOOST_TEST_PASSPOINT();

        const icon_type icon(path_type(TETENGO2_TEXT("hoge.ico")));
    }


BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()
