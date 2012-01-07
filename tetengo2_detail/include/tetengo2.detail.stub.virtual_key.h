/*! \file
    \brief The definition of tetengo2::detail::stub::virtual_key.

    Copyright (C) 2007-2012 kaoru

    $Id$
*/

#if !defined(TETENGO2_DETAIL_STUB_VIRTUALKEY_H)
#define TETENGO2_DETAIL_STUB_VIRTUALKEY_H

#include <boost/noncopyable.hpp>


namespace tetengo2 { namespace detail { namespace stub
{
    /*!
        \brief The class for a detail implementation of virtual keys.
    */
    class virtual_key : private boost::noncopyable
    {
    public:
        // types

        //! The code type.
        typedef unsigned char code_type;


        // static functions

        //! Returns the key code for 'A'.
        //! \return The key code.
        static code_type char_a() { return 'A'; }


    private:
        // forbidden operations

        virtual_key();

    
    };


}}}


#endif
