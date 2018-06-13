/*! \file
    \brief The definition of tetengo2::text::encoding::ascii.

    Copyright (C) 2007-2018 kaoru

    $Id$
*/

#include <algorithm>
#include <cassert>
#include <iterator>
#include <memory>
#include <stdexcept>
#include <string>

#include <boost/core/noncopyable.hpp>
#include <boost/throw_exception.hpp>

#include <tetengo2/detail/base/encoding.h>
#include <tetengo2/detail/base/impl_set.h>
#include <tetengo2/stdalt.h>
#include <tetengo2/text/encoding/ascii.h>


namespace tetengo2::text::encoding {
    class ascii::impl : private boost::noncopyable
    {
    public:
        // types

        using base_type = ascii::base_type;

        using pivot_type = ascii::pivot_type;

        using string_type = ascii::string_type;


        // functions

        const std::string& name_impl() const
        {
            static const std::string singleton{ "ASCII" };
            return singleton;
        }

        string_type from_pivot_impl(pivot_type pivot) const
        {
            switch (detail::detail_impl_set().encoding_().pivot_type_())
            {
            case detail::base::encoding::pivot_type_type::std_string:
            {
                if (tetengo2::stdalt::index(pivot) != 0)
                    pivot = std::string{};
                string_type string;
                std::transform(
                    tetengo2::stdalt::get<std::string>(pivot).begin(),
                    tetengo2::stdalt::get<std::string>(pivot).end(),
                    std::back_inserter(string),
                    to_ascii<char>);
                return string;
            }
            case detail::base::encoding::pivot_type_type::std_wstring:
            {
                if (tetengo2::stdalt::index(pivot) != 1)
                    pivot = std::wstring{};
                string_type string;
                std::transform(
                    tetengo2::stdalt::get<std::wstring>(pivot).begin(),
                    tetengo2::stdalt::get<std::wstring>(pivot).end(),
                    std::back_inserter(string),
                    to_ascii<wchar_t>);
                return string;
            }
            default:
                assert(false);
                BOOST_THROW_EXCEPTION(std::logic_error("Unknown encoding pivot."));
            }
        }

        pivot_type to_pivot_impl(string_type string) const
        {
            switch (detail::detail_impl_set().encoding_().pivot_type_())
            {
            case detail::base::encoding::pivot_type_type::std_string:
            {
                pivot_type pivot{ std::string{} };
                std::transform(
                    string.begin(),
                    string.end(),
                    std::back_inserter(tetengo2::stdalt::get<std::string>(pivot)),
                    from_ascii<char>);
                return pivot;
            }
            case detail::base::encoding::pivot_type_type::std_wstring:
            {
                pivot_type pivot{ std::wstring{} };
                std::transform(
                    string.begin(),
                    string.end(),
                    std::back_inserter(tetengo2::stdalt::get<std::wstring>(pivot)),
                    from_ascii<wchar_t>);
                return pivot;
            }
            default:
                assert(false);
                BOOST_THROW_EXCEPTION(std::logic_error("Unknown encoding pivot."));
            }
        }


    private:
        // types

        using string_char_type = typename string_type::value_type;


        // static functions

        template <typename PivotChar>
        static string_char_type to_ascii(const PivotChar pivot_char)
        {
            if (0 <= pivot_char && pivot_char <= 0x7F)
                return static_cast<string_char_type>(pivot_char);
            else
                return 0x3F;
        }

        template <typename PivotChar>
        static PivotChar from_ascii(const string_char_type ascii_char)
        {
            if (ascii_char < 0)
                BOOST_THROW_EXCEPTION((std::invalid_argument{ "Not ASCII code." }));

            return ascii_char;
        }
    };


    ascii::ascii() : m_p_impl{ std::make_shared<impl>() } {}

    ascii::~ascii() = default;

    const std::string& ascii::name_impl() const
    {
        return m_p_impl->name_impl();
    }

    ascii::string_type ascii::from_pivot_impl(pivot_type pivot) const
    {
        return m_p_impl->from_pivot_impl(pivot);
    }

    typename ascii::pivot_type ascii::to_pivot_impl(string_type string) const
    {
        return m_p_impl->to_pivot_impl(string);
    }
}
