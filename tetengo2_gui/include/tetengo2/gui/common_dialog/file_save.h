/*! \file
    \brief The definition of tetengo2::gui::common_dialog::file_save.

    Copyright (C) 2007-2018 kaoru

    $Id$
*/

#if !defined(TETENGO2_GUI_COMMONDIALOG_FILESAVE_H)
#define TETENGO2_GUI_COMMONDIALOG_FILESAVE_H

#include <memory>
#include <utility>
#include <vector>

#include <boost/core/noncopyable.hpp>

#include <tetengo2/detail/base/common_dialog.h>
#include <tetengo2/gui/widget/abstract_window.h>
#include <tetengo2/stdalt.h>
#include <tetengo2/type_list.h>


namespace tetengo2::gui::common_dialog {
    /*!
        \brief The class for a file save dialog.
    */
    class file_save : private boost::noncopyable
    {
    public:
        // types

        //! The string type.
        using string_type = tetengo2::type_list::string_type;

        //! The abstract window type.
        using abstract_window_type = gui::widget::abstract_window;

        //! The file filter type.
        using file_filter_type = std::pair<string_type, string_type>;

        //! The file filters type.
        using file_filters_type = std::vector<file_filter_type>;

        //! The details type.
        using details_type = detail::base::common_dialog::file_save_dialog_details_type;


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
            abstract_window_type&                                                 parent);

        /*!
            \brief Destroys the file save dialog.
        */
        ~file_save();


        // functions

        /*!
            \brief Returns the result.

            \return The result.
        */
        const tetengo2::stdalt::filesystem::path& result() const;

        /*!
            \brief Shows the dialog as model.

            \retval true  When the OK button is pressed.
            \retval false Otherwise.
        */
        bool do_modal();

        /*!
            \brief Returns the detail implementation.

            \return The detail implementation.
        */
        const details_type& details() const;

        /*!
            \brief Returns the detail implementation.

            \return The detail implementation.
        */
        details_type& details();


    private:
        // types

        class impl;


        // variables

        const std::unique_ptr<impl> m_p_impl;
    };
}


#endif
