/*! \file
    \brief The definition of tetengo2::gui::win32::font.

    Copyright (C) 2007-2009 kaoru

    $Id$
*/

#if !defined(TETENGO2_GUI_WIN32_FONT_H)
#define TETENGO2_GUI_WIN32_FONT_H

//#include <boost/concept_check.hpp>

#define NOMINMAX
#define OEMRESOURCE
#include <windows.h>

#include "concept_tetengo2.String.h"


namespace tetengo2 { namespace gui { namespace win32
{
    /*!
        \brief The class template for a font for Win32 platforms.
 
        \tparam String A string type. It must conform to
                       concept_tetengo2::String<String>.
        \tparam Size   A size type. It must conform to
                       boost::UnsignedInteger<Size>.
   */
    template <typename String, typename Size>
    class font
    {
    private:
        // concept checks

        BOOST_CONCEPT_ASSERT((concept_tetengo2::String<String>));
        BOOST_CONCEPT_ASSERT((boost::UnsignedInteger<Size>));


    public:
        // types

        //! The string type.
        typedef String string_type;

        //! The size type.
        typedef Size size_type;


        // constructors and destructor

        /*!
            \brief Creates a font.

            \param family A family.
            \param size   A size.
        */
        font(const string_type& family, const size_type size)
        {}

        /*!
            \brief Destroys the font.
        */
        virtual ~font()
        throw ()
        {}


        // functions


    };


}}}

#endif
