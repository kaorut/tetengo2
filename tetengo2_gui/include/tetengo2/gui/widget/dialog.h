/*! \file
    \brief The definition of tetengo2::gui::widget::dialog.

    Copyright (C) 2007-2018 kaoru

    $Id$
*/

#if !defined(TETENGO2_GUI_WIDGET_DIALOG_H)
#define TETENGO2_GUI_WIDGET_DIALOG_H

#include <memory>

#include <tetengo2/gui/widget/abstract_window.h>
#include <tetengo2/gui/widget/widget.h>


namespace tetengo2::gui::widget {
    /*!
        \brief The class for a modal dialog.
    */
    class dialog : public abstract_window
    {
    public:
        // types

        //! The result type.
        enum class result_type
        {
            undecided, //!< The result is not decided yet.
            accepted, //!< The settings are accepted.
            canceled, //!< The settings are canceled.
        };


        // constructors and destructor

        /*!
            \brief Creates a dialog.

            \param parent         A parent window.
            \param file_droppable Set true to enable file drop.
        */
        explicit dialog(abstract_window& parent, bool file_droppable = false);

        /*!
            \brief Destroys the dialog.
        */
        virtual ~dialog() noexcept;


        // functions

        /*!
            \brief Returns the result.

            \return The result.
        */
        result_type result() const;

        /*!
            \brief Sets the result.

            \param result A result.
        */
        void set_result(result_type result);

        /*!
            \brief Shows the dialog as modal.
        */
        void do_modal();


    private:
        // types

        class impl;


        // variables

        const std::unique_ptr<impl> m_p_impl;


        // virtual functions

        virtual void set_result_impl();

        virtual void do_modal_impl();

        virtual void on_close_impl(bool& cancel);

        virtual const details_type& details_impl() const override;

        virtual details_type& details_impl() override;
    };
}


#endif
