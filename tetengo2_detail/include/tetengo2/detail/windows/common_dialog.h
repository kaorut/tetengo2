/*! \file
    \brief The definition of tetengo2::detail::windows::common_dialog.

    Copyright (C) 2007-2018 kaoru

    $Id$
*/

#if !defined(TETENGO2_DETAIL_WINDOWS_COMMONDIALOG_H)
#define TETENGO2_DETAIL_WINDOWS_COMMONDIALOG_H

#include <algorithm> // IWYU pragma: keep
#include <cassert>
#include <cstddef>
#include <iterator> // IWYU pragma: keep
#include <memory> // IWYU pragma: keep
#include <string>
#include <system_error> // IWYU pragma: keep
#include <type_traits>
#include <utility>
#include <vector> // IWYU pragma: keep

#include <boost/core/noncopyable.hpp>
#include <boost/filesystem.hpp>
#include <boost/optional.hpp>
#include <boost/preprocessor.hpp>
#include <boost/scope_exit.hpp>
#include <boost/throw_exception.hpp>

#pragma warning(push)
#pragma warning(disable : 4005)
#include <intsafe.h>
#include <stdint.h> // IWYU pragma: keep
#pragma warning(pop)
#define NOMINMAX
#define OEMRESOURCE
#include <ObjBase.h>
#include <ShObjIdl.h>
#include <ShTypes.h>
#include <Windows.h>
#// prevent sort by ClangFormat
#include <CommCtrl.h>

#include <tetengo2/detail/windows/com_ptr.h> // IWYU pragma: keep
#include <tetengo2/detail/windows/error_category.h> // IWYU pragma: keep
#include <tetengo2/stdalt.h>
#include <tetengo2/text.h>


namespace tetengo2 { namespace detail {
    namespace windows {
#if !defined(DOCUMENTATION)
        namespace detail {
            // types

            using file_open_dialog_ptr_type = unique_com_ptr<::IFileOpenDialog>;

            using file_save_dialog_ptr_type = unique_com_ptr<::IFileSaveDialog>;

            using native_filter_type = std::pair<std::wstring, std::wstring>;

            using native_filters_type = std::vector<native_filter_type>;
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
            enum class message_box_button_style_type
            {
                ok, //!< With OK button.
                yes_no, //!< With Yes and No buttons.
            };

            //! The message box icon style type.
            enum class message_box_icon_style_type
            {
                error, //!< Error.
                warning, //!< Warning.
                information, //!< Information.
            };

            //! The message box button ID type.
            enum class message_box_button_id_type
            {
                ok, //!< OK button.
                yes, //!< Yes button.
                no, //!< No button.
                cancel, //!< Cancel button.
            };

            //! The message box details type.
            struct message_box_details_type
            {
#if !defined(DOCUMENTATION)
                ::HWND                                     parent_handle;
                std::wstring                               title;
                std::wstring                               main_content;
                std::wstring                               sub_content;
                bool                                       cancellable;
                message_box_button_style_type              button_style;
                message_box_icon_style_type                icon_style;
                std::vector<boost::optional<std::wstring>> custom_button_labels;

                message_box_details_type(
                    const ::HWND                               parent_handle,
                    std::wstring                               title,
                    std::wstring                               main_content,
                    std::wstring                               sub_content,
                    const bool                                 cancellable,
                    const message_box_button_style_type        button_style,
                    const message_box_icon_style_type          icon_style,
                    std::vector<boost::optional<std::wstring>> custom_button_labels)
                : parent_handle(parent_handle), title(std::move(title)), main_content(std::move(main_content)),
                  sub_content(std::move(sub_content)), cancellable(cancellable), button_style(button_style),
                  icon_style(icon_style), custom_button_labels(std::move(custom_button_labels))
                {}

#endif
            };

            //! The message box details pointer type.
            using message_box_details_ptr_type = std::unique_ptr<message_box_details_type>;

