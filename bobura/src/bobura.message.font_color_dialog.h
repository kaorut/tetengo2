/*! \file
    \brief The definition of bobura::message::font_color_dialog.

    Copyright (C) 2007-2012 kaoru

    $Id$
*/

#if !defined(BOBURA_MESSAGE_FONTCOLORDIALOG_H)
#define BOBURA_MESSAGE_FONTCOLORDIALOG_H

#include <limits>

#include <boost/optional.hpp>


namespace bobura { namespace message { namespace font_color_dialog
{
    /*!
        \brief The class template for a selection change observer of the category list box.

        \tparam Size    A size type.
        \tparam ListBox A list box type.
    */
    template <typename Size, typename ListBox>
    class category_list_box_selection_changed
    {
    public:
        // types

        //! The size type.
        typedef Size size_type;

        //! The list box type.
        typedef ListBox list_box_type;

        //! The update type.
        typedef std::function<void (const boost::optional<size_type>&)> update_type;


        // constructors and destructor

        /*!
            \brief Create a selection change observer of the category list box.

            \param current_category_index A current category index.
            \param list_box               A list box type.
            \param update                 A update function.
        */
        category_list_box_selection_changed(
            boost::optional<size_type>& current_category_index,
            const list_box_type&        list_box,
            const update_type           update
        )
        :
        m_current_category_index(current_category_index),
        m_list_box(list_box),
        m_update(update)
        {}


        // functions

        /*!
            \brief Called when the selection of the category list box is changed.
        */
        void operator()()
        const
        {
            const boost::optional<size_type> previous_category_index = m_current_category_index;
            m_current_category_index = m_list_box.selected_item_index();
            m_update(previous_category_index);
        }


    private:
        // variables

        boost::optional<size_type>& m_current_category_index;

        const list_box_type& m_list_box;

        update_type m_update;


    };


    /*!
        \brief The class template for a mouse click observer of the OK button.

        \tparam Dialog A dialog type.
    */
    template <typename Dialog>
    class ok_button_mouse_clicked
    {
    public:
        // types

        //! The dialog type.
        typedef Dialog dialog_type;


        // constructors and destructor

        /*!
            \brief Creates a mouse click observer of the OK button.

            \param dialog A dialog.
        */
        explicit ok_button_mouse_clicked(dialog_type& dialog)
        :
        m_dialog(dialog)
        {}


        // functions

        /*!
            \brief Called when the OK button is clicked.
        */
        void operator()()
        const
        {
            m_dialog.set_result(dialog_type::result_type::accepted);
            m_dialog.close();
        }


    private:
        // variables

        dialog_type& m_dialog;


    };


    /*!
        \brief The class template for a mouse click observer of the cancel button.

        \tparam Dialog A dialog type.
    */
    template <typename Dialog>
    class cancel_button_mouse_clicked
    {
    public:
        // types

        //! The dialog type.
        typedef Dialog dialog_type;


        // constructors and destructor

        /*!
            \brief Creates a mouse click observer of the cancel button.

            \param dialog A dialog.
        */
        explicit cancel_button_mouse_clicked(dialog_type& dialog)
        :
        m_dialog(dialog)
        {}


        // functions

        /*!
            \brief Called when the cancel button is clicked.
        */
        void operator()()
        const
        {
            m_dialog.set_result(dialog_type::result_type::canceled);
            m_dialog.close();
        }


    private:
        // variables

        dialog_type& m_dialog;


    };


}}}


#endif
