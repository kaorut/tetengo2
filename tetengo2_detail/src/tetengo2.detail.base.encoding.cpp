/*! \file
    \brief The definition of tetengo2::detail::base::encoding.

    Copyright (C) 2007-2017 kaoru

    $Id$
*/

#include <tetengo2/detail/base/encoding.h>


namespace tetengo2 { namespace detail { namespace base
{
    encoding::encoding()
    = default;

    encoding::~encoding()
    = default;

    encoding::utf8_string_type encoding::pivot_to_utf8(const pivot_type& pivot)
    const
    {
        return pivot_to_utf8_impl(pivot);
    }

    encoding::pivot_type encoding::utf8_to_pivot(const utf8_string_type& string)
    const
    {
        return utf8_to_pivot_impl(string);
    }

    encoding::cp932_string_type encoding::pivot_to_cp932(const pivot_type& pivot)
    const
    {
        return pivot_to_cp932_impl(pivot);
    }

    encoding::pivot_type encoding::cp932_to_pivot(const cp932_string_type& string)
    const
    {
        return cp932_to_pivot_impl(string);
    }


}}}
