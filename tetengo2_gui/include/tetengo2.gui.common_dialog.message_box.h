/*! \file
    \brief The definition of tetengo2::gui::common_dialog::message_box.

    Copyright (C) 2007-2012 kaoru

    $Id$
*/

#if !defined(TETENGO2_GUI_COMMONDIALOG_MESSAGEBOX_H)
#define TETENGO2_GUI_COMMONDIALOG_MESSAGEBOX_H

#include <utility>
#include <vector>

#include <boost/noncopyable.hpp>

#include "tetengo2.text.h"


namespace tetengo2 { namespace gui { namespace common_dialog
{
    /*!
        \brief The class template for a message box.

        \tparam Widget              A widget type.
        \tparam String              A string type.
        \tparam Encoder             An encoder type.
        \tparam CommonDialogDetails A detail implementation type of common
                                    dialogs.
    */
    template <
        typename Widget,
        typename String,
        typename Encoder,
        typename CommonDialogDetails
    >
    class message_box : private boost::noncopyable
    {
    public:
        // types

        //! The widget type.
        typedef Widget widget_type;

        //! The string type.
        typedef String string_type;

        //! The encoder type.
        typedef Encoder encoder_type;

        //! The detail implementation type of common dialogs.
        typedef CommonDialogDetails common_dialog_details_type;

        //! The detail implementation type.
        typedef
            typename common_dialog_details_type::message_box_details_type
            details_type;

        //! The detail implementaiton pointer type;

        typedef
            typename common_dialog_details_type::message_box_details_ptr_type
            details_ptr_type;


        // constructors and destructor

        /*!
            \brief Creates a message box.

            \tparam S A string type.

            \param title        A title.
            \param parent       A parent widget.
        */
        template <typename S>
        message_box(
            S&&          title,
            S&&          instruction,
            S&&          details,
            widget_type& parent
        )
        :
        m_p_details(
            common_dialog_details_type::create_message_box(
                parent,
                std::forward<S>(title),
                std::forward<S>(instruction),
                std::forward<S>(details),
                common_dialog_details_type::message_box_style_ok_cancel,
                encoder()
            )
        )
        {}


        // functions

        /*!
            \brief Shows the dialog as model.
        */
        void do_modal()
        {
            common_dialog_details_type::show_message_box(*m_p_details);
        }

        /*!
            \brief Returns the detail implementation.

            \return The detail implementation.
        */
        const details_type& details()
        const
        {
            return *m_p_details;
        }

        /*!
            \brief Returns the detail implementation.

            \return The detail implementation.
        */
        details_type& details()
        {
            return *m_p_details;
        }


    private:
        // static functions

        static const encoder_type& encoder()
        {
            static const encoder_type singleton;
            return singleton;
        }


        // variables

        details_ptr_type m_p_details;


    };


}}}


#endif
