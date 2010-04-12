/*! \file
    \brief The definition of tetengo2::encoding::ascii.

    Copyright (C) 2007-2010 kaoru

    $Id$
*/

#if !defined(TETENGO2_ENCODING_WIN32_UTF8_H)
#define TETENGO2_ENCODING_WIN32_UTF8_H

#include <stdexcept>
//#include <string>

#include <boost/iterator_adaptors.hpp>

#include "tetengo2.assignable.h"
#include "tetengo2.swappable.h"
#include "tetengo2.encoding.encoding.h"


namespace tetengo2 { namespace encoding
{
    /*!
        \brief The class for an ASCII encoding.
    */
    class ascii :
        public encoding,
        public assignable<ascii>,
        private swappable<ascii>
    {
    public:
        // types

        //! The string type.
        typedef std::string string_type;

        //! The string character type.
        typedef string_type::value_type string_char_type;


        // constructors and destructor

        /*!
            \brief Creates an ASCII encoding.
        */
        ascii()
        {}

        /*!
            \brief Copies an ASCII encoding.

            \param another Another ASCII encoding.
        */
        ascii(const ascii& another)
        {}

        /*!
            \brief Destroys the ASCII encoding.
        */
        ~ascii()
        throw ()
        {}


        // functions

        /*!
            \brief Swaps the members with another ASCII encoding.

            \param another Another ASCII encoding.
        */
        void swap(ascii& another)
        throw ()
        {}

        /*!
            \brief Assigns another ASCII encoding.

            \param another Another ASCII encoding.

            \return this object.
        */
        ascii& operator=(const ascii& another)
        {
            return assign(another);
        }

        /*!
            \brief Translates a string from the pivot encoding.

            \param pivot A pivot string.

            \return A translated string.
        */
        string_type from_pivot(const pivot_type& pivot)
        const
        {
            return string_type(
                boost::make_transform_iterator(pivot.begin(), to_ascii),
                boost::make_transform_iterator(pivot.end(), to_ascii)
            );
        }

        /*!
            \brief Translates a string to the pivot encoding.

            \param string A string.

            \return A translated pivot string.
        */
        pivot_type to_pivot(const string_type& string)
        const
        {
            return pivot_type(
                boost::make_transform_iterator(string.begin(), from_ascii),
                boost::make_transform_iterator(string.end(), from_ascii)
            );
        }


    private:
        // static functions

        static string_type::value_type to_ascii(
            const pivot_type::value_type pivot_char
        )
        {
            static const string_type::value_type question = 0x3F;

            return 0 <= pivot_char && pivot_char <= 0x7F ?
                static_cast<string_type::value_type>(pivot_char) :
                question;
        }

        static pivot_type::value_type from_ascii(
            const string_type::value_type ascii_char
        )
        {
            if (ascii_char < 0 || 0x80 <= ascii_char)
                throw std::invalid_argument("Not ASCII code.");

            return ascii_char;
        }


    };


}}


#endif
