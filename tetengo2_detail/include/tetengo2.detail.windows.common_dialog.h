/*! \file
    \brief The definition of tetengo2::detail::windows::common_dialog.

    Copyright (C) 2007-2012 kaoru

    $Id$
*/

#if !defined(TETENGO2_DETAIL_WINDOWS_COMMONDIALOG_H)
#define TETENGO2_DETAIL_WINDOWS_COMMONDIALOG_H

#include <algorithm>
#include <cassert>
#include <cstddef>
#include <iterator>
//#include <memory>
#include <stdexcept>
#include <string>
#include <tuple>
//#include <utility>
#include <vector>

#include <boost/scope_exit.hpp>
#include <boost/throw_exception.hpp>

#define NOMINMAX
#define OEMRESOURCE
#include <Windows.h>
#include <CommCtrl.h>
#include <ObjBase.h>
#include <ShObjIdl.h>
#include <ShTypes.h>
#include <Unknwn.h>

#include "tetengo2.cpp11.h"
#include "tetengo2.unique.h"


namespace tetengo2 { namespace detail { namespace windows
{
#if !defined(DOCUMENTATION)
    namespace detail
    {
        // types

        struct release_iunknown
        {
            void operator()(::IUnknown* p_unknown)
            const
            {
                if (p_unknown)
                {
                    p_unknown->Release();
                    p_unknown = NULL;
                }
            }

        };

        typedef
            std::unique_ptr< ::IFileOpenDialog, release_iunknown>
            file_open_dialog_ptr_type;

        typedef std::pair<std::wstring, std::wstring> native_filter_type;

        typedef std::vector<native_filter_type> native_filters_type;


    }
#endif

    /*!
        \brief The class for a detail implementation of dialogs.
    */
    class common_dialog
    {
    public:
        // types

        //! The message box button style type.
        enum message_box_button_style_type
        {
            message_box_button_style_ok,            //!< With OK button.
            message_box_button_style_ok_cancel,     //!< With OK and Cancel
                                                    //!< button.
            message_box_button_style_yes_no_cancel, //!< With Yes, No and Cancel
                                                    //!< button.
        };

        //! The message box icon style type.
        enum message_box_icon_style_type
        {
            message_box_icon_style_error,       //!< Error.
            message_box_icon_style_warning,     //!< Warning.
            message_box_icon_style_information, //!< Information.
        };

        //! The message box button id type.
        enum message_box_button_id_type
        {
            message_box_button_ok,     //!< OK button.
            message_box_button_yes,    //!< Yes button.
            message_box_button_no,     //!< No button.
            message_box_button_cancel, //!< Cancel button.
        };

        //! The message box details type.
        typedef
            std::tuple<
                ::HWND,
                std::wstring,
                std::wstring,
                std::wstring,
                message_box_button_style_type,
                message_box_icon_style_type
            >
            message_box_details_type;

        //! The message box details pointer type.
        typedef
            std::unique_ptr<message_box_details_type>
            message_box_details_ptr_type;

        //! The file open dialog details type.
        typedef
            std::tuple<
                detail::file_open_dialog_ptr_type,
                ::HWND,
                std::wstring,
                detail::native_filters_type
            >
            file_open_dialog_details_type;

        //! The file open dialog details pointer type.
        typedef std::unique_ptr<file_open_dialog_details_type>
            file_open_dialog_details_ptr_type;

        
        // static functions

        /*!
            \brief Creates a message box.

            \tparam Widget  A widget type.
            \tparam String  A string type.
            \tparam Encoder An encoder type.

            \param parent       A parent widget.
            \param title        A title.
            \param instruction  An instruction.
            \param details      Details.
            \param button_style A button style.
            \param icon_style   An icon style.
            \param encoder      An encoder.

            \return A unique pointer to a message box.
        */
        template <typename Widget, typename String, typename Encoder>
        static message_box_details_ptr_type create_message_box(
            Widget&                             parent,
            String&&                            title,
            String&&                            instruction,
            String&&                            details,
            const message_box_button_style_type button_style,
            const message_box_icon_style_type   icon_style,
            const Encoder&                      encoder
        )
        {
            return make_unique<message_box_details_type>(
                parent.details()->first.get(),
                encoder.encode(std::forward<String>(title)),
                encoder.encode(std::forward<String>(instruction)),
                encoder.encode(std::forward<String>(details)),
                button_style,
                icon_style
            );
        }

