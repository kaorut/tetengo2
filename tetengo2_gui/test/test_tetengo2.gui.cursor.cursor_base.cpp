/*! \file
    \brief Test of class tetengo2::gui::cursor::cursor_base.

    Copyright (C) 2007-2016 kaoru

    $Id$
*/

#include <boost/test/unit_test.hpp>

#include <tetengo2/gui/cursor/cursor_base.h>

#include "test_tetengo2.gui.type_list.h"


namespace
{
    // types

    using detail_type_list_type = test_tetengo2::gui::type_list::detail_for_test;

    using cursor_type = tetengo2::gui::cursor::cursor_base<detail_type_list_type::cursor_type>;

    class concrete_cursor_type : public cursor_type
    {
    public:
        concrete_cursor_type()
        :
        m_details()
        {}


    private:
        details_type m_details;

        virtual const details_type& details_impl()
        const override
        {
            return m_details;
        }

        virtual details_type& details_impl()
        override
        {
            return m_details;
        }


    };

}


BOOST_AUTO_TEST_SUITE(test_tetengo2)
BOOST_AUTO_TEST_SUITE(gui)
BOOST_AUTO_TEST_SUITE(cursor)
BOOST_AUTO_TEST_SUITE(cursor_base)
    // test cases

    BOOST_AUTO_TEST_CASE(construction)
    {
        BOOST_TEST_PASSPOINT();

        const concrete_cursor_type cursor{};
    }

    BOOST_AUTO_TEST_CASE(details)
    {
        BOOST_TEST_PASSPOINT();

        {
            const concrete_cursor_type cursor{};

            cursor.details();
        }
        {
            concrete_cursor_type cursor{};

            cursor.details();
        }
    }


BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()
