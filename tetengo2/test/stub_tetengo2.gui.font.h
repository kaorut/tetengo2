/*! \file
    \brief The definition of stub_tetengo2::gui::font.

    Copyright (C) 2007-2010 kaoru

    $Id$
*/

#if !defined(STUBTETENGO2_GUI_FONT_H)
#define STUBTETENGO2_GUI_FONT_H

#include <vector>

#include <boost/operators.hpp>
#include <boost/swap.hpp>

#include "tetengo2.assignable.h"
#include "tetengo2.cpp0x_keyword.h"
#include "tetengo2.swappable.h"
#include "tetengo2.text.h"


namespace stub_tetengo2 { namespace gui
{
    template <typename String, typename Size>
    class font :
        public tetengo2::assignable<font<String, Size>>,
        private tetengo2::swappable<font<String, Size>>,
        private boost::equality_comparable<font<String, Size>>
    {
    public:
        // types

        typedef String string_type;

        typedef Size size_type;

        typedef std::vector<string_type> families_type;


        // static functions

        static const font& dialog_font()
        {
            static const font singleton(
                string_type(TETENGO2_TEXT("MS UI Gothic")),
                12,
                false,
                false,
                false,
                false
            );
            return singleton;
        }

        static const families_type& installed_families()
        {
            static const families_type singleton;
            return singleton;
        }


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
        TETENGO2_NOEXCEPT
        {}


        // functions

        void swap(font& another)
        TETENGO2_NOEXCEPT
        {
            boost::swap(m_family, another.m_family);
            boost::swap(m_size, another.m_size);
            boost::swap(m_bold, another.m_bold);
            boost::swap(m_italic, another.m_italic);
            boost::swap(m_underline, another.m_underline);
            boost::swap(m_strikeout, another.m_strikeout);
        }

        font& operator=(const font& another)
        {
            return assign(another);
        }

        friend bool operator==(const font& one, const font& another)
        {
            return one.m_family == another.m_family &&
                one.m_size == another.m_size &&
                one.m_bold == another.m_bold &&
                one.m_italic == another.m_italic &&
                one.m_underline == another.m_underline &&
                one.m_strikeout == another.m_strikeout;
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


#endif
