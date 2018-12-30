/*! \file
    \brief The definition of tetengo2::detail::windows::icon.

    Copyright (C) 2007-2019 kaoru

    $Id$
*/

#include <memory>

#include <boost/core/noncopyable.hpp>

#include <tetengo2/detail/windows/icon.h>
#include <tetengo2/stdalt.h>


namespace tetengo2::detail::windows {
    class icon::impl : private boost::noncopyable
    {
    public:
        // types

        using dimension_type = icon::dimension_type;

        using icon_details_type = icon::icon_details_type;

        using icon_handle_type = icon::icon_handle_type;

        using icon_details_ptr_type = icon::icon_details_ptr_type;


        // functions

        dimension_type default_dimension_impl() const
        {
            const std::pair<int, int> big_icon_dimension_ = big_icon_dimension();
            return { dimension_type::unit_type::from_pixels(big_icon_dimension_.first),
                     dimension_type::unit_type::from_pixels(big_icon_dimension_.second) };
        }

        icon_details_ptr_type
        create_impl(const tetengo2::stdalt::filesystem::path& path, const dimension_type& dimension) const
        {
            const auto       width = static_cast<int>(dimension.width().to_pixels());
            const auto       height = static_cast<int>(dimension.height().to_pixels());
            icon_handle_type big_icon_handle{ load_icon(path, width, height) };

            const std::pair<int, int> small_icon_dimension_ = small_icon_dimension();
            icon_handle_type          small_icon_handle{ load_icon(
                path, small_icon_dimension_.first, small_icon_dimension_.second) };

            return std::make_unique<icon_details_impl_type>(std::move(big_icon_handle), std::move(small_icon_handle));
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

        inline static ::HICON
        load_icon(const tetengo2::stdalt::filesystem::path& path, const int width, const int height)
        {
            const ::HANDLE handle =
                ::LoadImageW(nullptr, path.c_str(), IMAGE_ICON, width, height, LR_LOADFROMFILE | LR_VGACOLOR);
            if (!handle)
                BOOST_THROW_EXCEPTION((std::ios_base::failure{ "Can't load icon file." }));

            return static_cast<::HICON>(handle);
        }
    };


    const icon& icon::instance()
    {
        static const icon singleton;
        return singleton;
    }

    icon::~icon() = default;

    icon::icon() : m_p_impl{ std::make_unique<impl>() } {}

    icon::dimension_type icon::default_dimension_impl() const
    {
        return m_p_impl->default_dimension_impl();
    }

    icon::icon_details_ptr_type
    icon::create_impl(const tetengo2::stdalt::filesystem::path& path, const dimension_type& dimension) const
    {
        return m_p_impl->create_impl(path, dimension);
    }
}