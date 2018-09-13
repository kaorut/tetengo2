/*! \file
    \brief The definition of tetengo2::gui::drawing::background.

    Copyright (C) 2007-2018 kaoru

    $Id$
*/

#include <memory>

#include <boost/core/noncopyable.hpp>

#include <tetengo2/gui/drawing/background.h>


namespace tetengo2::gui::drawing {
    class background::impl : private boost::noncopyable
    {
    public:
        // types

        using drawing_details_type = background::drawing_details_type;

        using details_type = background::details_type;

        using details_ptr_type = background::details_ptr_type;


        // functions

        std::unique_ptr<background> clone(const background& self) const
        {
            return self.clone_impl();
        }

        const drawing_details_type& drawing_details(const background& self) const
        {
            return self.drawing_details_impl();
        }

        const details_type& details(const background& self) const
        {
            return self.details_impl();
        }

        details_type& details(background& self)
        {
            return self.details_impl();
        }
    };


    background::~background() = default;

    std::unique_ptr<background> background::clone() const
    {
        return m_p_impl->clone(*this);
    }

    const background::drawing_details_type& background::drawing_details() const
    {
        return m_p_impl->drawing_details(*this);
    }

    const background::details_type& background::details() const
    {
        return m_p_impl->details(*this);
    }

    background::details_type& background::details()
    {
        return m_p_impl->details(*this);
    }

    background::background() : m_p_impl{ std::make_unique<impl>() } {}
}
