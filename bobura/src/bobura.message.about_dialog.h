/*! \file
    \brief The definition of bobura::message::ok_button_mouse_observer.

    Copyright (C) 2007-2010 kaoru

    $Id$
*/

#if !defined(BOBURA_MESSAGE_ABOUTDIALOG_H)
#define BOBURA_MESSAGE_ABOUTDIALOG_H

#include <cassert>
#include <cstddef>

#include <tetengo2.gui.mouse_observer.h>


namespace bobura { namespace message { namespace about_dialog
{
    /*!
        \brief The class template for a mouse observer of the OK button.
        
        \tparam Dialog A dialog type.
    */
    template <typename Dialog>
    class ok_button_mouse_observer :
        public tetengo2::gui::mouse_observer
    {
    public:
        // types

        //! \return The dialog type.
        typedef Dialog dialog_type;


        // constructors and destructor

        /*!
            \brief Creates a mouse observer of the OK button in the about
                   dialog.
            
            \param p_dialog A pointer to a dialog.
        */
        explicit ok_button_mouse_observer(
            dialog_type* const p_dialog
        )
        :
        m_p_dialog(p_dialog)
        {
            assert(m_p_dialog != NULL);
        }

        /*!
            \brief Destroys the mouse observer of the OK button in the about
                   dialog.
        */
        virtual ~ok_button_mouse_observer()
        throw ()
        {}


        // functions

        //! \copydoc tetengo2::gui::mouse_observer::clicked.
        virtual void clicked()
        {
            m_p_dialog->set_result(dialog_type::result_accepted);
            m_p_dialog->close();
        }


    private:
        // variables

        dialog_type* const m_p_dialog;


    };


}}}


#endif
