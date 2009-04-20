/*! \file
    \brief The definition of bobura::message::about_dialog_ok_button_mouse_observer.

    Copyright (C) 2007-2009 kaoru

    $Id$
*/

#if !defined(BOBURA_MESSAGE_ABOUTDIALOGOBSERVERS_H)
#define BOBURA_MESSAGE_ABOUTDIALOGOBSERVERS_H

#include <cassert>
#include <cstddef>

//#include <boost/concept_check.hpp>

#include <tetengo2.gui.mouse_observer.h>
#include <concept_tetengo2.gui.Dialog.h>


namespace bobura { namespace message
{
    /*!
        \brief The class template for a mouse observer of the OK button in the
               about dialog.
        
        \tparam Dialog A dialog type. It must conform to
                       concept_tetengo2::gui::Dialog<Dialog>.
    */
    template <typename Dialog>
    class about_dialog_ok_button_mouse_observer :
        public tetengo2::gui::mouse_observer
    {
    private:
        // concept checks

        BOOST_CONCEPT_ASSERT((concept_tetengo2::gui::Dialog<Dialog>));


    public:
        // types

        //! The dialog type.
        typedef Dialog dialog_type;


        // constructors and destructor

        /*!
            \brief Creates a mouse observer of the OK button in the about
                   dialog.
            
            \param p_dialog A pointer to a dialog.
        */
        explicit about_dialog_ok_button_mouse_observer(
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
        virtual ~about_dialog_ok_button_mouse_observer()
        throw ()
        {}


        // functions

        // The document will be derived from
        // tetengo2::gui::mouse_observer::clicked.
        virtual void clicked()
        {
            m_p_dialog->set_result(dialog_type::result_accepted);
            m_p_dialog->close();
        }


    private:
        // variables

        dialog_type* const m_p_dialog;


    };


}}

#endif
