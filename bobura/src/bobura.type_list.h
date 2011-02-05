/*! \file
    \brief The definition of bobura::type_list.

    Copyright (C) 2007-2011 kaoru

    $Id$
*/

#if !defined(BOBURA_TYPELIST_H)
#define BOBURA_TYPELIST_H

//#include <cstddef>
#include <istream>
//#include <string>
//#include <utility>

//#define BOOST_FILESYSTEM_VERSION 3
//#include <boost/filesystem.hpp>
//#include <boost/mpl/at.hpp>
//#include <boost/mpl/insert_range.hpp>
//#include <boost/mpl/pair.hpp>
//#include <boost/rational.hpp>

//#define NOMINMAX
//#define OEMRESOURCE
//#include <Windows.h>
//#if !defined(min) && !defined(DOCUMENTATION)
//#   define min(a, b) ((a) < (b) ? (a) : (b))
//#endif
//#if !defined(max) && !defined(DOCUMENTATION)
//#   define max(a, b) ((a) > (b) ? (a) : (b))
//#endif
//#include <GdiPlus.h>
//#undef min
//#undef max

#include <tetengo2.encoder.h>
#include <tetengo2.messages.h>
#include <tetengo2.message_catalog.h>
#include <tetengo2.message_catalog_parser.h>
#include <tetengo2.detail.windows.encoding.h>
#include <tetengo2.detail.windows.gdiplus.drawing.h>
#include <tetengo2.detail.windows.unit.h>
#include <tetengo2.encoding.locale.h>
#include <tetengo2.encoding.utf8.h>
#include <tetengo2.gui.drawing.background.h>
#include <tetengo2.gui.drawing.color.h>
#include <tetengo2.gui.drawing.font.h>
#include <tetengo2.gui.drawing.transparent_background.h>
#include <tetengo2.gui.drawing.win32.gdiplus.picture.h>
#include <tetengo2.gui.drawing.win32.gdiplus.picture_reader.h>
#include <tetengo2.gui.drawing.win32.gdiplus.widget_canvas.h>
#include <tetengo2.gui.menu_observer_set.h>
#include <tetengo2.gui.mouse_observer_set.h>
#include <tetengo2.gui.paint_observer_set.h>
#include <tetengo2.gui.traits.abstract_window_traits.h>
#include <tetengo2.gui.traits.button_traits.h>
#include <tetengo2.gui.traits.control_traits.h>
#include <tetengo2.gui.traits.dialog_traits.h>
#include <tetengo2.gui.traits.image_traits.h>
#include <tetengo2.gui.traits.label_traits.h>
#include <tetengo2.gui.traits.menu_traits.h>
#include <tetengo2.gui.traits.widget_traits.h>
#include <tetengo2.gui.traits.window_traits.h>
#include <tetengo2.gui.unit.em.h>
#include <tetengo2.gui.win32.abstract_popup_menu.h>
#include <tetengo2.gui.win32.abstract_window.h>
#include <tetengo2.gui.win32.alert.h>
#include <tetengo2.gui.win32.button.h>
#include <tetengo2.gui.win32.dialog.h>
#include <tetengo2.gui.win32.dialog_message_loop.h>
#include <tetengo2.gui.win32.gui_initializer_finalizer.h>
#include <tetengo2.gui.win32.image.h>
#include <tetengo2.gui.win32.label.h>
#include <tetengo2.gui.win32.main_menu.h>
#include <tetengo2.gui.win32.menu.h>
#include <tetengo2.gui.win32.menu_command.h>
#include <tetengo2.gui.win32.menu_separator.h>
#include <tetengo2.gui.win32.message_loop.h>
#include <tetengo2.gui.win32.popup_menu.h>
#include <tetengo2.gui.win32.quit_message_loop.h>
#include <tetengo2.gui.win32.widget.h>
#include <tetengo2.gui.win32.window.h>
#include <tetengo2.gui.window_observer_set.h>
#include <tetengo2.meta.assoc_list.h>

#include "bobura.about_dialog.h"
#include "bobura.bobura.h"
#include "bobura.main_window.h"
#include "bobura.settings.h"
#include "bobura.command.type_list_impl.h"
#include "bobura.message.type_list_impl.h"


namespace bobura
{
    /**** Common ************************************************************/

