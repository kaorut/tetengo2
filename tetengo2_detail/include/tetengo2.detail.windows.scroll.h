/*! \file
    \brief The definition of tetengo2::detail::windows::scroll.

    Copyright (C) 2007-2012 kaoru

    $Id$
*/

#if !defined(TETENGO2_DETAIL_WINDOWS_SCROLL_H)
#define TETENGO2_DETAIL_WINDOWS_SCROLL_H

#include <memory>
#include <tuple>

#include <boost/noncopyable.hpp>

#define NOMINMAX
#define OEMRESOURCE
#include <Windows.h>

#include "tetengo2.unique.h"


namespace tetengo2 { namespace detail { namespace windows
{
    /*!
        \brief The class for a detail implementation of a scroll.
    */
    class scroll : private boost::noncopyable
    {
    public:
        // types

        //! The scroll bar details type.
        typedef ::HWND scroll_bar_details_type;

        //! The scroll bar details pointer type.
        typedef std::unique_ptr<scroll_bar_details_type> scroll_bar_details_ptr_type;


        // static functions

        /*!
            \brief Creates a scroll bar.

            \tparam Widget A widget type.

            \param widget A widget.

            \return A unique pointer to a scroll bar. 

            \throw std::system_error When a system cursor cannot be created.
        */
        template <typename Widget>
        scroll_bar_details_ptr_type create_scroll_bar(Widget& widget)
        {
            return scroll_bar_details_ptr_type();
        }


    private:
        // static functions


        // forbidden operations

        scroll();


    };


}}}


#endif
