/*! \file
    \brief The definition of tetengo2::gui::drawing::font.

    Copyright (C) 2007-2018 kaoru

    $Id$
*/

#include <algorithm>
#include <memory>
#include <string>

#include <tetengo2/detail/stub/drawing.h>
#include <tetengo2/gui/drawing/font.h>


namespace tetengo2::gui::drawing {
    class font::impl
    {
    public:
        // types

        using string_type = font::string_type;

        using size_type = font::size_type;

        using drawing_details_type = detail::stub::drawing;


        // static functions

        static const font& dialog_font()
        {
            static const font singleton{ drawing_details_type::instance().make_dialog_font() };
            return singleton;
        }


        // constructors and destructor

        impl(
            string_type     family,
            const size_type size,
            const bool      bold,
            const bool      italic,
            const bool      underline,
            const bool      strikeout)
        : m_family{ std::move(family) }, m_size{ size }, m_bold{ bold }, m_italic{ italic }, m_underline{ underline },
          m_strikeout{ strikeout }
        {}


        // functions

        friend bool operator_equal(const impl& one, const impl& another)
        {
            return one.m_family == another.m_family && one.m_size == another.m_size && one.m_bold == another.m_bold &&
                   one.m_italic == another.m_italic && one.m_underline == another.m_underline &&
                   one.m_strikeout == another.m_strikeout;
        }

        font& operator_assign(const font& another, font& self)
        {
            impl temp{ *another.m_p_impl };
            *this = std::move(temp);
            return self;
        }

        font& operator_assign(font&& another, font& self)
        {
            *this = std::move(*another.m_p_impl);
            return self;
        }

        const string_type& family() const
        {
            return m_family;
        }

        size_type size() const
        {
            return m_size;
        }

        bool bold() const
        {
            return m_bold;
        }

        bool italic() const
        {
            return m_italic;
        }

        bool underline() const
        {
            return m_underline;
        }

        bool strikeout() const
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


    const font& font::dialog_font()
    {
        return impl::dialog_font();
    }

    font::font(
        string_type     family,
        const size_type size,
        const bool      bold,
        const bool      italic,
        const bool      underline,
        const bool      strikeout)
    : m_p_impl{ std::make_unique<impl>(std::move(family), size, bold, italic, underline, strikeout) }
    {}

    font::font(const font& another) : m_p_impl{ std::make_unique<impl>(*another.m_p_impl) } {}

    font::font(font&& another) : m_p_impl{ std::move(another.m_p_impl) } {}

    font::~font() = default;

    bool operator==(const font& one, const font& another)
    {
        return operator_equal(*one.m_p_impl, *another.m_p_impl);
    }

    font& font::operator=(const font& another)
    {
        return m_p_impl->operator_assign(another, *this);
    }

    font& font::operator=(font&& another)
    {
        return m_p_impl->operator_assign(std::move(another), *this);
    }

    const font::string_type& font::family() const
    {
        return m_p_impl->family();
    }

    font::size_type font::size() const
    {
        return m_p_impl->size();
    }

    bool font::bold() const
    {
        return m_p_impl->bold();
    }

    bool font::italic() const
    {
        return m_p_impl->italic();
    }

    bool font::underline() const
    {
        return m_p_impl->underline();
    }

    bool font::strikeout() const
    {
        return m_p_impl->strikeout();
    }
}
