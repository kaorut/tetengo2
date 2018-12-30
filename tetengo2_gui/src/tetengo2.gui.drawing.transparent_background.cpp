/*! \file
    \brief The definition of tetengo2::gui::drawing::transparent_background.

    Copyright (C) 2007-2019 kaoru

    $Id$
*/

#include <cassert>
#include <memory>

#include <boost/core/noncopyable.hpp>

#include <tetengo2/detail/base/gui_impl_set.h>
#include <tetengo2/gui/drawing/transparent_background.h>


namespace tetengo2::gui::drawing {
    class transparent_background::impl : private boost::noncopyable
    {
    public:
        // types

        using base_type = transparent_background::base_type;

        using drawing_details_type = transparent_background::drawing_details_type;

        using details_type = transparent_background::details_type;


        // constructors and destructor

        explicit impl(const drawing_details_type& drawing_details)
        : m_drawing_details{ drawing_details }, m_p_details{ m_drawing_details.create_transparent_background() }
        {}

        impl()
        : m_drawing_details{ detail::gui_detail_impl_set().drawing_() }, m_p_details{
              m_drawing_details.create_transparent_background()
          }
        {}


        // functions

        std::unique_ptr<base_type> clone_impl() const
        {
            return std::make_unique<transparent_background>(m_drawing_details);
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


    private:
        // types

        using details_ptr_type = drawing_details_type::background_details_ptr_type;


        // variables

        const drawing_details_type& m_drawing_details;

        const details_ptr_type m_p_details;
    };


    transparent_background::transparent_background(const drawing_details_type& drawing_details)
    : base_type{}, m_p_impl{ std::make_unique<impl>(drawing_details) }
    {}

    transparent_background::transparent_background() : base_type{}, m_p_impl{ std::make_unique<impl>() } {}

    transparent_background::~transparent_background() = default;

    std::unique_ptr<transparent_background::base_type> transparent_background::clone_impl() const
    {
        return m_p_impl->clone_impl();
    }

    const transparent_background::drawing_details_type& transparent_background::drawing_details_impl() const
    {
        return m_p_impl->drawing_details_impl();
    }

    const transparent_background::details_type& transparent_background::details_impl() const
    {
        return m_p_impl->details_impl();
    }

    transparent_background::details_type& transparent_background::details_impl()
    {
        return m_p_impl->details_impl();
    }
}
