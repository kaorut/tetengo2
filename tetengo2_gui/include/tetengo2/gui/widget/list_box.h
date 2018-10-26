/*! \file
    \brief The definition of tetengo2::gui::widget::list_box.

    Copyright (C) 2007-2018 kaoru

    $Id$
*/

#if !defined(TETENGO2_GUI_WIDGET_LISTBOX_H)
#define TETENGO2_GUI_WIDGET_LISTBOX_H

#include <memory>

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

        //! The size type.
        using size_type = tetengo2::type_list::size_type;

        //! The string type.
        using string_type = tetengo2::type_list::string_type;

        //! The list selection observer set type.
        using list_selection_observer_set_type = gui::message::list_selection_observer_set;


        // constructors and destructor

        /*!
            \brief Creates a list box.

            \param parent           A parent widget.
            \param scroll_bar_style A scroll bar style type.
        */
        list_box(widget& parent, scroll_bar_style_type scroll_bar_style);

        /*!
            \brief Destroys the list box.
        */
        virtual ~list_box() noexcept;


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
