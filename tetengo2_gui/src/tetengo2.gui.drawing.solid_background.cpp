/*! \file
    \brief The definition of tetengo2::gui::drawing::solid_background.

    Copyright (C) 2007-2018 kaoru

    $Id$
*/

#include <cassert>
#include <memory>
#include <utility>

#include <boost/core/noncopyable.hpp>

#include <tetengo2/detail/base/gui_impl_set.h>
#include <tetengo2/gui/drawing/solid_background.h>


namespace tetengo2::gui::drawing {
    class solid_background::impl : private boost::noncopyable
    {
    public:
        // types

        using base_type = solid_background::base_type;

        using color_type = solid_background::color_type;

        using drawing_details_type = solid_background::drawing_details_type;


        // constructors and destructor

        impl(const drawing_details_type& drawing_details, color_type color)
        : m_drawing_details{ drawing_details }, m_color{ std::move(color) }, m_p_details{
              m_drawing_details.create_solid_background(m_color)
          }
        {}

        explicit impl(color_type color)
        : m_drawing_details{ detail::gui_detail_impl_set().drawing_() }, m_color{ std::move(color) }, m_p_details{
              m_drawing_details.create_solid_background(m_color)
          }
        {}


        // functions

        std::unique_ptr<base_type> clone_impl() const
        {
            return std::make_unique<solid_background>(m_drawing_details, m_color);
        }

        const drawing_details_type& drawing_details_impl() const
        {
            return m_drawing_details;
        }

        const details_type& details_impl() const
        {
            assert(m_p_details);
            return *m_p_details;
        }

        details_type& details_impl()
        {
            assert(m_p_details);
            return *m_p_details;
        }
        const color_type& get_color() const
        {
            return m_color;
        }


    private:
        // types

        using details_type = solid_background::details_type;

        using details_ptr_type = drawing_details_type::background_details_ptr_type;


        // variables

        const drawing_details_type& m_drawing_details;

        const color_type m_color;

        const details_ptr_type m_p_details;
    };


    solid_background::solid_background(const drawing_details_type& drawing_details, color_type color)
    : base_type{}, m_p_impl{ std::make_unique<impl>(drawing_details, std::move(color)) }
    {}

    solid_background::solid_background(color_type color)
    : base_type{}, m_p_impl{ std::make_unique<impl>(std::move(color)) }
    {}

    solid_background::~solid_background() = default;

    const solid_background::color_type& solid_background::get_color() const
    {
        return m_p_impl->get_color();
    }

    std::unique_ptr<solid_background::base_type> solid_background::clone_impl() const
    {
        return m_p_impl->clone_impl();
    }

    const solid_background::drawing_details_type& solid_background::drawing_details_impl() const
    {
        return m_p_impl->drawing_details_impl();
    }

    const solid_background::details_type& solid_background::details_impl() const
    {
        return m_p_impl->details_impl();
    }

    solid_background::details_type& solid_background::details_impl()
    {
        return m_p_impl->details_impl();
    }
}
