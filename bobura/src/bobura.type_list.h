/*! \file
    \brief The definition of bobura::type_list.

    Copyright (C) 2007-2010 kaoru

    $Id$
*/

#if !defined(BOBURA_TYPELIST_H)
#define BOBURA_TYPELIST_H

//#include <cstddef>
//#include <istream>
//#include <string>

//#include <boost/filesystem.hpp>
//#include <boost/mpl/at.hpp>
//#include <boost/mpl/insert_range.hpp>
#include <boost/mpl/pair.hpp>

//#define NOMINMAX
//#define OEMRESOURCE
//#include <windows.h>
//#if !defined(min) && !defined(DOCUMENTATION)
//#   define min(a, b) ((a) < (b) ? (a) : (b))
//#endif
//#if !defined(max) && !defined(DOCUMENTATION)
//#   define max(a, b) ((a) > (b) ? (a) : (b))
//#endif
//#include <gdiplus.h>
//#undef min
//#undef max

#include <tetengo2.encoder.h>
#include <tetengo2.messages.h>
#include <tetengo2.message_catalog_parser.h>
#include <tetengo2.encoding.locale.h>
#include <tetengo2.encoding.win32.utf8.h>
#include <tetengo2.gui.menu_observer.h>
#include <tetengo2.gui.mouse_observer.h>
#include <tetengo2.gui.paint_observer.h>
#include <tetengo2.gui.window_observer.h>
#include <tetengo2.gui.win32.abstract_popup_menu.h>
#include <tetengo2.gui.win32.abstract_window.h>
#include <tetengo2.gui.win32.alert.h>
#include <tetengo2.gui.win32.button.h>
#include <tetengo2.gui.win32.canvas.h>
#include <tetengo2.gui.win32.dialog.h>
#include <tetengo2.gui.win32.dialog_message_loop.h>
#include <tetengo2.gui.win32.font.h>
#include <tetengo2.gui.win32.gui_initializer_finalizer.h>
#include <tetengo2.gui.win32.main_menu.h>
#include <tetengo2.gui.win32.menu.h>
#include <tetengo2.gui.win32.menu_command.h>
#include <tetengo2.gui.win32.menu_separator.h>
#include <tetengo2.gui.win32.message_loop.h>
#include <tetengo2.gui.win32.popup_menu.h>
#include <tetengo2.gui.win32.quit_message_loop.h>
#include <tetengo2.gui.win32.widget.h>
#include <tetengo2.gui.win32.window.h>
#include <tetengo2.meta.assoc_list.h>

#include "bobura.about_dialog.h"
#include "bobura.bobura.h"
#include "bobura.main_window.h"
#include "bobura.settings.h"
#include "bobura.command.type_list.h"

#include "bobura.message.message_type_lists.h"


namespace bobura
{
    /**** Common ************************************************************/

    namespace type
    {
        struct difference;     //!< The difference type.
        struct size;           //!< The size type.
        struct string;         //!< The string type.
    }

    //! \return The common type list.
    typedef
        tetengo2::meta::assoc_list<
            boost::mpl::pair<type::difference, std::ptrdiff_t>,
        tetengo2::meta::assoc_list<
            boost::mpl::pair<type::size, std::size_t>,
        tetengo2::meta::assoc_list<
            boost::mpl::pair<type::string, std::wstring>,
        tetengo2::meta::assoc_list_end
        > > >
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
    }

#if !defined(DOCUMENTATION)
    namespace detail { namespace locale
    {
        typedef
            tetengo2::encoding::locale<
                boost::mpl::at<common_type_list, type::string>::type
            >
            internal_encoding_type;
        typedef tetengo2::encoding::locale<std::wstring> ui_encoding_type;
        typedef tetengo2::encoding::win32::utf8 exception_encoding_type;
        typedef
            tetengo2::encoding::win32::utf8 message_catalog_encoding_type;
        typedef
            tetengo2::encoding::locale<std::string>
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
    }}
#endif

    //! \return The type list for the locale.
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
                type::messages_facet,
                tetengo2::messages<
                    boost::filesystem::wpath,
                    detail::locale::message_catalog_parser_type,
                    detail::locale::locale_name_encoder_type
                >
            >,
        tetengo2::meta::assoc_list_end
        > > > > > >
        locale_type_list;


    /**** User Interface ****************************************************/

    namespace type
    {
        struct gui_initializer_finalizer; //!< The GUI initializer and
                                          //!< finalizer type.
        struct message_loop;   //!< The message loop type.
        struct quit_message_loop; //!< The quit-message-loop type.
        struct canvas;         //!< The canvas type.
        struct alert;          //!< The alert type.
        struct window;         //!< The window type.
        struct popup_menu;     //!< The popup menu type.
        struct menu_command;   //!< The menu command type.
        struct menu_separator; //!< The menu separator type;
        struct dialog;         //!< The dialog type.
        struct button;         //!< The button type.
    }

