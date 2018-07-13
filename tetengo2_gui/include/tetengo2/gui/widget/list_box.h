/*! \file
    \brief The definition of tetengo2::gui::widget::list_box.

    Copyright (C) 2007-2018 kaoru

    $Id$
*/

#if !defined(TETENGO2_GUI_WIDGET_LISTBOX_H)
#define TETENGO2_GUI_WIDGET_LISTBOX_H

#include <algorithm>
#include <stdexcept>

#include <boost/predef.h>
#include <boost/throw_exception.hpp>

#include <tetengo2/gui/message/list_selection_observer_set.h>
#include <tetengo2/gui/widget/control.h>
#include <tetengo2/gui/widget/widget.h>
#include <tetengo2/stdalt.h>
#include <tetengo2/type_list.h>


namespace tetengo2::gui::widget {
    /*!
        \brief The class for a list box.
    */
    class list_box : public control
    {
    public:
        // types

        //! The integer size type.
        using size_type = tetengo2::type_list::size_type;

        //! The list selection observer set type.
        using list_selection_observer_set_type = gui::message::list_selection_observer_set;


        // constructors and destructor

        /*!
            \brief Creates a list box.

            \param parent           A parent widget.
            \param scroll_bar_style A scroll bar style type.
        */
        list_box(widget& parent, const scroll_bar_style_type scroll_bar_style)
        :
#if BOOST_COMP_MSVC
#pragma warning(push)
#pragma warning(disable : 4355)
#endif
          control{ scroll_bar_style,
                   message_handler_details_type::make_list_box_message_handler_map(*this, message_handler_map_type{}),
                   widget_details_type::instance().create_list_box(
                       parent,
                       static_cast<widget_details_type::scroll_bar_style_type>(scroll_bar_style)) },
#if BOOST_COMP_MSVC
#pragma warning(pop)
#endif
          m_list_selection_observer_set{}
        {
            control::initialize(this);

            parent.child_observer_set().created()(*this);
        }

        /*!
            \brief Destroys the list box.
        */
        virtual ~list_box() noexcept
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


        // functions

        /*!
            \brief Returns the value count.

            \return The value count.
        */
        size_type value_count() const
        {
            return widget_details_type::instance().list_box_value_count(*this);
        }

        /*!
            \brief Returns the value.

            \param index An index.

            \return The value.

            \throw std::out_of_range When index is out of the range.
        */
        string_type value(const size_type index) const
        {
            if (index >= value_count())
                BOOST_THROW_EXCEPTION((std::out_of_range{ "index is out of range." }));

            return widget_details_type::instance().list_box_value(*this, index);
        }

        /*!
            \brief Sets an value.

            \param index An index.
            \param value An value.

            \throw std::out_of_range When index is out of the range.
        */
        void set_value(const size_type index, string_type value)
        {
            if (index >= value_count())
                BOOST_THROW_EXCEPTION((std::out_of_range{ "index is out of range." }));

            widget_details_type::instance().set_list_box_value(*this, index, std::move(value));
        }

        /*!
            \brief Inserts an value.

            \param index An index.
            \param value An value.

            \throw std::out_of_range When index is out of the range.
        */
        void insert_value(const size_type index, string_type value)
        {
            if (index > value_count())
                BOOST_THROW_EXCEPTION((std::out_of_range{ "index is out of range." }));

            widget_details_type::instance().insert_list_box_value(*this, index, std::move(value));
        }

        /*!
            \brief Erases an value.

            \param index An index.

            \throw std::out_of_range When index is out of the range.
        */
        void erase_value(const size_type index)
        {
            if (index >= value_count())
                BOOST_THROW_EXCEPTION((std::out_of_range{ "index is out of range." }));

            widget_details_type::instance().erase_list_box_value(*this, index);
        }

        /*!
            \brief Clears the list box.
        */
        void clear()
        {
            widget_details_type::instance().clear_list_box(*this);
        }

        /*!
            \brief Returns the selected value index.

            \return The selected value index. Or TETENGO2_STDALT_NULLOPT when no value is selected.
        */
        tetengo2::stdalt::optional<size_type> selected_value_index() const
        {
            return widget_details_type::instance().selected_list_box_value_index(*this);
        }

        /*!
            \brief Selects an value.

            \param index An index.

            \throw std::out_of_range When index is out of the range.
        */
        void select_value(const size_type index)
        {
            if (index >= value_count())
                BOOST_THROW_EXCEPTION((std::out_of_range{ "index is out of range." }));

            widget_details_type::instance().select_list_box_value(*this, index);
        }

        /*!
            \brief Returns the list selection observer set.

            \return The list selection observer set.
        */
        const list_selection_observer_set_type& list_selection_observer_set() const
        {
            return m_list_selection_observer_set;
        }

        /*!
            \brief Returns the list selection observer set.

            \return The list selection observer set.
        */
        list_selection_observer_set_type& list_selection_observer_set()
        {
            return m_list_selection_observer_set;
        }


    private:
        // types

        using message_handler_map_type = typename message_handler_details_type::message_handler_map_type;


        // variables

        list_selection_observer_set_type m_list_selection_observer_set;
    };
}


#endif
