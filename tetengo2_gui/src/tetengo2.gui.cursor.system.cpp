/*! \file
    \brief The definition of tetengo2::gui::cursor::system.

    Copyright (C) 2007-2018 kaoru

    $Id$
*/

#include <cassert>
#include <memory>

#include <tetengo2/gui/cursor/cursor_base.h>
#include <tetengo2/gui/cursor/system.h>
#include <tetengo2/gui/cursor/system_cursor_style.h>


namespace tetengo2::gui::cursor {
    class system::impl : public cursor_base
    {
    public:
        // types

        using base_type = cursor_base;

        using details_type = cursor_base::details_type;

        using details_ptr_type = cursor_base::details_ptr_type;

        using style_type = system_cursor_style;


        // constructors and destructor

        impl(const style_type style, const cursor_details_type& cursor_details)
        : m_style{ style }, m_p_details{ cursor_details.create_system_cursor(style) }
        {}


        // functions

        style_type style() const
        {
            return m_style;
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
        // variables

        style_type m_style;

        details_ptr_type m_p_details;
    };


    system::system(style_type style, const cursor_details_type& cursor_details)
    : m_p_impl{ std::make_unique<impl>(style, cursor_details) }
    {}

    system::~system() = default;

    system::style_type system::style() const
    {
        return m_p_impl->style();
    }

    const system::details_type& system::details_impl() const
    {
        return m_p_impl->details_impl();
    }

    system::details_type& system::details_impl()
    {
        return m_p_impl->details_impl();
    }
}
