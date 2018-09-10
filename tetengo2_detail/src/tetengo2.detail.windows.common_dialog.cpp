/*! \file
    \brief The definition of tetengo2::detail::windows::common_dialog.

    Copyright (C) 2007-2018 kaoru

    $Id$
*/

#include <algorithm>
#include <cassert>
#include <cstddef>
#include <iterator>
#include <memory>
#include <string>
#include <system_error>
#include <type_traits>
#include <utility>
#include <vector>

#include <boost/core/noncopyable.hpp>
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

#include <tetengo2/detail/windows/com_ptr.h>
#include <tetengo2/detail/windows/common_dialog.h>
#include <tetengo2/detail/windows/error_category.h>
#include <tetengo2/detail/windows/gdiplus/drawing.h>
#include <tetengo2/detail/windows/widget.h>
#include <tetengo2/gui/drawing/color.h>
#include <tetengo2/gui/widget/abstract_window.h>
#include <tetengo2/stdalt.h>
#include <tetengo2/text.h>
#include <tetengo2/text/encoder.h>
#include <tetengo2/text/encoding/locale.h>
#include <tetengo2/type_list.h>


namespace tetengo2::detail::windows {
    namespace detail {
        // types

        using file_open_dialog_ptr_type = unique_com_ptr<::IFileOpenDialog>;

        using file_save_dialog_ptr_type = unique_com_ptr<::IFileSaveDialog>;

        using native_filter_type = std::pair<std::wstring, std::wstring>;

        using native_filters_type = std::vector<native_filter_type>;

        using native_common_dialog_encoder_type =
            text::encoder<type_list::internal_encoding_type, text::encoding::locale<std::wstring>>;

        inline const native_common_dialog_encoder_type& native_common_dialog_encoder()
        {
            static const native_common_dialog_encoder_type singleton;
            return singleton;
        }
    }


    class common_dialog::impl : private boost::noncopyable
    {
    public:
        // types

        using message_box_button_style_type = common_dialog::message_box_button_style_type;

        using message_box_icon_style_type = common_dialog::message_box_icon_style_type;

        using message_box_button_id_type = common_dialog::message_box_button_id_type;

        using message_box_details_type = common_dialog::message_box_details_type;

        struct windows_message_box_details_type : public message_box_details_type
        {
            ::HWND                                                parent_handle;
            std::wstring                                          title;
            std::wstring                                          main_content;
            std::wstring                                          sub_content;
            bool                                                  cancellable;
            message_box_button_style_type                         button_style;
            message_box_icon_style_type                           icon_style;
            std::vector<tetengo2::stdalt::optional<std::wstring>> custom_button_labels;

            windows_message_box_details_type(
                const ::HWND                                          parent_handle,
                std::wstring                                          title,
                std::wstring                                          main_content,
                std::wstring                                          sub_content,
                const bool                                            cancellable,
                const message_box_button_style_type                   button_style,
                const message_box_icon_style_type                     icon_style,
                std::vector<tetengo2::stdalt::optional<std::wstring>> custom_button_labels)
            : parent_handle{ parent_handle }, title{ std::move(title) }, main_content{ std::move(main_content) },
              sub_content{ std::move(sub_content) }, cancellable{ cancellable }, button_style{ button_style },
              icon_style{ icon_style }, custom_button_labels{ std::move(custom_button_labels) }
            {}

            virtual ~windows_message_box_details_type() = default;
        };

        using message_box_details_ptr_type = common_dialog::message_box_details_ptr_type;

        using filters_type = common_dialog::filters_type;

        using file_open_dialog_details_type = common_dialog::file_open_dialog_details_type;

        struct windows_file_open_dialog_details_type : public file_open_dialog_details_type
        {
            detail::file_open_dialog_ptr_type p_dialog;
            ::HWND                            parent_handle;
            std::wstring                      title;
            std::wstring                      default_extension;
            detail::native_filters_type       native_filters;

            windows_file_open_dialog_details_type(
                detail::file_open_dialog_ptr_type p_dialog,
                const ::HWND                      parent_handle,
                std::wstring                      title,
                std::wstring                      default_extension,
                detail::native_filters_type       native_filters)
            : p_dialog{ std::move(p_dialog) }, parent_handle{ parent_handle }, title{ std::move(title) },
              default_extension{ std::move(default_extension) }, native_filters{ std::move(native_filters) }
            {}