#if !defined(DOCUMENTATION)
    namespace detail { namespace ui
    {
        typedef
            tetengo2::gui::win32::quit_message_loop quit_message_loop_type;
        typedef
            tetengo2::gui::win32::font<
                boost::mpl::at<common_type_list, type::string>::type,
                boost::mpl::at<common_type_list, type::size>::type
            >
            font_type;
        typedef
            tetengo2::gui::win32::canvas<
                const Gdiplus::Graphics*,
                boost::mpl::at<common_type_list, type::size>::type,
                boost::mpl::at<common_type_list, type::string>::type,
                boost::mpl::at<locale_type_list, type::ui_encoder>::type,
                ::HWND,
                detail::ui::font_type
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
            tetengo2::gui::win32::widget<
                ::HWND,
                canvas_type,
                alert_type,
                boost::mpl::at<common_type_list, type::difference>::type,
                boost::mpl::at<common_type_list, type::size>::type,
                boost::mpl::at<common_type_list, type::string>::type,
                boost::mpl::at<locale_type_list, type::ui_encoder>::type,
                font_type,
                tetengo2::gui::paint_observer<canvas_type>,
                tetengo2::gui::mouse_observer
            >
            widget_type;
        typedef
            tetengo2::gui::win32::menu<
                ::UINT,
                ::HMENU,
                boost::mpl::at<common_type_list, type::string>::type,
                boost::mpl::at<locale_type_list, type::ui_encoder>::type,
                tetengo2::gui::menu_observer
            >
            menu_type;
        typedef
            tetengo2::gui::win32::abstract_popup_menu<menu_type>
            abstract_popup_menu_type;
        typedef
            tetengo2::gui::win32::main_menu<abstract_popup_menu_type>
            main_menu_type;
        typedef
            tetengo2::gui::win32::abstract_window<
                widget_type, main_menu_type, tetengo2::gui::window_observer
            >
            abstract_window_type;
        typedef
            tetengo2::gui::win32::dialog_message_loop
            dialog_message_loop_type;
    }}
#endif

    //! \return The type list for the user interface.
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
            boost::mpl::pair<type::canvas, detail::ui::canvas_type>,
        tetengo2::meta::assoc_list<
            boost::mpl::pair<type::alert, detail::ui::alert_type>,
        tetengo2::meta::assoc_list<
            boost::mpl::pair<
                type::window,
                tetengo2::gui::win32::window<detail::ui::abstract_window_type>
            >,
        tetengo2::meta::assoc_list<
            boost::mpl::pair<
                type::popup_menu,
                tetengo2::gui::win32::popup_menu<
                    detail::ui::abstract_popup_menu_type
                >
            >,
        tetengo2::meta::assoc_list<
            boost::mpl::pair<
                type::menu_command,
                tetengo2::gui::win32::menu_command<detail::ui::menu_type>
            >,
        tetengo2::meta::assoc_list<
            boost::mpl::pair<
                type::menu_separator,
                tetengo2::gui::win32::menu_separator<detail::ui::menu_type>
            >,
        tetengo2::meta::assoc_list<
            boost::mpl::pair<
                type::dialog,
                tetengo2::gui::win32::dialog<
                    detail::ui::abstract_window_type,
                    detail::ui::dialog_message_loop_type,
                    detail::ui::quit_message_loop_type
                >
            >,
        tetengo2::meta::assoc_list<
            boost::mpl::pair<
                type::button,
                tetengo2::gui::win32::button<detail::ui::widget_type>
            >,
        tetengo2::meta::assoc_list_end
        > > > > > > > > > > >
        ui_type_list;


    /**** About Dialog ******************************************************/

    namespace type
    {
        struct about_dialog;   //! The about dialog type.
    }

    typedef
        tetengo2::meta::assoc_list<
            boost::mpl::pair<
                type::about_dialog,
                about_dialog<
                    boost::mpl::at<ui_type_list, type::dialog>::type,
                    boost::mpl::at<ui_type_list, type::button>::type,
                    message::about_dialog_message_type_list<
                        boost::mpl::at<ui_type_list, type::dialog>::type
                    >
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
            message::main_window_message_type_list<
                boost::mpl::at<
                    command_type_list, command::type::command
                >::type,
                boost::mpl::at<ui_type_list, type::canvas>::type,
                boost::mpl::at<ui_type_list, type::quit_message_loop>::type
            >
            message_type_list_type;
    }}
#endif

    typedef
        tetengo2::meta::assoc_list<
            boost::mpl::pair<
                type::main_window,
                main_window<
                    boost::mpl::at<ui_type_list, type::window>::type,
                    boost::mpl::at<
                        ui_type_list, type::quit_message_loop
                    >::type,
                    boost::mpl::at<ui_type_list, type::menu_command>::type,
                    boost::mpl::at<ui_type_list, type::popup_menu>::type,
                    boost::mpl::at<ui_type_list, type::menu_separator>::type,
                    detail::main_window::command_type_list,
                    detail::main_window::message_type_list_type
                >
            >,
        tetengo2::meta::assoc_list_end
        > 
        main_window_type_list;


    /**** The Application ***************************************************/

    namespace type
    {
        struct settings;       //! The settings type.
        struct application;    //! The application type.
    }

#if !defined(DOCUMENTATION)
    namespace detail { namespace application
    {
        typedef
            settings<boost::mpl::at<common_type_list, type::string>::type>
            settings_type;
    }}
#endif

    typedef
        tetengo2::meta::assoc_list<
            boost::mpl::pair<
                type::settings,
                detail::application::settings_type
            >,
        tetengo2::meta::assoc_list<
            boost::mpl::pair<
                type::application,
                bobura<
                    detail::application::settings_type,
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
        > >
        bobura_type_list;


    /**** All ***************************************************************/

    //! \return The type list for Bobura.
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
