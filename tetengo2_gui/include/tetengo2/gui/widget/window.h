/*! \file
    \brief The definition of tetengo2::gui::widget::window.

    Copyright (C) 2007-2018 kaoru

    $Id$
*/

#if !defined(TETENGO2_GUI_WIDGET_WINDOW_H)
#define TETENGO2_GUI_WIDGET_WINDOW_H

#include <cassert>

#include <boost/predef.h>

#include <tetengo2/gui/widget/abstract_window.h>
#include <tetengo2/gui/widget/widget.h>


namespace tetengo2::gui::widget {
    /*!
        \brief The class for a window.
    */
    class window : public abstract_window
    {
    public:
        // constructors and destructor

        /*!
            \brief Creates a top level window.

            \param scroll_bar_style A scroll bar style.
            \param file_droppable   Set true to enable file drop.
        */
        explicit window(
            const scroll_bar_style_type scroll_bar_style = abstract_window::scroll_bar_style_type::none,
            const bool                  file_droppable = false)
        : abstract_window{ scroll_bar_style, file_droppable, message_handler_map_type{} }, m_p_details{
              widget_details_type::instance().create_window(
                  nullptr,
                  static_cast<widget_details_type::scroll_bar_style_type>(scroll_bar_style),
                  file_droppable)
          }
        {
            initialize_window();
        }

        /*!
            \brief Creates a owned window.

            \param parent           A parent window.
            \param scroll_bar_style A scroll bar style.
            \param file_droppable   Set true to enable file drop.
        */
        window(abstract_window& parent, const scroll_bar_style_type scroll_bar_style, const bool file_droppable)
        :
#if BOOST_COMP_MSVC
#pragma warning(push)
#pragma warning(disable : 4355)
#endif
          abstract_window{
              scroll_bar_style,
              file_droppable,
              message_handler_details_type::make_window_message_handler_map(*this, message_handler_map_type{})
          },
#if BOOST_COMP_MSVC
#pragma warning(pop)
#endif
          m_p_details{ widget_details_type::instance().create_window(
              &parent,
              static_cast<widget_details_type::scroll_bar_style_type>(scroll_bar_style),
              file_droppable) }
        {
            initialize_window();

            parent.child_observer_set().created()(*this);
        }

        /*!
            \brief Destroys the window.
        */
        virtual ~window() noexcept
        {
            try
            {
                if (this->has_parent())
                    this->parent().child_observer_set().destroying()(*this);
            }
            catch (...)
            {
            }
        }


    private:
        // types

        using message_handler_map_type = typename message_handler_details_type::message_handler_map_type;


        // variables

        const typename widget_details_type::widget_details_ptr_type m_p_details;


        // virtual functions

        virtual const details_type& details_impl() const override
        {
            assert(m_p_details);
            return *static_cast<const details_type*>(m_p_details.get());
        }

        virtual details_type& details_impl() override
        {
            assert(m_p_details);
            return *static_cast<details_type*>(m_p_details.get());
        }


        // functions

        void initialize_window()
        {
            abstract_window::initialize(this);
        }
    };
}


#endif
