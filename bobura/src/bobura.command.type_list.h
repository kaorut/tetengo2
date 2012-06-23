/*! \file
    \brief The definition of bobura::command::type.

    Copyright (C) 2007-2012 kaoru

    $Id$
*/

#if !defined(BOBURA_COMMAND_TYPELIST_H)
#define BOBURA_COMMAND_TYPELIST_H


namespace bobura { namespace command
{
    namespace type
    {
        struct command;               //!< The command type.
        struct about;                 //!< The about type.
        struct exit;                  //!< The exit type.
        struct file_property;         //!< The file property type.
        struct horizontally_zoom_in;  //!< The horizontal zoom-in type.
        struct horizontally_zoom_out; //!< The horizontal zoom-out type.
        struct load_from_file;        //!< The load-from-file type.
        struct new_file;              //!< The new-file type.
        struct nop;                   //!< The nop type.
        struct save_to_file;          //!< The save-to-file type.
    }


}}


#endif
