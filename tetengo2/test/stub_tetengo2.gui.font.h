/*! \file
    \brief The definition of stub_tetengo2::gui::font.

    Copyright (C) 2007-2009 kaoru

    $Id$
*/

#if !defined(STUBTETENGO2_GUI_FONT_H)
#define STUBTETENGO2_GUI_FONT_H

#include <algorithm>

//#include <boost/concept_check.hpp>
#include <boost/operators.hpp>

#include "concept_tetengo2.String.h"


namespace stub_tetengo2 { namespace gui
{
    template <typename String, typename Size>
    class font : public boost::equality_comparable<font<String, Size> >
    {
    private:
        // concept checks

        BOOST_CONCEPT_ASSERT((concept_tetengo2::String<String>));
        BOOST_CONCEPT_ASSERT((boost::UnsignedInteger<Size>));


    public:
        // types

        typedef String string_type;

        typedef Size size_type;


        // constructors and destructor

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

        font(const font& another)
        :
        m_family(another.m_family),
        m_size(another.m_size),
        m_bold(another.m_bold),
        m_italic(another.m_italic),
        m_underline(another.m_underline),
        m_strikeout(another.m_strikeout)
        {}

        virtual ~font()
        throw ()
        {}


        // functions

        void swap(font& another)
        {
            m_family.swap(another.m_family);
            std::swap(m_size, another.m_size);
            std::swap(m_bold, another.m_bold);
            std::swap(m_italic, another.m_italic);
            std::swap(m_underline, another.m_underline);
            std::swap(m_strikeout, another.m_strikeout);
        }

        font& operator=(const font& another)
        {
            font(another).swap(*this);
            return *this;
        }

        bool operator==(const font& another)
        const
        {
            return true;
        }

        const string_type& family()
        const
        {
            return m_family;
        }

        size_type size()
        const
        {
            return m_size;
        }

        bool bold()
        const
        {
            return m_bold;
        }

        bool italic()
        const
        {
            return m_italic;
        }

        bool underline()
        const
        {
            return m_underline;
        }

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


}}


namespace std
{
    template <typename String, typename Size>
    void swap(
        stub_tetengo2::gui::font<String, Size>& font1,
        stub_tetengo2::gui::font<String, Size>& font2
    )
    throw ()
    {
        BOOST_CONCEPT_ASSERT((concept_tetengo2::String<String>));
        BOOST_CONCEPT_ASSERT((boost::UnsignedInteger<Size>));

        font1.swap(font2);
    }

    
}


#endif
