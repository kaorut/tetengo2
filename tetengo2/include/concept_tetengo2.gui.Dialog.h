/*! \file
    \brief The definition of concept_tetengo2::gui::Dialog.

    Copyright (C) 2007-2010 kaoru

    $Id$
*/

#if !defined(CONCEPTTETENGO2_GUI_DIALOG_H)
#define CONCEPTTETENGO2_GUI_DIALOG_H

//#include <boost/concept_check.hpp>

#include "concept_tetengo2.gui.AbstractWindow.h"


namespace concept_tetengo2 { namespace gui
{
    /*!
        \brief The concept check class template for a dialog.

        \tparam Type A type.
    */
    template <typename Type>
    class Dialog : private AbstractWindow<Type>
    {
#if !defined(DOCUMENTATION)
    public:
        // typedef checks

        typedef typename Type::base_type base_type;

        typedef typename Type::message_loop_type message_loop_type;

        typedef typename Type::quit_message_loop_type quit_message_loop_type;

        typedef typename Type::result_type result_type;


        // usage checks

        BOOST_CONCEPT_USAGE(Dialog)
        {
            const result_type result = m_object.do_modal();
            boost::ignore_unused_variable_warning(result);

            m_object.set_result(result_type());

            const_constraints(m_object);
        }

        void const_constraints(const Type& object)
        {
            const result_type result = object.result();
            boost::ignore_unused_variable_warning(result);
        }


    private:
        // variables

        Type m_object;


#endif
    };


}}

#endif
