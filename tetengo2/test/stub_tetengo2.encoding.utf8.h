/*! \file
    \brief The definition of stub_tetengo2::encoding::utf8.

    Copyright (C) 2007-2010 kaoru

    $Id$
*/

#if !defined(STUBTETENGO2_ENCODING_UTF8_H)
#define STUBTETENGO2_ENCODING_UTF8_H //!< !! Include Guard !!

//#include <string>

#include "tetengo2.assignable.h"
#include "tetengo2.swappable.h"
#include "tetengo2.encoding.encoding.h"


namespace tetengo2 { namespace encoding
{
    class utf8 :
        public encoding,
        public assignable<utf8>,
        private swappable<utf8>
    {
    private:
    public:
        // types

        typedef std::string string_type;

        typedef string_type::value_type string_char_type;


        // constructors and destructor

        utf8()
        {}

        utf8(const utf8& another)
        {}

        ~utf8()
        throw ()
        {}


        // functions

        void swap(utf8& another)
        throw ()
        {}

        utf8& operator=(const utf8& another)
        {
            return assign(another);
        }

        string_type from_pivot(const pivot_type& pivot)
        const
        {
            return string_type();
        }

        pivot_type to_pivot(const string_type& string)
        const
        {
            return pivot_type();
        }


    };


}}


#endif