            virtual ~windows_file_open_dialog_details_type() = default;
        };

        using file_open_dialog_details_ptr_type = common_dialog::file_open_dialog_details_ptr_type;

        using file_save_dialog_details_type = common_dialog::file_save_dialog_details_type;

        struct windows_file_save_dialog_details_type : public file_save_dialog_details_type
        {
            detail::file_save_dialog_ptr_type p_dialog;
            ::HWND                            parent_handle;
            std::wstring                      title;
            std::wstring                      path;
            std::wstring                      default_extension;
            detail::native_filters_type       native_filters;
            std::size_t                       filter_index;

            windows_file_save_dialog_details_type(
                detail::file_save_dialog_ptr_type p_dialog,
                const ::HWND                      parent_handle,
                std::wstring                      title,
                std::wstring                      path,
                std::wstring                      default_extension,
                detail::native_filters_type       native_filters,
                const std::size_t                 filter_index)
            : p_dialog{ std::move(p_dialog) }, parent_handle{ parent_handle }, title{ std::move(title) },
              path{ std::move(path) }, default_extension{ std::move(default_extension) },
              native_filters{ std::move(native_filters) }, filter_index{ filter_index }
            {}

            virtual ~windows_file_save_dialog_details_type() = default;
        };
        using file_save_dialog_details_ptr_type = common_dialog::file_save_dialog_details_ptr_type;

        using font_dialog_details_type = common_dialog::font_dialog_details_type;

        struct windows_font_dialog_details_type : public font_dialog_details_type
        {
            ::HWND                      parent_handle;
            std::unique_ptr<::LOGFONTW> p_log_font;

            windows_font_dialog_details_type(const ::HWND parent_handle, std::unique_ptr<::LOGFONTW>&& p_log_font)
            : parent_handle{ parent_handle }, p_log_font{ std::move(p_log_font) }
            {}

            virtual ~windows_font_dialog_details_type() = default;
        };
        using font_dialog_details_ptr_type = common_dialog::font_dialog_details_ptr_type;

        using color_dialog_details_type = common_dialog::color_dialog_details_type;

        struct windows_color_dialog_details_type : public color_dialog_details_type
        {
            ::HWND     parent_handle;
            ::COLORREF native_color;

            windows_color_dialog_details_type(const ::HWND parent_handle, const ::COLORREF native_color)
            : parent_handle{ parent_handle }, native_color{ native_color }
            {}

            virtual ~windows_color_dialog_details_type() = default;
        };

        using color_dialog_details_ptr_type = common_dialog::color_dialog_details_ptr_type;


        // static functions

        static const common_dialog& instance()
        {
            static const common_dialog singleton;
            return singleton;
        }


        // functions

        message_box_details_ptr_type create_message_box_impl(
            gui::widget::abstract_window&                      parent,
            type_list::string_type                             title,
            type_list::string_type                             main_content,
            type_list::string_type                             sub_content,
            const bool                                         cancellable,
            const message_box_button_style_type                button_style,
            const message_box_icon_style_type                  icon_style,
            tetengo2::stdalt::optional<type_list::string_type> custom_ok_button_label,
            tetengo2::stdalt::optional<std::pair<type_list::string_type, type_list::string_type>>
                custom_yes_no_button_labels) const
        {
            return std::make_unique<windows_message_box_details_type>(
                reinterpret_cast<::HWND>(as_windows_widget_details(parent.details()).handle),
                detail::native_common_dialog_encoder().encode(std::move(title)),
                detail::native_common_dialog_encoder().encode(std::move(main_content)),
                detail::native_common_dialog_encoder().encode(std::move(sub_content)),
                cancellable,
                button_style,
                icon_style,
                to_custom_button_labels(std::move(custom_ok_button_label), std::move(custom_yes_no_button_labels)));
        }

        message_box_button_id_type show_message_box_impl(message_box_details_type& message_box) const
        {
            assert(dynamic_cast<windows_message_box_details_type*>(&message_box));
            auto&       windows_message_box = static_cast<windows_message_box_details_type&>(message_box);
            const auto  parent_window_handle = windows_message_box.parent_handle;
            const auto& title = windows_message_box.title;
            const auto& main_content = windows_message_box.main_content;
            const auto& sub_content = windows_message_box.sub_content;
            const auto  cancellable = windows_message_box.cancellable;
            const auto  button_style = windows_message_box.button_style;
            const auto  icon_style = windows_message_box.icon_style;
            const auto& custom_button_labels = windows_message_box.custom_button_labels;

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
                BOOST_THROW_EXCEPTION(
                    (std::system_error{ std::error_code{ result, win32_category() }, "Can't show a message box." }));
            }

