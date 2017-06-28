/*! \file
    \brief The definition of tetengo2::detail::windows::cursor.

    Copyright (C) 2007-2017 kaoru

    $Id$
*/

#if !defined(TETENGO2_DETAIL_WINDOWS_CURSOR_H)
#define TETENGO2_DETAIL_WINDOWS_CURSOR_H

#include <memory>
#include <system_error>
#include <type_traits>
#include <utility>

#include <boost/core/ignore_unused.hpp>
#include <boost/core/noncopyable.hpp>
#include <boost/throw_exception.hpp>

//#pragma warning (push)
//#pragma warning (disable: 4005)
#include <intsafe.h>
#include <stdint.h>
//#pragma warning(pop)
#define NOMINMAX
#define OEMRESOURCE
#include <Windows.h>

#include <tetengo2/detail/windows/error_category.h>


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
            {
                boost::ignore_unused(cursor_handle);
            }


        };


    }
#endif

    /*!
        \brief The class for a detail implementation of a cursor.
    */
    class cursor : private boost::noncopyable
    {
    public:
        // types

        //! The cursor details type.
        using cursor_details_type = std::remove_pointer< ::HCURSOR>::type;

        //! The cursor details pointer type.
        using cursor_details_ptr_type = std::unique_ptr<cursor_details_type, detail::cursor_deleter>;


        // static functions

        /*!
            \brief Creates a system cursor.

            \param style A style.

            \return A unique pointer to a system cursor.

            \throw std::system_error When a system cursor cannot be created.
        */
        static cursor_details_ptr_type create_system_cursor(const int style)
        {
            cursor_details_ptr_type p_cursor{
                reinterpret_cast<::HCURSOR>(
                    ::LoadImageW(
                    0,
                    MAKEINTRESOURCEW(translate_style(style)),
                    IMAGE_CURSOR,
                    0,
                    0,
                    LR_DEFAULTSIZE | LR_SHARED | LR_VGACOLOR
                    )
                )
            };
            if (!p_cursor)
            {
                BOOST_THROW_EXCEPTION((
                    std::system_error{
                        std::error_code{ static_cast<int>(::GetLastError()), win32_category() },
                        "Can't create a system cursor."
                    }
                ));
            }

            return std::move(p_cursor);
        }


    private:
        // static functions

        static ::WORD translate_style(const int style)
        {
            switch (style)
            {
            case 1:
                return OCR_HAND;
            case 2:
                return OCR_SIZEWE;
            case 3:
                return OCR_SIZENS;
            default:
                return OCR_NORMAL;
            }
        }


    };


}}}


#endif
