/*! \file
    \brief Test of class tetengo2::gui::widget::widget.

    Copyright (C) 2007-2012 kaoru

    $Id$
*/

//#include <cstddef>
//#include <memory>
//#include <stdexcept>
//#include <tuple>
//#include <utility>
//#include <vector>

//#include <boost/mpl/at.hpp>
//#include <boost/optional.hpp>
#include <boost/test/unit_test.hpp>

#include "test_tetengo2.gui.type_list.h"


namespace
{
    // types

    typedef
        boost::mpl::at<
            test_tetengo2::gui::type_list, test_tetengo2::gui::type::string
        >::type
        string_type;

    typedef
        std::tuple<string_type, std::size_t, bool, bool, bool, bool>
        details_font_type;

    typedef
        boost::mpl::at<
            test_tetengo2::gui::widget_type_list,
            test_tetengo2::gui::type::widget::position
        >::type
        position_type;

    typedef
        boost::mpl::at<
            test_tetengo2::gui::widget_type_list,
            test_tetengo2::gui::type::widget::dimension
        >::type
        dimension_type;

    typedef
        boost::mpl::at<
            test_tetengo2::gui::drawing_type_list,
            test_tetengo2::gui::type::drawing::background
        >::type
        background_type;

    typedef
        boost::mpl::at<
            test_tetengo2::gui::drawing_type_list,
            test_tetengo2::gui::type::drawing::transparent_background
        >::type
        transparent_background_type;

    typedef
        boost::mpl::at<
            test_tetengo2::gui::drawing_type_list,
            test_tetengo2::gui::type::drawing::font
        >::type
        font_type;

    typedef
        boost::mpl::at<
            test_tetengo2::gui::cursor_type_list,
            test_tetengo2::gui::type::cursor::system
        >::type
        system_cursor_type;

    typedef
        boost::mpl::at<
            test_tetengo2::gui::widget_type_list,
            test_tetengo2::gui::type::widget::widget
        >::type
        widget_type;

    class concrete_widget : public widget_type
    {
    public:
        static const encoder_type& test_encoder()
        {
            return encoder();
        }

        explicit concrete_widget(widget_type* const p_parent = NULL)
        :
        widget_type(message_handler_map_type()),
        m_p_details(
            tetengo2::make_unique<widget_details_type::widget_details_type>(
                p_parent,
                true,
                true,
                std::make_pair(0, 0),
                std::make_pair(1, 1),
                string_type(),
                details_font_type(
                    string_type(), 12, false, false, false, false
                ),
                std::vector<void*>(),
                false,
                false
            )
        )
        {
            initialize(this);
        }

        virtual ~concrete_widget()
        TETENGO2_CPP11_NOEXCEPT
        {}


    private:
        std::unique_ptr<details_type> m_p_details;

        virtual boost::optional<const details_type&> details_impl()
        const
        {
            return *m_p_details;
        }

        virtual boost::optional<details_type&> details_impl()
        {
            return *m_p_details;
        }


    };

    position_type make_position(
        const std::ptrdiff_t left,
        const std::ptrdiff_t top
    )
    {
        typedef tetengo2::gui::position<position_type>::left_type left_type;
        typedef tetengo2::gui::position<position_type>::top_type top_type;
        return position_type(left_type(left), top_type(top));
    }

    dimension_type make_dimension(
        const std::size_t width,
        const std::size_t height
    )
    {
        typedef
            tetengo2::gui::dimension<dimension_type>::width_type width_type;
        typedef
            tetengo2::gui::dimension<dimension_type>::height_type height_type;
        return dimension_type(width_type(width), height_type(height));
    }

}


