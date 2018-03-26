/*! \file
    \brief The definition of COM smart pointers for tetengo2::detail::windows.

    Copyright (C) 2007-2018 kaoru

    $Id$
*/

#if !defined(TETENGO2_DETAIL_WINDOWS_COMPTR_H)
#define TETENGO2_DETAIL_WINDOWS_COMPTR_H

#include <memory>

#pragma warning(push)
#pragma warning(disable : 4005)
#include <intsafe.h>
#include <stdint.h> // IWYU pragma: keep
#pragma warning(pop)
#define NOMINMAX
#define OEMRESOURCE
#include <Unknwn.h>
#include <Windows.h>


namespace tetengo2::detail::windows {
#if !defined(DOCUMENTATION)
    namespace detail {
        // types

        struct release_unknown
        {
            void operator()(::IUnknown* const p_unknown) const
            {
                if (p_unknown)
                    p_unknown->Release();
            }
        };
    }
#endif


    /*!
        \brief The meta function for a unique COM pointer.

        \tparam T A type.
    */
    template <typename T>
    using unique_com_ptr = std::unique_ptr<T, detail::release_unknown>;
}


#endif
