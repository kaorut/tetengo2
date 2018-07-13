/*! \file
    \brief The definition of tetengo2::gui::widget::button.

    Copyright (C) 2007-2018 kaoru

    $Id$
*/

#if !defined(TETENGO2_GUI_WIDGET_BUTTON_H)
#define TETENGO2_GUI_WIDGET_BUTTON_H

#include <boost/predef.h>

#include <tetengo2/gui/widget/control.h>
#include <tetengo2/gui/widget/widget.h>


namespace tetengo2::gui::widget {
    /*!
        \brief The class for a button.
    */
    class button : public control
    {
    public:
        // types

        //! The style type.
        enum class style_type
        {
            normal, //!< A normal button.
            default_, //!< A default button.
            cancel //!< A cancel button.
        };


        // constructors and destructor

        /*!
            \brief Creates a button.

            The window cannot have plural buttons with style_type::default_. And so is style_type::cancel.
            When creating a second button with style_type::default_ or style_type::cancel, std::runtime_error is
            thrown.

            \param parent A parent widget.
            \param style  A style.
        */
        explicit button(widget& parent, const style_type style = style_type::normal)
        :
#if BOOST_COMP_MSVC
#pragma warning(push)
#pragma warning(disable : 4355)
#endif
          control{
              control::scroll_bar_style_type::none,
              message_handler_details_type::make_button_message_handler_map(*this, message_handler_map_type{}),
              widget_details_type::instance().create_button(parent, style == style_type::default_, style == style_type::cancel)
          },
#if BOOST_COMP_MSVC
#pragma warning(pop)
#endif
          m_style{ style }
        {
            control::initialize(this);

            parent.child_observer_set().created()(*this);
        }

        /*!
            \brief Destroys the button.
        */
        virtual ~button() noexcept
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


        // functions

        /*!
            \brief Returns the style.

            \return The style.
        */
        style_type style() const
        {
            return m_style;
        }


    private:
        // types

        using message_handler_map_type = typename message_handler_details_type::message_handler_map_type;


        // variables

        const style_type m_style;
    };
}


#endif
