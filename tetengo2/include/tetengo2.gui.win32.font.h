/*! \file
    \brief The definition of tetengo2::gui::win32::font.

    Copyright (C) 2007-2009 kaoru

    $Id$
*/

#if !defined(TETENGO2_GUI_WIN32_FONT_H)
#define TETENGO2_GUI_WIN32_FONT_H

#include <algorithm>

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

            \param family    A family.
            \param size      A size.
            \param bold      Whether this font is bold.
            \param italic    Whether this font is italic.
            \param underline Whether this font is underlined.
            \param strikeout Whether this font is striked out.
        */
        font(
            const string_type& family,
            const size_type    size,
            const bool         bold,
            const bool         italic,
            const bool         underline,
            const bool         strikeout
        )
        :
        m_family(family),
        m_size(size),
        m_bold(bold),
        m_italic(italic),
        m_underline(underline),
        m_strikeout(strikeout)
        {}

        /*!
            \brief Copies a font.

            \param another Another font object.
        */
        font(const font& another)
        :
        m_family(another.m_family),
        m_size(another.m_size),
        m_bold(another.m_bold),
        m_italic(another.m_italic),
        m_underline(another.m_underline),
        m_strikeout(another.m_strikeout)
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
            m_family.swap(another.m_family);
            std::swap(m_size, another.m_size);
            std::swap(m_bold, another.m_bold);
            std::swap(m_italic, another.m_italic);
            std::swap(m_underline, another.m_underline);
            std::swap(m_strikeout, another.m_strikeout);
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

        /*!
            \brief Returns the family.

            \return The family.
        */
        const string_type& family()
        const
        {
            return m_family;
        }

        /*!
            \brief Returns the size.

            \return The size.
        */
        size_type size()
        const
        {
            return m_size;
        }

        /*!
            \brief Returns whether this font is bold.

            \retval true  This font is bold.
            \retval false Otherwise.
        */
        bool bold()
        const
        {
            return m_bold;
        }

        /*!
            \brief Returns whether this font is italic.

            \retval true  This font is italic.
            \retval false Otherwise.
        */
        bool italic()
        const
        {
            return m_italic;
        }

        /*!
            \brief Returns whether this font is underlined.

            \retval true  This font is underlined.
            \retval false Otherwise.
        */
        bool underline()
        const
        {
            return m_underline;
        }

        /*!
            \brief Returns whether this font is striked out.

            \retval true  This font is striked out.
            \retval false Otherwise.
        */
        bool strikeout()
        const
        {
            return m_strikeout;
        }


    private:
        // variables

        string_type m_family;

        size_type m_size;

        bool m_bold;

        bool m_italic;

        bool m_underline;

        bool m_strikeout;


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
