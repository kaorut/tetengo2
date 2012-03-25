/*! \file
    \brief Test of class tetengo2::gui::drawing::background.

    Copyright (C) 2007-2012 kaoru

    $Id$
*/

//#include <boost/mpl/at.hpp>
//#include <boost/optional.hpp>
#include <boost/test/unit_test.hpp>

#include "test_tetengo2.gui.type_list.h"


namespace
{
    // types

    typedef
        boost::mpl::at<
            test_tetengo2::gui::drawing_type_list,
            test_tetengo2::gui::type::drawing::background
        >::type
        background_type;

    struct concrete_background : public background_type
    {
        concrete_background()
        :
        background_type()
        {}


    private:
        virtual boost::optional<const background_type::details_type&>
        details_impl()
        const
        {
            return boost::none;
        }

        virtual boost::optional<background_type::details_type&>
        details_impl()
        {
            return boost::none;
        }


    };


}


BOOST_AUTO_TEST_SUITE(test_tetengo2)
BOOST_AUTO_TEST_SUITE(gui)
BOOST_AUTO_TEST_SUITE(drawing)
BOOST_AUTO_TEST_SUITE(background)
    // test cases

    BOOST_AUTO_TEST_CASE(construction)
    {
        BOOST_TEST_PASSPOINT();

        const concrete_background background;
    }

    BOOST_AUTO_TEST_CASE(details)
    {
        BOOST_TEST_PASSPOINT();

        {
            const concrete_background background;

            background.details();
        }
        {
            concrete_background background;

            background.details();
        }
    }


BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()