BOOST_AUTO_TEST_SUITE(test_tetengo2)
BOOST_AUTO_TEST_SUITE(gui)
BOOST_AUTO_TEST_SUITE(widget)
BOOST_AUTO_TEST_SUITE(widget)
    // test cases

    BOOST_AUTO_TEST_CASE(construction)
    {
        BOOST_TEST_PASSPOINT();

        const concrete_widget widget;
    }

    BOOST_AUTO_TEST_CASE(has_parent)
    {
        BOOST_TEST_PASSPOINT();

        {
            const concrete_widget widget;

            BOOST_CHECK(!widget.has_parent());
        }
        {
            concrete_widget parent;
            const concrete_widget widget(&parent);

            BOOST_CHECK(widget.has_parent());
        }
    }

    BOOST_AUTO_TEST_CASE(parent)
    {
        BOOST_TEST_PASSPOINT();

        {
            const concrete_widget widget;

            BOOST_CHECK_THROW(widget.parent(), std::logic_error);
        }
        {
            concrete_widget parent;
            const concrete_widget widget(&parent);

            BOOST_CHECK_EQUAL(&widget.parent(), &parent);
        }
        {
            concrete_widget parent;
            concrete_widget widget(&parent);

            BOOST_CHECK_EQUAL(&widget.parent(), &parent);
        }
    }

    BOOST_AUTO_TEST_CASE(root_ancestor)
    {
        BOOST_TEST_PASSPOINT();

        {
            const concrete_widget widget;

            BOOST_CHECK_THROW(widget.root_ancestor(), std::logic_error);
        }
        {
            concrete_widget parent;
            const concrete_widget widget(&parent);

            widget.root_ancestor();
        }
        {
            concrete_widget parent;
            concrete_widget widget(&parent);

            widget.root_ancestor();
        }
    }

    BOOST_AUTO_TEST_CASE(enabled)
    {
        BOOST_TEST_PASSPOINT();

        {
            concrete_widget widget;

            widget.set_enabled(true);

            BOOST_CHECK(widget.enabled());
        }
        {
            concrete_widget widget;

            widget.set_enabled(false);

            BOOST_CHECK(!widget.enabled());
        }
    }

    BOOST_AUTO_TEST_CASE(set_enabled)
    {
        BOOST_TEST_PASSPOINT();

        {
            concrete_widget widget;

            widget.set_enabled(true);

            BOOST_CHECK(widget.enabled());
        }
        {
            concrete_widget widget;

            widget.set_enabled(false);

            BOOST_CHECK(!widget.enabled());
        }
    }

    BOOST_AUTO_TEST_CASE(visible)
    {
        BOOST_TEST_PASSPOINT();

        {
            concrete_widget widget;

            widget.set_visible(true);

            BOOST_CHECK(widget.visible());
        }
        {
            concrete_widget widget;

            widget.set_visible(false);

            BOOST_CHECK(!widget.visible());
        }
    }

    BOOST_AUTO_TEST_CASE(set_visible)
    {
        BOOST_TEST_PASSPOINT();

        {
            concrete_widget widget;

            widget.set_visible(true);

            BOOST_CHECK(widget.visible());
        }
        {
            concrete_widget widget;

            widget.set_visible(false);

            BOOST_CHECK(!widget.visible());
        }
    }

    BOOST_AUTO_TEST_CASE(focused)
    {
        BOOST_TEST_PASSPOINT();

        {
            concrete_widget widget;

            widget.focus_observer_set().got_focus()();

            BOOST_CHECK(widget.focused());
        }
        {
            concrete_widget widget;

            widget.focus_observer_set().lost_focus()();

            BOOST_CHECK(!widget.focused());
        }
    }

    BOOST_AUTO_TEST_CASE(position)
    {
        BOOST_TEST_PASSPOINT();

        concrete_widget widget;

        widget.set_position(make_position(123, 456));

        const position_type position = widget.position();
        BOOST_CHECK(position == make_position(123, 456));
    }

    BOOST_AUTO_TEST_CASE(set_position)
    {
        BOOST_TEST_PASSPOINT();

        concrete_widget widget;

        widget.set_position(make_position(123, 456));

        const position_type position = widget.position();
        BOOST_CHECK(position == make_position(123, 456));
    }

    BOOST_AUTO_TEST_CASE(dimension)
    {
        BOOST_TEST_PASSPOINT();

        concrete_widget widget;

        widget.set_dimension(make_dimension(123, 456));

        const dimension_type dimension = widget.dimension();
        BOOST_CHECK(dimension == make_dimension(123, 456));
    }

    BOOST_AUTO_TEST_CASE(set_dimension)
    {
        BOOST_TEST_PASSPOINT();

        concrete_widget widget;

        widget.set_dimension(make_dimension(123, 456));

        const dimension_type dimension = widget.dimension();
        BOOST_CHECK(dimension == make_dimension(123, 456));
    }

    BOOST_AUTO_TEST_CASE(client_dimension)
    {
        BOOST_TEST_PASSPOINT();

        concrete_widget widget;

        widget.set_client_dimension(make_dimension(123, 456));

        const dimension_type client_dimension = widget.client_dimension();
        BOOST_CHECK(client_dimension == make_dimension(123, 456));
    }

    BOOST_AUTO_TEST_CASE(set_client_dimension)
    {
        BOOST_TEST_PASSPOINT();

        concrete_widget widget;

        widget.set_client_dimension(make_dimension(123, 456));

        const dimension_type client_dimension = widget.client_dimension();
        BOOST_CHECK(client_dimension == make_dimension(123, 456));
    }

    BOOST_AUTO_TEST_CASE(text)
    {
        BOOST_TEST_PASSPOINT();

        concrete_widget widget;

        widget.set_text("Tetengo");

        BOOST_CHECK(widget.text() == "Tetengo");
    }

    BOOST_AUTO_TEST_CASE(set_text)
    {
        BOOST_TEST_PASSPOINT();

        concrete_widget widget;

        widget.set_text("Tetengo");

        BOOST_CHECK(widget.text() == "Tetengo");
    }

    BOOST_AUTO_TEST_CASE(background)
    {
        BOOST_TEST_PASSPOINT();

        {
            concrete_widget widget;

            std::unique_ptr<background_type> p_background;
            widget.set_background(std::move(p_background));

            BOOST_CHECK(!widget.background());
        }
        {
            concrete_widget widget;

            std::unique_ptr<background_type> p_background(
                tetengo2::make_unique<transparent_background_type>()
            );
            widget.set_background(std::move(p_background));

            BOOST_CHECK(widget.background());
        }
    }

    BOOST_AUTO_TEST_CASE(set_background)
    {
        BOOST_TEST_PASSPOINT();

        {
            concrete_widget widget;

            std::unique_ptr<background_type> p_background;
            widget.set_background(std::move(p_background));
        }
        {
            concrete_widget widget;

            std::unique_ptr<background_type> p_background(
                tetengo2::make_unique<transparent_background_type>()
            );
            widget.set_background(std::move(p_background));
        }
    }

    BOOST_AUTO_TEST_CASE(font)
    {
        BOOST_TEST_PASSPOINT();

        concrete_widget widget;

        const font_type font(
            font_type::dialog_font().family(), 42, false, true, false, true
        );
        widget.set_font(font);

        BOOST_CHECK(widget.font() == font);
    }

    BOOST_AUTO_TEST_CASE(set_font)
    {
        BOOST_TEST_PASSPOINT();

        concrete_widget widget;

        const font_type font(
            font_type::dialog_font().family(), 42, false, true, false, true
        );
        widget.set_font(font);

        BOOST_CHECK(widget.font() == font);
    }

    BOOST_AUTO_TEST_CASE(cursor)
    {
        BOOST_TEST_PASSPOINT();

        const concrete_widget widget;

        BOOST_CHECK(!widget.cursor());
    }

    BOOST_AUTO_TEST_CASE(set_cursor)
    {
        BOOST_TEST_PASSPOINT();

        concrete_widget widget;

        std::unique_ptr<widget_type::cursor_type> p_cursor(
            tetengo2::make_unique<system_cursor_type>(
                system_cursor_type::style_hand
            )
        );
        widget.set_cursor(std::move(p_cursor));

        const boost::optional<const widget_type::cursor_type&> cursor =
            widget.cursor();
        BOOST_CHECK(cursor);
        BOOST_CHECK(
            dynamic_cast<const system_cursor_type&>(*cursor).style() ==
            system_cursor_type::style_hand
        );
    }

    BOOST_AUTO_TEST_CASE(children)
    {
        BOOST_TEST_PASSPOINT();

        {
            const concrete_widget widget;

            BOOST_CHECK(widget.children().empty());
        }
        {
            concrete_widget widget;
            concrete_widget child1(&widget);
            child1.set_text("hoge");
            concrete_widget child2(&widget);
            child2.set_text("fuga");

            BOOST_CHECK_EQUAL(widget.children().size(), 2U);
            BOOST_CHECK(
                widget.children()[0].get().text() == "hoge" ||
                widget.children()[1].get().text() == "hoge"
            );
            BOOST_CHECK(
                widget.children()[0].get().text() == "fuga" ||
                widget.children()[1].get().text() == "fuga"
            );
        }
    }

    BOOST_AUTO_TEST_CASE(repaint)
    {
        BOOST_TEST_PASSPOINT();

        const concrete_widget widget;

        widget.repaint();
    }

    BOOST_AUTO_TEST_CASE(create_canvas)
    {
        BOOST_TEST_PASSPOINT();

        const concrete_widget widget;

        widget.create_canvas();
    }

    BOOST_AUTO_TEST_CASE(click)
    {
        BOOST_TEST_PASSPOINT();

        {
            const concrete_widget widget;

            widget.click();
        }
        {
            concrete_widget widget;

            widget.click();
        }
    }

    BOOST_AUTO_TEST_CASE(focus_observer_set)
    {
        BOOST_TEST_PASSPOINT();

        {
            const concrete_widget widget;

            widget.focus_observer_set();
        }
        {
            concrete_widget widget;

            widget.focus_observer_set();
        }
    }

    BOOST_AUTO_TEST_CASE(paint_observer_set)
    {
        BOOST_TEST_PASSPOINT();

        {
            const concrete_widget widget;

            widget.paint_observer_set();
        }
        {
            concrete_widget widget;

            widget.paint_observer_set();
        }
    }

    BOOST_AUTO_TEST_CASE(keyboard_observer_set)
    {
        BOOST_TEST_PASSPOINT();

        {
            const concrete_widget widget;

            widget.keyboard_observer_set();
        }
        {
            concrete_widget widget;

            widget.keyboard_observer_set();
        }
    }

    BOOST_AUTO_TEST_CASE(mouse_observer_set)
    {
        BOOST_TEST_PASSPOINT();

        {
            const concrete_widget widget;

            widget.mouse_observer_set();
        }
        {
            concrete_widget widget;

            widget.mouse_observer_set();
        }
    }

    BOOST_AUTO_TEST_CASE(destroyed)
    {
        BOOST_TEST_PASSPOINT();

        {
            const concrete_widget widget;

            BOOST_CHECK(!widget.destroyed());
        }
        {
            concrete_widget widget;
            widget.set_destroyed();

            BOOST_CHECK(widget.destroyed());
        }
    }

    BOOST_AUTO_TEST_CASE(set_destroyed)
    {
        BOOST_TEST_PASSPOINT();

        concrete_widget widget;

        widget.set_destroyed();
    }

    BOOST_AUTO_TEST_CASE(details)
    {
        BOOST_TEST_PASSPOINT();

        {
            const concrete_widget widget;

            widget.details();
        }
        {
            concrete_widget widget;

            widget.details();
        }
    }

    BOOST_AUTO_TEST_CASE(message_handler_map)
    {
        BOOST_TEST_PASSPOINT();

        const concrete_widget widget;

        widget.message_handler_map();
    }

    BOOST_AUTO_TEST_CASE(encoder)
    {
        BOOST_TEST_PASSPOINT();

        // encoder() is called in test_encoder().
        concrete_widget::test_encoder();
    }

    BOOST_AUTO_TEST_CASE(initialize)
    {
        BOOST_TEST_PASSPOINT();

        // initialize() is called in the constructor of concrete_widget.
        const concrete_widget widget;
    }


BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()