    namespace type
    {
        struct difference;     //!< The difference type.
        struct size;           //!< The size type.
        struct string;         //!< The string type.
        struct path;           //!< The path type.
        struct settings;       //! The settings type.
    }

#if !defined(DOCUMENTATION)
    namespace detail { namespace common
    {
        typedef std::wstring string_type;
        typedef boost::filesystem::path path_type;
        typedef settings<string_type, path_type> settings_type;
    }}
#endif

    //! The common type list.
    typedef
        tetengo2::meta::assoc_list<
            boost::mpl::pair<type::difference, std::ptrdiff_t>,
        tetengo2::meta::assoc_list<
            boost::mpl::pair<type::size, std::size_t>,
        tetengo2::meta::assoc_list<
            boost::mpl::pair<type::string, detail::common::string_type>,
        tetengo2::meta::assoc_list<
            boost::mpl::pair<type::path, detail::common::path_type>,
        tetengo2::meta::assoc_list<
            boost::mpl::pair<type::settings, detail::common::settings_type>,
        tetengo2::meta::assoc_list_end
        >>>>>
        common_type_list;


    /**** Locale ************************************************************/

    namespace type
    {
        struct ui_encoder;     //!< The encoder type for the user interface.
        struct exception_encoder; //!< The encoder type for exceptions.
        struct message_catalog_encoder; //!< The encoder type for the
                                        //!< message catalog.
        struct locale_name_encoder; //!< The encoder type for locale names.

        struct message_catalog_parser; //!< The message catalog parser type.
        struct messages_facet; //!< The messages facet type.
        struct message_catalog; //!< The message catalog type.
    }

#if !defined(DOCUMENTATION)
    namespace detail { namespace locale
    {
        typedef tetengo2::detail::windows::encoding encoding_details_type;
        typedef
            tetengo2::encoding::locale<
                boost::mpl::at<common_type_list, type::string>::type,
                encoding_details_type
            >
            internal_encoding_type;
        typedef
            tetengo2::encoding::locale<std::wstring, encoding_details_type>
            ui_encoding_type;
        typedef
            tetengo2::encoding::utf8<encoding_details_type>
            exception_encoding_type;
        typedef
            tetengo2::encoding::utf8<encoding_details_type>
            message_catalog_encoding_type;
        typedef
            tetengo2::encoding::locale<std::string, encoding_details_type>
            locale_name_encoding_type;
        typedef
            tetengo2::encoder<
                internal_encoding_type, message_catalog_encoding_type
            >
            message_catalog_encoder_type;
        typedef
            tetengo2::message_catalog_parser<
                std::istream,
                boost::mpl::at<common_type_list, type::string>::type,
                message_catalog_encoder_type
            >
            message_catalog_parser_type;
        typedef
            tetengo2::encoder<
                internal_encoding_type, locale_name_encoding_type
            >
            locale_name_encoder_type;
        typedef
            tetengo2::messages<
                boost::mpl::at<common_type_list, type::path>::type,
                message_catalog_parser_type,
                locale_name_encoder_type
            >
            messages_type;
    }}
#endif

    //! The type list for the locale.
    typedef
        tetengo2::meta::assoc_list<
            boost::mpl::pair<
                type::ui_encoder,
                tetengo2::encoder<
                    detail::locale::internal_encoding_type,
                    detail::locale::ui_encoding_type
                >
            >,
        tetengo2::meta::assoc_list<
            boost::mpl::pair<
                type::exception_encoder,
                tetengo2::encoder<
                    detail::locale::internal_encoding_type,
                    detail::locale::exception_encoding_type
                >
            >,
        tetengo2::meta::assoc_list<
            boost::mpl::pair<
                type::message_catalog_encoder,
                detail::locale::message_catalog_encoder_type
            >,
        tetengo2::meta::assoc_list<
            boost::mpl::pair<
                type::locale_name_encoder,
                detail::locale::locale_name_encoder_type
            >,
        tetengo2::meta::assoc_list<
            boost::mpl::pair<
                type::message_catalog_parser,
                detail::locale::message_catalog_parser_type
            >,
        tetengo2::meta::assoc_list<
            boost::mpl::pair<
                type::messages_facet, detail::locale::messages_type
            >,
        tetengo2::meta::assoc_list<
            boost::mpl::pair<
                type::message_catalog,
                tetengo2::message_catalog<detail::locale::messages_type>
            >,
        tetengo2::meta::assoc_list_end
        >>>>>>>
        locale_type_list;


    /**** User Interface ****************************************************/

