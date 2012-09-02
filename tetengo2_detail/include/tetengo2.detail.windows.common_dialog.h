/*! \file
    \brief The definition of tetengo2::detail::windows::common_dialog.

    Copyright (C) 2007-2012 kaoru

    $Id$
*/

#if !defined(TETENGO2_DETAIL_WINDOWS_COMMONDIALOG_H)
#define TETENGO2_DETAIL_WINDOWS_COMMONDIALOG_H

#include <algorithm>
//#include <cassert>
//#include <cstddef>
//#include <iterator>
//#include <memory>
//#include <stdexcept>
//#include <string>
//#include <system_error>
#include <tuple>
//#include <utility>
//#include <vector>

//#include <boost/noncopyable.hpp>
#include <boost/optional.hpp>
#include <boost/scope_exit.hpp>
//#include <boost/throw_exception.hpp>
#include <boost/utility.hpp>

#pragma warning (push)
#pragma warning (disable: 4005)
#include <intsafe.h>
#include <stdint.h>
#pragma warning(pop)
//#define NOMINMAX
//#define OEMRESOURCE
//#include <Windows.h>
#include <CommCtrl.h>
#include <ObjBase.h>
#include <ShObjIdl.h>
#include <ShTypes.h>

#include "tetengo2.cpp11.h"
#include "tetengo2.detail.windows.com_ptr.h"
#include "tetengo2.detail.windows.error_category.h"
#include "tetengo2.unique.h"
#include "tetengo2.text.h"


namespace tetengo2 { namespace detail { namespace windows
{
#if !defined(DOCUMENTATION)
    namespace detail
    {
        // types

        typedef unique_com_ptr< ::IFileOpenDialog>::type file_open_dialog_ptr_type;

        typedef unique_com_ptr< ::IFileSaveDialog>::type file_save_dialog_ptr_type;

        typedef std::pair<std::wstring, std::wstring> native_filter_type;

        typedef std::vector<native_filter_type> native_filters_type;


    }
#endif

    /*!
        \brief The class for a detail implementation of dialogs.
    */
    class common_dialog : private boost::noncopyable
    {
    public:
        // types

        //! The message box button style type.
        struct message_box_button_style_type { enum enum_t //!< Scoped enum.
        {
            ok,     //!< With OK button.
            yes_no, //!< With Yes and No buttons.
        };};

        //! The message box icon style type.
        struct message_box_icon_style_type { enum enum_t //!< Scoped enum.
        {
            error,       //!< Error.
            warning,     //!< Warning.
            information, //!< Information.
        };};

        //! The message box button ID type.
        struct message_box_button_id_type { enum enum_t //!< Scoped enum.
        {
            ok,     //!< OK button.
            yes,    //!< Yes button.
            no,     //!< No button.
            cancel, //!< Cancel button.
        };};

        //! The message box details type.
        typedef
            std::tuple<
                ::HWND,
                std::wstring,
                std::wstring,
                std::wstring,
                bool,
                message_box_button_style_type::enum_t,
                message_box_icon_style_type::enum_t,
                std::vector<boost::optional<std::wstring>>
            >
            message_box_details_type;

        //! The message box details pointer type.
        typedef std::unique_ptr<message_box_details_type> message_box_details_ptr_type;

        //! The file open dialog details type.
        typedef
            std::tuple<
                detail::file_open_dialog_ptr_type, ::HWND, std::wstring, std::wstring, detail::native_filters_type
            >
            file_open_dialog_details_type;

        //! The file open dialog details pointer type.
        typedef std::unique_ptr<file_open_dialog_details_type> file_open_dialog_details_ptr_type;

        //! The file save dialog details type.
        typedef
            std::tuple<
                detail::file_save_dialog_ptr_type,
                ::HWND,
                std::wstring,
                std::wstring,
                std::wstring,
                detail::native_filters_type,
                std::size_t
            >
            file_save_dialog_details_type;

        //! The file save dialog details pointer type.
        typedef std::unique_ptr<file_save_dialog_details_type> file_save_dialog_details_ptr_type;

