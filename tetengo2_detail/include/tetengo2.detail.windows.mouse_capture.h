/*! \file
    \brief The definition of tetengo2::detail::windows::mouse_capture.

    Copyright (C) 2007-2014 kaoru

    $Id$
*/

#if !defined(TETENGO2_DETAIL_WINDOWS_MOUSECAPTURE_H)
#define TETENGO2_DETAIL_WINDOWS_MOUSECAPTURE_H

#include <boost/noncopyable.hpp>

#pragma warning (push)
#pragma warning (disable: 4005)
#include <intsafe.h>
#include <stdint.h>
#pragma warning(pop)
#define NOMINMAX
#define OEMRESOURCE
#include <Windows.h>

#include "tetengo2.stdalt.h"


namespace tetengo2 { namespace detail { namespace windows
{
    /*!
        \brief The class for a detail implementation of a mouse capture.
    */
    class mouse_capture : private boost::noncopyable
    {
    public:
        // constructors and destructor

        /*!
            \brief Creates a detail implementation of a mouse capture.

            \tparam Widget A widget type.

            \param widget A widget.
        */
        template <typename Widget>
        explicit mouse_capture(const Widget& widget)
        {
            ::SetCapture(widget.details().handle.get());
        }

        /*!
            \brief Destroys the detail implementation of a mouse capture.
        */
        ~mouse_capture()
        TETENGO2_STDALT_NOEXCEPT
        {
            ::ReleaseCapture();
        }


    private:
        // variables


    };


}}}


#endif
