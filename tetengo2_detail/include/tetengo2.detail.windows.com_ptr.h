/*! \file
    \brief The definition of tetengo2::detail::windows::com_ptr.

    Copyright (C) 2007-2012 kaoru

    $Id$
*/

#if !defined(TETENGO2_DETAIL_WINDOWS_COMPTR_H)
#define TETENGO2_DETAIL_WINDOWS_COMPTR_H

#include <memory>

//#define NOMINMAX
//#define OEMRESOURCE
//#include <Windows.h>
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
        typedef std::unique_ptr<T, detail::release_unknown> type;


    };


}}}


#endif
