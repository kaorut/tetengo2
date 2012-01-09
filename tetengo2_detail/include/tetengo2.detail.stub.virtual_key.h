/*! \file
    \brief The definition of tetengo2::detail::stub::virtual_key.

    Copyright (C) 2007-2012 kaoru

    $Id$
*/

#if !defined(TETENGO2_DETAIL_STUB_VIRTUALKEY_H)
#define TETENGO2_DETAIL_STUB_VIRTUALKEY_H

#include <utility>

#include <boost/noncopyable.hpp>

#include "tetengo2.text.h"


namespace tetengo2 { namespace detail { namespace stub
{
    /*!
        \brief The class template for a detail implementation of virtual keys.

        \tparam String A string type.
    */
    template <typename String>
    class virtual_key : private boost::noncopyable
    {
    public:
        // types

        //! The code type.
        typedef unsigned char code_type;

        //! The string type.
        typedef String string_type;

        //! The code and string type.
        typedef std::pair<code_type, string_type> code_and_string_type;


        // static functions

        //! Returns the key code and string for 'A'.
        //! \return The key code and string.
        static code_and_string_type char_a()
        {
            return code_and_string_type('A', string_type(TETENGO2_TEXT("A")));
        }


    private:
        // forbidden operations

        virtual_key();

    
    };


}}}


#endif
