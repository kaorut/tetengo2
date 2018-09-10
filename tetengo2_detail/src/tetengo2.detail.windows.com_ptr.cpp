/*! \file
    \brief The definition of COM smart pointers for tetengo2::detail::windows.

    Copyright (C) 2007-2018 kaoru

    $Id$
*/

#include <tetengo2/detail/windows/com_ptr.h>

#pragma warning(push)
#pragma warning(disable : 4005)
#include <intsafe.h>
#include <stdint.h> // IWYU pragma: keep
#pragma warning(pop)
#define NOMINMAX
#define OEMRESOURCE
#include <Unknwn.h>
#include <Windows.h>


namespace tetengo2::detail::windows::detail {
    void release_unknown::operator()(::IUnknown* const p_unknown) const
    {
        if (p_unknown)
            p_unknown->Release();
    }
}
