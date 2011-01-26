/*! \file
    \brief The definition of stub_tetengo2::gui::drawing::font.

    Copyright (C) 2007-2011 kaoru

    $Id$
*/

#if !defined(STUBTETENGO2_GUI_FONT_H)
#define STUBTETENGO2_GUI_FONT_H

#include <utility>

#include <boost/operators.hpp>

#include "tetengo2.text.h"


namespace stub_tetengo2 { namespace gui { namespace drawing
{
    template <typename String, typename Size>
    class font : private boost::equality_comparable<font<String, Size>>
    {
    public:
        // types

        typedef String string_type;

        typedef Size size_type;


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


        // constructors and destructor

        template <typename S>
        font(
            S&&             family,
            const size_type size,
            const bool      bold,
            const bool      italic,
            const bool      underline,
            const bool      strikeout
        )
        :
        m_family(std::forward<S>(family)),
        m_size(size),
        m_bold(bold),
        m_italic(italic),
        m_underline(underline),
        m_strikeout(strikeout)
        {}


        // functions

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


}}}


#endif
