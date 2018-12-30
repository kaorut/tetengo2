/*! \file
    \brief The definition of tetengo2::gui::widget::progress_bar.

    Copyright (C) 2007-2019 kaoru

    $Id$
*/

#if !defined(TETENGO2_GUI_WIDGET_PROGRESSBAR_H)
#define TETENGO2_GUI_WIDGET_PROGRESSBAR_H

#include <memory>

#include <tetengo2/gui/widget/control.h>
#include <tetengo2/type_list.h>


namespace tetengo2::gui::widget {
    class widget;


    /*!
        \brief The class for a progress bar.
    */
    class progress_bar : public control
    {
    public:
        // types

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
        explicit progress_bar(widget& parent);

        /*!
            \brief Destroys the progress bar.
        */
        virtual ~progress_bar() noexcept;


        // functions

        /*!
            \brief Returns the goal.

            \return The goal.
        */
        size_type goal() const;

        /*!
            \brief Sets a goal.

            \param goal A goal.
        */
        void set_goal(size_type goal);

        /*!
            \brief Returns the progress.

            \return The progress.
        */
        size_type progress() const;

        /*!
            \brief Sets a progress.

            \param progress A progress.
        */
        void set_progress(size_type progress);

        /*!
            \brief Returns the state.

            \return The state.
        */
        state_type state() const;

        /*!
            \brief Sets a state.

            \param state A state.
        */
        void set_state(state_type state);


    private:
        // types

        class impl;


        // variables

        const std::unique_ptr<impl> m_p_impl;
    };
}


#endif
