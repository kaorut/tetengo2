/*! \file
    \brief The definition of tetengo2::gui::widget::dropdown_box.

    Copyright (C) 2007-2019 kaoru

    $Id$
*/

#include <algorithm>
#include <stdexcept>

#include <boost/core/noncopyable.hpp>
#include <boost/predef.h>
#include <boost/throw_exception.hpp>

#include <tetengo2/detail/base/gui_impl_set.h>
#include <tetengo2/detail/base/message_handler.h>
#include <tetengo2/gui/message/list_selection_observer_set.h>
#include <tetengo2/gui/widget/control.h>
#include <tetengo2/gui/widget/dropdown_box.h>
#include <tetengo2/gui/widget/widget.h>
#include <tetengo2/stdalt.h>
#include <tetengo2/type_list.h>


namespace tetengo2::gui::widget {
    class dropdown_box::impl : private boost::noncopyable
    {
    public:
        // types

        using size_type = dropdown_box::size_type;

        using list_selection_observer_set_type = dropdown_box::list_selection_observer_set_type;


        // constructors and destructor

        impl() : m_list_selection_observer_set{} {}


        // functions

        size_type value_count(const dropdown_box& self) const
        {
            return widget_details().dropdown_box_value_count(self);
        }

        string_type value(const size_type index, const dropdown_box& self) const
        {
            if (index >= value_count(self))
                BOOST_THROW_EXCEPTION((std::out_of_range{ "index is out of range." }));

            return widget_details().dropdown_box_value(self, index);
        }

        void set_value(const size_type index, string_type value, dropdown_box& self)
        {
            if (index >= value_count(self))
                BOOST_THROW_EXCEPTION((std::out_of_range{ "index is out of range." }));

            widget_details().set_dropdown_box_value(self, index, std::move(value));
        }

        void insert_value(const size_type index, string_type value, dropdown_box& self)
        {
            if (index > value_count(self))
                BOOST_THROW_EXCEPTION((std::out_of_range{ "index is out of range." }));

            widget_details().insert_dropdown_box_value(self, index, std::move(value));
        }

        void erase_value(const size_type index, dropdown_box& self)
        {
            if (index >= value_count(self))
                BOOST_THROW_EXCEPTION((std::out_of_range{ "index is out of range." }));

            widget_details().erase_dropdown_box_value(self, index);
        }

        void clear(dropdown_box& self)
        {
            widget_details().clear_dropdown_box(self);
        }

        tetengo2::stdalt::optional<size_type> selected_value_index(const dropdown_box& self) const
        {
            return widget_details().selected_dropdown_box_value_index(self);
        }

        void select_value(const size_type index, dropdown_box& self)
        {
            if (index >= value_count(self))
                BOOST_THROW_EXCEPTION((std::out_of_range{ "index is out of range." }));

            widget_details().select_dropdown_box_value(self, index);
        }

        const list_selection_observer_set_type& list_selection_observer_set() const
        {
            return m_list_selection_observer_set;
        }

        list_selection_observer_set_type& list_selection_observer_set()
        {
            return m_list_selection_observer_set;
        }


    private:
        // variables

        list_selection_observer_set_type m_list_selection_observer_set;
    };


    dropdown_box::dropdown_box(widget& parent)
    :
#if BOOST_COMP_MSVC
#pragma warning(push)
#pragma warning(disable : 4355)
#endif
      control{ control::scroll_bar_style_type::none,
               detail::gui_detail_impl_set().message_handler_().make_dropdown_box_message_handler_map(
                   *this,
                   message_handler_map_type{}),
               widget_details().create_dropdown_box(parent) },
#if BOOST_COMP_MSVC
#pragma warning(pop)
#endif
      m_p_impl{ std::make_unique<impl>() }
    {
        control::initialize(this);

        parent.child_observer_set().created()(*this);
    }

    dropdown_box::~dropdown_box() noexcept
    {
        try
        {
            if (this->has_parent())
                this->parent().child_observer_set().destroying()(*this);
        }
        catch (...)
        {
        }
    }

    dropdown_box::size_type dropdown_box::value_count() const
    {
        return m_p_impl->value_count(*this);
    }

    dropdown_box::string_type dropdown_box::value(const size_type index) const
    {
        return m_p_impl->value(index, *this);
    }

    void dropdown_box::set_value(const size_type index, string_type value)
    {
        m_p_impl->set_value(index, std::move(value), *this);
    }

    void dropdown_box::insert_value(const size_type index, string_type value)
    {
        m_p_impl->insert_value(index, std::move(value), *this);
    }

    void dropdown_box::erase_value(const size_type index)
    {
        m_p_impl->erase_value(index, *this);
    }

    void dropdown_box::clear()
    {
        m_p_impl->clear(*this);
    }

    tetengo2::stdalt::optional<dropdown_box::size_type> dropdown_box::selected_value_index() const
    {
        return m_p_impl->selected_value_index(*this);
    }

    void dropdown_box::select_value(const size_type index)
    {
        m_p_impl->select_value(index, *this);
    }

    const dropdown_box::list_selection_observer_set_type& dropdown_box::list_selection_observer_set() const
    {
        return m_p_impl->list_selection_observer_set();
    }

    dropdown_box::list_selection_observer_set_type& dropdown_box::list_selection_observer_set()
    {
        return m_p_impl->list_selection_observer_set();
    }
}
