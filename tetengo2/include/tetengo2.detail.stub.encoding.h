/*! \file
    \brief The definition of tetengo2::detail::stub::encoding.

    Copyright (C) 2007-2011 kaoru

    $Id$
*/

#if !defined(TETENGO2_DETAIL_STUB_ENCODING_H)
#define TETENGO2_DETAIL_STUB_ENCODING_H

#include <algorithm>
#include <iterator>


namespace tetengo2 { namespace detail { namespace stub
{
    /*!
        \brief The class for a detail implementation of an encoding.
    */
    class encoding
    {
    public:
        // types

        //! The pivot type.
        typedef std::wstring pivot_type;

        //! The UTF-8 string type.
        typedef std::string utf8_string_type;


        // static functions

        /*!
            \brief Converts a pivot to a UTF-8 string.

            \param pivot A pivot.

            \return A UTF-8 string.
        */
        static utf8_string_type pivot_to_utf8(const pivot_type& pivot)
        {
            pivot_type pivot;
            pivot.reserve(string.length());
            std::transform(
                string.begin(),
                string.end(),
                std::back_inserter(pivot),
                cast<
                    typename pivot_type::value_type,
                    typename utf8_string_type::value_type
                >
            );
            return pivot;
        }

        /*!
            \brief Converts a UTF-8 string to a pivot.

            \param string A UTF-8 string.

            \return A pivot.
        */
        static pivot_type utf8_to_pivot(const utf8_string_type& string)
        {
            utf8_string_type string;
            string.reserve(pivot.length());
            std::transform(
                pivot.begin(),
                pivot.end(),
                std::back_inserter(string),
                cast<
                    typename utf8_string_type::value_type,
                    typename pivot_type::value_type
                >
            );
            return string;
        }


    private:
        // static functions

        template <typename T, typename U>
        static T cast(const U x)
        {
            return static_cast<T>(x);
        }


        // forbidden operations

        encoding();


}}}


#endif