            //! The file open dialog details type.
            struct file_open_dialog_details_type
            {
#if !defined(DOCUMENTATION)
                detail::file_open_dialog_ptr_type p_dialog;
                ::HWND                            parent_handle;
                std::wstring                      title;
                std::wstring                      default_extension;
                detail::native_filters_type       native_filters;

                file_open_dialog_details_type(
                    detail::file_open_dialog_ptr_type p_dialog,
                    const ::HWND                      parent_handle,
                    std::wstring                      title,
                    std::wstring                      default_extension,
                    detail::native_filters_type       native_filters)
                : p_dialog(std::move(p_dialog)), parent_handle(parent_handle), title(std::move(title)),
                  default_extension(std::move(default_extension)), native_filters(std::move(native_filters))
                {}

#endif
            };

            //! The file open dialog details pointer type.
            using file_open_dialog_details_ptr_type = std::unique_ptr<file_open_dialog_details_type>;

            //! The file save dialog details type.
            struct file_save_dialog_details_type
            {
#if !defined(DOCUMENTATION)
                detail::file_save_dialog_ptr_type p_dialog;
                ::HWND                            parent_handle;
                std::wstring                      title;
                std::wstring                      path;
                std::wstring                      default_extension;
                detail::native_filters_type       native_filters;
                std::size_t                       filter_index;

                file_save_dialog_details_type(
                    detail::file_save_dialog_ptr_type p_dialog,
                    const ::HWND                      parent_handle,
                    std::wstring                      title,
                    std::wstring                      path,
                    std::wstring                      default_extension,
                    detail::native_filters_type       native_filters,
                    const std::size_t                 filter_index)
                : p_dialog(std::move(p_dialog)), parent_handle(parent_handle), title(std::move(title)),
                  path(std::move(path)), default_extension(std::move(default_extension)),
                  native_filters(std::move(native_filters)), filter_index(filter_index)
                {}

#endif
            };

            //! The file save dialog details pointer type.
            using file_save_dialog_details_ptr_type = std::unique_ptr<file_save_dialog_details_type>;

            //! The font dialog details type.
            struct font_dialog_details_type
            {
#if !defined(DOCUMENTATION)
                ::HWND                      parent_handle;
                std::unique_ptr<::LOGFONTW> p_log_font;

                font_dialog_details_type(const ::HWND parent_handle, std::unique_ptr<::LOGFONTW>&& p_log_font)
                : parent_handle(parent_handle), p_log_font(std::move(p_log_font))
                {}
#endif
            };


            //! The font dialog details pointer type.
            using font_dialog_details_ptr_type = std::unique_ptr<font_dialog_details_type>;

            //! The color dialog details type.
            struct color_dialog_details_type
            {
#if !defined(DOCUMENTATION)
                ::HWND     parent_handle;
                ::COLORREF native_color;

                color_dialog_details_type(const ::HWND parent_handle, const ::COLORREF native_color)
                : parent_handle(parent_handle), native_color(native_color)
                {}
#endif
            };

            //! The color dialog details pointer type.
            using color_dialog_details_ptr_type = std::unique_ptr<color_dialog_details_type>;


            // static functions