    namespace type
    {
        struct gui_initializer_finalizer; //!< The GUI initializer and
                                          //!< finalizer type.
        struct message_loop;   //!< The message loop type.
        struct quit_message_loop; //!< The quit-message-loop type.
        struct position;       //!< The position type.
        struct dimension;      //!< The dimension type.
        struct picture;        //!< The picture type.
        struct picture_reader; //!< The picture reader type.
        struct canvas;         //!< The canvas type.
        struct alert;          //!< The alert type.
        struct window;         //!< The window type.
        struct popup_menu;     //!< The popup menu type.
        struct menu_command;   //!< The menu command type.
        struct menu_separator; //!< The menu separator type;
        struct dialog;         //!< The dialog type.
        struct label;          //!< The label type.
        struct image;          //!< The image type.
        struct button;         //!< The button type.
        struct transparent_background; //!< The transparent background type.
    }

#if !defined(DOCUMENTATION)
    namespace detail { namespace ui
    {
        typedef
            tetengo2::gui::win32::quit_message_loop quit_message_loop_type;
        typedef tetengo2::detail::windows::unit unit_details_type;
        typedef
            tetengo2::gui::unit::em<
                boost::rational<
                    boost::mpl::at<common_type_list, type::difference>::type
                >,
                boost::mpl::at<common_type_list, type::difference>::type,
                unit_details_type
            >
            unit_difference_type;
        typedef
            std::pair<unit_difference_type, unit_difference_type>
            position_type;
        typedef
            tetengo2::gui::unit::em<
                boost::rational<
                    boost::mpl::at<common_type_list, type::size>::type
                >,
                boost::mpl::at<common_type_list, type::size>::type,
                unit_details_type
            >
            unit_size_type;
        typedef std::pair<unit_size_type, unit_size_type> dimension_type;
        typedef
            tetengo2::detail::windows::gdiplus::drawing drawing_details_type;
        typedef
            tetengo2::gui::drawing::background<drawing_details_type>
            background_type;
        typedef
            tetengo2::gui::drawing::transparent_background<
                drawing_details_type
            >
            transparent_background_type;
        typedef
            tetengo2::gui::drawing::font<
                boost::mpl::at<common_type_list, type::string>::type,
                boost::mpl::at<common_type_list, type::size>::type,
                drawing_details_type
            >
            font_type;
        typedef
            tetengo2::gui::drawing::win32::gdiplus::picture<unit_size_type>
            picture_type;
        typedef
            tetengo2::gui::drawing::win32::gdiplus::picture_reader<
                picture_type,
                boost::mpl::at<common_type_list, type::path>::type
            >
            picture_reader_type;
        typedef
            tetengo2::gui::drawing::win32::gdiplus::widget_canvas<
                const Gdiplus::Graphics*,
                boost::mpl::at<common_type_list, type::size>::type,
                boost::mpl::at<common_type_list, type::string>::type,
                dimension_type,
                boost::mpl::at<locale_type_list, type::ui_encoder>::type,
                background_type,
                font_type,
                picture_type
            >
            canvas_type;
        typedef
            tetengo2::gui::win32::alert<
                ::HWND,
                boost::mpl::at<locale_type_list, type::ui_encoder>::type,
                boost::mpl::at<
                    locale_type_list, type::exception_encoder
                >::type
            >
            alert_type;
        typedef
            tetengo2::gui::traits::widget_traits<
                ::HWND,
                canvas_type,
                alert_type,
                position_type,
                dimension_type,
                boost::mpl::at<common_type_list, type::string>::type,
                boost::mpl::at<locale_type_list, type::ui_encoder>::type,
                background_type,
                font_type,
                tetengo2::gui::paint_observer_set<canvas_type>,
                tetengo2::gui::mouse_observer_set
            >
            widget_traits_type;
        typedef tetengo2::gui::win32::widget<widget_traits_type> widget_type;
        typedef
            tetengo2::gui::traits::menu_traits<
                ::UINT,
                ::HMENU,
                boost::mpl::at<common_type_list, type::string>::type,
                boost::mpl::at<locale_type_list, type::ui_encoder>::type,
                tetengo2::gui::menu_observer_set
            >
            menu_traits_type;
        typedef tetengo2::gui::win32::menu<menu_traits_type> menu_type;
        typedef
            tetengo2::gui::win32::abstract_popup_menu<menu_traits_type>
            abstract_popup_menu_type;
        typedef
            tetengo2::gui::win32::main_menu<menu_traits_type> main_menu_type;
        typedef
            tetengo2::gui::traits::abstract_window_traits<
                widget_traits_type,
                main_menu_type,
                tetengo2::gui::window_observer_set
            >
            abstract_window_traits_type;
        typedef
            tetengo2::gui::win32::abstract_window<abstract_window_traits_type>
            abstract_window_type;
        typedef
            tetengo2::gui::traits::window_traits<abstract_window_traits_type>
            window_traits_type;
        typedef tetengo2::gui::win32::window<window_traits_type> window_type;
        typedef
            tetengo2::gui::traits::dialog_traits<
                abstract_window_traits_type,
                tetengo2::gui::win32::dialog_message_loop,
                quit_message_loop_type
            >
            dialog_traits_type;
        typedef tetengo2::gui::win32::dialog<dialog_traits_type> dialog_type;
        typedef tetengo2::gui::drawing::color<unsigned char> color_type;
        typedef
            tetengo2::gui::traits::control_traits<
                widget_traits_type, color_type
            >
            control_traits_type;
        typedef
            tetengo2::gui::traits::label_traits<control_traits_type>
            label_traits_type;
        typedef tetengo2::gui::win32::label<label_traits_type> label_type;
        typedef
            tetengo2::gui::traits::image_traits<
                control_traits_type, picture_type
            >
            image_traits_type;
        typedef tetengo2::gui::win32::image<image_traits_type> image_type;
        typedef
            tetengo2::gui::traits::button_traits<control_traits_type>
            button_traits_type;
        typedef tetengo2::gui::win32::button<button_traits_type> button_type;
    }}
#endif

