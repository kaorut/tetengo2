/*! \file
    \brief Test of class tetengo2::gui::cursor.

    Copyright (C) 2007-2012 kaoru

    $Id$
*/

//#include <boost/optional.hpp>
#include <boost/test/unit_test.hpp>

#include "tetengo2.detail.stub.cursor.h"

#include "tetengo2.gui.cursor.h"


namespace
{
    // types

    typedef tetengo2::gui::cursor<tetengo2::detail::stub::cursor> cursor_type;

    class concrete_cursor_type : public cursor_type
    {
    public:
        concrete_cursor_type()
        :
        m_details()
        {}


    private:
        details_type m_details;

        virtual boost::optional<const details_type&> details_impl()
        const
        {
            return m_details;
        }

        virtual boost::optional<details_type&> details_impl()
        {
            return m_details;
        }


    };

}


BOOST_AUTO_TEST_SUITE(test_tetengo2)
BOOST_AUTO_TEST_SUITE(gui)
BOOST_AUTO_TEST_SUITE(cursor)
    // test cases

    BOOST_AUTO_TEST_CASE(construction)
    {
        BOOST_TEST_PASSPOINT();

        const concrete_cursor_type cursor;
    }

    BOOST_AUTO_TEST_CASE(details)
    {
        BOOST_TEST_PASSPOINT();

        {
            const concrete_cursor_type cursor;

            cursor.details();
        }
        {
            concrete_cursor_type cursor;

            cursor.details();
        }
    }


BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()
