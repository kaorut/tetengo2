/*! \file
    \brief The definition of concept_tetengo2::gui::Font.

    Copyright (C) 2007-2009 kaoru

    $Id$
*/

#if !defined(CONCEPTTETENGO2_GUI_FONT_H)
#define CONCEPTTETENGO2_GUI_FONT_H

#include <boost/concept_check.hpp>


namespace concept_tetengo2 { namespace gui
{
    /*!
        \brief The concept check class template for a font.

        \tparam Type A type.
    */
    template <typename Type>
    class Font :
        private boost::CopyConstructible<Type>,
        private boost::Assignable<Type>,
        private boost::EqualityComparable<Type>
    {
#if !defined(DOCUMENTATION)
    public:
        // usage checks

        BOOST_CONCEPT_USAGE(Font)
        {}

        
#endif
    };


}}

#endif