        //! The font dialog details type.
        typedef std::tuple< ::HWND, std::wstring, std::unique_ptr< ::LOGFONTW>> font_dialog_details_type;

        //! The font dialog details pointer type.
        typedef std::unique_ptr<font_dialog_details_type> font_dialog_details_ptr_type;

        //! The color dialog details type.
        struct color_dialog_details_type {};

        //! The color dialog details pointer type.
        typedef std::unique_ptr<color_dialog_details_type> color_dialog_details_ptr_type;

        
        // static functions

        /*!
            \brief Creates a message box.

            \tparam AbstractWindow An abstract window type.
            \tparam String1        A string type #1.
            \tparam String2        A string type #2.
            \tparam String3        A string type #3.
            \tparam String4        A string type #4.
            \tparam Encoder        An encoder type.

            \param parent                      A parent window.
            \param title                       A title.
            \param main_content                A main content.
            \param sub_content                 A sub content.
            \param cancellable                 Whether the message box is cancellable.
            \param button_style                A button style.
            \param icon_style                  An icon style.
            \param custom_ok_button_label      A custom OK button label.
            \param custom_yes_no_button_labels A custom Yes and No button labels.
            \param encoder                     An encoder.

            \return A unique pointer to a message box.
        */
        template <
            typename AbstractWindow,
            typename String1,
            typename String2,
            typename String3,
            typename String4,
            typename Encoder
        >
        static message_box_details_ptr_type create_message_box(
            AbstractWindow&                                      parent,
            String1&&                                            title,
            String2&&                                            main_content,
            String3&&                                            sub_content,
            const bool                                           cancellable,
            const typename message_box_button_style_type::enum_t button_style,
            const typename message_box_icon_style_type::enum_t   icon_style,
            const boost::optional<String4>&                      custom_ok_button_label,
            const boost::optional<std::pair<String4, String4>>&  custom_yes_no_button_labels,
            const Encoder&                                       encoder
        )
        {
            return
                make_unique<message_box_details_type>(
                    std::get<0>(*parent.details()).get(),
                    encoder.encode(std::forward<String1>(title)),
                    encoder.encode(std::forward<String2>(main_content)),
                    encoder.encode(std::forward<String3>(sub_content)),
                    cancellable,
                    button_style,
                    icon_style,
                    to_custom_button_labels(custom_ok_button_label, custom_yes_no_button_labels, encoder)
                );
        }

        /*!
            \brief Shows a message box and return a button id.

            \param message_box A message box.

            \return The path.

            \throw std::system_error When the message box cannot be shown.
        */
        static message_box_button_id_type::enum_t show_message_box(message_box_details_type& message_box)
        {
            const ::HWND parent_window_handle = std::get<0>(message_box);
            const std::wstring& title = std::get<1>(message_box);
            const std::wstring& main_content = std::get<2>(message_box);
            const std::wstring& sub_content = std::get<3>(message_box);
            const bool cancellable = std::get<4>(message_box);
            const message_box_button_style_type::enum_t button_style = std::get<5>(message_box);
            const message_box_icon_style_type::enum_t icon_style = std::get<6>(message_box);
            const std::vector<boost::optional<std::wstring>>&
            custom_button_labels = std::get<7>(message_box);

            const std::vector< ::TASKDIALOG_BUTTON> custom_buttons = make_custom_buttons(custom_button_labels);

            ::TASKDIALOGCONFIG config = {};
            config.cbSize = sizeof(::TASKDIALOGCONFIG);
            config.hwndParent = parent_window_handle;
            config.dwCommonButtons = to_task_dialog_common_buttons(button_style, cancellable, custom_button_labels);
            config.pszWindowTitle = title.c_str();
            config.pszMainIcon = to_task_dialog_icon(icon_style);
            config.pszMainInstruction = main_content.c_str();
            config.pszContent = sub_content.empty() ? NULL : sub_content.c_str();
            config.cButtons = static_cast< ::UINT>(custom_buttons.size());
            config.pButtons = custom_buttons.data();

            int selected_button = 0;
            const ::HRESULT result = ::TaskDialogIndirect(&config, &selected_button, NULL, NULL);
            if (result != S_OK)
            {
                BOOST_THROW_EXCEPTION(
                    std::system_error(std::error_code(result, win32_category()), "Can't show a message box.")
                );
            }

            return to_message_box_button_id(selected_button);
        }

