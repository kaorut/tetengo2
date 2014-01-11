/*! \file
    \brief The definition of tetengo2::detail::stub::encoding.

    Copyright (C) 2007-2014 kaoru

    $Id$
*/

#if !defined(TETENGO2_DETAIL_STUB_ENCODING_H)
#define TETENGO2_DETAIL_STUB_ENCODING_H

#include <algorithm>
#include <iterator>
#include <string>

#include <boost/noncopyable.hpp>


namespace tetengo2 { namespace detail { namespace stub
{
    /*!
        \brief The class for a detail implementation of an encoding.
    */
    class encoding : private boost::noncopyable
    {
    public:
        // types

        //! The pivot type.
        typedef std::wstring pivot_type;

        //! The UTF-8 string type.
        typedef std::string utf8_string_type;

        //! The CP932 string type.
        typedef std::string cp932_string_type;


        // static functions

        /*!
            \brief Converts a pivot to a UTF-8 string.

            \param pivot A pivot.

            \return A UTF-8 string.
        */
        static utf8_string_type pivot_to_utf8(const pivot_type& pivot)
        {
            utf8_string_type string;
            string.reserve(pivot.length());
            std::transform(
                pivot.begin(),
                pivot.end(),
                std::back_inserter(string),
                [](const pivot_type::value_type c) { return static_cast<utf8_string_type::value_type>(c); }
            );
            return string;
        }

        /*!
            \brief Converts a UTF-8 string to a pivot.

            \param string A UTF-8 string.

            \return A pivot.
        */
        static pivot_type utf8_to_pivot(const utf8_string_type& string)
        {
            pivot_type pivot;
            pivot.reserve(string.length());
            std::transform(
                string.begin(),
                string.end(),
                std::back_inserter(pivot),
                [](const utf8_string_type::value_type c) { return static_cast<pivot_type::value_type>(c); }
            );
            return pivot;
        }

        /*!
            \brief Converts a pivot to a CP932 string.

            \param pivot A pivot.

            \return A CP932 string.
        */
        static cp932_string_type pivot_to_cp932(const pivot_type& pivot)
        {
            cp932_string_type string;
            string.reserve(pivot.length());
            std::transform(
                pivot.begin(),
                pivot.end(),
                std::back_inserter(string),
                [](const pivot_type::value_type c) { return static_cast<cp932_string_type::value_type>(c); }
            );
            return string;
        }

        /*!
            \brief Converts a CP932 string to a pivot.

            \param string A CP932 string.

            \return A pivot.
        */
        static pivot_type cp932_to_pivot(const cp932_string_type& string)
        {
            pivot_type pivot;
            pivot.reserve(string.length());
            std::transform(
                string.begin(),
                string.end(),
                std::back_inserter(pivot),
                [](const cp932_string_type::value_type c) { return static_cast<pivot_type::value_type>(c); }
            );
            return pivot;
        }


    private:
        // forbidden operations

        encoding();


    };


}}}


#endif
