/*! \file
    \brief Test of class tetengo2::gui::message::dialog_message_loop.

    Copyright (C) 2007-2018 kaoru

    $Id$
*/

#include <memory>
#include <sstream>

#include <boost/preprocessor.hpp>
#include <boost/test/unit_test.hpp>

#include <tetengo2/detail/base/widget.h>
#include <tetengo2/detail/stub/widget.h>
#include <tetengo2/gui/message/dialog_message_loop.h>
#include <tetengo2/gui/widget/abstract_window.h>
#include <tetengo2/gui/widget/widget.h>


namespace {
    // types

    using abstract_window_type = tetengo2::gui::widget::abstract_window;

    using dialog_message_loop_type = tetengo2::gui::message::dialog_message_loop;

    class concrete_window : public abstract_window_type
    {
    public:
        concrete_window()
        : abstract_window_type{ abstract_window_type::scroll_bar_style_type::none, false, message_handler_map_type{} },
          m_p_details{ std::make_unique<tetengo2::detail::stub::widget::widget_details_type>() }
        {
            abstract_window_type::initialize(this);
        }

        virtual ~concrete_window() = default;


    private:
        typename widget_details_type::widget_details_ptr_type m_p_details;

        virtual const details_type& details_impl() const override
        {
            return *static_cast<const details_type*>(m_p_details.get());
        }

        virtual details_type& details_impl() override
        {
            return *static_cast<details_type*>(m_p_details.get());
        }
    };
}


BOOST_AUTO_TEST_SUITE(test_tetengo2)
    BOOST_AUTO_TEST_SUITE(gui)
        BOOST_AUTO_TEST_SUITE(message)
            BOOST_AUTO_TEST_SUITE(dialog_message_loop)
                // test cases

                BOOST_AUTO_TEST_CASE(construction)
                {
                    BOOST_TEST_PASSPOINT();

                    concrete_window                window{};
                    const dialog_message_loop_type dialog_message_loop{ window };
                }

                BOOST_AUTO_TEST_CASE(operator_paren)
                {
                    BOOST_TEST_PASSPOINT();

                    concrete_window                window{};
                    const dialog_message_loop_type dialog_message_loop{ window };

                    dialog_message_loop();
                }


            BOOST_AUTO_TEST_SUITE_END()
        BOOST_AUTO_TEST_SUITE_END()
    BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()
