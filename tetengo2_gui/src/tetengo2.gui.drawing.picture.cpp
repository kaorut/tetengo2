/*! \file
    \brief The definition of tetengo2::gui::drawing::picture.

    Copyright (C) 2007-2019 kaoru

    $Id$
*/

#include <algorithm>
#include <cassert>
#include <memory>
#include <stdexcept>

#include <boost/core/noncopyable.hpp>
#include <boost/throw_exception.hpp>

#include <tetengo2/detail/base/drawing.h>
#include <tetengo2/detail/base/gui_impl_set.h>
#include <tetengo2/gui/drawing/picture.h>


namespace tetengo2::gui::drawing {
    /*!
        \brief The class for a picture.
    */
    class picture::impl : private boost::noncopyable
    {
    public:
        // types

        using dimension_type = picture::dimension_type;

        using drawing_details_type = detail::base::drawing;

        using details_type = drawing_details_type::picture_details_type;

        using details_ptr_type = drawing_details_type::picture_details_ptr_type;


        // constructors and destructor

        impl(const drawing_details_type& drawing_details, const dimension_type& dimension)
        : m_drawing_details{ drawing_details }, m_p_details{ m_drawing_details.create_picture(dimension) }
        {}

        explicit impl(const dimension_type& dimension)
        : m_drawing_details{ detail::gui_detail_impl_set().drawing_() }, m_p_details{ m_drawing_details.create_picture(
                                                                             dimension) }
        {}

        impl(const drawing_details_type& drawing_details, details_ptr_type p_details)
        : m_drawing_details{ drawing_details }, m_p_details{ std::move(p_details) }
        {
            if (!m_p_details)
                BOOST_THROW_EXCEPTION((std::invalid_argument{ "The detail implementation is nullptr." }));
        }

        explicit impl(details_ptr_type p_details)
        : m_drawing_details{ detail::gui_detail_impl_set().drawing_() }, m_p_details{ std::move(p_details) }
        {
            if (!m_p_details)
                BOOST_THROW_EXCEPTION((std::invalid_argument{ "The detail implementation is nullptr." }));
        }


        // functions

        dimension_type dimension() const
        {
            return m_drawing_details.picture_dimension(*m_p_details);
        }

        const drawing_details_type& drawing_details() const
        {
            return m_drawing_details;
        }

        const details_type& details() const
        {
            assert(m_p_details);
            return *m_p_details;
        }

        details_type& details()
        {
            assert(m_p_details);
            return *m_p_details;
        }


    private:
        // variables

        const drawing_details_type& m_drawing_details;

        const details_ptr_type m_p_details;
    };


    picture::picture(const drawing_details_type& drawing_details, const dimension_type& dimension)
    : m_p_impl{ std::make_unique<impl>(drawing_details, dimension) }
    {}

    picture::picture(const dimension_type& dimension) : m_p_impl{ std::make_unique<impl>(dimension) } {}

    picture::picture(const drawing_details_type& drawing_details, details_ptr_type p_details)
    : m_p_impl{ std::make_unique<impl>(drawing_details, std::move(p_details)) }
    {}

    picture::picture(details_ptr_type p_details) : m_p_impl{ std::make_unique<impl>(std::move(p_details)) } {}

    picture::~picture() = default;

    picture::dimension_type picture::dimension() const
    {
        return m_p_impl->dimension();
    }

    const picture::drawing_details_type& picture::drawing_details() const
    {
        return m_p_impl->drawing_details();
    }

    const picture::details_type& picture::details() const
    {
        return m_p_impl->details();
    }

    picture::details_type& picture::details()
    {
        return m_p_impl->details();
    }
}
