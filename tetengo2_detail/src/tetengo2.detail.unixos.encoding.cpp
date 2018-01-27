/*! \file
    \brief The definition of tetengo2::detail::unixos::encoding.

    Copyright (C) 2007-2018 kaoru

    $Id$
*/

#include <iconv.h>

#include <cassert>
#include <cerrno>
#include <cstddef>
#include <memory>
#include <stdexcept>
#include <string>
#include <utility>
#include <vector>

#include <boost/core/noncopyable.hpp>

#include <tetengo2/detail/unixos/encoding.h>
#include <tetengo2/stdalt.h>


namespace tetengo2 { namespace detail { namespace unixos
{
    class encoding::impl : private boost::noncopyable
    {
    public:
        // types

        using pivot_type = encoding::pivot_type;

        using utf8_string_type = encoding::utf8_string_type;

        using cp932_string_type = encoding::cp932_string_type;


        // static functions

        static const encoding& instance()
        {
            static const encoding singleton;
            return singleton;
        }


        // constructors

        impl()
        = default;


        // functions

        utf8_string_type pivot_to_utf8_impl(pivot_type pivot)
        const
        {
            return pivot;
        }

        pivot_type utf8_to_pivot_impl(utf8_string_type string)
        const
        {
            return string;
        }

        cp932_string_type pivot_to_cp932_impl(pivot_type pivot)
        const
        {
            return utf8_to_cp932().convert(std::move(pivot));
        }

        pivot_type cp932_to_pivot_impl(cp932_string_type string)
        const
        {
            return cp932_to_utf8().convert(std::move(string));
        }


    private:
        // types

        class iconv_converter
        {
        public:
            iconv_converter(const char* const from, const char* const to)
            :
            m_conversion_descriptor(::iconv_open(to, from))
            {
                if (m_conversion_descriptor == reinterpret_cast< ::iconv_t>(-1))
                    throw std::runtime_error("Can't open iconv.");
            }

            ~iconv_converter()
            {
                ::iconv_close(m_conversion_descriptor);
            }

            std::string convert(const std::string& input)
            const
            {
                std::string converted{};

                char* p_in = const_cast<char*>(input.c_str());
                const std::size_t in_length = input.length();
                std::size_t in_left = in_length;
                for (;;)
                {
                    static const std::size_t outbuf_capacity = 10;
                    std::vector<char> outbuf(outbuf_capacity, 0);
                    char* p_out = &outbuf[0];
                    std::size_t out_left = outbuf_capacity;

                    errno = 0;
                    const std::size_t result = ::iconv(m_conversion_descriptor, &p_in, &in_left, &p_out, &out_left);
                    if (result == static_cast<std::size_t>(-1) && errno == EINVAL)
                        break;

                    converted.append(&outbuf[0], outbuf_capacity - out_left);

                    if (errno == EILSEQ)
                    {
                        assert(in_left > 0);
                        converted += '?';
                        ++p_in;
                        --in_left;
                    }

                    if (in_left == 0)
                        break;
                }

                return converted;
            }

        private:
            iconv_t m_conversion_descriptor;

        };


        // static functions

        static const iconv_converter& utf8_to_cp932()
        {
            static const iconv_converter singleton{ "UTF-8", "CP932" };
            return singleton;
        }

        static const iconv_converter& cp932_to_utf8()
        {
            static const iconv_converter singleton{ "CP932", "UTF-8" };
            return singleton;
        }


    };


    const encoding& encoding::instance()
    {
        return impl::instance();
    }

    encoding::~encoding()
    = default;

    encoding::encoding()
    :
    m_p_impl(stdalt::make_unique<impl>())
    {}

    encoding::utf8_string_type encoding::pivot_to_utf8_impl(pivot_type pivot)
    const
    {
        return m_p_impl->pivot_to_utf8_impl(std::move(pivot));
    }

    encoding::pivot_type encoding::utf8_to_pivot_impl(utf8_string_type string)
    const
    {
        return m_p_impl->utf8_to_pivot_impl(std::move(string));
    }

    encoding::cp932_string_type encoding::pivot_to_cp932_impl(pivot_type pivot)
    const
    {
        return m_p_impl->pivot_to_cp932_impl(std::move(pivot));
    }

    encoding::pivot_type encoding::cp932_to_pivot_impl(cp932_string_type string)
    const
    {
        return m_p_impl->cp932_to_pivot_impl(std::move(string));
    }


}}}
