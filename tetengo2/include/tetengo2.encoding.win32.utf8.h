/*! \file
    \brief The definition of tetengo2::encoding::win32::utf8.

    Copyright (C) 2007-2010 kaoru

    $Id$
*/

#if !defined(TETENGO2_ENCODING_WIN32_UTF8_H)
#define TETENGO2_ENCODING_WIN32_UTF8_H

#include <string>

#include <boost/type_traits.hpp>

#include "tetengo2.assignable.h"
#include "tetengo2.swappable.h"
#include "tetengo2.encoding.encoding.h"


namespace tetengo2 { namespace encoding { namespace win32
{
    /*!
        \brief The class for a UTF-8 encoding.
    */
    class utf8 :
        public encoding,
        public assignable<utf8>,
        private swappable<utf8>
    {
    public:
        // types

        //! The string type.
        typedef std::string string_type;

        //! The string character type.
        typedef string_type::value_type string_char_type;


        // constructors and destructor

        /*!
            \brief Creates a UTF-8 encoding.
        */
        utf8()
        {}

        /*!
            \brief Copies a UTF-8 encoding.

            \param another Another UTF-8 encoding.
        */
        utf8(const utf8& another)
        {}

        /*!
            \brief Destroys the UTF-8 encoding.
        */
        ~utf8()
        throw ()
        {}


        // functions

        /*!
            \brief Swaps the members with another UTF-8 encoding.

            \param another Another UTF-8 encoding.
        */
        void swap(utf8& another)
        throw ()
        {}

        /*!
            \brief Assigns another UTF-8 encoding.

            \param another Another UTF-8 encoding.

            \return this object.
        */
        utf8& operator=(const utf8& another)
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


}}}


#endif
