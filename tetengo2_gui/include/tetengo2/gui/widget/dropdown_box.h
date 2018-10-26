/*! \file
    \brief The definition of tetengo2::gui::widget::dropdown_box.

    Copyright (C) 2007-2018 kaoru

    $Id$
*/

#if !defined(TETENGO2_GUI_WIDGET_DROPDOWNBOX_H)
#define TETENGO2_GUI_WIDGET_DROPDOWNBOX_H

#include <memory>

#include <tetengo2/gui/message/list_selection_observer_set.h>
#include <tetengo2/gui/widget/control.h>
#include <tetengo2/gui/widget/widget.h>
#include <tetengo2/stdalt.h>
#include <tetengo2/type_list.h>


namespace tetengo2::gui::widget {
    /*!
        \brief The class for a dropdown box.
    */
    class dropdown_box : public control
    {
    public:
        // types

        //! The size type.
        using size_type = tetengo2::type_list::size_type;

        //! The list selection observer set type.
        using list_selection_observer_set_type = gui::message::list_selection_observer_set;


        // constructors and destructor

        /*!
            \brief Creates a dropdown box.

            \param parent A parent widget.
        */
        explicit dropdown_box(widget& parent);

        /*!
            \brief Destroys the dropdown box.
        */
        virtual ~dropdown_box() noexcept;


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
        string_type value(size_type index) const;

        /*!
            \brief Sets an value.

            \param index An index.
            \param value An value.

            \throw std::out_of_range When index is out of the range.
        */
        void set_value(size_type index, string_type value);

        /*!
            \brief Inserts an value.

            \param index An index.
            \param value An value.

            \throw std::out_of_range When index is out of the range.
        */
        void insert_value(size_type index, string_type value);

        /*!
            \brief Erases an value.

            \param index An index.

            \throw std::out_of_range When index is out of the range.
        */
        void erase_value(size_type index);

        /*!
            \brief Clears the dropdown box.
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
