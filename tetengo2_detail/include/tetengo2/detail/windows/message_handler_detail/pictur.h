/*! \file
    \brief The definition of tetengo2::detail::windows::message_handler_detail::picture_box.

    Copyright (C) 2007-2014 kaoru

    $Id$
*/

#if !defined(DOCUMENTATION)
#if !defined(TETENGO2_DETAIL_WINDOWS_MESSAGEHANDLERDETAIL_PICTUREBOX_H)
#define TETENGO2_DETAIL_WINDOWS_MESSAGEHANDLERDETAIL_PICTUREBOX_H

#include <memory>
#include <system_error>

#include <boost/core/ignore_unused.hpp>
#include <boost/optional.hpp>
#include <boost/scope_exit.hpp>
#include <boost/throw_exception.hpp>

#pragma warning (push)
#pragma warning (disable: 4005)
#include <intsafe.h>
#include <stdint.h>
#pragma warning(pop)
#define NOMINMAX
#define OEMRESOURCE
#include <Windows.h>


namespace tetengo2 { namespace detail { namespace windows { namespace message_handler_detail
{
    namespace picture_box
    {
        template <typename PictureBox>
        boost::optional< ::LRESULT> on_erase_background(
            PictureBox&    picture_box,
            const ::WPARAM w_param,
            const ::LPARAM l_param
        )
        {
            boost::ignore_unused(w_param, l_param);

            if (picture_box.fast_paint_observer_set().paint_background().empty())
                return boost::none;

            const std::unique_ptr<typename PictureBox::fast_canvas_type> p_canvas = picture_box.create_fast_canvas();

            if (!picture_box.fast_paint_observer_set().paint_background()(*p_canvas))
                return boost::none;

            return boost::make_optional< ::LRESULT>(TRUE);
        }

        template <typename PictureBox>
        boost::optional< ::LRESULT> on_paint(PictureBox& picture_box, const ::WPARAM w_param, const ::LPARAM l_param)
        {
            boost::ignore_unused(w_param, l_param);

            if (picture_box.fast_paint_observer_set().paint().empty())
                return boost::none;

            ::PAINTSTRUCT paint_struct{};
            if (!::BeginPaint(picture_box.details().handle.get(), &paint_struct))
            {
                BOOST_THROW_EXCEPTION((
                    std::system_error{
                        std::error_code{ ERROR_FUNCTION_FAILED, win32_category() }, "Can't begin paint."
                    }
                ));
            }
            BOOST_SCOPE_EXIT((&picture_box)(&paint_struct))
            {
                ::EndPaint(picture_box.details().handle.get(), &paint_struct);
            } BOOST_SCOPE_EXIT_END;

            const std::unique_ptr<typename PictureBox::fast_canvas_type> p_canvas = picture_box.create_fast_canvas();

            picture_box.fast_paint_observer_set().paint()(*p_canvas);

            return boost::make_optional< ::LRESULT>(0);
        }


    }


}}}}


#endif
#endif
