/*! \file
    \brief The definition of tetengo2::gui::common_dialog::file_save.

    Copyright (C) 2007-2018 kaoru

    $Id$
*/

#if !defined(TETENGO2_GUI_COMMONDIALOG_FILESAVE_H)
#define TETENGO2_GUI_COMMONDIALOG_FILESAVE_H

#include <utility>
#include <vector>

#include <boost/core/noncopyable.hpp>

#include <tetengo2/gui/widget/abstract_window.h>
#include <tetengo2/stdalt.h>
#include <tetengo2/type_list.h>


namespace tetengo2::gui::common_dialog {
    /*!
        \brief The class template for a file save dialog.

        \tparam CommonDialogDetails   A detail implementation type of common dialogs.
        \tparam WidgetDetails         A detail implementation type of a widget.
        \tparam DrawingDetails        A detail implementation type of drawing.
        \tparam ScrollDetails         A detail implementation type of a scroll.
        \tparam MessageHandlerDetails A detail implementation type of a message handler.
        \tparam MenuDetails           A detail implementation type of a menu.
    */
    template <
        typename CommonDialogDetails,
        typename WidgetDetails,
        typename DrawingDetails,
        typename ScrollDetails,
        typename MessageHandlerDetails>
    class file_save : private boost::noncopyable
    {
    public:
        // types

        //! The string type.
        using string_type = tetengo2::type_list::string_type;

        //! The common dialog details type.
        using common_dialog_details_type = CommonDialogDetails;

        //! The details type.
        using details_type = typename common_dialog_details_type::file_save_dialog_details_type;

        //! The detail implementaiton pointer type;
        using details_ptr_type = typename common_dialog_details_type::file_save_dialog_details_ptr_type;

        //! The abstract window type.
        using abstract_window_type = gui::widget::abstract_window;

        //! The file filter type.
        using file_filter_type = std::pair<string_type, string_type>;

        //! The file filters type.
        using file_filters_type = std::vector<file_filter_type>;


        // constructors and destructor

        /*!
            \brief Creates a file save dialog.

            \param title        A title.
            \param path         A path.
            \param file_filters A file filters.
            \param parent       A parent widget.
        */
        file_save(
            string_type                                                           title,
            const tetengo2::stdalt::optional<tetengo2::stdalt::filesystem::path>& path,
            file_filters_type                                                     file_filters,
            abstract_window_type&                                                 parent)
        : m_p_details{ common_dialog_details_type::create_file_save_dialog(
              parent,
              std::move(title),
              path,
              std::move(file_filters)) },
          m_result{ path ? *path : tetengo2::stdalt::filesystem::path{} }
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
            const auto result = common_dialog_details_type::show_file_save_dialog(*m_p_details);
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
        // variables

        details_ptr_type m_p_details;

        tetengo2::stdalt::filesystem::path m_result;
    };
}


#endif
