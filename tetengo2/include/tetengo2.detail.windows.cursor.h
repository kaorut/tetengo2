/*! \file
    \brief The definition of tetengo2::detail::windows::cursor.

    Copyright (C) 2007-2011 kaoru

    $Id$
*/

#if !defined(TETENGO2_DETAIL_WINDOWS_CURSOR_H)
#define TETENGO2_DETAIL_WINDOWS_CURSOR_H

#include <type_traits>

#define NOMINMAX
#define OEMRESOURCE
#include <Windows.h>

#include "tetengo2.cpp0x.h"


namespace tetengo2 { namespace detail { namespace windows
{
#if !defined(DOCUMENTATION)
    namespace detail
    {
        // types

        struct cursor_deleter
        {
            void operator()(const ::HCURSOR cursor_handle)
            const
            {}


        };


    }
#endif

    /*!
        \brief The class for a detail implementation of a cursor.
    */
    class cursor
    {
    public:
        // types

        //! The cursor details type.
        typedef std::remove_pointer< ::HCURSOR>::type cursor_details_type;

        //! The cursor details pointer type.
        typedef
            cpp0x::unique_ptr<
                cursor_details_type, detail::cursor_deleter
            >::type
            cursor_details_ptr_type;


        // static functions

        /*!
            \brief Creates a system cursor.

            \tparam SystemCursor A system cursor type.

            \param style A style.

            \return A unique pointer to a system cursor.

            \throw std::runtime_error When a system cursor cannot be created.
        */
        template <typename SystemCursor>
        static cursor_details_ptr_type create_system_cursor(
            const typename SystemCursor::style_type style
        )
        {
            cursor_details_ptr_type p_cursor(
                reinterpret_cast< ::HCURSOR>(
                    ::LoadImageW(
                        0,
                        MAKEINTRESOURCEW(OCR_HAND),
                        IMAGE_CURSOR,
                        0,
                        0,
                        LR_DEFAULTSIZE | LR_SHARED | LR_VGACOLOR
                    )
                )
            );
            if (!p_cursor)
                throw std::runtime_error("Can't create a system cursor.");

            return std::move(p_cursor);
        }


    };


}}}


#endif
