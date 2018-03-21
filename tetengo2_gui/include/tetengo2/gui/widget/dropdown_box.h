/*! \file
    \brief The definition of tetengo2::gui::widget::dropdown_box.

    Copyright (C) 2007-2018 kaoru

    $Id$
*/

#if !defined(TETENGO2_GUI_WIDGET_DROPDOWNBOX_H)
#define TETENGO2_GUI_WIDGET_DROPDOWNBOX_H

#include <stdexcept>

#include <boost/optional.hpp>
#include <boost/predef.h>
#include <boost/throw_exception.hpp>

#include <tetengo2/gui/message/list_selection_observer_set.h>
#include <tetengo2/gui/widget/control.h>


namespace tetengo2 { namespace gui { namespace widget {
    /*!
        \brief The class template for a dropdown box.

        \tparam Traits        A traits type.
        \tparam DetailsTraits A detail implementation type traits.
    */
    template <typename Traits, typename DetailsTraits>
    class dropdown_box : public control<Traits, DetailsTraits>
    {
    public:
        // types

        //! The traits type.
        using traits_type = Traits;

        //! The details traits type.
        using details_traits_type = DetailsTraits;

        //! The widget details type.
        using widget_details_type = typename details_traits_type::widget_details_type;

        //! The message handler details type.
        using message_handler_details_type = typename details_traits_type::message_handler_details_type;

        //! The base type.
        using base_type = control<traits_type, details_traits_type>;

        //! The widget type.
        using widget_type = typename base_type::base_type;

        //! The size type.
        using size_type = typename base_type::size_type;

        //! The string type.
        using string_type = typename base_type::string_type;

        //! The list selection observer set type.
        using list_selection_observer_set_type = gui::message::list_selection_observer_set;


        // constructors and destructor

        /*!
            \brief Creates a dropdown box.

            \param parent A parent widget.
        */
        explicit dropdown_box(widget_type& parent)
        :
#if BOOST_COMP_MSVC
#pragma warning(push)
#pragma warning(disable : 4355)
#endif
          base_type{
              base_type::scroll_bar_style_type::none,
              message_handler_details_type::make_dropdown_box_message_handler_map(*this, message_handler_map_type{}),
              widget_details_type::create_dropdown_box(parent)
          },
#if BOOST_COMP_MSVC
#pragma warning(pop)
#endif
          m_list_selection_observer_set{}
        {
            base_type::initialize(this);

            parent.child_observer_set().created()(*this);
        }

        /*!
            \brief Destroys the dropdown box.
        */
        virtual ~dropdown_box() noexcept
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
            return widget_details_type::template dropdown_box_value_count<size_type>(*this);
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

            return widget_details_type::template dropdown_box_value<string_type>(*this, index, widget_type::encoder());
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

            widget_details_type::set_dropdown_box_value(*this, index, std::move(value), widget_type::encoder());
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

            widget_details_type::insert_dropdown_box_value(*this, index, std::move(value), widget_type::encoder());
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

            widget_details_type::erase_dropdown_box_value(*this, index);
        }

        /*!
            \brief Clears the dropdown box.
        */
        void clear()
        {
            widget_details_type::clear_dropdown_box(*this);
        }

        /*!
            \brief Returns the selected value index.

            \return The selected value index. Or boost::none when no value is selected.
        */
        boost::optional<size_type> selected_value_index() const
        {
            return widget_details_type::template selected_dropdown_box_value_index<size_type>(*this);
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

            widget_details_type::select_dropdown_box_value(*this, index);
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


}}}


#endif
