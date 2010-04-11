/*! \file
    \brief The definition of tetengo2::encoding::ascii.

    Copyright (C) 2007-2010 kaoru

    $Id$
*/

#if !defined(TETENGO2_ENCODING_WIN32_UTF8_H)
#define TETENGO2_ENCODING_WIN32_UTF8_H

//#include <string>

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
            return string_type();
        }

        /*!
            \brief Translates a string to the pivot encoding.

            \param string A string.

            \return A translated pivot string.
        */
        pivot_type to_pivot(const string_type& string)
        const
        {
            return pivot_type();
        }


    };


}}


#endif
