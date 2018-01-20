/*! \file
    \brief Test of class tetengo2::gui::menu::shortcut_key.

    Copyright (C) 2007-2017 kaoru

    $Id$
*/

#include <sstream>
#include <string>

#include <boost/operators.hpp>
#include <boost/preprocessor.hpp>
#include <boost/test/unit_test.hpp>

#include <tetengo2/gui/menu/shortcut_key.h>
#include <tetengo2/gui/virtual_key.h>
#include <tetengo2/text.h>

#include "test_tetengo2.gui.detail_type_list.h"
#include "test_tetengo2.gui.type_list.h"


namespace
{
    // types

    using detail_type_list_type = test_tetengo2::gui::type_list::detail_for_test;

    using common_type_list_type = test_tetengo2::gui::type_list::common<detail_type_list_type>;

    using string_type = common_type_list_type::string_type;

    using virtual_key_details_type = detail_type_list_type::virtual_key_type;

    using virtual_key_type = tetengo2::gui::virtual_key<string_type, virtual_key_details_type>;

    using shortcut_key_type = tetengo2::gui::menu::shortcut_key<string_type, virtual_key_details_type>;


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
            const shortcut_key_type shortcut_key{ virtual_key_type::char_a(), false, false, false };
        }
        {
            const shortcut_key_type shortcut_key{ virtual_key_type::char_a(), false, false, true };
        }
        {
            const shortcut_key_type shortcut_key{ virtual_key_type::char_a(), false, true, false };
        }
        {
            const shortcut_key_type shortcut_key{ virtual_key_type::char_a(), false, true, true };
        }
        {
            const shortcut_key_type shortcut_key{ virtual_key_type::char_a(), true, false, false };
        }
        {
            const shortcut_key_type shortcut_key{ virtual_key_type::char_a(), true, false, true };
        }
        {
            const shortcut_key_type shortcut_key{ virtual_key_type::char_a(), true, true, false };
        }
        {
            const shortcut_key_type shortcut_key{ virtual_key_type::char_a(), true, true, true };
        }
    }

    BOOST_AUTO_TEST_CASE(operator_equal)
    {
        BOOST_TEST_PASSPOINT();

        {
            const shortcut_key_type shortcut_key1{ virtual_key_type::char_a(), false, false, false };
            const shortcut_key_type shortcut_key2{ virtual_key_type::char_a(), false, false, false };

            BOOST_CHECK(shortcut_key1 == shortcut_key2);
        }
        {
            const shortcut_key_type shortcut_key1{ virtual_key_type::char_a(), false, false, false };
            const shortcut_key_type shortcut_key2{ virtual_key_type::char_b(), false, false, false };

            BOOST_CHECK(shortcut_key1 != shortcut_key2);
        }
        {
            const shortcut_key_type shortcut_key1{ virtual_key_type::char_a(), false, false, false };
            const shortcut_key_type shortcut_key2{ virtual_key_type::char_a(), true, false, false };

            BOOST_CHECK(shortcut_key1 != shortcut_key2);
        }
        {
            const shortcut_key_type shortcut_key1{ virtual_key_type::char_a(), false, false, false };
            const shortcut_key_type shortcut_key2{ virtual_key_type::char_a(), false, true, false };

            BOOST_CHECK(shortcut_key1 != shortcut_key2);
        }
        {
            const shortcut_key_type shortcut_key1{ virtual_key_type::char_a(), false, false, false };
            const shortcut_key_type shortcut_key2{ virtual_key_type::char_a(), false, false, true };

            BOOST_CHECK(shortcut_key1 != shortcut_key2);
        }
    }

    BOOST_AUTO_TEST_CASE(key)
    {
        BOOST_TEST_PASSPOINT();

        {
            const shortcut_key_type shortcut_key{ virtual_key_type::char_a(), false, false, false };

            BOOST_CHECK(shortcut_key.key() == virtual_key_type::char_a());
        }
        {
            const shortcut_key_type shortcut_key{ virtual_key_type::enter(), false, false, false };

            BOOST_CHECK(shortcut_key.key() == virtual_key_type::enter());
        }
    }

    BOOST_AUTO_TEST_CASE(shift)
    {
        BOOST_TEST_PASSPOINT();

        {
            const shortcut_key_type shortcut_key{ virtual_key_type::char_a(), false, false, false };

            BOOST_TEST(!shortcut_key.shift());
        }
        {
            const shortcut_key_type shortcut_key{ virtual_key_type::char_a(), true, false, false };

            BOOST_TEST(shortcut_key.shift());
        }
    }

    BOOST_AUTO_TEST_CASE(control)
    {
        BOOST_TEST_PASSPOINT();

        {
            const shortcut_key_type shortcut_key{ virtual_key_type::char_a(), false, false, false };

            BOOST_TEST(!shortcut_key.control());
        }
        {
            const shortcut_key_type shortcut_key{ virtual_key_type::char_a(), false, true, false };

            BOOST_TEST(shortcut_key.control());
        }
    }

    BOOST_AUTO_TEST_CASE(meta)
    {
        BOOST_TEST_PASSPOINT();

        {
            const shortcut_key_type shortcut_key{ virtual_key_type::char_a(), false, false, false };

            BOOST_TEST(!shortcut_key.meta());
        }
        {
            const shortcut_key_type shortcut_key{ virtual_key_type::char_a(), false, false, true };

            BOOST_TEST(shortcut_key.meta());
        }
    }

    BOOST_AUTO_TEST_CASE(to_string)
    {
        BOOST_TEST_PASSPOINT();

        {
            const shortcut_key_type shortcut_key{ virtual_key_type::char_a(), false, false, false };

            BOOST_CHECK(shortcut_key.to_string() == string_type{ TETENGO2_TEXT("A") });
        }
        {
            const shortcut_key_type shortcut_key{ virtual_key_type::char_b(), false, true, false };

            BOOST_CHECK(shortcut_key.to_string() == string_type{ TETENGO2_TEXT("Ctrl+B") });
        }
        {
            const shortcut_key_type shortcut_key{ virtual_key_type::char_c(), true, false, true };

            BOOST_CHECK(shortcut_key.to_string() == string_type{ TETENGO2_TEXT("Shift+Alt+C") });
        }
    }


BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()
