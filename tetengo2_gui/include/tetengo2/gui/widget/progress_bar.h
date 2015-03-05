/*! \file
    \brief The definition of tetengo2::gui::widget::progress_bar.

    Copyright (C) 2007-2015 kaoru

    $Id$
*/

#if !defined(TETENGO2_GUI_WIDGET_PROGRESSBAR_H)
#define TETENGO2_GUI_WIDGET_PROGRESSBAR_H

#include <boost/predef.h>

#include <tetengo2/gui/widget/control.h>
#include <tetengo2/stdalt.h>


namespace tetengo2 { namespace gui { namespace widget
{
    /*!
        \brief The class template for a progress bar.

        \tparam Traits        A traits type.
        \tparam DetailsTraits A detail implementation type traits.
    */
    template <typename Traits, typename DetailsTraits>
    class progress_bar : public control<Traits, DetailsTraits>
    {
    public:
        // types

        //! The traits type.
        using traits_type = Traits;

        //! The size type.
        using size_type = typename traits_type::size_type;

        //! The details traits type.
        using details_traits_type = DetailsTraits;

        //! The widget details type.
        using widget_details_type = typename details_traits_type::widget_details_type;

        //! The message handler details type.
        using message_handler_details_type = typename details_traits_type::message_handler_details_type;

        //! The base type.
        using base_type = control<traits_type, details_traits_type>;

        //! The widget type.
        using widget_type = typename base_type::base_type;

        //! The state type.
        enum class state_type
        {
            running, //!< The running state.
            pausing, //!< The pausing state.
            error,   //!< The error state.
        };


        // constructors and destructor

        /*!
            \brief Creates a progress bar.

            \param parent A parent widget.
        */
        explicit progress_bar(widget_type& parent)
        :
#if BOOST_COMP_MSVC
#   pragma warning(push)
#   pragma warning(disable: 4355)
#endif
        base_type(
            base_type::scroll_bar_style_type::none,
            message_handler_details_type::make_button_message_handler_map(*this, message_handler_map_type{}),
            widget_details_type::create_progress_bar(parent)
        )
#if BOOST_COMP_MSVC
#   pragma warning(pop)
#endif
        {
            base_type::initialize(this);
        }

        /*!
            \brief Destroys the progress bar.
        */
        virtual ~progress_bar()
        TETENGO2_STDALT_DESTRUCTOR_DEFAULT_IMPLEMENTATION;


        // functions

        /*!
            \brief Returns the goal.

            \return The goal.
        */
        size_type goal()
        const
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
        size_type progress()
        const
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
        state_type state()
        const
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


}}}


#endif
