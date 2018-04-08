/*! \file
    \brief The definition of tetengo2::gui::common_dialog::file_open.

    Copyright (C) 2007-2018 kaoru

    $Id$
*/

#if !defined(TETENGO2_GUI_COMMONDIALOG_FILEOPEN_H)
#define TETENGO2_GUI_COMMONDIALOG_FILEOPEN_H

#include <utility>
#include <vector>

#include <boost/core/noncopyable.hpp>

#include <tetengo2/gui/widget/abstract_window.h>
#include <tetengo2/stdalt.h>


namespace tetengo2::gui::common_dialog {
    /*!
        \brief The class template for a file open dialog.

        \tparam String              A string type.
        \tparam WidgetTraits        A widget traits type.
        \tparam CommonDialogDetails A detail implementation type of common dialogs.
        \tparam WidgetDetailsTraits A detail implementation type traits of a widget.
        \tparam MenuDetails         A detail implementation type of a menu.
    */
    template <
        typename String,
        typename WidgetTraits,
        typename CommonDialogDetails,
        typename WidgetDetailsTraits,
        typename MenuDetails>
    class file_open : private boost::noncopyable
    {
    public:
        // types

        //! The string type.
        using string_type = String;

        //! The widget traits type.
        using widget_traits_type = WidgetTraits;

        //! The encoder type.
        using encoder_type = typename widget_traits_type::encoder_type;

        //! The common dialog details type.
        using common_dialog_details_type = CommonDialogDetails;

        //! The details type.
        using details_type = typename common_dialog_details_type::file_open_dialog_details_type;

        //! The detail implementaiton pointer type;
        using details_ptr_type = typename common_dialog_details_type::file_open_dialog_details_ptr_type;

        //! The widget details traits type.
        using widget_details_traits_type = WidgetDetailsTraits;

        //! The menu details type.
        using menu_details_type = MenuDetails;

        //! The abstract window type.
        using abstract_window_type =
            gui::widget::abstract_window<widget_traits_type, widget_details_traits_type, menu_details_type>;

        //! The file filter type.
        using file_filter_type = std::pair<string_type, string_type>;

        //! The file filters type.
        using file_filters_type = std::vector<file_filter_type>;


        // constructors and destructor

        /*!
            \brief Creates a file open dialog.

            \param title        A title.
            \param file_filters A file filters.
            \param parent       A parent widget.
        */
        file_open(string_type title, file_filters_type file_filters, abstract_window_type& parent)
        : m_p_details{ common_dialog_details_type::create_file_open_dialog(
              parent,
              std::move(title),
              std::move(file_filters),
              encoder()) },
          m_result{}
        {}


        // functions

        /*!
            \brief Returns the result.

            \return The result.
        */
        const tetengo2::stdalt::filesystem::path& result() const
        {
            return m_result;
        }

        /*!
            \brief Shows the dialog as model.

            \retval true  When the OK button is pressed.
            \retval false Otherwise.
        */
        bool do_modal()
        {
            const auto result = common_dialog_details_type::show_file_open_dialog(*m_p_details, encoder());
            if (!result)
                return false;

            m_result = *result;
            return true;
        }

        /*!
            \brief Returns the detail implementation.

            \return The detail implementation.
        */
        const details_type& details() const
        {
            return *m_p_details;
        }

        /*!
            \brief Returns the detail implementation.

            \return The detail implementation.
        */
        details_type& details()
        {
            return *m_p_details;
        }


    private:
        // static functions

        static const encoder_type& encoder()
        {
            static const encoder_type singleton{};
            return singleton;
        }


        // variables

        details_ptr_type m_p_details;

        tetengo2::stdalt::filesystem::path m_result;
    };
}


#endif
