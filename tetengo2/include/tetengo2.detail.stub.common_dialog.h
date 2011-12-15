/*! \file
    \brief The definition of tetengo2::detail::stub::common_dialog.

    Copyright (C) 2007-2011 kaoru

    $Id$
*/

#if !defined(TETENGO2_DETAIL_STUB_COMMONDIALOG_H)
#define TETENGO2_DETAIL_STUB_COMMONDIALOG_H


namespace tetengo2 { namespace detail { namespace stub
{
    /*!
        \brief The class for a detail implementation of dialogs.
    */
    class common_dialog
    {
    public:
        // types

        //! The file open dialog details type.
        struct file_open_dialog_details_type {};

        //! The file open dialog details pointer type.
        typedef
            std::unique_ptr<file_open_dialog_details_type>
            file_open_dialog_details_ptr_type;

        
        // static functions

        /*!
            \brief Creates a file open dialog.

            \tparam Widget A widget type.
        */
        template <typename Widget>
        static file_open_dialog_details_ptr_type create_file_open_dialog(
            Widget& parent
        )
        {
            return make_unique<file_open_dialog_details_type>();
        }

        /*!
            \brief Shows a file open dialog and return a path.

            \tparam Path A path type.

            \param dialog A pointer to a file open dialog.

            \return The path.
        */
        template <typename Path>
        static Path show_file_open_dialog(
            file_open_dialog_details_type& dialog
        )
        {
            return Path();
        }


    };


}}}


#endif
