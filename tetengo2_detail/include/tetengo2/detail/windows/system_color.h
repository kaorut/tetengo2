/*! \file
    \brief The definition of tetengo2::detail::windows::system_color.

    Copyright (C) 2007-2016 kaoru

    $Id$
*/

#if !defined(TETENGO2_DETAIL_WINDOWS_SYSTEMCOLOR_H)
#define TETENGO2_DETAIL_WINDOWS_SYSTEMCOLOR_H

#include <cassert>
#include <stdexcept>

#include <boost/core/noncopyable.hpp>
#include <boost/throw_exception.hpp>

#pragma warning (push)
#pragma warning (disable: 4005)
#include <intsafe.h>
#include <stdint.h>
#pragma warning(pop)
#define NOMINMAX
#define OEMRESOURCE
#include <Windows.h>


namespace tetengo2 { namespace detail { namespace windows
{
    /*!
        \brief The class for a detail implementation of a system color.
    */
    class system_color : private boost::noncopyable
    {
    public:
        // types

        //! The system color index type.
        enum class system_color_index_type
        {
            title_bar_text,       //!< Title bar text.
            title_bar_background, //!< Title bar background.
            dialog_background,    //!< Dialog background.
            control_background,   //!< Control background.
            control_text,         //!< Control text.
            selected_background,  //!< Selected background.
            selected_text,        //!< Selected text.
            hyperlink_text,       //!< Hyperlink text.
        };


        // functions

        /*!
            \brief Returns the system color.

            \tparam Color A color type.

            \param index An index;

            \return The system color.
        */
        template <typename Color>
        static Color get_system_color(const system_color_index_type index)
        {
            switch (index)
            {
            case system_color_index_type::title_bar_text:
                return get_system_color_impl<Color>(COLOR_CAPTIONTEXT);
            case system_color_index_type::title_bar_background:
                return get_system_color_impl<Color>(COLOR_ACTIVECAPTION);
            case system_color_index_type::dialog_background:
                return get_system_color_impl<Color>(COLOR_3DFACE);
            case system_color_index_type::control_background:
                return get_system_color_impl<Color>(COLOR_WINDOW);
            case system_color_index_type::control_text:
                return get_system_color_impl<Color>(COLOR_WINDOWTEXT);
            case system_color_index_type::selected_background:
                return get_system_color_impl<Color>(COLOR_HIGHLIGHT);
            case system_color_index_type::selected_text:
                return get_system_color_impl<Color>(COLOR_HIGHLIGHTTEXT);
            case system_color_index_type::hyperlink_text:
                return get_system_color_impl<Color>(COLOR_HOTLIGHT);
            default:
                assert(false);
                BOOST_THROW_EXCEPTION((std::invalid_argument{ "Invalid system color index." }));
            }
        }


    private:
        // static functions

        template <typename Color>
        static Color get_system_color_impl(const int index)
        {
            const auto color_ref = ::GetSysColor(index);
            return { GetRValue(color_ref), GetGValue(color_ref), GetBValue(color_ref) };
        }


        // forbidden operations

        system_color()
        = delete;


    };


}}}


#endif
