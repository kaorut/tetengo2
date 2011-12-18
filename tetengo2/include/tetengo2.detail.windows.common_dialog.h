/*! \file
    \brief The definition of tetengo2::detail::windows::common_dialog.

    Copyright (C) 2007-2011 kaoru

    $Id$
*/

#if !defined(TETENGO2_DETAIL_WINDOWS_COMMONDIALOG_H)
#define TETENGO2_DETAIL_WINDOWS_COMMONDIALOG_H

//#include <memory>
#include <stdexcept>

#include <boost/throw_exception.hpp>

#define NOMINMAX
#define OEMRESOURCE
#include <Windows.h>
#include <ShObjIdl.h>
#include <atlbase.h>

#include "tetengo2.unique.h"


namespace tetengo2 { namespace detail { namespace windows
{
    /*!
        \brief The class for a detail implementation of dialogs.
    */
    class common_dialog
    {
    public:
        // types

        //! The file open dialog details type.
        typedef ::IFileOpenDialog file_open_dialog_details_type;

        //! The file open dialog details pointer type.
        typedef ATL::CComPtr<file_open_dialog_details_type>
            file_open_dialog_details_ptr_type;

        
        // static functions

        /*!
            \brief Creates a file open dialog.

            \tparam Widget A widget type.

            \param parent A parent widget.

            \return A unique pointer to a file open dialog.
        */
        template <typename Widget>
        static file_open_dialog_details_ptr_type create_file_open_dialog(
            Widget& parent
        )
        {
            file_open_dialog_details_ptr_type p_dialog;

            const ::HRESULT creation_result =
                p_dialog.CoCreateInstance(__uuidof(::FileOpenDialog));
            if (!SUCCEEDED(creation_result))
            {
                BOOST_THROW_EXCEPTION(
                    std::runtime_error("Can't create a file open dialog.")
                );
            }

            return p_dialog;
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
            const ::HRESULT showing_result = dialog.Show(NULL);
            if (!SUCCEEDED(showing_result))
            {
                BOOST_THROW_EXCEPTION(
                    std::runtime_error("Can't show the file open dialog.")
                );
            }

            return Path(L"hoge.txt");
        }


    };


}}}


#endif
