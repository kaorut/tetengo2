/*! \file
    \brief The definition of tetengo2::gui::widget::map_box.

    Copyright (C) 2007-2019 kaoru

    $Id$
*/

#if !defined(TETENGO2_GUI_WIDGET_MAPBOX_H)
#define TETENGO2_GUI_WIDGET_MAPBOX_H

#include <memory>
#include <utility>

#include <tetengo2/gui/message/list_selection_observer_set.h>
#include <tetengo2/gui/widget/custom_control.h>
#include <tetengo2/gui/widget/widget.h>
#include <tetengo2/stdalt.h>
#include <tetengo2/type_list.h>


namespace tetengo2::gui::widget {
    /*!
        \brief The class for a map box.
    */
    class map_box : public custom_control
    {
    public:
        // types

        //! The size type.
        using size_type = tetengo2::type_list::size_type;

        //! The string type.
        using string_type = tetengo2::type_list::string_type;

        //! The position unit type.
        using position_unit_type = typename position_type::unit_type;

        //! The list selection observer set type.
        using list_selection_observer_set_type = gui::message::list_selection_observer_set;

        //! The value type.
        using value_type = std::pair<string_type, string_type>;


        // constructors and destructor

        /*!
            \brief Creates a map box.

            \param parent A parent widget.
        */
        explicit map_box(widget& parent);

        /*!
            \brief Destroys the map box.
        */
        virtual ~map_box();


        // functions

        /*!
            \brief Returns the value count.

            \return The value count.
        */
        size_type value_count() const;

        /*!
            \brief Returns the value.

            \param index An index.

            \return The value.

            \throw std::out_of_range When index is out of the range.
        */
        const value_type& value(size_type index) const;

        /*!
            \brief Sets an value.

            \param index An index.
            \param value An value.

            \throw std::out_of_range When index is out of the range.
        */
        void set_value(size_type index, value_type value);

        /*!
            \brief Inserts an value.

            \param index An index.
            \param value An value.

            \throw std::out_of_range When index is out of the range.
        */
        void insert_value(size_type index, value_type value);

        /*!
            \brief Erases an value.

            \param index An index.

            \throw std::out_of_range When index is out of the range.
        */
        void erase_value(size_type index);

        /*!
            \brief Clears the list box.
        */
        void clear();

        /*!
            \brief Returns the selected value index.

            \return The selected value index. Or TETENGO2_STDALT_NULLOPT when no value is selected.
        */
        tetengo2::stdalt::optional<size_type> selected_value_index() const;

        /*!
            \brief Selects an value.

            \param index An index.

            \throw std::out_of_range When index is out of the range.
        */
        void select_value(size_type index);

        /*!
            \brief Returns the splitter position.

            \return The splitter position.
        */
        const position_unit_type& splitter_position() const;

        /*!
            \brief Sets a splitter position.

            \param position A position.
        */
        void set_splitter_position(position_unit_type position);

        /*!
            \brief Returns the list selection observer set.

            \return The list selection observer set.
        */
        const list_selection_observer_set_type& list_selection_observer_set() const;

        /*!
            \brief Returns the list selection observer set.

            \return The list selection observer set.
        */
        list_selection_observer_set_type& list_selection_observer_set();


    private:
        // types

        class impl;


        // variables

        const std::unique_ptr<impl> m_p_impl;
    };
}


#endif
