/*! \file
    \brief Test of class tetengo2::gui::message::message_loop.

    Copyright (C) 2007-2014 kaoru

    $Id$
*/

#include <boost/mpl/at.hpp>
#include <boost/test/unit_test.hpp>

#include <tetengo2.h>
#include <tetengo2.gui.h>

#include "test_tetengo2.gui.detail_type_list.h"
#include "test_tetengo2.gui.type_list.h"


namespace
{
    // types

    using detail_type_list_type = test_tetengo2::gui::detail_type_list;

    using type_list_type = test_tetengo2::gui::type_list<detail_type_list_type>;

    using menu_details_type = boost::mpl::at<detail_type_list_type, test_tetengo2::gui::type::detail::menu>::type;

    using abstract_window_type =
        tetengo2::gui::widget::abstract_window<
            boost::mpl::at<type_list_type, test_tetengo2::gui::type::widget_traits>::type,
            boost::mpl::at<type_list_type, test_tetengo2::gui::type::widget_details_traits>::type,
            menu_details_type
        >;

    using message_loop_details_type =
        boost::mpl::at<detail_type_list_type, test_tetengo2::gui::type::detail::message_loop>::type;

    using message_loop_type =
        tetengo2::gui::message::message_loop<abstract_window_type, message_loop_details_type>;

    class concrete_window : public abstract_window_type
    {
    public:
        concrete_window()
        :
        abstract_window_type(abstract_window_type::scroll_bar_style_type::none, false, message_handler_map_type{}),
        m_p_details(tetengo2::stdalt::make_unique<details_type>())
        {
            this->initialize(this);
        }

        virtual ~concrete_window()
        TETENGO2_STDALT_DESTRUCTOR_DEFAULT_IMPLEMENTATION;


    private:
        details_ptr_type m_p_details;

        virtual const details_type& details_impl()
        const override
        {
            return *m_p_details;
        }

        virtual details_type& details_impl()
        override
        {
            return *m_p_details;
        }


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

        concrete_window window{};
        const message_loop_type message_loop{ window };
    }

    BOOST_AUTO_TEST_CASE(operator_paren)
    {
        BOOST_TEST_PASSPOINT();

        concrete_window window{};
        const message_loop_type message_loop{ window };

        message_loop();
    }


BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()
