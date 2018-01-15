/*! \file
    \brief The definition of tetengo2::text::encoding::ascii.

    Copyright (C) 2007-2017 kaoru

    $Id$
*/

#include <memory>
#include <stdexcept>
#include <string>

#include <boost/core/noncopyable.hpp>
#include <boost/iterator/iterator_facade.hpp>
#include <boost/iterator/transform_iterator.hpp>
#include <boost/throw_exception.hpp>

#include <tetengo2/text/encoding/ascii.h>


namespace tetengo2 { namespace text { namespace encoding
{
    class ascii::impl : private boost::noncopyable
    {
    public:
        // types

        using base_type = ascii::base_type;

        using pivot_type = ascii::pivot_type;

        using string_type = ascii::string_type;


        // functions

        const std::string& name_impl()
        const
        {
            static const std::string singleton{ "ASCII" };
            return singleton;
        }

        string_type from_pivot_impl(pivot_type pivot)
        const
        {
            return
                {
                    boost::make_transform_iterator(pivot.begin(), to_ascii),
                    boost::make_transform_iterator(pivot.end(), to_ascii)
                };
        }

        pivot_type to_pivot_impl(string_type string)
        const
        {
            return
                {
                    boost::make_transform_iterator(string.begin(), from_ascii),
                    boost::make_transform_iterator(string.end(), from_ascii)
                };
        }


    private:
        // types

        using pivot_char_type = typename pivot_type::value_type;

        using string_char_type = typename string_type::value_type;


        // static functions

        static string_char_type to_ascii(const pivot_char_type pivot_char)
        {
            return to_ascii_impl(pivot_char);
        }

        static string_char_type to_ascii_impl(const char pivot_char)
        {
            if (pivot_char >= 0)
                return pivot_char;
            else
                return 0x3F;
        }

        static string_char_type to_ascii_impl(const wchar_t pivot_char)
        {
            if (pivot_char <= 0x7F)
                return static_cast<string_char_type>(pivot_char);
            else
                return 0x3F;
        }

        static pivot_char_type from_ascii(const string_char_type ascii_char)
        {
            if (ascii_char < 0)
                BOOST_THROW_EXCEPTION((std::invalid_argument{ "Not ASCII code." }));

            return ascii_char;
        }


    };


    ascii::ascii()
    :
    m_p_impl(std::make_shared<impl>())
    {}

    ascii::~ascii()
    = default;

    const std::string& ascii::name_impl()
    const
    {
        return m_p_impl->name_impl();
    }

    ascii::string_type ascii::from_pivot_impl(pivot_type pivot)
    const
    {
        return m_p_impl->from_pivot_impl(pivot);
    }

    typename ascii::pivot_type ascii::to_pivot_impl(string_type string)
    const
    {
        return m_p_impl->to_pivot_impl(string);
    }


}}}
