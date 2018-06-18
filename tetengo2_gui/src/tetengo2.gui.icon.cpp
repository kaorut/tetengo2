/*! \file
    \brief The definition of tetengo2::gui::icon.

    Copyright (C) 2007-2018 kaoru

    $Id$
*/

#include <cassert>
#include <memory>
#include <utility>

#include <boost/core/noncopyable.hpp>

#include <tetengo2/detail/base/gui_impl_set.h>
#include <tetengo2/detail/base/icon.h>
#include <tetengo2/gui/icon.h>
#include <tetengo2/stdalt.h>


namespace tetengo2::gui {
    class icon::impl : private boost::noncopyable
    {
    public:
        // types

        using dimension_type = icon::dimension_type;

        using details_type = icon::details_type;

        using icon_details_type = icon::icon_details_type;


        // constructors and destructor

        explicit impl(tetengo2::stdalt::filesystem::path path)
        : m_path{ std::move(path) }, m_dimension{ detail::gui_detail_impl_set().icon_().default_dimension() },
          m_p_icon_details{ detail::gui_detail_impl_set().icon_().create(m_path, m_dimension) }
        {}

        impl(tetengo2::stdalt::filesystem::path path, dimension_type dimension)
        : m_path{ std::move(path) }, m_dimension{ std::move(dimension) }, m_p_icon_details{
              detail::gui_detail_impl_set().icon_().create(m_path, m_dimension)
          }
        {}


        // functions

        const tetengo2::stdalt::filesystem::path& path() const
        {
            return m_path;
        }

        const dimension_type& dimension() const
        {
            return m_dimension;
        }

        const icon_details_type& details() const
        {
            assert(m_p_icon_details);
            return *m_p_icon_details;
        }

        icon_details_type& details()
        {
            assert(m_p_icon_details);
            return *m_p_icon_details;
        }


    private:
        // types

        using icon_details_ptr_type = details_type::icon_details_ptr_type;


        // variables

        const tetengo2::stdalt::filesystem::path m_path;

        const dimension_type m_dimension;

        const icon_details_ptr_type m_p_icon_details;
    };


    icon::icon(tetengo2::stdalt::filesystem::path path) : m_p_impl{ std::make_unique<impl>(std::move(path)) }
    {}

    icon::icon(tetengo2::stdalt::filesystem::path path, dimension_type dimension)
    : m_p_impl{ std::make_unique<impl>(std::move(path), std::move(dimension)) }
    {}

    icon::~icon() = default;

    const tetengo2::stdalt::filesystem::path& icon::path() const
    {
        return m_p_impl->path();
    }

    const icon::dimension_type& icon::dimension() const
    {
        return m_p_impl->dimension();
    }

    const icon::icon_details_type& icon::details() const
    {
        return m_p_impl->details();
    }

    icon::icon_details_type& icon::details()
    {
        return m_p_impl->details();
    }
}