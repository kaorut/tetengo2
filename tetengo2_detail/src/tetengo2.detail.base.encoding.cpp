/*! \file
    \brief The definition of tetengo2::detail::base::encoding.

    Copyright (C) 2007-2018 kaoru

    $Id$
*/

#include <utility>

#include <tetengo2/detail/base/encoding.h>


namespace tetengo2::detail::base {
    encoding::encoding() = default;

    encoding::~encoding() = default;

    encoding::utf8_string_type encoding::pivot_to_utf8(pivot_type pivot) const
    {
        return pivot_to_utf8_impl(std::move(pivot));
    }

    encoding::pivot_type encoding::utf8_to_pivot(utf8_string_type string) const
    {
        return utf8_to_pivot_impl(std::move(string));
    }

    encoding::cp932_string_type encoding::pivot_to_cp932(pivot_type pivot) const
    {
        return pivot_to_cp932_impl(std::move(pivot));
    }

    encoding::pivot_type encoding::cp932_to_pivot(cp932_string_type string) const
    {
        return cp932_to_pivot_impl(std::move(string));
    }
}
