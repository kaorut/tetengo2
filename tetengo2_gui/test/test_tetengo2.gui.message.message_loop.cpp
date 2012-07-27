/*! \file
    \brief Test of class tetengo2::gui::message::message_loop.

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
        boost::mpl::at<test_tetengo2::gui::widget_type_list, test_tetengo2::gui::type::widget::abstract_window>::type
        abstract_window_type;

    typedef
        boost::mpl::at<test_tetengo2::gui::widget_type_list, test_tetengo2::gui::type::widget::message_loop>::type
        message_loop_type;

    class concrete_window : public abstract_window_type
    {
    public:
        concrete_window()
        :
        abstract_window_type(abstract_window_type::scroll_bar_style_type::none, message_handler_map_type()),
        m_p_details(tetengo2::make_unique<details_type>())
        {
            initialize(this);
        }

        virtual ~concrete_window()
        {}

        virtual boost::optional<const details_type&> details_impl()
        const
        {
            return boost::make_optional<const details_type&>(*m_p_details);
        }

        virtual boost::optional<details_type&> details_impl()
        {
            return boost::make_optional<details_type&>(*m_p_details);
        }


    private:
        details_ptr_type m_p_details;


    };


}


BOOST_AUTO_TEST_SUITE(test_tetengo2)
BOOST_AUTO_TEST_SUITE(gui)
BOOST_AUTO_TEST_SUITE(message)
BOOST_AUTO_TEST_SUITE(message_loop)
    // test cases

    BOOST_AUTO_TEST_CASE(construction)
    {
        BOOST_TEST_PASSPOINT();

        concrete_window window;
        const message_loop_type message_loop(window);
    }

    BOOST_AUTO_TEST_CASE(operator_paren)
    {
        BOOST_TEST_PASSPOINT();

        concrete_window window;
        const message_loop_type message_loop(window);

        message_loop();
    }


BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()
