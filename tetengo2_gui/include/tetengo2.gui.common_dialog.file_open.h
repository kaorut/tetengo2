/*! \file
    \brief The definition of tetengo2::gui::common_dialog::file_open.

    Copyright (C) 2007-2012 kaoru

    $Id$
*/

#if !defined(TETENGO2_GUI_COMMONDIALOG_FILEOPEN_H)
#define TETENGO2_GUI_COMMONDIALOG_FILEOPEN_H

#include <utility>
#include <vector>

#include <boost/noncopyable.hpp>

#include "tetengo2.text.h"


namespace tetengo2 { namespace gui { namespace common_dialog
{
    /*!
        \brief The class template for a file open dialog.

        \tparam AbstractWindow      An abstract window type.
        \tparam String              A string type.
        \tparam Path                A path type.
        \tparam Encoder             An encoder type.
        \tparam CommonDialogDetails A detail implementation type of common
                                    dialogs.
    */
    template <
        typename AbstractWindow,
        typename String,
        typename Path,
        typename Encoder,
        typename CommonDialogDetails
    >
    class file_open : private boost::noncopyable
    {
    public:
        // types

        //! The abstract window type.
        typedef AbstractWindow abstract_window_type;

        //! The string type.
        typedef String string_type;

        //! The path type.
        typedef Path path_type;

        //! The encoder type.
        typedef Encoder encoder_type;

        //! The detail implementation type of common dialogs.
        typedef CommonDialogDetails common_dialog_details_type;

        //! The detail implementation type.
        typedef
            typename common_dialog_details_type::file_open_dialog_details_type
            details_type;

        //! The detail implementaiton pointer type;

        typedef
            typename common_dialog_details_type::file_open_dialog_details_ptr_type
            details_ptr_type;

        //! The file filter type.
        typedef std::pair<string_type, string_type> file_filter_type;

        //! The file filters type.
        typedef std::vector<file_filter_type> file_filters_type;


        // constructors and destructor

        /*!
            \brief Creates a file open dialog.

            \tparam S  A string type.
            \tparam FF A file filters type.

            \param title        A title.
            \param file_filters A file filters.
            \param parent       A parent widget.
        */
        template <typename S, typename FF>
        file_open(S&& title, FF&& file_filters, abstract_window_type& parent)
        :
        m_p_details(
            common_dialog_details_type::create_file_open_dialog(
                parent,
                std::forward<S>(title),
                std::forward<FF>(file_filters),
                encoder()
            )
        ),
        m_result()
        {}


        // functions

        /*!
            \brief Returns the result.

            \return The result.
        */
        const path_type& result()
        const
        {
            return m_result;
        }

        /*!
            \brief Shows the dialog as model.
        */
        void do_modal()
        {
            m_result =
                common_dialog_details_type::template show_file_open_dialog<
                    path_type>(*m_p_details, encoder());
        }

        /*!
            \brief Returns the detail implementation.

            \return The detail implementation.
        */
        const details_type& details()
        const
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
            static const encoder_type singleton;
            return singleton;
        }


        // variables

        details_ptr_type m_p_details;

        path_type m_result;


    };


}}}


#endif