            /*!
                \brief Creates a message box.

                \tparam AbstractWindow An abstract window type.
                \tparam String         A string type.
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
            template <typename AbstractWindow, typename String, typename Encoder>
            static message_box_details_ptr_type create_message_box(
                AbstractWindow&                            parent,
                String                                     title,
                String                                     main_content,
                String                                     sub_content,
                const bool                                 cancellable,
                const message_box_button_style_type        button_style,
                const message_box_icon_style_type          icon_style,
                boost::optional<String>                    custom_ok_button_label,
                boost::optional<std::pair<String, String>> custom_yes_no_button_labels,
                const Encoder&                             encoder)
            {
                return stdalt::make_unique<message_box_details_type>(
                    parent.details().handle.get(),
                    encoder.encode(std::move(title)),
                    encoder.encode(std::move(main_content)),
                    encoder.encode(std::move(sub_content)),
                    cancellable,
                    button_style,
                    icon_style,
                    to_custom_button_labels(
                        std::move(custom_ok_button_label), std::move(custom_yes_no_button_labels), encoder));
            }

            /*!
                \brief Shows a message box and return a button id.

                \param message_box A message box.

                \return The path.

                \throw std::system_error When the message box cannot be shown.
            */
            static message_box_button_id_type show_message_box(message_box_details_type& message_box)
            {
                const auto  parent_window_handle = message_box.parent_handle;
                const auto& title = message_box.title;
                const auto& main_content = message_box.main_content;
                const auto& sub_content = message_box.sub_content;
                const auto  cancellable = message_box.cancellable;
                const auto  button_style = message_box.button_style;
                const auto  icon_style = message_box.icon_style;
                const auto& custom_button_labels = message_box.custom_button_labels;

                const auto custom_buttons = make_custom_buttons(custom_button_labels);

                ::TASKDIALOGCONFIG config{};
                config.cbSize = sizeof(::TASKDIALOGCONFIG);
                config.hwndParent = parent_window_handle;
                config.dwCommonButtons = to_task_dialog_common_buttons(button_style, cancellable, custom_button_labels);
                config.pszWindowTitle = title.c_str();
                config.pszMainIcon = to_task_dialog_icon(icon_style);
                config.pszMainInstruction = main_content.c_str();
                config.pszContent = sub_content.empty() ? nullptr : sub_content.c_str();
                config.cButtons = static_cast<::UINT>(custom_buttons.size());
                config.pButtons = custom_buttons.data();

                int        selected_button = 0;
                const auto result = ::TaskDialogIndirect(&config, &selected_button, nullptr, nullptr);
                if (result != S_OK)
                {
                    BOOST_THROW_EXCEPTION((
                        std::system_error{ std::error_code{ result, win32_category() }, "Can't show a message box." }));
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
                String          title,
                const Filters&  filters,
                const Encoder&  encoder)
            {
                ::IFileOpenDialog* p_raw_dialog = nullptr;
                const auto         creation_result =
                    ::CoCreateInstance(__uuidof(::FileOpenDialog), nullptr, CLSCTX_ALL, IID_PPV_ARGS(&p_raw_dialog));
                if (FAILED(creation_result))
                {
                    BOOST_THROW_EXCEPTION((std::system_error{ std::error_code{ creation_result, win32_category() },
                                                              "Can't create a file open dialog." }));
                }
                detail::file_open_dialog_ptr_type p_dialog{ p_raw_dialog };
                return stdalt::make_unique<file_open_dialog_details_type>(
                    std::move(p_dialog),
                    parent.details().handle.get(),
                    encoder.encode(std::move(title)),
                    encoder.encode(to_default_extension(filters)),
                    to_native_filters(filters, encoder));
            }

            /*!
                \brief Shows a file open dialog and return a path.

                \tparam Encoder An encoder type.

                \param dialog  A file open dialog.
                \param encoder An encoder.

                \return The path.

                \throw std::system_error When the file open dialog cannot be shown.
            */
            template <typename Encoder>
            static boost::optional<boost::filesystem::path>
            show_file_open_dialog(file_open_dialog_details_type& dialog, const Encoder& encoder)
            {
                const auto title_set_result = dialog.p_dialog->SetTitle(dialog.title.c_str());
                if (FAILED(title_set_result))
                {
                    BOOST_THROW_EXCEPTION((std::system_error{ std::error_code{ title_set_result, win32_category() },
                                                              "Can't set title." }));
                }

                if (!dialog.native_filters.empty())
                {
                    const auto default_extension_set_result =
                        dialog.p_dialog->SetDefaultExtension(dialog.default_extension.c_str());
                    if (FAILED(default_extension_set_result))
                    {
                        BOOST_THROW_EXCEPTION(
                            (std::system_error{ std::error_code{ default_extension_set_result, win32_category() },
                                                "Can't set default extension." }));
                    }
                }

                auto       filterspecs = to_filterspecs(dialog.native_filters);
                const auto filter_set_result =
                    dialog.p_dialog->SetFileTypes(static_cast<::UINT>(filterspecs.size()), filterspecs.data());
                if (FAILED(filter_set_result))
                {
                    BOOST_THROW_EXCEPTION((std::system_error{ std::error_code{ filter_set_result, win32_category() },
                                                              "Can't set file type filter." }));
                }

                const auto showing_result = dialog.p_dialog->Show(dialog.parent_handle);
                if (FAILED(showing_result))
                    return boost::none;

                ::IShellItem* p_raw_item = nullptr;
                const auto    result_result = dialog.p_dialog->GetResult(&p_raw_item);
                if (FAILED(result_result))
                {
                    BOOST_THROW_EXCEPTION((std::system_error{ std::error_code{ result_result, win32_category() },
                                                              "Can't get the result." }));
                }
                const typename unique_com_ptr<::IShellItem> p_item{ p_raw_item };

                wchar_t*   file_name = nullptr;
                const auto file_title_result = p_item->GetDisplayName(SIGDN_FILESYSPATH, &file_name);
                if (FAILED(file_title_result))
                {
                    BOOST_THROW_EXCEPTION((std::system_error{ std::error_code{ file_title_result, win32_category() },
                                                              "Can't get the file path." }));
                }
                BOOST_SCOPE_EXIT((file_name))
                {
                    ::CoTaskMemFree(file_name);
                }
                BOOST_SCOPE_EXIT_END;

                return boost::make_optional(boost::filesystem::path{ encoder.decode(file_name) });
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
            template <
                typename AbstractWindow,
                typename String,
                typename OptionalPath,
                typename Filters,
                typename Encoder>
            static file_save_dialog_details_ptr_type create_file_save_dialog(
                AbstractWindow&     parent,
                String              title,
                const OptionalPath& path,
                const Filters&      filters,
                const Encoder&      encoder)
            {
                ::IFileSaveDialog* p_raw_dialog = nullptr;
                const auto         creation_result =
                    ::CoCreateInstance(__uuidof(::FileSaveDialog), nullptr, CLSCTX_ALL, IID_PPV_ARGS(&p_raw_dialog));
                if (FAILED(creation_result))
                {
                    BOOST_THROW_EXCEPTION((std::system_error{ std::error_code{ creation_result, win32_category() },
                                                              "Can't create a file save dialog." }));
                }
                detail::file_save_dialog_ptr_type p_dialog{ p_raw_dialog };
                return stdalt::make_unique<file_save_dialog_details_type>(
                    std::move(p_dialog),
                    parent.details().handle.get(),
                    encoder.encode(std::move(title)),
                    encoder.encode(to_native_path<String>(path)),
                    encoder.encode(to_default_extension(filters)),
                    to_native_filters(filters, encoder),
                    find_filter_index(filters, path));
            }

            /*!
                \brief Shows a file save dialog and return a path.

                \tparam boost::filesystem::path    A path type.
                \tparam Encoder An encoder type.

                \param dialog  A file save dialog.
                \param encoder An encoder.

                \return The path.

                \throw std::system_error When the file save dialog cannot be shown.
            */
            template <typename Encoder>
            static boost::optional<boost::filesystem::path>
            show_file_save_dialog(file_save_dialog_details_type& dialog, const Encoder& encoder)
            {
                const auto title_set_result = dialog.p_dialog->SetTitle(dialog.title.c_str());
                if (FAILED(title_set_result))
                {
                    BOOST_THROW_EXCEPTION((std::system_error{ std::error_code{ title_set_result, win32_category() },
                                                              "Can't set title." }));
                }

                ::IShellItem* p_raw_default_path = nullptr;
                if (!dialog.path.empty())
                {
                    const auto default_path_result =
                        ::SHCreateItemFromParsingName(dialog.path.c_str(), nullptr, IID_PPV_ARGS(&p_raw_default_path));
                    if (FAILED(default_path_result))
                    {
                        BOOST_THROW_EXCEPTION(
                            (std::system_error{ std::error_code{ default_path_result, win32_category() },
                                                "Can't create default path item." }));
                    }
                }
                BOOST_SCOPE_EXIT((p_raw_default_path))
                {
                    if (p_raw_default_path)
                        p_raw_default_path->Release();
                }
                BOOST_SCOPE_EXIT_END;
                if (!dialog.path.empty())
                {
                    const auto default_path_set_result = dialog.p_dialog->SetSaveAsItem(p_raw_default_path);
                    if (FAILED(default_path_set_result))
                    {
                        BOOST_THROW_EXCEPTION((std::system_error{
                            std::error_code{ default_path_set_result, win32_category() }, "Can't set default path." }));
                    }
                }

                if (!dialog.default_extension.empty())
                {
                    const auto default_extension_set_result =
                        dialog.p_dialog->SetDefaultExtension(dialog.default_extension.c_str());
                    if (FAILED(default_extension_set_result))
                    {
                        BOOST_THROW_EXCEPTION(
                            (std::system_error{ std::error_code{ default_extension_set_result, win32_category() },
                                                "Can't set default extension." }));
                    }
                }

                const auto filterspecs = to_filterspecs(dialog.native_filters);
                const auto filter_set_result =
                    dialog.p_dialog->SetFileTypes(static_cast<::UINT>(filterspecs.size()), filterspecs.data());
                if (FAILED(filter_set_result))
                {
                    BOOST_THROW_EXCEPTION((std::system_error{ std::error_code{ filter_set_result, win32_category() },
                                                              "Can't set file type filters." }));
                }

                if (dialog.filter_index > 0)
                {
                    const auto filter_index_set_result =
                        dialog.p_dialog->SetFileTypeIndex(static_cast<::UINT>(dialog.filter_index));
                    if (FAILED(filter_index_set_result))
                    {
                        BOOST_THROW_EXCEPTION(
                            (std::system_error{ std::error_code{ filter_set_result, win32_category() },
                                                "Can't set file type filter index." }));
                    }
                }

                const auto showing_result = dialog.p_dialog->Show(dialog.parent_handle);
                if (FAILED(showing_result))
                    return boost::none;

                ::IShellItem* p_raw_item = nullptr;
                const auto    result_result = dialog.p_dialog->GetResult(&p_raw_item);
                if (FAILED(result_result))
                {
                    BOOST_THROW_EXCEPTION((std::system_error{ std::error_code{ result_result, win32_category() },
                                                              "Can't get the result." }));
                }
                const typename unique_com_ptr<::IShellItem> p_item{ p_raw_item };

                wchar_t*   file_name = nullptr;
                const auto file_title_result = p_item->GetDisplayName(SIGDN_FILESYSPATH, &file_name);
                if (FAILED(file_title_result))
                {
                    BOOST_THROW_EXCEPTION((std::system_error{ std::error_code{ file_title_result, win32_category() },
                                                              "Can't get the file path." }));
                }
                BOOST_SCOPE_EXIT((file_name))
                {
                    ::CoTaskMemFree(file_name);
                }
                BOOST_SCOPE_EXIT_END;

                return boost::make_optional(boost::filesystem::path{ encoder.decode(file_name) });
            }

            /*!
                \brief Creates a font dialog.

                \tparam AbstractWindow An abstract window type.
                \tparam OptionalFont   An optional font type.
                \tparam Encoder        An encoder type.

                \param parent  A parent window.
                \param font    A font.
                \param encoder An encoder.

                \return A unique pointer to a font dialog.

                \throw std::system_error When the font dialog cannot be created.
            */
            template <typename AbstractWindow, typename OptionalFont, typename Encoder>
            static font_dialog_details_ptr_type
            create_font_dialog(AbstractWindow& parent, const OptionalFont& font, const Encoder& encoder)
            {
                auto p_log_font = stdalt::make_unique<::LOGFONTW>();
                if (font)
                {
                    p_log_font->lfHeight = -static_cast<::LONG>(font->size());
                    p_log_font->lfWeight = font->bold() ? FW_BOLD : FW_NORMAL;
                    p_log_font->lfItalic = font->italic() ? TRUE : FALSE;
                    p_log_font->lfUnderline = font->underline() ? TRUE : FALSE;
                    p_log_font->lfStrikeOut = font->strikeout() ? TRUE : FALSE;

                    const auto native_face_name = encoder.encode(font->family());
                    const auto native_face_name_length =
                        std::min<std::size_t>(native_face_name.length(), LF_FACESIZE - 1);
                    std::copy(
                        native_face_name.begin(),
                        std::next(native_face_name.begin(), native_face_name_length),
                        p_log_font->lfFaceName);
                    p_log_font->lfFaceName[native_face_name_length] = 0;
                }
                else
                {
                    using font_type = typename std::decay<OptionalFont>::type::value_type;
                    const auto& dialog_font = font_type::dialog_font();

                    p_log_font->lfHeight = -static_cast<::LONG>(dialog_font.size());
                    p_log_font->lfWeight = dialog_font.bold() ? FW_BOLD : FW_NORMAL;
                    p_log_font->lfItalic = dialog_font.italic() ? TRUE : FALSE;
                    p_log_font->lfUnderline = dialog_font.underline() ? TRUE : FALSE;
                    p_log_font->lfStrikeOut = dialog_font.strikeout() ? TRUE : FALSE;

                    const auto native_face_name = encoder.encode(dialog_font.family());
                    const auto native_face_name_length =
                        std::min<std::size_t>(native_face_name.length(), LF_FACESIZE - 1);
                    std::copy(
                        native_face_name.begin(),
                        std::next(native_face_name.begin(), native_face_name_length),
                        p_log_font->lfFaceName);
                    p_log_font->lfFaceName[native_face_name_length] = 0;
                }
                p_log_font->lfCharSet = DEFAULT_CHARSET;
                p_log_font->lfOutPrecision = OUT_DEFAULT_PRECIS;
                p_log_font->lfClipPrecision = CLIP_DEFAULT_PRECIS;
                p_log_font->lfQuality = DEFAULT_QUALITY;
                p_log_font->lfPitchAndFamily = DEFAULT_PITCH;

                return stdalt::make_unique<font_dialog_details_type>(
                    parent.details().handle.get(), std::move(p_log_font));
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
                ::CHOOSEFONTW choose_font{};
                choose_font.lStructSize = sizeof(::CHOOSEFONTW);
                choose_font.hwndOwner = dialog.parent_handle;
                choose_font.hDC = nullptr;
                choose_font.lpLogFont = dialog.p_log_font.get();
                choose_font.iPointSize = 0;
                choose_font.Flags = CF_EFFECTS | CF_FORCEFONTEXIST | CF_NOVERTFONTS | CF_INITTOLOGFONTSTRUCT;
                choose_font.rgbColors = 0;
                choose_font.lCustData = 0;
                choose_font.lpfnHook = nullptr;
                choose_font.lpTemplateName = nullptr;
                choose_font.hInstance = nullptr;
                choose_font.lpszStyle = nullptr;
                choose_font.nFontType = 0;
                choose_font.nSizeMin = 0;
                choose_font.nSizeMax = 0;

                const auto result = ::ChooseFontW(&choose_font);
                if (result == FALSE)
                    return boost::none;

                return boost::make_optional(
                    Font{ encoder.decode(choose_font.lpLogFont->lfFaceName),
                          static_cast<typename Font::size_type>(
                              choose_font.lpLogFont->lfHeight < 0 ? -choose_font.lpLogFont->lfHeight :
                                                                    choose_font.lpLogFont->lfHeight),
                          choose_font.lpLogFont->lfWeight >= FW_BOLD,
                          choose_font.lpLogFont->lfItalic != FALSE,
                          choose_font.lpLogFont->lfUnderline != FALSE,
                          choose_font.lpLogFont->lfStrikeOut != FALSE });
            }

            /*!
                \brief Creates a color dialog.

                \tparam AbstractWindow An abstract window type.
                \tparam OptionalColor  An optional color type.

                \param parent A parent window.
                \param color  A color.

                \return A unique pointer to a color dialog.

                \throw std::system_error When the color dialog cannot be created.
            */
            template <typename AbstractWindow, typename OptionalColor>
            static color_dialog_details_ptr_type create_color_dialog(AbstractWindow& parent, const OptionalColor& color)
            {
                const ::COLORREF native_color = color ? RGB(color->red(), color->green(), color->blue()) : 0;
                return stdalt::make_unique<color_dialog_details_type>(parent.details().handle.get(), native_color);
            }

            /*!
                \brief Shows a color dialog and return a font.

                \tparam Color A color type.

                \param dialog A color dialog.

                \return The color.

                \throw std::system_error When the color dialog cannot be shown.
            */
            template <typename Color>
            static boost::optional<Color> show_color_dialog(color_dialog_details_type& dialog)
            {
                static std::vector<::COLORREF> custom_colors(16, RGB(0xFF, 0xFF, 0xFF));
                ::CHOOSECOLORW                 choose_color{};
                choose_color.lStructSize = sizeof(::CHOOSECOLORW);
                choose_color.hwndOwner = dialog.parent_handle;
                choose_color.hInstance = nullptr;
                choose_color.rgbResult = dialog.native_color;
                choose_color.lpCustColors = custom_colors.data();
                choose_color.Flags = CC_ANYCOLOR | CC_RGBINIT | CC_FULLOPEN;
                choose_color.lCustData = 0;
                choose_color.lpfnHook = nullptr;
                choose_color.lpTemplateName = nullptr;

                const auto result = ::ChooseColorW(&choose_color);
                if (result == FALSE)
                    return boost::none;

                return boost::make_optional(Color{ GetRValue(choose_color.rgbResult),
                                                   GetGValue(choose_color.rgbResult),
                                                   GetBValue(choose_color.rgbResult) });
            }


        private:
            // static functions

            template <typename String, typename Encoder>
            static std::vector<boost::optional<std::wstring>> to_custom_button_labels(
                const boost::optional<String>&                    ok_button_label,
                const boost::optional<std::pair<String, String>>& yes_no_button_labels,
                const Encoder&                                    encoder)
            {
                std::vector<boost::optional<std::wstring>> labels{};
                labels.reserve(3);

                if (ok_button_label)
                    labels.emplace_back(encoder.encode(*ok_button_label));
                else
                    labels.push_back(boost::none);

                if (yes_no_button_labels)
                {
                    labels.emplace_back(encoder.encode(yes_no_button_labels->first));
                    labels.emplace_back(encoder.encode(yes_no_button_labels->second));
                }
                else
                {
                    labels.push_back(boost::none);
                    labels.push_back(boost::none);
                }

                assert(labels.size() == 3);
                return labels;
            }

            static std::vector<::TASKDIALOG_BUTTON>
            make_custom_buttons(const std::vector<boost::optional<std::wstring>>& button_labels)
            {
                assert(button_labels.size() == 3);

                std::vector<::TASKDIALOG_BUTTON> buttons{};

                if (button_labels[0])
                {
                    ::TASKDIALOG_BUTTON button{};
                    button.nButtonID = IDOK;
                    button.pszButtonText = button_labels[0]->c_str();
                    buttons.push_back(button);
                }

                if (button_labels[1])
                {
                    assert(button_labels[2]);
                    {
                        ::TASKDIALOG_BUTTON button{};
                        button.nButtonID = IDYES;
                        button.pszButtonText = button_labels[1]->c_str();
                        buttons.push_back(button);
                    }
                    {
                        ::TASKDIALOG_BUTTON button{};
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
                const std::vector<boost::optional<std::wstring>>& custom_button_labels)
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
                    BOOST_THROW_EXCEPTION((std::invalid_argument{ "Invalid button style." }));
                }

                if (cancellable)
                    flags |= TDCBF_CANCEL_BUTTON;

                return flags;
            }

            static ::PCWSTR to_task_dialog_icon(const message_box_icon_style_type style)
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
                    BOOST_THROW_EXCEPTION((std::invalid_argument{ "Invalid icon style." }));
                }
            }

