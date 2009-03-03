/*! \file
    \brief The definition of concept_bobura::AboutDialog.

    Copyright (C) 2007-2009 kaoru

    $Id$
*/

#if !defined(CONCEPTBOBURA_ABOUTDIALOG_H)
#define CONCEPTBOBURA_ABOUTDIALOG_H

//#include <boost/concept_check.hpp>

#include <concept_tetengo2.gui.Dialog.h>


namespace concept_bobura
{
    /*!
        \brief The concept check class template for about_dialog.

        \tparam Type A type.
    */
    template <typename Type>
    class AboutDialog : public concept_tetengo2::gui::Dialog<Type>
    {
#if !defined(DOCUMENTATION)
    public:
        // typedef checks

        typedef typename Type::command_type_list_type command_type_list_type;

        typedef typename Type::message_type_list_type message_type_list_type;


        // usage checks

        BOOST_CONCEPT_USAGE(AboutDialog)
        {}


#endif
    };


}

#endif
