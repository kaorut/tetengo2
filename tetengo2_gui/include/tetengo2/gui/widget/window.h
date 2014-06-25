/*! \file
    \brief The definition of tetengo2::gui::widget::window.

    Copyright (C) 2007-2014 kaoru

    $Id$
*/

#if !defined(TETENGO2_GUI_WIDGET_WINDOW_H)
#define TETENGO2_GUI_WIDGET_WINDOW_H

#include <cassert>

#include <boost/predef.h>

#include <tetengo2/gui/widget/abstract_window.h>
#include <tetengo2/stdalt.h>


namespace tetengo2 { namespace gui { namespace widget
{
    /*!
        \brief The class template for a window.

        \tparam Traits                A traits type.
        \tparam WidgetDetails         A detail implementation type of a widget.
        \tparam DrawingDetails        A detail implementation type of drawing.
        \tparam IconDetails           A detail implementation type of an icon.
        \tparam AlertDetails          A detail implementation type of an alert.
        \tparam CursorDetails         A detail implementation type of a cursor.
        \tparam ScrollDetails         A detail implementation type of a scroll.
        \tparam MessageHandlerDetails A detail implementation type of a message handler.
        \tparam VirtualKeyDetails     A detail implementation type of a virtual key.
        \tparam MenuDetails           A detail implementation type of a menu.
    */
    template <
        typename Traits,
        typename WidgetDetails,
        typename DrawingDetails,
        typename IconDetails,
        typename AlertDetails,
        typename CursorDetails,
        typename ScrollDetails,
        typename MessageHandlerDetails,
        typename VirtualKeyDetails,
        typename MenuDetails
    >
    class window :
        public abstract_window<
            typename Traits::base_type,
            WidgetDetails,
            DrawingDetails,
            IconDetails,
            AlertDetails,
            CursorDetails,
            ScrollDetails,
            MessageHandlerDetails,
            VirtualKeyDetails,
            MenuDetails
        >
    {
    public:
        // types

        //! The traits type.
        using traits_type = Traits;

        //! The detail implementation type of a widget.
        using widget_details_type = WidgetDetails;

        //! The drawing details type.
        using drawing_details_type = DrawingDetails;

        //! The icon details type.
        using icon_details_type = IconDetails;

        //! The alert details type.
        using alert_details_type = AlertDetails;

        //! The cursor details type.
        using cursor_details_type = CursorDetails;

        //! The scroll details type.
        using scroll_details_type = ScrollDetails;

        //! The message handler details type.
        using message_handler_details_type = MessageHandlerDetails;

        //! The virtual key details type.
        using virtual_key_details_type = VirtualKeyDetails;

        //! The menu details type.
        using menu_details_type = MenuDetails;

        //! The base type.
        using base_type =
            abstract_window<
                typename traits_type::base_type,
                widget_details_type,
                drawing_details_type,
                icon_details_type,
                alert_details_type,
                cursor_details_type,
                scroll_details_type,
                message_handler_details_type,
                virtual_key_details_type,
                menu_details_type
            >;

        //! The string type.
        using string_type = typename base_type::string_type;

        //! The icon type.
        using icon_type = typename base_type::icon_type;

        //! The detail implementation type.
        using details_type = typename widget_details_type::widget_details_type;

        //! The detail implementation pointer type.
        using details_ptr_type = typename widget_details_type::widget_details_ptr_type;

        //! The scroll bar style type.
        using scroll_bar_style_type = typename base_type::scroll_bar_style_type;

        //! The window state type.
        using window_state_type = typename base_type::window_state_type;


        // constructors and destructor

        /*!
            \brief Creates a top level window.

            \param scroll_bar_style A scroll bar style.
            \param file_droppable   Set true to enable file drop.
        */
        explicit window(
            const scroll_bar_style_type scroll_bar_style = base_type::scroll_bar_style_type::none,
            const bool file_droppable = false
        )
        :
        base_type(scroll_bar_style, file_droppable, message_handler_map_type{}),
        m_p_details(
            widget_details_type::template create_window<typename base_type::base_type>(
                nullptr, scroll_bar_style, file_droppable
            )
        )
        {
            initialize_window();
        }

        /*!
            \brief Creates a owned window.

            \param parent           A parent window.
            \param scroll_bar_style A scroll bar style.
            \param file_droppable   Set true to enable file drop.
        */
        window(base_type& parent, const scroll_bar_style_type scroll_bar_style, const bool file_droppable)
        :
#if BOOST_COMP_MSVC
#   pragma warning(push)
#   pragma warning(disable: 4355)
#endif
        base_type(
            scroll_bar_style,
            file_droppable,
            message_handler_details_type::make_window_message_handler_map(*this, message_handler_map_type{})
        ),
#if BOOST_COMP_MSVC
#   pragma warning(pop)
#endif
        m_p_details(
            widget_details_type::template create_window<typename base_type::base_type>(
                &parent, scroll_bar_style, file_droppable
            )
        )
        {
            initialize_window();
        }

        /*!
            \brief Destroys the window.
        */
        virtual ~window()
        TETENGO2_STDALT_DESTRUCTOR_DEFAULT_IMPLEMENTATION;


    private:
        // types

        using message_handler_map_type = typename message_handler_details_type::message_handler_map_type;


        // variables

        const details_ptr_type m_p_details;


        // virtual functions

        virtual const details_type& details_impl()
        const override
        {
            assert(m_p_details);
            return *m_p_details;
        }

        virtual details_type& details_impl()
        override
        {
            assert(m_p_details);
            return *m_p_details;
        }


        // functions

        void initialize_window()
        {
            this->initialize(this);
        }


    };


}}}


#endif