    //! The type list for the user interface.
    typedef
        tetengo2::meta::assoc_list<
            boost::mpl::pair<
                type::gui_initializer_finalizer,
                tetengo2::gui::win32::gui_initializer_finalizer
            >,
        tetengo2::meta::assoc_list<
            boost::mpl::pair<
                type::message_loop, tetengo2::gui::win32::message_loop
            >,
        tetengo2::meta::assoc_list<
            boost::mpl::pair<
                type::quit_message_loop, detail::ui::quit_message_loop_type
            >,
        tetengo2::meta::assoc_list<
            boost::mpl::pair<type::position, detail::ui::position_type>,
        tetengo2::meta::assoc_list<
            boost::mpl::pair<type::dimension, detail::ui::dimension_type>,
        tetengo2::meta::assoc_list<
            boost::mpl::pair<type::picture, detail::ui::picture_type>,
        tetengo2::meta::assoc_list<
            boost::mpl::pair<
                type::picture_reader, detail::ui::picture_reader_type
            >,
        tetengo2::meta::assoc_list<
            boost::mpl::pair<type::canvas, detail::ui::canvas_type>,
        tetengo2::meta::assoc_list<
            boost::mpl::pair<type::alert, detail::ui::alert_type>,
        tetengo2::meta::assoc_list<
            boost::mpl::pair<type::window, detail::ui::window_type>,
        tetengo2::meta::assoc_list<
            boost::mpl::pair<
                type::popup_menu,
                tetengo2::gui::win32::popup_menu<detail::ui::menu_traits_type>
            >,
        tetengo2::meta::assoc_list<
            boost::mpl::pair<
                type::menu_command,
                tetengo2::gui::win32::menu_command<
                    detail::ui::menu_traits_type
                >
            >,
        tetengo2::meta::assoc_list<
            boost::mpl::pair<
                type::menu_separator,
                tetengo2::gui::win32::menu_separator<
                    detail::ui::menu_traits_type
                >
            >,
        tetengo2::meta::assoc_list<
            boost::mpl::pair<type::dialog, detail::ui::dialog_type>,
        tetengo2::meta::assoc_list<
            boost::mpl::pair<type::label, detail::ui::label_type>,
        tetengo2::meta::assoc_list<
            boost::mpl::pair<type::image, detail::ui::image_type>,
        tetengo2::meta::assoc_list<
            boost::mpl::pair<type::button, detail::ui::button_type>,
        tetengo2::meta::assoc_list<
            boost::mpl::pair<
                type::transparent_background,
                detail::ui::transparent_background_type
            >,
        tetengo2::meta::assoc_list_end
        >>>>>>>>>>>>>>>>>>
        ui_type_list;


    /**** About Dialog ******************************************************/

