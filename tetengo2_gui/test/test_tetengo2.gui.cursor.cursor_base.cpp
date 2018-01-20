/*! \file
    \brief Test of class tetengo2::gui::cursor::cursor_base.

    Copyright (C) 2007-2017 kaoru

    $Id$
*/

#include <sstream>

#include <boost/preprocessor.hpp>
#include <boost/test/unit_test.hpp>

#include <tetengo2/gui/cursor/cursor_base.h>


namespace
{
    // types

    using cursor_type = tetengo2::gui::cursor::cursor_base;

    class concrete_cursor_type : public cursor_type
    {
    public:
        concrete_cursor_type()
        {}

    private:
        virtual const details_type& details_impl()
        const override
        {
            static const details_type singleton{};
            return singleton;
        }

        virtual details_type& details_impl()
        override
        {
            static details_type singleton{};
            return singleton;
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