            static message_box_button_id_type to_message_box_button_id(const int win32_button_id)
            {
                switch (win32_button_id)
                {
                case IDOK:
                    return message_box_button_id_type::ok;
                case IDCANCEL:
                    return message_box_button_id_type::cancel;
                case IDYES:
                    return message_box_button_id_type::yes;
                case IDNO:
                    return message_box_button_id_type::no;
                default:
                    assert(false);
                    BOOST_THROW_EXCEPTION((std::invalid_argument{ "Invalid button ID." }));
                }
            }

            template <typename String, typename OptionalPath>
            static String to_native_path(const OptionalPath& path)
            {
                return path ? path->template string<String>() : String{};
            }

            template <typename String>
            static bool match_extension(const boost::filesystem::path& path, const String& extension)
            {
                const auto path_string = path.template string<String>();
                const auto dotted_extension = String{ TETENGO2_TEXT(".") } + extension;
                if (path_string.length() < dotted_extension.length())
                    return false;

                const String path_extension{ std::prev(path_string.end(), dotted_extension.length()),
                                             path_string.end() };

                return path_extension == dotted_extension;
            }

            template <typename String, typename OptionalPath>
            static std::size_t
            find_filter_index(const std::vector<std::pair<String, String>>& filters, const OptionalPath& path)
            {
                if (!path)
                    return 0;

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
                return filters.empty() ? String{} : filters[0].second;
            }