        /*!
            \brief Shows a message box and return a button id.

            \param message_box A message box.

            \return The path.
        */
        static message_box_button_id_type show_message_box(
            message_box_details_type& message_box
        )
        {
            int selected_button = 0;
            const ::HRESULT result =
                ::TaskDialog(
                    std::get<0>(message_box),
                    NULL,
                    std::get<1>(message_box).c_str(),
                    std::get<2>(message_box).c_str(),
                    std::get<3>(message_box).c_str(),
                    to_task_dialog_common_buttons(std::get<4>(message_box)),
                    to_task_dialog_icon(std::get<5>(message_box)),
                    &selected_button
                );
            if (result != S_OK)
            {
                BOOST_THROW_EXCEPTION(
                    std::runtime_error("Can't show a message box.")
                );
            }

            return to_message_box_button_id(selected_button);
        }

        /*!
            \brief Creates a file open dialog.

            \tparam Widget  A widget type.
            \tparam String  A string type.
            \tparam Filters A filters type.
            \tparam Encoder An encoder type.

            \param parent  A parent widget.
            \param title   A title.
            \param filters A file filters.
                           Each element is a pair of a label and a file
                           pattern.
            \param encoder An encoder.

            \return A unique pointer to a file open dialog.
        */
        template <
            typename Widget,
            typename String,
            typename Filters,
            typename Encoder
        >
        static file_open_dialog_details_ptr_type create_file_open_dialog(
            Widget&        parent,
            String&&       title,
            Filters&&      filters,
            const Encoder& encoder
        )
        {
            ::IFileOpenDialog* p_raw_dialog = NULL;
            const ::HRESULT creation_result =
                ::CoCreateInstance(
                    __uuidof(::FileOpenDialog),
                    NULL,
                    CLSCTX_ALL,
                    IID_PPV_ARGS(&p_raw_dialog)
                );
            if (!SUCCEEDED(creation_result))
            {
                BOOST_THROW_EXCEPTION(
                    std::runtime_error("Can't create a file open dialog.")
                );
            }
            detail::file_open_dialog_ptr_type p_dialog(p_raw_dialog);
            return make_unique<file_open_dialog_details_type>(
                std::move(p_dialog),
                parent.details()->first.get(),
                encoder.encode(std::forward<String>(title)),
                to_native_filters(filters, encoder)
            );
        }

        /*!
            \brief Shows a file open dialog and return a path.

            \tparam Path    A path type.
            \tparam Encoder An encoder type.

            \param dialog  A file open dialog.
            \param encoder An encoder.

            \return The path.
        */
        template <typename Path, typename Encoder>
        static Path show_file_open_dialog(
            file_open_dialog_details_type& dialog,
            const Encoder&                 encoder
        )
        {
            std::get<0>(dialog)->SetTitle(std::get<2>(dialog).c_str());

            std::vector< ::COMDLG_FILTERSPEC> filterspecs =
                to_filterspecs(std::get<3>(dialog));
            std::get<0>(dialog)->SetFileTypes(
                static_cast< ::UINT>(filterspecs.size()), filterspecs.data()
            );

            const ::HRESULT showing_result =
                std::get<0>(dialog)->Show(std::get<1>(dialog));
            if (!SUCCEEDED(showing_result))
                return Path();

            ::IShellItem* p_raw_item = NULL;
            const ::HRESULT result_result =
                std::get<0>(dialog)->GetResult(&p_raw_item);
            if (!SUCCEEDED(result_result))
            {
                BOOST_THROW_EXCEPTION(
                    std::runtime_error("Can't get the result.")
                );
            }
            const std::unique_ptr< ::IShellItem, detail::release_iunknown>
            p_item(p_raw_item);

            wchar_t* file_name = NULL;
            const ::HRESULT file_title_result =
                p_item->GetDisplayName(SIGDN_FILESYSPATH, &file_name);
            if (!SUCCEEDED(file_title_result))
            {
                BOOST_THROW_EXCEPTION(
                    std::runtime_error("Can't get the file path.")
                );
            }
            BOOST_SCOPE_EXIT((file_name))
            {
                ::CoTaskMemFree(file_name);
            } BOOST_SCOPE_EXIT_END;

            return Path(encoder.decode(file_name));
        }


