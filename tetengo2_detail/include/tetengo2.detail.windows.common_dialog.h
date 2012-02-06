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

#include <boost/optional.hpp>
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
            message_box_button_style_ok,     //!< With OK button.
            message_box_button_style_yes_no, //!< With Yes and No buttons.
        };

        //! The message box icon style type.
        enum message_box_icon_style_type
        {
            message_box_icon_style_error,       //!< Error.
            message_box_icon_style_warning,     //!< Warning.
            message_box_icon_style_information, //!< Information.
        };

        //! The message box button ID type.
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
                bool,
                message_box_button_style_type,
                message_box_icon_style_type,
                std::vector<boost::optional<std::wstring>>
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
            \tparam String1 A string type #1.
            \tparam String2 A string type #2.
            \tparam String3 A string type #3.
            \tparam String4 A string type #4.
            \tparam Encoder An encoder type.

            \param parent                      A parent widget.
            \param title                       A title.
            \param main_content                A main content.
            \param sub_content                 A sub content.
            \param cancellable                 Whether the message box is
                                               cancellable.
            \param button_style                A button style.
            \param icon_style                  An icon style.
            \param custom_ok_button_label      A custom OK button label.
            \param custom_yes_no_button_labels A custom Yes and No button
                                               labels.
            \param encoder                     An encoder.

            \return A unique pointer to a message box.
        */
        template <
            typename Widget,
            typename String1,
            typename String2,
            typename String3,
            typename String4,
            typename Encoder
        >
        static message_box_details_ptr_type create_message_box(
            Widget&                                             parent,
            String1&&                                           title,
            String2&&                                           main_content,
            String3&&                                           sub_content,
            const bool                                          cancellable,
            const message_box_button_style_type                 button_style,
            const message_box_icon_style_type                   icon_style,
            const boost::optional<String4>&                     custom_ok_button_label,
            const boost::optional<std::pair<String4, String4>>& custom_yes_no_button_labels,
            const Encoder&                                      encoder
        )
        {
            return make_unique<message_box_details_type>(
                std::get<0>(*parent.details()).get(),
                encoder.encode(std::forward<String1>(title)),
                encoder.encode(std::forward<String2>(main_content)),
                encoder.encode(std::forward<String3>(sub_content)),
                cancellable,
                button_style,
                icon_style,
                to_custom_button_labels(
                    custom_ok_button_label,
                    custom_yes_no_button_labels,
                    encoder
                )
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
            const ::HWND parent_window_handle = std::get<0>(message_box);
            const std::wstring& title = std::get<1>(message_box);
            const std::wstring& main_content = std::get<2>(message_box);
            const std::wstring& sub_content = std::get<3>(message_box);
            const bool cancellable = std::get<4>(message_box);
            const message_box_button_style_type button_style =
                std::get<5>(message_box);
            const message_box_icon_style_type icon_style =
                std::get<6>(message_box);
            const std::vector<boost::optional<std::wstring>>&
            custom_button_labels = std::get<7>(message_box);

            const std::vector< ::TASKDIALOG_BUTTON> custom_buttons =
                make_custom_buttons(custom_button_labels);

            ::TASKDIALOGCONFIG config = {};
            config.cbSize = sizeof(::TASKDIALOGCONFIG);
            config.hwndParent = parent_window_handle;
            config.dwCommonButtons =
                to_task_dialog_common_buttons(
                    button_style, cancellable, custom_button_labels
                );
            config.pszWindowTitle = title.c_str();
            config.pszMainIcon = to_task_dialog_icon(icon_style);
            config.pszMainInstruction = main_content.c_str();
            config.pszContent =
                sub_content.empty() ? NULL : sub_content.c_str();
            config.cButtons = static_cast< ::UINT>(custom_buttons.size());
            config.pButtons = custom_buttons.data();

            int selected_button = 0;
            const ::HRESULT result =
                ::TaskDialogIndirect(&config, &selected_button, NULL, NULL);
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
                std::get<0>(*parent.details()).get(),
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

        template <typename String, typename Encoder>
        static std::vector<boost::optional<std::wstring>>
        to_custom_button_labels(
            const boost::optional<String>&                    ok_button_label,
            const boost::optional<std::pair<String, String>>& yes_no_button_labels,
            const Encoder&                                    encoder
        )
        {
            std::vector<boost::optional<std::wstring>> labels;
            labels.reserve(3);

            if (ok_button_label)
            {
                labels.push_back(
                    boost::make_optional(encoder.encode(*ok_button_label))
                );
            }
            else
            {
                labels.push_back(boost::none);
            }

            if (yes_no_button_labels)
            {
                labels.push_back(
                    boost::make_optional(
                        encoder.encode(yes_no_button_labels->first)
                    )
                );
                labels.push_back(
                    boost::make_optional(
                        encoder.encode(yes_no_button_labels->second)
                    )
                );
            }
            else
            {
                labels.push_back(boost::none);
                labels.push_back(boost::none);
            }

            assert(labels.size() == 3);
            return labels;
        }

        static std::vector< ::TASKDIALOG_BUTTON> make_custom_buttons(
            const std::vector<boost::optional<std::wstring>>& button_labels
        )
        {
            assert(button_labels.size() == 3);

            std::vector< ::TASKDIALOG_BUTTON> buttons;

            if (button_labels[0])
            {
                ::TASKDIALOG_BUTTON button = {};
                button.nButtonID = IDOK;
                button.pszButtonText = button_labels[0]->c_str();
                buttons.push_back(button);
            }

            if (button_labels[1])
            {
                assert(button_labels[2]);
                {
                    ::TASKDIALOG_BUTTON button = {};
                    button.nButtonID = IDYES;
                    button.pszButtonText = button_labels[1]->c_str();
                    buttons.push_back(button);
                }
                {
                    ::TASKDIALOG_BUTTON button = {};
                    button.nButtonID = IDNO;
                    button.pszButtonText = button_labels[2]->c_str();
                    buttons.push_back(button);
                }
            }

            return buttons;
        }

        static ::TASKDIALOG_COMMON_BUTTON_FLAGS to_task_dialog_common_buttons(
            const message_box_button_style_type               style,
            const bool                                        cancellable,
            const std::vector<boost::optional<std::wstring>>& custom_button_labels
        )
        {
            assert(custom_button_labels.size() == 3);

            ::TASKDIALOG_COMMON_BUTTON_FLAGS flags = 0;
            switch (style)
            {
            case message_box_button_style_ok:
                if (!custom_button_labels[0])
                {
                    flags = TDCBF_OK_BUTTON;
                }
                break;
            case message_box_button_style_yes_no:
                if (!custom_button_labels[1])
                {
                    assert(!custom_button_labels[2]);
                    flags = TDCBF_YES_BUTTON | TDCBF_NO_BUTTON;
                }
                break;
            default:
                assert(false);
                BOOST_THROW_EXCEPTION(
                    std::invalid_argument("Invalid button style.")
                );
            }

            if (cancellable)
                flags |= TDCBF_CANCEL_BUTTON;

            return flags;
        }

        static ::PCWSTR to_task_dialog_icon(
            const message_box_icon_style_type style
        )
        {
            switch (style)
            {
            case message_box_icon_style_error:
                return TD_ERROR_ICON;
            case message_box_icon_style_warning:
                return TD_WARNING_ICON;
            case message_box_icon_style_information:
                return TD_INFORMATION_ICON;
            default:
                assert(false);
                BOOST_THROW_EXCEPTION(
                    std::invalid_argument("Invalid icon style.")
                );
            }
        }

        static message_box_button_id_type to_message_box_button_id(
            const int win32_button_id
        )
        {
            switch (win32_button_id)
            {
            case IDOK:     return message_box_button_ok;
            case IDCANCEL: return message_box_button_cancel;
            case IDYES:    return message_box_button_yes;
            case IDNO:     return message_box_button_no;
            default:
                assert(false);
                BOOST_THROW_EXCEPTION(
                    std::invalid_argument("Invalid button ID.")
                );
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
