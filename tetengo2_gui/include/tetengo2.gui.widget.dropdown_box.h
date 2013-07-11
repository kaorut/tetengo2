/*! \file
    \brief The definition of tetengo2::gui::widget::dropdown_box.

    Copyright (C) 2007-2013 kaoru

    $Id$
*/

#if !defined(TETENGO2_GUI_WIDGET_DROPDOWNBOX_H)
#define TETENGO2_GUI_WIDGET_DROPDOWNBOX_H

//#include <stdexcept>
//#include <utility>

//#include <boost/optional.hpp>
//#include <boost/throw_exception.hpp>

#include "tetengo2.gui.measure.h"
#include "tetengo2.gui.widget.control.h"
#include "tetengo2.stdalt.h"


namespace tetengo2 { namespace gui { namespace widget
{
    /*!
        \brief The class template for a dropdown box.

        \tparam Traits                A traits type.
        \tparam WidgetDetails         A detail implementation type of a widget.
        \tparam MessageHandlerDetails A detail implementation type of a message handler.
   */
    template <typename Traits, typename WidgetDetails, typename MessageHandlerDetails>
    class dropdown_box : public control<typename Traits::base_type, WidgetDetails, MessageHandlerDetails>
    {
    public:
        // types

        //! The traits type.
        typedef Traits traits_type;

        //! The integer size type.
        typedef typename traits_type::int_size_type int_size_type;

        //! The dropdown box observer set type.
        typedef typename traits_type::dropdown_box_observer_set_type dropdown_box_observer_set_type;

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


        // constructors and destructor

        /*!
            \brief Creates a dropdown box.

            \param parent A parent widget.
        */
        dropdown_box(widget_type& parent)
        :
#if defined(_MSC_VER)
#   pragma warning(push)
#   pragma warning(disable: 4355)
#endif
        base_type(
            base_type::scroll_bar_style_type::none,
            message_handler_details_type::make_dropdown_box_message_handler_map(*this, message_handler_map_type()),
            widget_details_type::create_dropdown_box(parent)
        ),
#if defined(_MSC_VER)
#   pragma warning(pop)
#endif
        m_dropdown_box_observer_set()
        {
            this->initialize(this);
        }

        /*!
            \brief Destroys the dropdown box.
        */
        virtual ~dropdown_box()
        TETENGO2_CPP11_NOEXCEPT
        {}


        // functions

        /*!
            \brief Returns the item count.

            \return The item count.
        */
        int_size_type item_count()
        const
        {
            return widget_details_type::template dropdown_box_item_count<int_size_type>(*this);
        }

        /*!
            \brief Returns the item.

            \param index An index.

            \return The item.

            \throw std::out_of_range When index is out of the range.
        */
        string_type item(const int_size_type index)
        const
        {
            if (index >= item_count())
                BOOST_THROW_EXCEPTION(std::out_of_range("index is out of range."));

            return widget_details_type::template dropdown_box_item<string_type>(*this, index, widget_type::encoder());
        }

        /*!
            \brief Sets an item.

            \param index An index.
            \param item  An item.

            \throw std::out_of_range When index is out of the range.
        */
        void set_item(const int_size_type index, string_type item)
        {
            if (index >= item_count())
                BOOST_THROW_EXCEPTION(std::out_of_range("index is out of range."));

            widget_details_type::set_dropdown_box_item(*this, index, std::move(item), widget_type::encoder());
        }

        /*!
            \brief Inserts an item.

            \param index An index.
            \param item  An item.

            \throw std::out_of_range When index is out of the range.
        */
        void insert_item(const int_size_type index, string_type item)
        {
            if (index > item_count())
                BOOST_THROW_EXCEPTION(std::out_of_range("index is out of range."));

            widget_details_type::insert_dropdown_box_item(*this, index, std::move(item), widget_type::encoder());
        }

        /*!
            \brief Erases an item.

            \param index An index.

            \throw std::out_of_range When index is out of the range.
        */
        void erase_item(const int_size_type index)
        {
            if (index >= item_count())
                BOOST_THROW_EXCEPTION(std::out_of_range("index is out of range."));

            widget_details_type::erase_dropdown_box_item(*this, index);
        }

        /*!
            \brief Clears the dropdown box.
        */
        void clear()
        {
            widget_details_type::clear_dropdown_box(*this);
        }

        /*!
            \brief Returns the selected item index.

            \return The selected item index. Or boost::none when no item is selected.
        */
        boost::optional<int_size_type> selected_item_index()
        const
        {
            return widget_details_type::template selected_dropdown_box_item_index<int_size_type>(*this);
        }

        /*!
            \brief Selects an item.

            \param index An index.

            \throw std::out_of_range When index is out of the range.
        */
        void select_item(const int_size_type index)
        {
            if (index >= item_count())
                BOOST_THROW_EXCEPTION(std::out_of_range("index is out of range."));

            return widget_details_type::select_dropdown_box_item(*this, index);
        }

        /*!
            \brief Returns the dropdown box observer set.

            \return The dropdown box observer set.
        */
        const dropdown_box_observer_set_type& dropdown_box_observer_set()
        const
        {
            return m_dropdown_box_observer_set;
        }

        /*!
            \brief Returns the dropdown box observer set.

            \return The dropdown box observer set.
        */
        dropdown_box_observer_set_type& dropdown_box_observer_set()
        {
            return m_dropdown_box_observer_set;
        }


    private:
        // types

        typedef typename message_handler_details_type::message_handler_map_type message_handler_map_type;


        // variables

        dropdown_box_observer_set_type m_dropdown_box_observer_set;


    };


}}}


#endif
