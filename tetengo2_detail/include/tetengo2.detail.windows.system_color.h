/*! \file
    \brief The definition of tetengo2::detail::windows::system_color.

    Copyright (C) 2007-2012 kaoru

    $Id$
*/

#if !defined(TETENGO2_DETAIL_WINDOWS_SYSTEMCOLOR_H)
#define TETENGO2_DETAIL_WINDOWS_SYSTEMCOLOR_H

#include <cassert>
#include <stdexcept>

#include <boost/noncopyable.hpp>
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
        enum system_color_index_type
        {
            system_color_index_dialog_background, //!< Dialog background.
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
            case system_color_index_dialog_background:
                {
                    const ::COLORREF color_ref = ::GetSysColor(COLOR_3DFACE);
                    return Color(GetRValue(color_ref), GetGValue(color_ref), GetBValue(color_ref));
                }
            default:
                assert(false);
                BOOST_THROW_EXCEPTION(std::invalid_argument("Invalid system color index."));
            }
        }


    private:
        // forbidden operations

        system_color();


    };


}}}


#endif
