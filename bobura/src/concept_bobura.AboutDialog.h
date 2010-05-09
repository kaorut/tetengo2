/*! \file
    \brief The definition of concept_bobura::AboutDialog.

    Copyright (C) 2007-2010 kaoru

    $Id$
*/

#if !defined(CONCEPTBOBURA_ABOUTDIALOG_H)
#define CONCEPTBOBURA_ABOUTDIALOG_H //!< !! Include Guard !!

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
        // usage checks

        BOOST_CONCEPT_USAGE(AboutDialog)
        {}


#endif
    };


}

#endif
