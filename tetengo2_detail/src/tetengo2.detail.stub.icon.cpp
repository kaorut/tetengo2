/*! \file
    \brief The definition of tetengo2::detail::stub::icon.

    Copyright (C) 2007-2019 kaoru

    $Id$
*/

#include <memory>

#include <boost/core/noncopyable.hpp>

#include <tetengo2/detail/stub/icon.h>
#include <tetengo2/gui/unit/em.h>
#include <tetengo2/stdalt.h>


namespace tetengo2::detail::stub {
    class icon::impl : private boost::noncopyable
    {
    public:
        // types

        using dimension_type = icon::dimension_type;

        using icon_details_type = icon::icon_details_type;

        using icon_details_ptr_type = icon::icon_details_ptr_type;


        // functions

        dimension_type default_dimension_impl() const
        {
            using dimension_unit_type = dimension_type::unit_type;
            return { dimension_unit_type{ 42 }, dimension_unit_type{ 42 } };
        }

        icon_details_ptr_type create_impl(
            TETENGO2_STDALT_MAYBE_UNUSED const tetengo2::stdalt::filesystem::path& path,
            TETENGO2_STDALT_MAYBE_UNUSED const dimension_type& dimension) const
        {
            return std::make_unique<icon_details_type>();
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