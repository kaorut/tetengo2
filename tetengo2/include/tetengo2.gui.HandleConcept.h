/*! \file
    \brief The definition of tetengo2::gui::HandleConcept.

    Copyright (C) 2007-2008 kaoru

    $Id$
*/

#if !defined(TETENGO2_GUI_HANDLECONCEPT_H)
#define TETENGO2_GUI_HANDLECONCEPT_H

#include <boost/concept_check.hpp>


namespace tetengo2 { namespace gui
{
    /*!
        \brief The concept check class template for handles.

        \tparam Handle A handle type.
    */
    template <typename Handle>
    class HandleConcept :
        private boost::CopyConstructible<Handle>,
        private boost::Convertible<Handle, const void*>,
        private boost::Assignable<Handle>,
        private boost::EqualityComparable<Handle>
    {
#if !defined(DOCUMENTATION)
    public:
        // usage checks

        BOOST_CONCEPT_USAGE(HandleConcept)
        {}


#endif
    };


}}

#endif