    private:
        // static functions

        static ::TASKDIALOG_COMMON_BUTTON_FLAGS to_task_dialog_common_buttons(
            const message_box_button_style_type style
        )
        {
            switch (style)
            {
            case message_box_button_style_ok_cancel:
                return TDCBF_OK_BUTTON | TDCBF_CANCEL_BUTTON;
            case message_box_button_style_yes_no_cancel:
                return
                    TDCBF_YES_BUTTON | TDCBF_NO_BUTTON | TDCBF_CANCEL_BUTTON;
            default:
                assert(style == message_box_button_style_ok);
                return TDCBF_OK_BUTTON;
            }
        }

        static ::PCWSTR to_task_dialog_icon(
            const message_box_icon_style_type style
        )
        {
            switch (style)
            {
            case message_box_icon_style_error:   return TD_ERROR_ICON;
            case message_box_icon_style_warning: return TD_WARNING_ICON;
            default:
                assert(style == message_box_icon_style_information);
                return TD_INFORMATION_ICON;
            }
        }

        static message_box_button_id_type to_message_box_button_id(
            const int win32_button_id
        )
        {
            switch (win32_button_id)
            {
            case IDOK:  return message_box_button_ok;
            case IDYES: return message_box_button_yes;
            case IDNO:  return message_box_button_no;
            default:
                assert(win32_button_id == IDCANCEL);
                return message_box_button_cancel;
            }
        }

        template <typename String, typename Encoder>
        static detail::native_filter_type to_native_filter(
            const std::pair<String, String>& filter,
            const Encoder&                   encoder
        )
        {
            return detail::native_filter_type(
                encoder.encode(filter.first), encoder.encode(filter.second)
            );
        }

        template <typename String, typename Encoder>
        static detail::native_filters_type to_native_filters(
            const std::vector<std::pair<String, String>>& filters,
            const Encoder&                                encoder
        )
        {
            detail::native_filters_type native_filters;
            native_filters.reserve(filters.size());

            std::transform(
                filters.begin(),
                filters.end(),
                std::back_inserter(native_filters),
                TETENGO2_CPP11_BIND(
                    to_native_filter<String, Encoder>,
                    cpp11::placeholders_1(),
                    cpp11::cref(encoder)
                )
            );

            return native_filters;
        }

        static ::COMDLG_FILTERSPEC to_filterspec(
            const detail::native_filter_type& native_filter
        )
        {
            ::COMDLG_FILTERSPEC filterspec = {};

            filterspec.pszName = native_filter.first.c_str();
            filterspec.pszSpec = native_filter.second.c_str();

            return filterspec;
        }

        static std::vector< ::COMDLG_FILTERSPEC> to_filterspecs(
            const detail::native_filters_type& native_filters
        )
        {
            std::vector< ::COMDLG_FILTERSPEC> filterspecs;
            filterspecs.reserve(native_filters.size());

            std::transform(
                native_filters.begin(),
                native_filters.end(),
                std::back_inserter(filterspecs),
                to_filterspec
            );

            return filterspecs;
        }


    };


}}}


#endif
