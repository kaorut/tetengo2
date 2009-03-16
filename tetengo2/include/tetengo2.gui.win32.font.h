/*! \file
    \brief The definition of tetengo2::gui::win32::font.

    Copyright (C) 2007-2009 kaoru

    $Id$
*/

#if !defined(TETENGO2_GUI_WIN32_FONT_H)
#define TETENGO2_GUI_WIN32_FONT_H

//#include <boost/concept_check.hpp>
#include <boost/operators.hpp>

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
    class font : public boost::equality_comparable<font<String, Size> >
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
            \brief Copies a font.

            \param another Another font object.
        */
        font(const font& another)
        {}

        /*!
            \brief Destroys the font.
        */
        virtual ~font()
        throw ()
        {}


        // functions

        /*!
            \brief Swaps the members with another font object.

            \param another Another font object.
        */
        void swap(font& another)
        throw ()
        {

        }

        /*!
            \brief Assigns another font object.

            \param another Another font object.

            \return this object.
        */
        font& operator=(const font& another)
        {
            font(another).swap(*this);
            return *this;
        }

        /*!
            \brief Checks whether this is equal to anther font object.

            \param another Another font object.

            \retval true  When this is equal to another.
            \retval false Otherwise.
        */
        bool operator==(const font& another)
        const
        {
            return true;
        }


    };


}}}

namespace std
{
    /*!
        \brief Swaps two font objects.

        \tparam String A string type. It must conform to
                       concept_tetengo2::String<String>.
        \tparam Size   A size type. It must conform to
                       boost::UnsignedInteger<Size>.

        \param font1 A font object #1.
        \param font2 A font object #2.
    */
    template <typename String, typename Size>
    void swap(
        tetengo2::gui::win32::font<String, Size>& font1,
        tetengo2::gui::win32::font<String, Size>& font2
    )
    throw ()
    {
        BOOST_CONCEPT_ASSERT((concept_tetengo2::String<String>));
        BOOST_CONCEPT_ASSERT((boost::UnsignedInteger<Size>));

        font1.swap(font2);
    }


}

#endif