            return to_message_box_button_id(selected_button);
        }

        file_open_dialog_details_ptr_type create_file_open_dialog_impl(
            gui::widget::abstract_window& parent,
            type_list::string_type        title,
            const filters_type&           filters) const
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
            return std::make_unique<windows_file_open_dialog_details_type>(
                std::move(p_dialog),
                reinterpret_cast<::HWND>(as_windows_widget_details(parent.details()).handle),
                detail::native_common_dialog_encoder().encode(std::move(title)),
                detail::native_common_dialog_encoder().encode(to_default_extension(filters)),
                to_native_filters(filters));
        }

        tetengo2::stdalt::optional<tetengo2::stdalt::filesystem::path>
        show_file_open_dialog_impl(file_open_dialog_details_type& dialog) const
        {
            assert(dynamic_cast<windows_file_open_dialog_details_type*>(&dialog));
            auto&      windows_dialog = static_cast<windows_file_open_dialog_details_type&>(dialog);
            const auto title_set_result = windows_dialog.p_dialog->SetTitle(windows_dialog.title.c_str());
            if (FAILED(title_set_result))
            {
                BOOST_THROW_EXCEPTION(
                    (std::system_error{ std::error_code{ title_set_result, win32_category() }, "Can't set title." }));
            }

            if (!windows_dialog.native_filters.empty())
            {
                const auto default_extension_set_result =
                    windows_dialog.p_dialog->SetDefaultExtension(windows_dialog.default_extension.c_str());
                if (FAILED(default_extension_set_result))
                {
                    BOOST_THROW_EXCEPTION(
                        (std::system_error{ std::error_code{ default_extension_set_result, win32_category() },
                                            "Can't set default extension." }));
                }
            }

            auto       filterspecs = to_filterspecs(windows_dialog.native_filters);
            const auto filter_set_result =
                windows_dialog.p_dialog->SetFileTypes(static_cast<::UINT>(filterspecs.size()), filterspecs.data());
            if (FAILED(filter_set_result))
            {
                BOOST_THROW_EXCEPTION((std::system_error{ std::error_code{ filter_set_result, win32_category() },
                                                          "Can't set file type filter." }));
            }

            const auto showing_result = windows_dialog.p_dialog->Show(windows_dialog.parent_handle);
            if (FAILED(showing_result))
                return TETENGO2_STDALT_NULLOPT;

            ::IShellItem* p_raw_item = nullptr;
            const auto    result_result = windows_dialog.p_dialog->GetResult(&p_raw_item);
            if (FAILED(result_result))
            {
                BOOST_THROW_EXCEPTION(
                    (std::system_error{ std::error_code{ result_result, win32_category() }, "Can't get the result." }));
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

            return tetengo2::stdalt::make_optional(
                tetengo2::stdalt::filesystem::path{ detail::native_common_dialog_encoder().decode(file_name) });
        }

        file_save_dialog_details_ptr_type create_file_save_dialog_impl(
            gui::widget::abstract_window&                                         parent,
            type_list::string_type                                                title,
            const tetengo2::stdalt::optional<tetengo2::stdalt::filesystem::path>& path,
            const filters_type&                                                   filters) const
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
            return std::make_unique<windows_file_save_dialog_details_type>(
                std::move(p_dialog),
                reinterpret_cast<::HWND>(as_windows_widget_details(parent.details()).handle),
                detail::native_common_dialog_encoder().encode(std::move(title)),
                detail::native_common_dialog_encoder().encode(to_native_path(path)),
                detail::native_common_dialog_encoder().encode(to_default_extension(filters)),
                to_native_filters(filters),
                find_filter_index(filters, path));
        }

        tetengo2::stdalt::optional<tetengo2::stdalt::filesystem::path>
        show_file_save_dialog_impl(file_save_dialog_details_type& dialog) const
        {
            assert(dynamic_cast<windows_file_save_dialog_details_type*>(&dialog));
            auto&      windows_dialog = static_cast<windows_file_save_dialog_details_type&>(dialog);
            const auto title_set_result = windows_dialog.p_dialog->SetTitle(windows_dialog.title.c_str());
            if (FAILED(title_set_result))
            {
                BOOST_THROW_EXCEPTION(
                    (std::system_error{ std::error_code{ title_set_result, win32_category() }, "Can't set title." }));
            }

            ::IShellItem* p_raw_default_path = nullptr;
            if (!windows_dialog.path.empty())
            {
                const auto default_path_result = ::SHCreateItemFromParsingName(
                    windows_dialog.path.c_str(), nullptr, IID_PPV_ARGS(&p_raw_default_path));
                if (FAILED(default_path_result))
                {
                    BOOST_THROW_EXCEPTION((std::system_error{ std::error_code{ default_path_result, win32_category() },
                                                              "Can't create default path item." }));
                }
            }
            BOOST_SCOPE_EXIT((p_raw_default_path))
            {
                if (p_raw_default_path)
                    p_raw_default_path->Release();
            }
            BOOST_SCOPE_EXIT_END;
            if (!windows_dialog.path.empty())
            {
                const auto default_path_set_result = windows_dialog.p_dialog->SetSaveAsItem(p_raw_default_path);
                if (FAILED(default_path_set_result))
                {
                    BOOST_THROW_EXCEPTION((std::system_error{
                        std::error_code{ default_path_set_result, win32_category() }, "Can't set default path." }));
                }
            }

            if (!windows_dialog.default_extension.empty())
            {
                const auto default_extension_set_result =
                    windows_dialog.p_dialog->SetDefaultExtension(windows_dialog.default_extension.c_str());
                if (FAILED(default_extension_set_result))
                {
                    BOOST_THROW_EXCEPTION(
                        (std::system_error{ std::error_code{ default_extension_set_result, win32_category() },
                                            "Can't set default extension." }));
                }
            }

            const auto filterspecs = to_filterspecs(windows_dialog.native_filters);
            const auto filter_set_result =
                windows_dialog.p_dialog->SetFileTypes(static_cast<::UINT>(filterspecs.size()), filterspecs.data());
            if (FAILED(filter_set_result))
            {
                BOOST_THROW_EXCEPTION((std::system_error{ std::error_code{ filter_set_result, win32_category() },
                                                          "Can't set file type filters." }));
            }

            if (windows_dialog.filter_index > 0)
            {
                const auto filter_index_set_result =
                    windows_dialog.p_dialog->SetFileTypeIndex(static_cast<::UINT>(windows_dialog.filter_index));
                if (FAILED(filter_index_set_result))
                {
                    BOOST_THROW_EXCEPTION((std::system_error{ std::error_code{ filter_set_result, win32_category() },
                                                              "Can't set file type filter index." }));
                }
            }

            const auto showing_result = windows_dialog.p_dialog->Show(windows_dialog.parent_handle);
            if (FAILED(showing_result))
                return TETENGO2_STDALT_NULLOPT;

            ::IShellItem* p_raw_item = nullptr;
            const auto    result_result = windows_dialog.p_dialog->GetResult(&p_raw_item);
            if (FAILED(result_result))
            {
                BOOST_THROW_EXCEPTION(
                    (std::system_error{ std::error_code{ result_result, win32_category() }, "Can't get the result." }));
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

            return tetengo2::stdalt::make_optional(
                tetengo2::stdalt::filesystem::path{ detail::native_common_dialog_encoder().decode(file_name) });
        }

        font_dialog_details_ptr_type create_font_dialog_impl(
            gui::widget::abstract_window&                         parent,
            const tetengo2::stdalt::optional<gui::drawing::font>& font) const
        {
            auto p_log_font = std::make_unique<::LOGFONTW>();
            if (font)
            {
                p_log_font->lfHeight = -static_cast<::LONG>(font->size());
                p_log_font->lfWeight = font->bold() ? FW_BOLD : FW_NORMAL;
                p_log_font->lfItalic = font->italic() ? TRUE : FALSE;
                p_log_font->lfUnderline = font->underline() ? TRUE : FALSE;
                p_log_font->lfStrikeOut = font->strikeout() ? TRUE : FALSE;

                const auto native_face_name = detail::native_common_dialog_encoder().encode(font->family());
                const auto native_face_name_length = std::min<std::size_t>(native_face_name.length(), LF_FACESIZE - 1);
                std::copy(
                    native_face_name.begin(),
                    std::next(native_face_name.begin(), native_face_name_length),
                    p_log_font->lfFaceName);
                p_log_font->lfFaceName[native_face_name_length] = 0;
            }
            else
            {
                const auto& dialog_font = gui::drawing::font::dialog_font();

                p_log_font->lfHeight = -static_cast<::LONG>(dialog_font.size());
                p_log_font->lfWeight = dialog_font.bold() ? FW_BOLD : FW_NORMAL;
                p_log_font->lfItalic = dialog_font.italic() ? TRUE : FALSE;
                p_log_font->lfUnderline = dialog_font.underline() ? TRUE : FALSE;
                p_log_font->lfStrikeOut = dialog_font.strikeout() ? TRUE : FALSE;

                const auto native_face_name = detail::native_common_dialog_encoder().encode(dialog_font.family());
                const auto native_face_name_length = std::min<std::size_t>(native_face_name.length(), LF_FACESIZE - 1);
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

            return std::make_unique<windows_font_dialog_details_type>(
                reinterpret_cast<::HWND>(as_windows_widget_details(parent.details()).handle), std::move(p_log_font));
        }

        tetengo2::stdalt::optional<gui::drawing::font> show_font_dialog_impl(font_dialog_details_type& dialog) const
        {
            assert(dynamic_cast<windows_font_dialog_details_type*>(&dialog));
            auto&         windows_dialog = static_cast<windows_font_dialog_details_type&>(dialog);
            ::CHOOSEFONTW choose_font{};
            choose_font.lStructSize = sizeof(::CHOOSEFONTW);
            choose_font.hwndOwner = windows_dialog.parent_handle;
            choose_font.hDC = nullptr;
            choose_font.lpLogFont = windows_dialog.p_log_font.get();
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
                return TETENGO2_STDALT_NULLOPT;

            return tetengo2::stdalt::make_optional(
                gui::drawing::font{ detail::native_common_dialog_encoder().decode(choose_font.lpLogFont->lfFaceName),
                                    static_cast<type_list::size_type>(
                                        choose_font.lpLogFont->lfHeight < 0 ? -choose_font.lpLogFont->lfHeight :
                                                                              choose_font.lpLogFont->lfHeight),
                                    choose_font.lpLogFont->lfWeight >= FW_BOLD,
                                    choose_font.lpLogFont->lfItalic != FALSE,
                                    choose_font.lpLogFont->lfUnderline != FALSE,
                                    choose_font.lpLogFont->lfStrikeOut != FALSE });
        }

        color_dialog_details_ptr_type create_color_dialog_impl(
            gui::widget::abstract_window&                          parent,
            const tetengo2::stdalt::optional<gui::drawing::color>& color) const
        {
            const ::COLORREF native_color = color ? RGB(color->red(), color->green(), color->blue()) : 0;
            return std::make_unique<windows_color_dialog_details_type>(
                reinterpret_cast<::HWND>(as_windows_widget_details(parent.details()).handle), native_color);
        }

        tetengo2::stdalt::optional<gui::drawing::color> show_color_dialog_impl(color_dialog_details_type& dialog) const
        {
            assert(dynamic_cast<windows_color_dialog_details_type*>(&dialog));
            auto&                          windows_dialog = static_cast<windows_color_dialog_details_type&>(dialog);
            static std::vector<::COLORREF> custom_colors(16, RGB(0xFF, 0xFF, 0xFF));
            ::CHOOSECOLORW                 choose_color{};
            choose_color.lStructSize = sizeof(::CHOOSECOLORW);
            choose_color.hwndOwner = windows_dialog.parent_handle;
            choose_color.hInstance = nullptr;
            choose_color.rgbResult = windows_dialog.native_color;
            choose_color.lpCustColors = custom_colors.data();
            choose_color.Flags = CC_ANYCOLOR | CC_RGBINIT | CC_FULLOPEN;
            choose_color.lCustData = 0;
            choose_color.lpfnHook = nullptr;
            choose_color.lpTemplateName = nullptr;

            const auto result = ::ChooseColorW(&choose_color);
            if (result == FALSE)
                return TETENGO2_STDALT_NULLOPT;

            return tetengo2::stdalt::make_optional(gui::drawing::color{ GetRValue(choose_color.rgbResult),
                                                                        GetGValue(choose_color.rgbResult),
                                                                        GetBValue(choose_color.rgbResult) });
        }

    private:
        // types

        using widget_details_type = tetengo2::detail::windows::widget::widget_details_type;

        using windows_widget_details_type = tetengo2::detail::windows::widget::windows_widget_details_type;


        // static functions

        static const windows_widget_details_type& as_windows_widget_details(const widget_details_type& base)
        {
            assert(dynamic_cast<const windows_widget_details_type*>(&base));
            return static_cast<const windows_widget_details_type&>(base);
        }

        static windows_widget_details_type& as_windows_widget_details(widget_details_type& base)
        {
            assert(dynamic_cast<windows_widget_details_type*>(&base));
            return static_cast<windows_widget_details_type&>(base);
        }

        static std::vector<tetengo2::stdalt::optional<std::wstring>> to_custom_button_labels(
            const tetengo2::stdalt::optional<type_list::string_type>& ok_button_label,
            const tetengo2::stdalt::optional<std::pair<type_list::string_type, type_list::string_type>>&
                yes_no_button_labels)
        {
            std::vector<tetengo2::stdalt::optional<std::wstring>> labels{};
            labels.reserve(3);

            if (ok_button_label)
                labels.emplace_back(detail::native_common_dialog_encoder().encode(*ok_button_label));
            else
                labels.push_back(TETENGO2_STDALT_NULLOPT);

            if (yes_no_button_labels)
            {
                labels.emplace_back(detail::native_common_dialog_encoder().encode(yes_no_button_labels->first));
                labels.emplace_back(detail::native_common_dialog_encoder().encode(yes_no_button_labels->second));
            }
            else
            {
                labels.push_back(TETENGO2_STDALT_NULLOPT);
                labels.push_back(TETENGO2_STDALT_NULLOPT);
            }

            assert(labels.size() == 3);
            return labels;
        }

        static std::vector<::TASKDIALOG_BUTTON>
        make_custom_buttons(const std::vector<tetengo2::stdalt::optional<std::wstring>>& button_labels)
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
            const message_box_button_style_type                          style,
            const bool                                                   cancellable,
            const std::vector<tetengo2::stdalt::optional<std::wstring>>& custom_button_labels)
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

        static type_list::string_type
        to_default_extension(const std::vector<std::pair<type_list::string_type, type_list::string_type>>& filters)
        {
            return filters.empty() ? type_list::string_type{} : filters[0].second;
        }

        static detail::native_filter_type
        to_native_filter(const std::pair<type_list::string_type, type_list::string_type>& filter)
        {
            return { detail::native_common_dialog_encoder().encode(filter.first),
                     std::wstring{ L"*." } + detail::native_common_dialog_encoder().encode(filter.second) };
        }

        static detail::native_filters_type
        to_native_filters(const std::vector<std::pair<type_list::string_type, type_list::string_type>>& filters)
        {
            detail::native_filters_type native_filters;
            native_filters.reserve(filters.size());

            std::transform(
                filters.begin(),
                filters.end(),
                std::back_inserter(native_filters),
                [](const std::pair<type_list::string_type, type_list::string_type>& filter) {
                    return to_native_filter(filter);
                });

            return native_filters;
        }

        static ::COMDLG_FILTERSPEC to_filterspec(const detail::native_filter_type& native_filter)
        {
            ::COMDLG_FILTERSPEC filterspec{};

            filterspec.pszName = native_filter.first.c_str();
            filterspec.pszSpec = native_filter.second.c_str();

            return filterspec;
        }

        static bool
        match_extension(const tetengo2::stdalt::filesystem::path& path, const type_list::string_type& extension)
        {
            const auto path_string = path.template string<type_list::string_type::value_type>();
            const auto dotted_extension = type_list::string_type{ TETENGO2_TEXT(".") } + extension;
            if (path_string.length() < dotted_extension.length())
                return false;

            const type_list::string_type path_extension{ std::prev(path_string.end(), dotted_extension.length()),
                                                         path_string.end() };

            return path_extension == dotted_extension;
        }

        static std::size_t find_filter_index(
            const std::vector<std::pair<type_list::string_type, type_list::string_type>>& filters,
            const tetengo2::stdalt::optional<tetengo2::stdalt::filesystem::path>&         path)
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

        static std::vector<::COMDLG_FILTERSPEC> to_filterspecs(const detail::native_filters_type& native_filters)
        {
            std::vector<::COMDLG_FILTERSPEC> filterspecs{};
            filterspecs.reserve(native_filters.size());

            std::transform(
                native_filters.begin(), native_filters.end(), std::back_inserter(filterspecs), to_filterspec);

            return filterspecs;
        }

        static type_list::string_type
        to_native_path(const tetengo2::stdalt::optional<tetengo2::stdalt::filesystem::path>& path)
        {
            return path ? path->template string<type_list::string_type::value_type>() : type_list::string_type{};
        }
    };


    const common_dialog& common_dialog::instance()
    {
        return impl::instance();
    }

    common_dialog::~common_dialog() = default;

    common_dialog::common_dialog() : m_p_impl{ std::make_unique<impl>() } {}

    common_dialog::message_box_details_ptr_type common_dialog::create_message_box_impl(
        gui::widget::abstract_window&                      parent,
        type_list::string_type                             title,
        type_list::string_type                             main_content,
        type_list::string_type                             sub_content,
        const bool                                         cancellable,
        const message_box_button_style_type                button_style,
        const message_box_icon_style_type                  icon_style,
        tetengo2::stdalt::optional<type_list::string_type> custom_ok_button_label,
        tetengo2::stdalt::optional<std::pair<type_list::string_type, type_list::string_type>>
            custom_yes_no_button_labels) const
    {
        return m_p_impl->create_message_box_impl(
            parent,
            std::move(title),
            std::move(main_content),
            std::move(sub_content),
            cancellable,
            button_style,
            icon_style,
            std::move(custom_ok_button_label),
            std::move(custom_yes_no_button_labels));
    }

    common_dialog::message_box_button_id_type
    common_dialog::show_message_box_impl(message_box_details_type& message_box) const
    {
        return m_p_impl->show_message_box_impl(message_box);
    }

    common_dialog::file_open_dialog_details_ptr_type common_dialog::create_file_open_dialog_impl(
        gui::widget::abstract_window& parent,
        type_list::string_type        title,
        const filters_type&           filters) const
    {
        return m_p_impl->create_file_open_dialog_impl(parent, std::move(title), filters);
    }

    tetengo2::stdalt::optional<tetengo2::stdalt::filesystem::path>
    common_dialog::show_file_open_dialog_impl(file_open_dialog_details_type& dialog) const
    {
        return m_p_impl->show_file_open_dialog_impl(dialog);
    }

    common_dialog::file_save_dialog_details_ptr_type common_dialog::create_file_save_dialog_impl(
        gui::widget::abstract_window&                                         parent,
        type_list::string_type                                                title,
        const tetengo2::stdalt::optional<tetengo2::stdalt::filesystem::path>& path,
        const filters_type&                                                   filters) const
    {
        return m_p_impl->create_file_save_dialog_impl(parent, std::move(title), path, filters);
    }

    tetengo2::stdalt::optional<tetengo2::stdalt::filesystem::path>
    common_dialog::show_file_save_dialog_impl(file_save_dialog_details_type& dialog) const
    {
        return m_p_impl->show_file_save_dialog_impl(dialog);
    }

    common_dialog::font_dialog_details_ptr_type common_dialog::create_font_dialog_impl(
        gui::widget::abstract_window&                         parent,
        const tetengo2::stdalt::optional<gui::drawing::font>& font) const
    {
        return m_p_impl->create_font_dialog_impl(parent, font);
    }

    tetengo2::stdalt::optional<gui::drawing::font>
    common_dialog::show_font_dialog_impl(font_dialog_details_type& dialog) const
    {
        return m_p_impl->show_font_dialog_impl(dialog);
    }

    common_dialog::color_dialog_details_ptr_type common_dialog::create_color_dialog_impl(
        gui::widget::abstract_window&                          parent,
        const tetengo2::stdalt::optional<gui::drawing::color>& color) const
    {
        return m_p_impl->create_color_dialog_impl(parent, color);
    }

    tetengo2::stdalt::optional<gui::drawing::color>
    common_dialog::show_color_dialog_impl(color_dialog_details_type& dialog) const
    {
        return m_p_impl->show_color_dialog_impl(dialog);
    }
}
