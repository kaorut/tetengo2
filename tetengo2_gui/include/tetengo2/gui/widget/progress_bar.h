/*! \file
    \brief The definition of tetengo2::gui::widget::progress_bar.

    Copyright (C) 2007-2018 kaoru

    $Id$
*/

#if !defined(TETENGO2_GUI_WIDGET_PROGRESSBAR_H)
#define TETENGO2_GUI_WIDGET_PROGRESSBAR_H

#include <boost/predef.h>

#include <tetengo2/gui/widget/control.h>
#include <tetengo2/type_list.h>


namespace tetengo2::gui::widget {
    /*!
        \brief The class template for a progress bar.

        \tparam WidgetDetails         A detail implementation type of a widget.
        \tparam DrawingDetails        A detail implementation type of drawing.
        \tparam ScrollDetails         A detail implementation type of a scroll.
        \tparam MessageHandlerDetails A detail implementation type of a message handler.
    */
    template <typename WidgetDetails, typename DrawingDetails, typename ScrollDetails, typename MessageHandlerDetails>
    class progress_bar : public control<WidgetDetails, DrawingDetails, ScrollDetails, MessageHandlerDetails>
    {
    public:
        // types

        //! The widget details type.
        using widget_details_type = WidgetDetails;

        //! The message handler details type.
        using message_handler_details_type = MessageHandlerDetails;

        //! The base type.
        using base_type = control<WidgetDetails, DrawingDetails, ScrollDetails, MessageHandlerDetails>;

        //! The widget type.
        using widget_type = typename base_type::base_type;

        //! The size type.
        using size_type = tetengo2::type_list::size_type;

        //! The state type.
        enum class state_type
        {
            running, //!< The running state.
            pausing, //!< The pausing state.
            error, //!< The error state.
        };


        // constructors and destructor

        /*!
            \brief Creates a progress bar.

            \param parent A parent widget.
        */
        explicit progress_bar(widget_type& parent)
        :
#if BOOST_COMP_MSVC
#pragma warning(push)
#pragma warning(disable : 4355)
#endif
          base_type
        {
            base_type::scroll_bar_style_type::none,
                message_handler_details_type::make_button_message_handler_map(*this, message_handler_map_type{}),
                widget_details_type::create_progress_bar(parent)
        }
#if BOOST_COMP_MSVC
#pragma warning(pop)
#endif
        {
            base_type::initialize(this);

            parent.child_observer_set().created()(*this);
        }

        /*!
            \brief Destroys the progress bar.
        */
        virtual ~progress_bar() noexcept
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
            \brief Returns the goal.

            \return The goal.
        */
        size_type goal() const
        {
            return widget_details_type::progress_bar_goal(*this);
        }

        /*!
            \brief Sets a goal.

            \param goal A goal.
        */
        void set_goal(const size_type goal)
        {
            widget_details_type::set_progress_bar_goal(*this, goal);
        }

        /*!
            \brief Returns the progress.

            \return The progress.
        */
        size_type progress() const
        {
            return widget_details_type::progress_bar_progress(*this);
        }

        /*!
            \brief Sets a progress.

            \param progress A progress.
        */
        void set_progress(const size_type progress)
        {
            widget_details_type::set_progress_bar_progress(*this, progress);
        }

        /*!
            \brief Returns the state.

            \return The state.
        */
        state_type state() const
        {
            return widget_details_type::progress_bar_state(*this);
        }

        /*!
            \brief Sets a state.

            \param state A state.
        */
        void set_state(const state_type state)
        {
            widget_details_type::set_progress_bar_state(*this, state);
        }


    private:
        // types

        using message_handler_map_type = typename message_handler_details_type::message_handler_map_type;
    };
}


#endif
