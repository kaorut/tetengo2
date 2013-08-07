/*! \file
    \brief The definition of tetengo2::detail::windows::icon.

    Copyright (C) 2007-2013 kaoru

    $Id$
*/

#if !defined(TETENGO2_DETAIL_WINDOWS_ICON_H)
#define TETENGO2_DETAIL_WINDOWS_ICON_H

#include <cassert>
#include <ios>
#include <memory>
#include <utility>

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

#include "tetengo2.stdalt.h"


namespace tetengo2 { namespace detail { namespace windows
{
    /*!
        \brief The class for a detail implementation of an icon.
    */
    class icon : private boost::noncopyable
    {
    public:
        // types

        //! The icon details type.
        struct icon_details_type
        {
#if !defined(DOCUMENTATION)
            ::HICON m_icon_handle;
            ::HICON m_small_icon_handle;

            icon_details_type(const ::HICON icon_handle, const ::HICON small_icon_handle)
            :
            m_icon_handle(icon_handle),
            m_small_icon_handle(small_icon_handle)
            {
                assert(icon_handle);
                assert(small_icon_handle);
            }

            ~icon_details_type()
            TETENGO2_STDALT_NOEXCEPT
            {
                ::DestroyIcon(m_icon_handle);
                ::DestroyIcon(m_small_icon_handle);
            }
#endif

        };

        //! The icon details pointer type.
        typedef std::unique_ptr<icon_details_type> icon_details_ptr_type;


        // static functions

        /*!
            \brief Creates an icon.

            \tparam Path A path type.

            \param path A path.

            \return A unique pointer to an icon.
        */
        template <typename Path>
        static icon_details_ptr_type create(const Path& path)
        {
            const std::pair<int, int> icon_dimension_ = icon_dimension();
            const ::HANDLE icon_handle =
                ::LoadImageW(
                    nullptr,
                    path.c_str(),
                    IMAGE_ICON,
                    icon_dimension_.first,
                    icon_dimension_.second,
                    LR_LOADFROMFILE | LR_VGACOLOR
                );
            if (!icon_handle)
                BOOST_THROW_EXCEPTION(std::ios_base::failure("Can't load icon file."));

            const std::pair<int, int> small_icon_dimension_ = small_icon_dimension();
            const ::HANDLE small_icon_handle =
                ::LoadImageW(
                    nullptr,
                    path.c_str(),
                    IMAGE_ICON,
                    small_icon_dimension_.first,
                    small_icon_dimension_.second,
                    LR_LOADFROMFILE | LR_VGACOLOR
                );
            if (!small_icon_handle)
                BOOST_THROW_EXCEPTION(std::ios_base::failure("Can't load icon file."));

            return
                tetengo2::stdalt::make_unique<icon_details_type>(
                    static_cast< ::HICON>(icon_handle), static_cast< ::HICON>(small_icon_handle)
                );
        }


    private:
        // static functions

        static std::pair<int, int> icon_dimension()
        {
            return std::make_pair(::GetSystemMetrics(SM_CXICON), ::GetSystemMetrics(SM_CYICON));
        }

        static std::pair<int, int> small_icon_dimension()
        {
            return std::make_pair(::GetSystemMetrics(SM_CXSMICON), ::GetSystemMetrics(SM_CYSMICON));
        }


    };


}}}


#endif
