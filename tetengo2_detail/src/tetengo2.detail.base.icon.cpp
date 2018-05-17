/*! \file
    \brief The definition of tetengo2::detail::base::icon.

    Copyright (C) 2007-2018 kaoru

    $Id$
*/

#include <memory>

#include <boost/core/noncopyable.hpp>

#include <tetengo2/detail/base/icon.h>
#include <tetengo2/stdalt.h>


namespace tetengo2::detail::base {
    class icon::impl : private boost::noncopyable
    {
    public:
        // types

        using dimension_type = icon::dimension_type;

        using icon_details_type = icon::icon_details_type;

        using icon_details_ptr_type = icon::icon_details_ptr_type;


        // functions

        dimension_type default_dimension(const icon& base) const
        {
            return base.default_dimension_impl();
        }

        icon_details_ptr_type
        create(const tetengo2::stdalt::filesystem::path& path, const dimension_type& dimension, const icon& base) const
        {
            return base.create_impl(path, dimension);
        }
    };


    icon::~icon() {}

    icon::dimension_type icon::default_dimension() const
    {
        return m_p_impl->default_dimension(*this);
    }

    icon::icon_details_ptr_type
    icon::create(const tetengo2::stdalt::filesystem::path& path, const dimension_type& dimension) const
    {
        return m_p_impl->create(path, dimension, *this);
    }

    icon::icon() : m_p_impl{ std::make_unique<impl>() } {}
}
