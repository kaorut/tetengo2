/*! \file
    \brief Test of class tetengo2::gui::menu::recursive_iterator.

    Copyright (C) 2007-2012 kaoru

    $Id$
*/

//#include <memory>
//#include <string>
//#include <utility>

#include <boost/test/unit_test.hpp>

#include "tetengo2.detail.stub.encoding.h"
#include "tetengo2.detail.stub.menu.h"
#include "tetengo2.detail.stub.virtual_key.h"
#include "tetengo2.gui.menu.abstract_popup.h"
#include "tetengo2.gui.menu.menu_base.h"
#include "tetengo2.gui.menu.popup.h"
#include "tetengo2.gui.menu.shortcut_key.h"
#include "tetengo2.gui.menu.traits.h"
#include "tetengo2.gui.message.menu_observer_set.h"
#include "tetengo2.gui.virtual_key.h"
#include "tetengo2.text.encoder.h"
#include "tetengo2.text.encoding.locale.h"
#include "tetengo2.unique.h"

#include "tetengo2.gui.menu.recursive_iterator.h"


namespace
{
    // types

    typedef tetengo2::detail::stub::encoding encoding_details_type;

    typedef
        tetengo2::gui::menu::shortcut_key<
            tetengo2::gui::virtual_key<
                tetengo2::detail::stub::virtual_key<std::string>
            >
        >
        shortcut_key_type;

    typedef
        tetengo2::text::encoding::locale<std::wstring, encoding_details_type>
        internal_encoding_type;

    typedef
        tetengo2::text::encoding::locale<std::wstring, encoding_details_type>
        encoding_type;

    typedef
        tetengo2::text::encoder<internal_encoding_type, encoding_type>
        encoder_type;

    typedef
        tetengo2::gui::menu::traits<
            std::string,
            shortcut_key_type,
            encoder_type,
            tetengo2::gui::message::menu_observer_set
        >
        menu_traits_type;

    typedef tetengo2::detail::stub::menu menu_details_type;

    typedef
        tetengo2::gui::menu::menu_base<menu_traits_type, menu_details_type>
        menu_base_type;

    typedef
        tetengo2::gui::menu::abstract_popup<
            menu_traits_type, menu_details_type
        >
        abstract_popup_menu_type;

    typedef
        tetengo2::gui::menu::popup<menu_traits_type, menu_details_type>
        popup_menu_type;

    typedef
        tetengo2::gui::menu::recursive_iterator<menu_base_type>
        iterator_type;


    // functions

    std::unique_ptr<menu_base_type> create_menu()
    {
        std::unique_ptr<menu_base_type> p_menu(
            tetengo2::make_unique<popup_menu_type>("0")
        );

        p_menu->insert(
            p_menu->end(), tetengo2::make_unique<popup_menu_type>("1")
        );
        p_menu->begin()->insert(
            p_menu->begin()->end(),
            tetengo2::make_unique<popup_menu_type>("2")
        );
        p_menu->insert(
            p_menu->end(),
            tetengo2::make_unique<popup_menu_type>("3")
        );

        return std::move(p_menu);
    }


}

BOOST_AUTO_TEST_SUITE(test_tetengo2)
BOOST_AUTO_TEST_SUITE(gui)
BOOST_AUTO_TEST_SUITE(menu)
BOOST_AUTO_TEST_SUITE(recursive_iterator)
    // test cases

    BOOST_AUTO_TEST_CASE(construction)
    {
        BOOST_TEST_PASSPOINT();

        {
            const iterator_type iterator;
        }
        {
            const std::unique_ptr<menu_base_type> p_menu(create_menu());

            const iterator_type iterator(p_menu.get());
        }
    }

    BOOST_AUTO_TEST_CASE(operator_preincrement)
    {
        BOOST_TEST_PASSPOINT();

        {
            const std::unique_ptr<menu_base_type> p_menu(create_menu());

            iterator_type iterator(p_menu.get());

            BOOST_CHECK(iterator->text() == "0");
            ++iterator;
            BOOST_CHECK(iterator->text() == "1");
            ++iterator;
            BOOST_CHECK(iterator->text() == "2");
            ++iterator;
            BOOST_CHECK(iterator->text() == "3");
            ++iterator;
            BOOST_CHECK(iterator == iterator_type());
        }
    }


BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()
