/*! \file
    \brief The definition of tetengo2::detail::windows::cursor.

    Copyright (C) 2007-2017 kaoru

    $Id$
*/

#include <system_error>
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

#include <tetengo2/detail/windows/cursor.h>
#include <tetengo2/detail/windows/error_category.h>
#include <tetengo2/stdalt.h>


namespace tetengo2 { namespace detail { namespace windows
{
    class cursor::impl : private boost::noncopyable
    {
    public:
        // types

        using cursor_details_type = cursor::cursor_details_type;

        using cursor_details_ptr_type = cursor::cursor_details_ptr_type;


        // static functions

        static const cursor& instance()
        {
            static const cursor singleton;
            return singleton;
        }


        // functions

        cursor_details_ptr_type create_system_cursor_impl(const int style)
        const
        {
            cursor_details_ptr_type p_cursor{
                reinterpret_cast<cursor_details_type*>(
                    ::LoadImageW(
                    0,
                    MAKEINTRESOURCEW(translate_style(style)),
                    IMAGE_CURSOR,
                    0,
                    0,
                    LR_DEFAULTSIZE | LR_SHARED | LR_VGACOLOR
                    )
                ),
                delete_details
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

        static void delete_details(cursor_details_type* const p_details)
        {
            boost::ignore_unused(p_details);
        }


    };


    const cursor& cursor::instance()
    {
        return impl::instance();
    }

    cursor::~cursor()
    = default;

    cursor::cursor()
    :
    m_p_impl(stdalt::make_unique<impl>())
    {}

    cursor::cursor_details_ptr_type cursor::create_system_cursor_impl(const int style)
    const
    {
        return m_p_impl->create_system_cursor_impl(style);
    }
    

}}}