            template <typename String, typename Encoder>
            static detail::native_filter_type
            to_native_filter(const std::pair<String, String>& filter, const Encoder& encoder)
            {
                return { encoder.encode(filter.first), std::wstring{ L"*." } + encoder.encode(filter.second) };
            }

            template <typename String, typename Encoder>
            static detail::native_filters_type
            to_native_filters(const std::vector<std::pair<String, String>>& filters, const Encoder& encoder)
            {
                detail::native_filters_type native_filters;
                native_filters.reserve(filters.size());

                std::transform(
                    filters.begin(),
                    filters.end(),
                    std::back_inserter(native_filters),
                    [&encoder](const std::pair<String, String>& filter) { return to_native_filter(filter, encoder); });

                return native_filters;
            }

            static ::COMDLG_FILTERSPEC to_filterspec(const detail::native_filter_type& native_filter)
            {
                ::COMDLG_FILTERSPEC filterspec{};

                filterspec.pszName = native_filter.first.c_str();
                filterspec.pszSpec = native_filter.second.c_str();

                return filterspec;
            }

            static std::vector<::COMDLG_FILTERSPEC> to_filterspecs(const detail::native_filters_type& native_filters)
            {
                std::vector<::COMDLG_FILTERSPEC> filterspecs{};
                filterspecs.reserve(native_filters.size());

                std::transform(
                    native_filters.begin(), native_filters.end(), std::back_inserter(filterspecs), to_filterspec);

                return filterspecs;
            }
        };
    }
}}


#endif
