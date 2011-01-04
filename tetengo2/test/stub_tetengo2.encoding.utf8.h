/*! \file
    \brief The definition of stub_tetengo2::encoding::utf8.

    Copyright (C) 2007-2011 kaoru

    $Id$
*/

#if !defined(STUBTETENGO2_ENCODING_UTF8_H)
#define STUBTETENGO2_ENCODING_UTF8_H

//#include <string>

#include "tetengo2.encoding.encoding.h"


namespace stub_tetengo2 { namespace encoding
{
    class utf8 : public tetengo2::encoding::encoding
    {
    private:
    public:
        // types

        typedef std::string string_type;

        typedef string_type::value_type string_char_type;


        // functions

        template <typename P>
        string_type from_pivot(P&& pivot)
        const
        {
            return string_type();
        }

        template <typename S>
        pivot_type to_pivot(S&& string)
        const
        {
            return pivot_type();
        }


    };


}}


#endif