    namespace type
    {
        struct about_dialog;   //! The about dialog type.
    }

    //! The type list for the about dialog.
    typedef
        tetengo2::meta::assoc_list<
            boost::mpl::pair<
                type::about_dialog,
                about_dialog<
                    boost::mpl::at<ui_type_list, type::dialog>::type,
                    boost::mpl::at<
                        locale_type_list, type::message_catalog
                    >::type,
                    boost::mpl::at<common_type_list, type::settings>::type,
                    boost::mpl::at<ui_type_list, type::label>::type,
                    boost::mpl::at<ui_type_list, type::image>::type,
                    boost::mpl::at<ui_type_list, type::button>::type,
                    boost::mpl::at<ui_type_list, type::picture_reader>::type,
                    boost::mpl::at<
                        ui_type_list, type::transparent_background
                    >::type,
                    message::about_dialog::type_list<
                        boost::mpl::at<ui_type_list, type::dialog>::type
                    >::type
                >
            >,
        tetengo2::meta::assoc_list_end
        > 
        about_dialog_type_list;


    /**** Main Window *******************************************************/

    namespace type
    {
        struct main_window;    //! The main window type.
    }

#if !defined(DOCUMENTATION)
    namespace detail { namespace main_window
    {
        typedef
            command::type_list<
                boost::mpl::at<ui_type_list, type::window>::type,
                boost::mpl::at<
                    about_dialog_type_list, type::about_dialog
                >::type
            >::type
            command_type_list;
        typedef
            message::main_window::type_list<
                boost::mpl::at<
                    command_type_list, command::type::command
                >::type,
                boost::mpl::at<ui_type_list, type::canvas>::type,
                boost::mpl::at<ui_type_list, type::position>::type,
                boost::mpl::at<ui_type_list, type::picture_reader>::type
            >::type
            message_type_list;
    }}
#endif

    //! The type list for the main window.
    typedef
        tetengo2::meta::assoc_list<
            boost::mpl::pair<
                type::main_window,
                main_window<
                    boost::mpl::at<ui_type_list, type::window>::type,
                    boost::mpl::at<
                        locale_type_list, type::message_catalog
                    >::type,
                    boost::mpl::at<common_type_list, type::settings>::type,
                    boost::mpl::at<
                        ui_type_list, type::quit_message_loop
                    >::type,
                    boost::mpl::at<ui_type_list, type::menu_command>::type,
                    boost::mpl::at<ui_type_list, type::popup_menu>::type,
                    boost::mpl::at<ui_type_list, type::menu_separator>::type,
                    detail::main_window::command_type_list,
                    detail::main_window::message_type_list
                >
            >,
        tetengo2::meta::assoc_list_end
        > 
        main_window_type_list;


    /**** The Application ***************************************************/

    namespace type
    {
        struct application;    //! The application type.
    }

    //! The type list for the application.
    typedef
        tetengo2::meta::assoc_list<
            boost::mpl::pair<
                type::application,
                bobura<
                    boost::mpl::at<common_type_list, type::settings>::type,
                    boost::mpl::at<
                        locale_type_list, type::message_catalog
                    >::type,
                    boost::mpl::at<
                        main_window_type_list, type::main_window
                    >::type,
                    boost::mpl::at<ui_type_list, type::message_loop>::type,
                    boost::mpl::at<
                        ui_type_list, type::quit_message_loop
                    >::type,
                    boost::mpl::at<
                        ui_type_list, type::gui_initializer_finalizer
                    >::type
                >
            >,
        tetengo2::meta::assoc_list_end
        >
        bobura_type_list;


    /**** All ***************************************************************/

    //! The type list for Bobura.
    typedef
        boost::mpl::insert_range<
            common_type_list, tetengo2::meta::assoc_list_end,
        boost::mpl::insert_range<
            locale_type_list, tetengo2::meta::assoc_list_end,
        boost::mpl::insert_range<
            ui_type_list, tetengo2::meta::assoc_list_end,
        boost::mpl::insert_range<
            about_dialog_type_list, tetengo2::meta::assoc_list_end,
        boost::mpl::insert_range<
            main_window_type_list, tetengo2::meta::assoc_list_end,
        boost::mpl::insert_range<
            bobura_type_list, tetengo2::meta::assoc_list_end,
        tetengo2::meta::assoc_list_end
        >::type>::type>::type>::type>::type>::type
        type_list;


}


#endif
