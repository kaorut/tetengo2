/*! \file
    \brief The definition of the type list for tetengo2.

    Copyright (C) 2007-2017 kaoru

    $Id$
*/

#if !defined(TETENGO2_TYPELIST_H)
#define TETENGO2_TYPELIST_H

#include <cstddef>
#include <string>

#include <tetengo2/text/encoding/locale.h>


namespace tetengo2 { namespace type_list
{
    //! The type for integer.
    using integer_type = int;

    //! The type for size.
    using size_type = std::size_t;

    //! The type for float.
    using float_type = double;

    //! The type for string.
    using string_type = std::wstring;

    //! The type for internal encoding.
    using internal_encoding_type = text::encoding::locale<string_type>;


}}


#endif
