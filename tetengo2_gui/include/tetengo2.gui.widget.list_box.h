/*! \file
    \brief The definition of tetengo2::gui::widget::list_box.

    Copyright (C) 2007-2013 kaoru

    $Id$
*/

#if !defined(TETENGO2_GUI_WIDGET_LISTBOX_H)
#define TETENGO2_GUI_WIDGET_LISTBOX_H

//#include <stdexcept>
//#include <utility>

//#include <boost/optional.hpp>
//#include <boost/predef.h>
//#include <boost/throw_exception.hpp>

#include "tetengo2.gui.measure.h"
#include "tetengo2.gui.widget.control.h"
#include "tetengo2.stdalt.h"


namespace tetengo2 { namespace gui { namespace widget
{
    /*!
        \brief The class template for a list box.

        \tparam Traits                A traits type.
        \tparam WidgetDetails         A detail implementation type of a widget.
        \tparam MessageHandlerDetails A detail implementation type of a message handler.
   */
    template <typename Traits, typename WidgetDetails, typename MessageHandlerDetails>
    class list_box : public control<typename Traits::base_type, WidgetDetails, MessageHandlerDetails>
    {
    public:
        // types

        //! The traits type.
        typedef Traits traits_type;

        //! The integer size type.
        typedef typename traits_type::int_size_type int_size_type;

        //! The list selection observer set type.
        typedef typename traits_type::list_selection_observer_set_type list_selection_observer_set_type;

        //! The detail implementation type of a widget.
        typedef WidgetDetails widget_details_type;

        //! The detail implementation type of a message handler.
        typedef MessageHandlerDetails message_handler_details_type;

        //! The base type.
        typedef control<typename traits_type::base_type, widget_details_type, message_handler_details_type> base_type;

        //! The widget type.
        typedef typename base_type::base_type widget_type;

        //! The string type.
        typedef typename base_type::string_type string_type;

        //! The detail implementation type.
        typedef typename widget_details_type::widget_details_type details_type;

        //! The scroll bar style type.
        typedef typename base_type::scroll_bar_style_type scroll_bar_style_type;


        // constructors and destructor

        /*!
            \brief Creates a list box.

            \param parent           A parent widget.
            \param scroll_bar_style A scroll bar style type.
        */
        list_box(widget_type& parent, const scroll_bar_style_type scroll_bar_style)
        :
#if BOOST_COMP_MSVC
#   pragma warning(push)
#   pragma warning(disable: 4355)
#endif
        base_type(
            scroll_bar_style,
            message_handler_details_type::make_list_box_message_handler_map(*this, message_handler_map_type()),
            widget_details_type::create_list_box(parent, scroll_bar_style)
        ),
#if BOOST_COMP_MSVC
#   pragma warning(pop)
#endif
        m_list_selection_observer_set()
        {
            this->initialize(this);
        }

        /*!
            \brief Destroys the list box.
        */
        virtual ~list_box()
        TETENGO2_STDALT_NOEXCEPT
        {}


        // functions

        /*!
            \brief Returns the value count.

            \return The value count.
        */
        int_size_type value_count()
        const
        {
            return widget_details_type::template list_box_value_count<int_size_type>(*this);
        }

        /*!
            \brief Returns the value.

            \param index An index.

            \return The value.

            \throw std::out_of_range When index is out of the range.
        */
        string_type value(const int_size_type index)
        const
        {
            if (index >= value_count())
                BOOST_THROW_EXCEPTION(std::out_of_range("index is out of range."));

            return widget_details_type::template list_box_value<string_type>(*this, index, widget_type::encoder());
        }

        /*!
            \brief Sets an value.

            \param index An index.
            \param value An value.

            \throw std::out_of_range When index is out of the range.
        */
        void set_value(const int_size_type index, string_type value)
        {
            if (index >= value_count())
                BOOST_THROW_EXCEPTION(std::out_of_range("index is out of range."));

            widget_details_type::set_list_box_value(*this, index, std::move(value), widget_type::encoder());
        }

        /*!
            \brief Inserts an value.

            \param index An index.
            \param value An value.

            \throw std::out_of_range When index is out of the range.
        */
        void insert_value(const int_size_type index, string_type value)
        {
            if (index > value_count())
                BOOST_THROW_EXCEPTION(std::out_of_range("index is out of range."));

            widget_details_type::insert_list_box_value(*this, index, std::move(value), widget_type::encoder());
        }

        /*!
            \brief Erases an value.

            \param index An index.

            \throw std::out_of_range When index is out of the range.
        */
        void erase_value(const int_size_type index)
        {
            if (index >= value_count())
                BOOST_THROW_EXCEPTION(std::out_of_range("index is out of range."));

            widget_details_type::erase_list_box_value(*this, index);
        }

        /*!
            \brief Clears the list box.
        */
        void clear()
        {
            widget_details_type::clear_list_box(*this);
        }

        /*!
            \brief Returns the selected value index.

            \return The selected value index. Or boost::none when no value is selected.
        */
        boost::optional<int_size_type> selected_value_index()
        const
        {
            return widget_details_type::template selected_list_box_value_index<int_size_type>(*this);
        }

        /*!
            \brief Selects an value.

            \param index An index.

            \throw std::out_of_range When index is out of the range.
        */
        void select_value(const int_size_type index)
        {
            if (index >= value_count())
                BOOST_THROW_EXCEPTION(std::out_of_range("index is out of range."));

            widget_details_type::select_list_box_value(*this, index);
        }

        /*!
            \brief Returns the list selection observer set.

            \return The list selection observer set.
        */
        const list_selection_observer_set_type& list_selection_observer_set()
        const
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

        typedef typename message_handler_details_type::message_handler_map_type message_handler_map_type;


        // variables

        list_selection_observer_set_type m_list_selection_observer_set;


    };


}}}


#endif
