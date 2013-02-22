/*! \file
    \brief The definition of bobura::type_list.

    Copyright (C) 2007-2013 kaoru

    $Id$
*/

#if !defined(BOBURA_TYPELIST_H)
#define BOBURA_TYPELIST_H

//#include <boost/mpl/at.hpp>
//#include <boost/mpl/pair.hpp>

#include <tetengo2.meta.assoc_list.h>

#include "bobura.basic_type_list.h"
#include "bobura.command.command_base.h"
#include "bobura.command.set.h"
#include "bobura.diagram_picture_box.h"
#include "bobura.main_window.h"
#include "bobura.message.type_list_impl.h"
#include "bobura.view.diagram.zoom.h"


namespace bobura
{
    /**** Main Window *******************************************************/

    namespace type { namespace main_window
    {
        struct command_set;    //!< The command set type.
        struct main_window;    //!< The main window type.
        struct message_type_list; //!< The main window message type list type.
        struct diagram_picture_box;
        struct diagram_picture_box_message_type_list; //!< The diagram picture box message type list type.
    }}

#if !defined(DOCUMENTATION)
    namespace detail { namespace main_window
    {
        typedef
            message::diagram_picture_box::type_list<
                boost::mpl::at<ui_type_list, type::ui::picture_box>::type,
                boost::mpl::at<view_type_list, type::view::view>::type,
                bobura::view::diagram::zoom,
                boost::mpl::at<ui_type_list, type::ui::fast_canvas>::type
            >::type
            diagram_picture_box_message_type_list;
        typedef
            diagram_picture_box<
                boost::mpl::at<ui_type_list, type::ui::picture_box>::type,
                boost::mpl::at<ui_type_list, type::ui::abstract_window>::type,
                diagram_picture_box_message_type_list
            >
            diagram_picture_box_type;
        typedef
            message::main_window::type_list<
                boost::mpl::at<ui_type_list, type::ui::popup_menu>::type,
                command::command_base,
                boost::mpl::at<model_type_list, type::model::model>::type,
                boost::mpl::at<view_type_list, type::view::view>::type,
                boost::mpl::at<ui_type_list, type::ui::abstract_window>::type,
                diagram_picture_box_type,
                boost::mpl::at<load_save_type_list, type::load_save::confirm_file_save>::type,
                boost::mpl::at<setting_type_list, type::setting::settings>::type
            >::type
            main_window_message_type_list;
    }}
#endif

    //! The type list for the main window.
    typedef
        tetengo2::meta::assoc_list<
            boost::mpl::pair<type::main_window::command_set, command::set>,
        tetengo2::meta::assoc_list<
            boost::mpl::pair<
                type::main_window::main_window,
                main_window<
                    boost::mpl::at<ui_type_list, type::ui::window>::type,
                    boost::mpl::at<locale_type_list, type::locale::message_catalog>::type,
                    detail::main_window::diagram_picture_box_type,
                    boost::mpl::at<setting_type_list, type::setting::settings>::type,
                    boost::mpl::at<load_save_type_list, type::load_save::confirm_file_save>::type
                >
            >,
        tetengo2::meta::assoc_list<
            boost::mpl::pair<type::main_window::message_type_list, detail::main_window::main_window_message_type_list>,
        tetengo2::meta::assoc_list<
            boost::mpl::pair<type::main_window::diagram_picture_box, detail::main_window::diagram_picture_box_type>,
        tetengo2::meta::assoc_list<
            boost::mpl::pair<
                type::main_window::diagram_picture_box_message_type_list,
                detail::main_window::diagram_picture_box_message_type_list
            >,
        tetengo2::meta::assoc_list_end
        >>>>>
        main_window_type_list;


    /**** The Application ***************************************************/

    namespace type { namespace application
    {
        struct model_message_type_list; //!< The model message type list type.
    }}

    //! The type list for the application.
    typedef
        tetengo2::meta::assoc_list<
            boost::mpl::pair<
                type::application::model_message_type_list,
                message::timetable_model::type_list<
                    boost::mpl::at<model_type_list, type::model::model>::type,
                    boost::mpl::at<view_type_list, type::view::view>::type,
                    boost::mpl::at<main_window_type_list, type::main_window::main_window>::type
                >::type
            >,
        tetengo2::meta::assoc_list_end
        >
        application_type_list;


}


#endif
