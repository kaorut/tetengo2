/*! \file
    \brief The definition of COM smart pointers for tetengo2::detail::windows.

    Copyright (C) 2007-2014 kaoru

    $Id$
*/

#if !defined(TETENGO2_DETAIL_WINDOWS_COMPTR_H)
#define TETENGO2_DETAIL_WINDOWS_COMPTR_H

#include <memory>

#pragma warning (push)
#pragma warning (disable: 4005)
#include <intsafe.h>
#include <stdint.h>
#pragma warning(pop)
#define NOMINMAX
#define OEMRESOURCE
#include <Windows.h>
#include <Unknwn.h>


namespace tetengo2 { namespace detail { namespace windows
{
#if !defined(DOCUMENTATION)
    namespace detail
    {
        // types

        struct release_unknown
        {
            void operator()(::IUnknown* const p_unknown)
            const
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
    struct unique_com_ptr
    {
        //! The unique COM pointer type.
        using type = std::unique_ptr<T, detail::release_unknown>;


    };


}}}


#endif