        /*!
            \brief Creates a file open dialog.

            \tparam AbstractWindow An abstract window type.
            \tparam String         A string type.
            \tparam Filters        A filters type.
            \tparam Encoder        An encoder type.

            \param parent  A parent window.
            \param title   A title.
            \param filters A file filters. Each element is a pair of a label and a file pattern.
            \param encoder An encoder.

            \return A unique pointer to a file open dialog.

            \throw std::system_error When the file open dialog cannot be created.
        */
        template <typename AbstractWindow, typename String, typename Filters, typename Encoder>
        static file_open_dialog_details_ptr_type create_file_open_dialog(
            AbstractWindow& parent,
            String&&        title,
            Filters&&       filters,
            const Encoder&  encoder
        )
        {
            ::IFileOpenDialog* p_raw_dialog = NULL;
            const ::HRESULT creation_result =
                ::CoCreateInstance(__uuidof(::FileOpenDialog), NULL, CLSCTX_ALL, IID_PPV_ARGS(&p_raw_dialog));
            if (FAILED(creation_result))
            {
                BOOST_THROW_EXCEPTION(
                    std::system_error(
                        std::error_code(creation_result, win32_category()), "Can't create a file open dialog."
                    )
                );
            }
            detail::file_open_dialog_ptr_type p_dialog(p_raw_dialog);
            return
                make_unique<file_open_dialog_details_type>(
                    std::move(p_dialog),
                    std::get<0>(*parent.details()).get(),
                    encoder.encode(std::forward<String>(title)),
                    encoder.encode(to_default_extension(filters)),
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

            \throw std::system_error When the file open dialog cannot be shown.
        */
        template <typename Path, typename Encoder>
        static boost::optional<Path> show_file_open_dialog(
            file_open_dialog_details_type& dialog,
            const Encoder&                 encoder
        )
        {
            const ::HRESULT title_set_result = std::get<0>(dialog)->SetTitle(std::get<2>(dialog).c_str());
            if (FAILED(title_set_result))
            {
                BOOST_THROW_EXCEPTION(
                    std::system_error(std::error_code(title_set_result, win32_category()), "Can't set title.")
                );
            }

            if (!std::get<4>(dialog).empty())
            {
                const ::HRESULT default_extension_set_result =
                    std::get<0>(dialog)->SetDefaultExtension(std::get<3>(dialog).c_str());
                if (FAILED(default_extension_set_result))
                {
                    BOOST_THROW_EXCEPTION(
                        std::system_error(
                            std::error_code(default_extension_set_result, win32_category()),
                            "Can't set default extension."
                        )
                    );
                }
            }

            std::vector< ::COMDLG_FILTERSPEC> filterspecs = to_filterspecs(std::get<4>(dialog));
            const ::HRESULT filter_set_result =
                std::get<0>(dialog)->SetFileTypes(static_cast< ::UINT>(filterspecs.size()), filterspecs.data());
            if (FAILED(filter_set_result))
            {
                BOOST_THROW_EXCEPTION(
                    std::system_error(
                        std::error_code(filter_set_result, win32_category()), "Can't set file type filter."
                    )
                );
            }

            const ::HRESULT showing_result = std::get<0>(dialog)->Show(std::get<1>(dialog));
            if (FAILED(showing_result))
                return boost::none;

            ::IShellItem* p_raw_item = NULL;
            const ::HRESULT result_result = std::get<0>(dialog)->GetResult(&p_raw_item);
            if (FAILED(result_result))
            {
                BOOST_THROW_EXCEPTION(
                    std::system_error(std::error_code(result_result, win32_category()), "Can't get the result.")
                );
            }
            const typename unique_com_ptr< ::IShellItem>::type p_item(p_raw_item);

            wchar_t* file_name = NULL;
            const ::HRESULT file_title_result = p_item->GetDisplayName(SIGDN_FILESYSPATH, &file_name);
            if (FAILED(file_title_result))
            {
                BOOST_THROW_EXCEPTION(
                    std::system_error(std::error_code(file_title_result, win32_category()), "Can't get the file path.")
                );
            }
            BOOST_SCOPE_EXIT((file_name))
            {
                ::CoTaskMemFree(file_name);
            } BOOST_SCOPE_EXIT_END;

            return boost::make_optional(Path(encoder.decode(file_name)));
        }

        /*!
            \brief Creates a file save dialog.

            \tparam AbstractWindow An abstract window type.
            \tparam String         A string type.
            \tparam OptionalPath   An optional path type.
            \tparam Filters        A filters type.
            \tparam Encoder        An encoder type.

            \param parent  A parent window.
            \param title   A title.
            \param path    A path.
            \param filters A file filters. Each element is a pair of a label and a file pattern.
            \param encoder An encoder.

            \return A unique pointer to a file save dialog.

            \throw std::system_error When the file save dialog cannot be created.
        */
        template <typename AbstractWindow, typename String, typename OptionalPath, typename Filters, typename Encoder>
        static file_save_dialog_details_ptr_type create_file_save_dialog(
            AbstractWindow& parent,
            String&&        title,
            OptionalPath&&  path,
            Filters&&       filters,
            const Encoder&  encoder
        )
        {
            ::IFileSaveDialog* p_raw_dialog = NULL;
            const ::HRESULT creation_result =
                ::CoCreateInstance(__uuidof(::FileSaveDialog), NULL, CLSCTX_ALL, IID_PPV_ARGS(&p_raw_dialog));
            if (FAILED(creation_result))
            {
                BOOST_THROW_EXCEPTION(
                    std::system_error(
                        std::error_code(creation_result, win32_category()), "Can't create a file save dialog."
                    )
                );
            }
            detail::file_save_dialog_ptr_type p_dialog(p_raw_dialog);
            return
                make_unique<file_save_dialog_details_type>(
                    std::move(p_dialog),
                    std::get<0>(*parent.details()).get(),
                    encoder.encode(std::forward<String>(title)),
                    encoder.encode(to_native_path<String>(path)),
                    encoder.encode(to_default_extension(filters)),
                    to_native_filters(filters, encoder),
                    find_filter_index(filters, path)
                );
        }

        /*!
            \brief Shows a file save dialog and return a path.

            \tparam Path    A path type.
            \tparam Encoder An encoder type.

            \param dialog  A file save dialog.
            \param encoder An encoder.

            \return The path.

            \throw std::system_error When the file save dialog cannot be shown.
        */
        template <typename Path, typename Encoder>
        static boost::optional<Path> show_file_save_dialog(
            file_save_dialog_details_type& dialog,
            const Encoder&                 encoder
        )
        {
            const ::HRESULT title_set_result = std::get<0>(dialog)->SetTitle(std::get<2>(dialog).c_str());
            if (FAILED(title_set_result))
            {
                BOOST_THROW_EXCEPTION(
                    std::system_error(std::error_code(title_set_result, win32_category()), "Can't set title.")
                );
            }

            ::IShellItem* p_raw_default_path = NULL;
            if (!std::get<3>(dialog).empty())
            {
                const ::HRESULT default_path_result =
                    ::SHCreateItemFromParsingName(
                        std::get<3>(dialog).c_str(), NULL, IID_PPV_ARGS(&p_raw_default_path)
                    );
                if (FAILED(default_path_result))
                {
                    BOOST_THROW_EXCEPTION(
                        std::system_error(
                            std::error_code(default_path_result, win32_category()), "Can't create default path item."
                        )
                    );
                }
            }
            BOOST_SCOPE_EXIT((p_raw_default_path))
            {
                if (p_raw_default_path)
                    p_raw_default_path->Release();
            } BOOST_SCOPE_EXIT_END;
            if (!std::get<3>(dialog).empty())
            {
                const ::HRESULT default_path_set_result = std::get<0>(dialog)->SetSaveAsItem(p_raw_default_path);
                if (FAILED(default_path_set_result))
                {
                    BOOST_THROW_EXCEPTION(
                        std::system_error(
                            std::error_code(default_path_set_result, win32_category()), "Can't set default path."
                        )
                    );
                }
            }

            if (!std::get<4>(dialog).empty())
            {
                const ::HRESULT default_extension_set_result =
                    std::get<0>(dialog)->SetDefaultExtension(std::get<4>(dialog).c_str());
                if (FAILED(default_extension_set_result))
                {
                    BOOST_THROW_EXCEPTION(
                        std::system_error(
                            std::error_code(default_extension_set_result, win32_category()),
                            "Can't set default extension."
                        )
                    );
                }
            }

            const std::vector< ::COMDLG_FILTERSPEC> filterspecs = to_filterspecs(std::get<5>(dialog));
            const ::HRESULT filter_set_result =
                std::get<0>(dialog)->SetFileTypes(static_cast< ::UINT>(filterspecs.size()), filterspecs.data());
            if (FAILED(filter_set_result))
            {
                BOOST_THROW_EXCEPTION(
                    std::system_error(
                        std::error_code(filter_set_result, win32_category()), "Can't set file type filters."
                    )
                );
            }

            if (std::get<6>(dialog) > 0)
            {
                const ::HRESULT filter_index_set_result =
                    std::get<0>(dialog)->SetFileTypeIndex(static_cast< ::UINT>(std::get<6>(dialog)));
                if (FAILED(filter_index_set_result))
                {
                    BOOST_THROW_EXCEPTION(
                        std::system_error(
                            std::error_code(filter_set_result, win32_category()), "Can't set file type filter index."
                        )
                    );
                }
            }

            const ::HRESULT showing_result = std::get<0>(dialog)->Show(std::get<1>(dialog));
            if (FAILED(showing_result))
                return boost::none;

            ::IShellItem* p_raw_item = NULL;
            const ::HRESULT result_result = std::get<0>(dialog)->GetResult(&p_raw_item);
            if (FAILED(result_result))
            {
                BOOST_THROW_EXCEPTION(
                    std::system_error(std::error_code(result_result, win32_category()), "Can't get the result.")
                );
            }
            const typename unique_com_ptr< ::IShellItem>::type p_item(p_raw_item);

            wchar_t* file_name = NULL;
            const ::HRESULT file_title_result = p_item->GetDisplayName(SIGDN_FILESYSPATH, &file_name);
            if (FAILED(file_title_result))
            {
                BOOST_THROW_EXCEPTION(
                    std::system_error(std::error_code(file_title_result, win32_category()), "Can't get the file path.")
                );
            }
            BOOST_SCOPE_EXIT((file_name))
            {
                ::CoTaskMemFree(file_name);
            } BOOST_SCOPE_EXIT_END;

            return boost::make_optional(Path(encoder.decode(file_name)));
        }

        /*!
            \brief Creates a font dialog.

            \tparam AbstractWindow An abstract window type.
            \tparam String         A string type.
            \tparam OptionalFont   An optional font type.
            \tparam Encoder        An encoder type.

            \param parent  A parent window.
            \param title   A title.
            \param font    A font.
            \param encoder An encoder.

            \return A unique pointer to a font dialog.

            \throw std::system_error When the font dialog cannot be created.
        */
        template <typename AbstractWindow, typename String, typename OptionalFont, typename Encoder>
        static font_dialog_details_ptr_type create_font_dialog(
            AbstractWindow& parent,
            String&&        title,
            OptionalFont&&  font,
            const Encoder&  encoder
        )
        {
            std::unique_ptr< ::LOGFONTW> p_log_font;
            if (font)
            {
                p_log_font = make_unique< ::LOGFONT>();
                p_log_font->lfHeight = -static_cast< ::LONG>(font->size());
                p_log_font->lfWeight = font->bold() ? FW_BOLD : FW_NORMAL;
                p_log_font->lfItalic = font->italic() ? TRUE : FALSE;
                p_log_font->lfUnderline = font->underline() ? TRUE : FALSE;
                p_log_font->lfStrikeOut = font->strikeout() ? TRUE : FALSE;
                p_log_font->lfCharSet = DEFAULT_CHARSET;
                p_log_font->lfOutPrecision = OUT_DEFAULT_PRECIS;
                p_log_font->lfClipPrecision = CLIP_DEFAULT_PRECIS;
                p_log_font->lfQuality = DEFAULT_QUALITY;
                p_log_font->lfPitchAndFamily = DEFAULT_PITCH;
                
                const std::wstring native_face_name = encoder.encode(font->family());
                const std::size_t native_face_name_length =
                    std::min<std::size_t>(native_face_name.length(), LF_FACESIZE - 1);
                std::copy(
                    native_face_name.begin(),
                    boost::next(native_face_name.begin(), native_face_name_length),
                    p_log_font->lfFaceName
                );
                p_log_font->lfFaceName[native_face_name_length] = 0;
            }

            return
                make_unique<font_dialog_details_type>(
                    std::get<0>(*parent.details()).get(), encoder.encode(title), std::move(p_log_font)
                );
        }

        /*!
            \brief Shows a font dialog and return a font.

            \tparam Font    A font type.
            \tparam Encoder An encoder type.

            \param dialog  A font dialog.
            \param encoder An encoder.

            \return The font.

            \throw std::system_error When the font dialog cannot be shown.
        */
        template <typename Font, typename Encoder>
        static boost::optional<Font> show_font_dialog(font_dialog_details_type& dialog, const Encoder& encoder)
        {
            return
                boost::make_optional(
                    Font(typename Font::string_type(TETENGO2_TEXT("font_dialog_font")), 42, false, true, false, true)
                );
        }

        /*!
            \brief Creates a color dialog.

            \tparam AbstractWindow An abstract window type.
            \tparam String         A string type.
            \tparam Encoder        An encoder type.

            \param parent  A parent window.
            \param title   A title.
            \param encoder An encoder.

            \return A unique pointer to a color dialog.

            \throw std::system_error When the color dialog cannot be created.
        */
        template <typename AbstractWindow, typename String, typename Encoder>
        static color_dialog_details_ptr_type create_color_dialog(
            AbstractWindow& parent,
            String&&        title,
            const Encoder&  encoder
        )
        {
            return make_unique<color_dialog_details_type>();
        }

        /*!
            \brief Shows a color dialog and return a font.

            \tparam Color   A color type.
            \tparam Encoder An encoder type.

            \param dialog  A font dialog.
            \param encoder An encoder.

            \return The color.

            \throw std::system_error When the color dialog cannot be shown.
        */
        template <typename Color, typename Encoder>
        static boost::optional<Color> show_color_dialog(color_dialog_details_type& dialog, const Encoder& encoder)
        {
            return boost::make_optional(Color(0xAB, 0xCD, 0xEF));
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
                labels.push_back(boost::make_optional(encoder.encode(*ok_button_label)));
            else
                labels.push_back(boost::none);

            if (yes_no_button_labels)
            {
                labels.push_back(boost::make_optional(encoder.encode(yes_no_button_labels->first)));
                labels.push_back(boost::make_optional(encoder.encode(yes_no_button_labels->second)));
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
            const message_box_button_style_type::enum_t       style,
            const bool                                        cancellable,
            const std::vector<boost::optional<std::wstring>>& custom_button_labels
        )
        {
            assert(custom_button_labels.size() == 3);

            ::TASKDIALOG_COMMON_BUTTON_FLAGS flags = 0;
            switch (style)
            {
            case message_box_button_style_type::ok:
                if (!custom_button_labels[0])
                    flags = TDCBF_OK_BUTTON;
                break;
            case message_box_button_style_type::yes_no:
                if (!custom_button_labels[1])
                {
                    assert(!custom_button_labels[2]);
                    flags = TDCBF_YES_BUTTON | TDCBF_NO_BUTTON;
                }
                break;
            default:
                assert(false);
                BOOST_THROW_EXCEPTION(std::invalid_argument("Invalid button style."));
            }

            if (cancellable)
                flags |= TDCBF_CANCEL_BUTTON;

            return flags;
        }

        static ::PCWSTR to_task_dialog_icon(const message_box_icon_style_type::enum_t style)
        {
            switch (style)
            {
            case message_box_icon_style_type::error:
                return TD_ERROR_ICON;
            case message_box_icon_style_type::warning:
                return TD_WARNING_ICON;
            case message_box_icon_style_type::information:
                return TD_INFORMATION_ICON;
            default:
                assert(false);
                BOOST_THROW_EXCEPTION(std::invalid_argument("Invalid icon style."));
            }
        }

        static message_box_button_id_type::enum_t to_message_box_button_id(const int win32_button_id)
        {
            switch (win32_button_id)
            {
            case IDOK:     return message_box_button_id_type::ok;
            case IDCANCEL: return message_box_button_id_type::cancel;
            case IDYES:    return message_box_button_id_type::yes;
            case IDNO:     return message_box_button_id_type::no;
            default:
                assert(false);
                BOOST_THROW_EXCEPTION(std::invalid_argument("Invalid button ID."));
            }
        }

        template <typename String, typename OptionalPath>
        static String to_native_path(const OptionalPath& path)
        {
            return path ? path->template string<String>() : String();
        }

        template <typename Path, typename String>
        static bool match_extension(const Path& path, const String& extension)
        {
            const String path_string = path.template string<String>();
            const String dotted_extension = String(TETENGO2_TEXT(".")) + extension;
            if (path_string.length() < dotted_extension.length())
                return false;

            const String path_extension(
                boost::prior(path_string.end(), dotted_extension.length()), path_string.end()
            );

            return path_extension == dotted_extension;
        }

        template <typename String, typename OptionalPath>
        static std::size_t find_filter_index(
            const std::vector<std::pair<String, String>>& filters,
            const OptionalPath&                           path
        )
        {
            if (!path) return 0;

            for (std::size_t i = 0; i < filters.size(); ++i)
            {
                if (match_extension(*path, filters[i].second))
                    return i + 1;
            }

            return 0;
        }

        template <typename String>
        static String to_default_extension(const std::vector<std::pair<String, String>>& filters)
        {
            return filters.empty() ? String() : filters[0].second;
        }

        template <typename String, typename Encoder>
        static detail::native_filter_type to_native_filter(
            const std::pair<String, String>& filter,
            const Encoder&                   encoder
        )
        {
            return
                detail::native_filter_type(
                    encoder.encode(filter.first), std::wstring(L"*.") + encoder.encode(filter.second)
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
                TETENGO2_CPP11_BIND(to_native_filter<String, Encoder>, cpp11::placeholders_1(), cpp11::cref(encoder))
            );

            return native_filters;
        }

        static ::COMDLG_FILTERSPEC to_filterspec(const detail::native_filter_type& native_filter)
        {
            ::COMDLG_FILTERSPEC filterspec = {};

            filterspec.pszName = native_filter.first.c_str();
            filterspec.pszSpec = native_filter.second.c_str();

            return filterspec;
        }

        static std::vector< ::COMDLG_FILTERSPEC> to_filterspecs(const detail::native_filters_type& native_filters)
        {
            std::vector< ::COMDLG_FILTERSPEC> filterspecs;
            filterspecs.reserve(native_filters.size());

            std::transform(
                native_filters.begin(), native_filters.end(), std::back_inserter(filterspecs), to_filterspec
            );

            return filterspecs;
        }


    };


}}}


#endif
