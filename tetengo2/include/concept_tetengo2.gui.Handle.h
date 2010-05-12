/*! \file
    \brief The definition of concept_concept_tetengo2::gui::Handle.

    Copyright (C) 2007-2010 kaoru

    $Id$
*/

#if !defined(CONCEPTTETENGO2_GUI_HANDLE_H)
#define CONCEPTTETENGO2_GUI_HANDLE_H

#include <boost/concept_check.hpp>


namespace concept_tetengo2 { namespace gui
{
    /*!
        \brief The concept check class template for a handle.

        \tparam Type A type.
    */
    template <typename Type>
    class Handle :
        private boost::CopyConstructible<Type>,
        private boost::Convertible<Type, const void*>,
        private boost::Assignable<Type>,
        private boost::EqualityComparable<Type>
    {
#if !defined(DOCUMENTATION)
    public:
        // usage checks

        BOOST_CONCEPT_USAGE(Handle)
        {}


#endif
    };


}}

#endif
