/*! \file
    \brief The definition of tetengo2::detail::unixos::encoding.

    Copyright (C) 2007-2015 kaoru

    $Id$
*/

#if !defined(TETENGO2_DETAIL_UNIXOS_ENCODING_H)
#define TETENGO2_DETAIL_UNIXOS_ENCODING_H

#include <iconv.h>

#include <cassert>
#include <cerrno>
#include <cstddef>
#include <stdexcept>
#include <string>
#include <vector>

#include <boost/core/noncopyable.hpp>


namespace tetengo2 { namespace detail { namespace unixos
{
    /*!
        \brief The class for a detail implementation of an encoding.
    */
    class encoding : private boost::noncopyable
    {
    public:
        // types

        //! The pivot type.
        //!
        //! Stores UTF-8.
        using pivot_type = std::string;

        //! The UTF-8 string type.
        using utf8_string_type = std::string;

        //! The CP932 string type.
        using cp932_string_type = std::string;


        // static functions

        /*!
            \brief Converts a pivot to a UTF-8 string.

            \param pivot A pivot.

            \return A UTF-8 string.
        */
        static utf8_string_type pivot_to_utf8(const pivot_type& pivot)
        {
            return pivot;
        }

        /*!
            \brief Converts a UTF-8 string to a pivot.

            \param string A UTF-8 string.

            \return A pivot.
        */
        static pivot_type utf8_to_pivot(const utf8_string_type& string)
        {
            return string;
        }

        /*!
            \brief Converts a pivot to a CP932 string.

            \param pivot A pivot.

            \return A CP932 string.
        */
        static cp932_string_type pivot_to_cp932(const pivot_type& pivot)
        {
            return utf8_to_cp932().convert(pivot);
        }

        /*!
            \brief Converts a CP932 string to a pivot.

            \param string A CP932 string.

            \return A pivot.
        */
        static pivot_type cp932_to_pivot(const cp932_string_type& string)
        {
            return cp932_to_utf8().convert(string);
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


        // forbidden operations

        encoding()
        = delete;


    };


}}}


#endif
