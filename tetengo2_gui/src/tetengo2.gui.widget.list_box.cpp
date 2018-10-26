/*! \file
    \brief The definition of tetengo2::gui::widget::list_box.

    Copyright (C) 2007-2018 kaoru

    $Id$
*/

#include <algorithm>
#include <memory>
#include <stdexcept>

#include <boost/core/noncopyable.hpp>
#include <boost/predef.h>
#include <boost/throw_exception.hpp>

#include <tetengo2/detail/base/gui_impl_set.h>
#include <tetengo2/detail/base/message_handler.h>
#include <tetengo2/gui/message/list_selection_observer_set.h>
#include <tetengo2/gui/widget/control.h>
#include <tetengo2/gui/widget/list_box.h>
#include <tetengo2/gui/widget/widget.h>
#include <tetengo2/stdalt.h>
#include <tetengo2/type_list.h>


namespace tetengo2::gui::widget {
    class list_box::impl : private boost::noncopyable
    {
    public:
        // types

        using size_type = list_box::size_type;

        using string_type = list_box::string_type;

        using list_selection_observer_set_type = list_box::list_selection_observer_set_type;


        // constructors and destructor

        impl() : m_list_selection_observer_set{} {}


        // functions

        size_type value_count(const list_box& self) const
        {
            return widget_details().list_box_value_count(self);
        }

        string_type value(const size_type index, const list_box& self) const
        {
            if (index >= value_count(self))
                BOOST_THROW_EXCEPTION((std::out_of_range{ "index is out of range." }));

            return widget_details().list_box_value(self, index);
        }

        void set_value(const size_type index, string_type value, list_box& self)
        {
            if (index >= value_count(self))
                BOOST_THROW_EXCEPTION((std::out_of_range{ "index is out of range." }));

            widget_details().set_list_box_value(self, index, std::move(value));
        }

        void insert_value(const size_type index, string_type value, list_box& self)
        {
            if (index > value_count(self))
                BOOST_THROW_EXCEPTION((std::out_of_range{ "index is out of range." }));

            widget_details().insert_list_box_value(self, index, std::move(value));
        }

        void erase_value(const size_type index, list_box& self)
        {
            if (index >= value_count(self))
                BOOST_THROW_EXCEPTION((std::out_of_range{ "index is out of range." }));

            widget_details().erase_list_box_value(self, index);
        }

        void clear(list_box& self)
        {
            widget_details().clear_list_box(self);
        }

        tetengo2::stdalt::optional<size_type> selected_value_index(const list_box& self) const
        {
            return widget_details().selected_list_box_value_index(self);
        }

        void select_value(const size_type index, list_box& self)
        {
            if (index >= value_count(self))
                BOOST_THROW_EXCEPTION((std::out_of_range{ "index is out of range." }));

            widget_details().select_list_box_value(self, index);
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


    list_box::list_box(widget& parent, const scroll_bar_style_type scroll_bar_style)
    :
#if BOOST_COMP_MSVC
#pragma warning(push)
#pragma warning(disable : 4355)
#endif
      control{ scroll_bar_style,
               detail::gui_detail_impl_set().message_handler_().make_list_box_message_handler_map(
                   *this,
                   message_handler_map_type{}),
               widget_details().create_list_box(
                   parent,
                   static_cast<widget_details_type::scroll_bar_style_type>(scroll_bar_style)) },
#if BOOST_COMP_MSVC
#pragma warning(pop)
#endif
      m_p_impl{ std::make_unique<impl>() }
    {
        control::initialize(this);

        parent.child_observer_set().created()(*this);
    }

    list_box::~list_box() noexcept
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

    list_box::size_type list_box::value_count() const
    {
        return m_p_impl->value_count(*this);
    }

    list_box::string_type list_box::value(const size_type index) const
    {
        return m_p_impl->value(index, *this);
    }

    void list_box::set_value(const size_type index, string_type value)
    {
        m_p_impl->set_value(index, std::move(value), *this);
    }

    void list_box::insert_value(const size_type index, string_type value)
    {
        m_p_impl->insert_value(index, std::move(value), *this);
    }

    void list_box::erase_value(const size_type index)
    {
        m_p_impl->erase_value(index, *this);
    }

    void list_box::clear()
    {
        m_p_impl->clear(*this);
    }

    tetengo2::stdalt::optional<list_box::size_type> list_box::selected_value_index() const
    {
        return m_p_impl->selected_value_index(*this);
    }

    void list_box::select_value(const size_type index)
    {
        m_p_impl->select_value(index, *this);
    }

    const list_box::list_selection_observer_set_type& list_box::list_selection_observer_set() const
    {
        return m_p_impl->list_selection_observer_set();
    }

    list_box::list_selection_observer_set_type& list_box::list_selection_observer_set()
    {
        return m_p_impl->list_selection_observer_set();
    }
}
