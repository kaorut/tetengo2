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

#include <tetengo2.encoder.h>
#include <tetengo2.messages.h>
#include <tetengo2.message_catalog_parser.h>
#include <tetengo2.encoding.locale.h>
#include <tetengo2.encoding.win32.utf8.h>
#include <tetengo2.gui.win32.gui_type_list.h>

#include "bobura.about_dialog.h"
#include "bobura.bobura.h"
#include "bobura.main_window.h"
#include "bobura.settings.h"
#include "bobura.command.command_type_list.h"
#include "bobura.message.message_type_lists.h"


namespace bobura
{
    /*!
        \brief The class for a type list of bobura.
    */
    class type_list
    {
    public:
        // types

        //! \return The difference type.
        typedef std::ptrdiff_t difference_type;

        //! \return The size type.
        typedef std::size_t size_type;

        //! \return The string type.
        typedef std::wstring string_type;

        //! \return The internal encoding type.
        typedef
            tetengo2::encoding::locale<string_type> internal_encoding_type;

        //! \return The encoding type.for the user interface.
        typedef
            tetengo2::encoding::locale<std::wstring> ui_encoding_type;

        //! \return The encoding type.for exceptions.
        typedef tetengo2::encoding::win32::utf8 exception_encoding_type;

        //! \return The message catalog type.for the message catalog.
        typedef tetengo2::encoding::win32::utf8 message_catalog_encoding_type;

        //! \return The encoding type.for locale names.
        typedef
            tetengo2::encoding::locale<std::string> locale_name_encoding_type;

        //! \return The encoder type.for the user interface.
        typedef
            tetengo2::encoder<internal_encoding_type, ui_encoding_type>
            ui_encoder_type;

        //! \return The encoder type.for exceptions.
        typedef
            tetengo2::encoder<internal_encoding_type, exception_encoding_type>
            exception_encoder_type;

        //! \return The encoder type.for the message catalog.
        typedef
            tetengo2::encoder<
                internal_encoding_type, message_catalog_encoding_type
            >
            message_catalog_encoder_type;

        //! \return The encoder type.for locale names.
        typedef
            tetengo2::encoder<
                internal_encoding_type, locale_name_encoding_type
            >
            locale_name_encoder_type;

        //! \return The message catalog parser type.
        typedef
            tetengo2::message_catalog_parser<
                std::istream, string_type, message_catalog_encoder_type
            >
            message_catalog_parser_type;

        //! \return The messages facet type.
        typedef
            tetengo2::messages<
                boost::filesystem::wpath,
                message_catalog_parser_type,
                locale_name_encoder_type
            >
            messages_type;

        //! \return The type list type.to create platform specific GUI components.
        typedef
            tetengo2::gui::win32::gui_type_list<
                difference_type,
                size_type,
                string_type,
                ui_encoder_type,
                exception_encoder_type
            >
            gui_type_list_type;

        //! \return The GUI initialization and finalization manager type.
        typedef
            gui_type_list_type::gui_initializer_finalizer_type
            gui_initializer_finalizer_type;

        //! \return The binary functor type.of the alert.
        typedef gui_type_list_type::alert_type alert_type;

        //! \return The settings type.
        typedef settings<string_type> settings_type;

        //! \return The about dialog message type list type.
        typedef
            message::about_dialog_message_type_list<
                typename gui_type_list_type::dialog_type
            >
            about_dialog_message_type_list_type;


        //! \return The about dialog type.
        typedef
            about_dialog<
                typename gui_type_list_type::dialog_type,
                typename gui_type_list_type::button_type,
                about_dialog_message_type_list_type
            >
            about_dialog_type;

        //! \return The command type list type.
        typedef
            command::command_type_list<
                typename gui_type_list_type::window_type, about_dialog_type
            >
            command_type_list_type;

        //! \return The message type list type.
        typedef
            message::main_window_message_type_list<
                typename command_type_list_type::command_type,
                typename gui_type_list_type::canvas_type,
                typename gui_type_list_type::quit_message_loop_type
            >
            main_window_message_type_list_type;

        //! \return The main window type.
        typedef
            main_window<
                gui_type_list_type,
                command_type_list_type,
                main_window_message_type_list_type
            >
            main_window_type;

        //! \return The Bobura application type.
        typedef
            bobura<settings_type, main_window_type, gui_type_list_type>
            bobura_type;


    private:
        // forbidden operations

        type_list();


    };


}

#endif
