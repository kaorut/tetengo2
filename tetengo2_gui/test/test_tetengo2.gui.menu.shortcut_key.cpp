/*! \file
    \brief Test of class tetengo2::gui::menu::shortcut_key.

    Copyright (C) 2007-2013 kaoru

    $Id$
*/

//#include <boost/mpl/at.hpp>
#include <boost/test/unit_test.hpp>

#include "tetengo2.text.h"

#include "test_tetengo2.gui.type_list.h"


namespace
{
    // types

    typedef
        boost::mpl::at<
            test_tetengo2::gui::gui_common_type_list, test_tetengo2::gui::type::gui_common::virtual_key
        >::type
        virtual_key_type;

    typedef boost::mpl::at<test_tetengo2::gui::type_list, test_tetengo2::gui::type::string>::type string_type;

    typedef
        boost::mpl::at<test_tetengo2::gui::menu_type_list, test_tetengo2::gui::type::menu::shortcut_key>::type
        shortcut_key_type;


}


BOOST_AUTO_TEST_SUITE(test_tetengo2)
BOOST_AUTO_TEST_SUITE(gui)
BOOST_AUTO_TEST_SUITE(menu)
BOOST_AUTO_TEST_SUITE(shortcut_key)
    // test cases

    BOOST_AUTO_TEST_CASE(construction)
    {
        BOOST_TEST_PASSPOINT();

        {
            const shortcut_key_type shortcut_key(virtual_key_type::char_a(), false, false, false);
        }
        {
            const shortcut_key_type shortcut_key(virtual_key_type::char_a(), false, false, true);
        }
        {
            const shortcut_key_type shortcut_key(virtual_key_type::char_a(), false, true, false);
        }
        {
            const shortcut_key_type shortcut_key(virtual_key_type::char_a(), false, true, true);
        }
        {
            const shortcut_key_type shortcut_key(virtual_key_type::char_a(), true, false, false);
        }
        {
            const shortcut_key_type shortcut_key(virtual_key_type::char_a(), true, false, true);
        }
        {
            const shortcut_key_type shortcut_key(virtual_key_type::char_a(), true, true, false);
        }
        {
            const shortcut_key_type shortcut_key(virtual_key_type::char_a(), true, true, true);
        }
    }

    BOOST_AUTO_TEST_CASE(operator_equal)
    {
        BOOST_TEST_PASSPOINT();

        {
            const shortcut_key_type shortcut_key1(virtual_key_type::char_a(), false, false, false);
            const shortcut_key_type shortcut_key2(virtual_key_type::char_a(), false, false, false);

            BOOST_CHECK(shortcut_key1 == shortcut_key2);
        }
        {
            const shortcut_key_type shortcut_key1(virtual_key_type::char_a(), false, false, false);
            const shortcut_key_type shortcut_key2(virtual_key_type::char_b(), false, false, false);

            BOOST_CHECK(shortcut_key1 != shortcut_key2);
        }
        {
            const shortcut_key_type shortcut_key1(virtual_key_type::char_a(), false, false, false);
            const shortcut_key_type shortcut_key2(virtual_key_type::char_a(), true, false, false);

            BOOST_CHECK(shortcut_key1 != shortcut_key2);
        }
        {
            const shortcut_key_type shortcut_key1(virtual_key_type::char_a(), false, false, false);
            const shortcut_key_type shortcut_key2(virtual_key_type::char_a(), false, true, false);

            BOOST_CHECK(shortcut_key1 != shortcut_key2);
        }
        {
            const shortcut_key_type shortcut_key1(virtual_key_type::char_a(), false, false, false);
            const shortcut_key_type shortcut_key2(virtual_key_type::char_a(), false, false, true);

            BOOST_CHECK(shortcut_key1 != shortcut_key2);
        }
    }

    BOOST_AUTO_TEST_CASE(key)
    {
        BOOST_TEST_PASSPOINT();

        {
            const shortcut_key_type shortcut_key(virtual_key_type::char_a(), false, false, false);

            BOOST_CHECK(shortcut_key.key() == virtual_key_type::char_a());
        }
        {
            const shortcut_key_type shortcut_key(virtual_key_type::enter(), false, false, false);

            BOOST_CHECK(shortcut_key.key() == virtual_key_type::enter());
        }
    }

    BOOST_AUTO_TEST_CASE(shift)
    {
        BOOST_TEST_PASSPOINT();

        {
            const shortcut_key_type shortcut_key(virtual_key_type::char_a(), false, false, false);

            BOOST_CHECK(!shortcut_key.shift());
        }
        {
            const shortcut_key_type shortcut_key(virtual_key_type::char_a(), true, false, false);

            BOOST_CHECK(shortcut_key.shift());
        }
    }

    BOOST_AUTO_TEST_CASE(control)
    {
        BOOST_TEST_PASSPOINT();

        {
            const shortcut_key_type shortcut_key(virtual_key_type::char_a(), false, false, false);

            BOOST_CHECK(!shortcut_key.control());
        }
        {
            const shortcut_key_type shortcut_key(virtual_key_type::char_a(), false, true, false);

            BOOST_CHECK(shortcut_key.control());
        }
    }

    BOOST_AUTO_TEST_CASE(meta)
    {
        BOOST_TEST_PASSPOINT();

        {
            const shortcut_key_type shortcut_key(virtual_key_type::char_a(), false, false, false);

            BOOST_CHECK(!shortcut_key.meta());
        }
        {
            const shortcut_key_type shortcut_key(virtual_key_type::char_a(), false, false, true);

            BOOST_CHECK(shortcut_key.meta());
        }
    }

    BOOST_AUTO_TEST_CASE(to_string)
    {
        BOOST_TEST_PASSPOINT();

        {
            const shortcut_key_type shortcut_key(virtual_key_type::char_a(), false, false, false);

            BOOST_CHECK(shortcut_key.to_string() == string_type(TETENGO2_TEXT("A")));
        }
        {
            const shortcut_key_type shortcut_key(virtual_key_type::char_b(), false, true, false);

            BOOST_CHECK(shortcut_key.to_string() == string_type(TETENGO2_TEXT("Ctrl+B")));
        }
        {
            const shortcut_key_type shortcut_key(virtual_key_type::char_c(), true, false, true);

            BOOST_CHECK(shortcut_key.to_string() == string_type(TETENGO2_TEXT("Shift+Alt+C")));
        }
    }


BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()
