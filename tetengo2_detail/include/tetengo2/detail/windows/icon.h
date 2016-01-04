/*! \file
    \brief The definition of tetengo2::detail::windows::icon.

    Copyright (C) 2007-2016 kaoru

    $Id$
*/

#if !defined(TETENGO2_DETAIL_WINDOWS_ICON_H)
#define TETENGO2_DETAIL_WINDOWS_ICON_H

#include <cassert>
#include <ios>
#include <memory>
#include <type_traits>
#include <utility>

#include <boost/core/noncopyable.hpp>
#include <boost/filesystem.hpp>
#include <boost/throw_exception.hpp>

#pragma warning (push)
#pragma warning (disable: 4005)
#include <intsafe.h>
#include <stdint.h>
#pragma warning(pop)
#define NOMINMAX
#define OEMRESOURCE
#include <Windows.h>

#include <tetengo2/gui/measure.h>
#include <tetengo2/stdalt.h>


namespace tetengo2 { namespace detail { namespace windows
{
    /*!
        \brief The class for a detail implementation of an icon.
    */
    class icon : private boost::noncopyable
    {
    public:
        // types

#if !defined(DOCUMENTATION)
        struct icon_deleter_type
        {
            void operator()(const ::HICON handle)
            const
            {
                if (handle)
                    ::DestroyIcon(handle);
            }

        };

        using icon_handle_type = std::unique_ptr<typename std::remove_pointer< ::HICON>::type, icon_deleter_type>;
#endif

        //! The icon details type.
        struct icon_details_type
        {
#if !defined(DOCUMENTATION)
            const icon_handle_type big_icon_handle;
            const icon_handle_type small_icon_handle;

            icon_details_type(icon_handle_type big_icon_handle_, icon_handle_type small_icon_handle_)
            :
            big_icon_handle(std::move(big_icon_handle_)),
            small_icon_handle(std::move(small_icon_handle_))
            {
                assert(big_icon_handle);
                assert(small_icon_handle);
            }
#endif

        };

        //! The icon details pointer type.
        using icon_details_ptr_type = std::unique_ptr<icon_details_type>;


        // static functions

        /*!
            \brief Returns the default dimension.

            \tparam Dimension A dimension type.
            
            \return The default dimension.
        */
        template <typename Dimension>
        static Dimension default_dimension()
        {
            const std::pair<int, int> big_icon_dimension_ = big_icon_dimension();
            return
                {
                    typename gui::dimension<Dimension>::width_type::from_pixels(big_icon_dimension_.first),
                    typename gui::dimension<Dimension>::height_type::from_pixels(big_icon_dimension_.second)
                };
        }

        /*!
            \brief Creates an icon.

            \tparam Dimension A dimension type.

            \param path      A path.
            \param dimension A dimension.

            \return A unique pointer to an icon.
        */
        template <typename Dimension>
        static icon_details_ptr_type create(const boost::filesystem::path& path, const Dimension& dimension)
        {
            const int width = gui::to_pixels<int>(gui::dimension<Dimension>::width(dimension));
            const int height = gui::to_pixels<int>(gui::dimension<Dimension>::height(dimension));
            icon_handle_type big_icon_handle{ load_icon(path, width, height) };

            const std::pair<int, int> small_icon_dimension_ = small_icon_dimension();
            icon_handle_type small_icon_handle{
                load_icon(path, small_icon_dimension_.first, small_icon_dimension_.second)
            };

            return stdalt::make_unique<icon_details_type>(std::move(big_icon_handle), std::move(small_icon_handle));
        }


    private:
        // static functions

        static std::pair<int, int> big_icon_dimension()
        {
            return std::make_pair(::GetSystemMetrics(SM_CXICON), ::GetSystemMetrics(SM_CYICON));
        }

        static std::pair<int, int> small_icon_dimension()
        {
            return std::make_pair(::GetSystemMetrics(SM_CXSMICON), ::GetSystemMetrics(SM_CYSMICON));
        }

        inline static ::HICON load_icon(const boost::filesystem::path& path, const int width, const int height)
        {
            const ::HANDLE handle =
                ::LoadImageW(nullptr, path.c_str(), IMAGE_ICON, width, height, LR_LOADFROMFILE | LR_VGACOLOR);
            if (!handle)
                BOOST_THROW_EXCEPTION((std::ios_base::failure{ "Can't load icon file." }));

            return static_cast< ::HICON>(handle);
        }


    };


}}}


#endif
