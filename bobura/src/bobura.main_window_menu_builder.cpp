/*! \file
    \brief The definition of bobura::main_window_menu_builder.

    Copyright (C) 2007-2013 kaoru

    $Id$
*/

//#include <memory>
//#include <utility>
//#include <vector>

//#include <boost/mpl/at.hpp>

#include <tetengo2.cpp11.h>
#include <tetengo2.unique.h>
#include <tetengo2.text.h>

#include "bobura.type_list.h"

#include "bobura.main_window_menu_builder.h"


namespace bobura
{
    namespace
    {
        typedef boost::mpl::at<ui_type_list, type::ui::menu_command>::type menu_command_type;

        typedef boost::mpl::at<ui_type_list, type::ui::popup_menu>::type popup_menu_type;

        typedef menu_command_type::base_type menu_base_type;

        typedef menu_base_type::string_type string_type;

        typedef menu_base_type::shortcut_key_type shortcut_key_type;

        typedef shortcut_key_type::virtual_key_type virtual_key_type;

        typedef boost::mpl::at<ui_type_list, type::ui::menu_separator>::type menu_separator_type;

        typedef
            boost::mpl::at<main_window_type_list, type::main_window::message_type_list>::type
            main_window_message_type_list_type;


    }


    class main_window_menu_builder::impl
    {
    public:
        // types

        typedef main_window_menu_builder::menu_bar_type menu_bar_type;

        typedef main_window_menu_builder::command_set_type command_set_type;

        typedef main_window_menu_builder::model_type model_type;

        typedef main_window_menu_builder::main_window_type main_window_type;

        typedef main_window_menu_builder::message_catalog_type message_catalog_type;


        // constructors and destructor

        impl(
            const command_set_type&     command_set,
            model_type&                 model,
            main_window_type&           main_window,
            const message_catalog_type& message_catalog
        )
        :
        m_command_set(command_set),
        m_model(model),
        m_main_window(main_window),
        m_message_catalog(message_catalog)
        {}


        // functions

        std::unique_ptr<menu_bar_type> build()
        const
        {
            std::unique_ptr<menu_bar_type> p_menu_bar(tetengo2::make_unique<menu_bar_type>());

            p_menu_bar->insert(p_menu_bar->end(), build_file_menu());
            p_menu_bar->insert(p_menu_bar->end(), build_format_menu());
            p_menu_bar->insert(p_menu_bar->end(), build_view_menu());
            p_menu_bar->insert(p_menu_bar->end(), build_help_menu());

            return std::move(p_menu_bar);
        }


    private:
        // types

        typedef command_set_type::command_type command_type;

        typedef std::vector<const command_type*> commands_type;

        typedef boost::mpl::at<view_type_list, type::view::scale_list>::type view_scale_list_type;


        // variables

        const command_set_type& m_command_set;

        model_type& m_model;

        main_window_type& m_main_window;

        const message_catalog_type& m_message_catalog;


        // functions

        std::unique_ptr<popup_menu_type> build_file_menu()
        const
        {
            std::unique_ptr<popup_menu_type> p_popup_menu =
                tetengo2::make_unique<popup_menu_type>(m_message_catalog.get(TETENGO2_TEXT("Menu:&File")));
            commands_type commands;

            append_menu_command(
                *p_popup_menu,
                m_message_catalog.get(TETENGO2_TEXT("Menu:File:&New")),
                m_command_set.new_file(),
                commands,
                shortcut_key_type(virtual_key_type::char_n(), false, true, false)
            );
            append_menu_command(
                *p_popup_menu,
                m_message_catalog.get(TETENGO2_TEXT("Menu:File:&Open...")),
                m_command_set.load_from_file(),
                commands,
                shortcut_key_type(virtual_key_type::char_o(), false, true, false)
            );
            append_menu_command(
                *p_popup_menu,
                m_message_catalog.get(TETENGO2_TEXT("Menu:File:&Reload")),
                m_command_set.reload(),
                commands,
                shortcut_key_type(virtual_key_type::f5(), false, false, false)
            );
            append_menu_command(
                *p_popup_menu,
                m_message_catalog.get(TETENGO2_TEXT("Menu:File:&Save")),
                m_command_set.save_to_file(),
                commands,
                shortcut_key_type(virtual_key_type::char_s(), false, true, false)
            );
            append_menu_command(
                *p_popup_menu,
                m_message_catalog.get(TETENGO2_TEXT("Menu:File:Save &As...")),
                m_command_set.ask_file_path_and_save_to_file(),
                commands
            );

            append_menu_separator(*p_popup_menu, commands);

            append_menu_command(
                *p_popup_menu,
                m_message_catalog.get(TETENGO2_TEXT("Menu:File:Proper&ty...")),
                m_command_set.file_property(),
                commands
            );
            append_menu_separator(*p_popup_menu, commands);
            append_menu_command(
                *p_popup_menu,
                m_message_catalog.get(TETENGO2_TEXT("Menu:File:E&xit")),
                m_command_set.exit(),
                commands
            );

            connect_popup_menu_observer(*p_popup_menu, std::move(commands));
            return std::move(p_popup_menu);
        }

        std::unique_ptr<popup_menu_type> build_format_menu()
        const
        {
            std::unique_ptr<popup_menu_type> p_popup_menu =
                tetengo2::make_unique<popup_menu_type>(m_message_catalog.get(TETENGO2_TEXT("Menu:D&iagram")));
            commands_type commands;

            append_menu_command(
                *p_popup_menu,
                m_message_catalog.get(TETENGO2_TEXT("Menu:Diagram:&Fonts And Colors...")),
                m_command_set.font_color(),
                commands
            );
            append_menu_command(
                *p_popup_menu,
                m_message_catalog.get(TETENGO2_TEXT("Menu:Diagram:Train &Kinds...")),
                m_command_set.train_kind(),
                commands
            );


            connect_popup_menu_observer(*p_popup_menu, std::move(commands));
            return std::move(p_popup_menu);
        }

        std::unique_ptr<popup_menu_type> build_view_menu()
        const
        {
            std::unique_ptr<popup_menu_type> p_popup_menu =
                tetengo2::make_unique<popup_menu_type>(m_message_catalog.get(TETENGO2_TEXT("Menu:&View")));
            commands_type commands;

            append_popup_menu(*p_popup_menu, build_horizontal_zoom_menu(), commands);
            append_popup_menu(*p_popup_menu, build_vertical_zoom_menu(), commands);

            connect_popup_menu_observer(*p_popup_menu, std::move(commands));
            return std::move(p_popup_menu);
        }

        std::unique_ptr<popup_menu_type> build_horizontal_zoom_menu()
        const
        {
            std::unique_ptr<popup_menu_type> p_popup_menu =
                tetengo2::make_unique<popup_menu_type>(
                    m_message_catalog.get(TETENGO2_TEXT("Menu:View:&Horizontal Zoom"))
                );
            commands_type commands;

            append_menu_command(
                *p_popup_menu,
                m_message_catalog.get(TETENGO2_TEXT("Menu:View:Horizontal Zoom:Zoom &In")),
                m_command_set.horizontally_zoom_in(),
                commands,
                shortcut_key_type(virtual_key_type::right(), false, true, false)
            );
            append_menu_command(
                *p_popup_menu,
                m_message_catalog.get(TETENGO2_TEXT("Menu:View:Horizontal Zoom:Zoom &Out")),
                m_command_set.horizontally_zoom_out(),
                commands,
                shortcut_key_type(virtual_key_type::left(), false, true, false)
            );

            append_menu_separator(*p_popup_menu, commands);

            append_horizontal_zoom_scale_menus(*p_popup_menu, commands);

            connect_popup_menu_observer(*p_popup_menu, std::move(commands));
            return std::move(p_popup_menu);
        }

        void append_horizontal_zoom_scale_menus(popup_menu_type& popup_menu, commands_type& commands)
        const
        {
            const view_scale_list_type scale_list;

            for (view_scale_list_type::size_type i = 0; i < scale_list.size(); ++i)
            {
                append_menu_command(
                    popup_menu,
                    make_zoom_scale_label(scale_list.label_at(i)),
                    m_command_set.set_horizontal_scale(i),
                    commands
                );
            }
        }

        std::unique_ptr<popup_menu_type> build_vertical_zoom_menu()
        const
        {
            std::unique_ptr<popup_menu_type> p_popup_menu =
                tetengo2::make_unique<popup_menu_type>(
                    m_message_catalog.get(TETENGO2_TEXT("Menu:View:&Vertical Zoom"))
                );
            commands_type commands;

            append_menu_command(
                *p_popup_menu,
                m_message_catalog.get(TETENGO2_TEXT("Menu:View:Vertical Zoom:Zoom &In")),
                m_command_set.vertically_zoom_in(),
                commands,
                shortcut_key_type(virtual_key_type::down(), false, true, false)
            );
            append_menu_command(
                *p_popup_menu,
                m_message_catalog.get(TETENGO2_TEXT("Menu:View:Vertical Zoom:Zoom &Out")),
                m_command_set.vertically_zoom_out(),
                commands,
                shortcut_key_type(virtual_key_type::up(), false, true, false)
            );

            append_menu_separator(*p_popup_menu, commands);

            append_vertical_zoom_scale_menus(*p_popup_menu, commands);

            connect_popup_menu_observer(*p_popup_menu, std::move(commands));
            return std::move(p_popup_menu);
        }

        void append_vertical_zoom_scale_menus(popup_menu_type& popup_menu, commands_type& commands)
        const
        {
            const view_scale_list_type scale_list;

            for (view_scale_list_type::size_type i = 0; i < scale_list.size(); ++i)
            {
                append_menu_command(
                    popup_menu,
                    make_zoom_scale_label(scale_list.label_at(i)),
                    m_command_set.set_vertical_scale(i),
                    commands
                );
            }
        }

        string_type make_zoom_scale_label(const string_type& label)
        const
        {
            return string_type(TETENGO2_TEXT("&")) + label;
        }

        std::unique_ptr<popup_menu_type> build_help_menu()
        const
        {
            std::unique_ptr<popup_menu_type> p_popup_menu =
                tetengo2::make_unique<popup_menu_type>(m_message_catalog.get(TETENGO2_TEXT("Menu:&Help")));
            commands_type commands;

            append_menu_command(
                *p_popup_menu,
                m_message_catalog.get(TETENGO2_TEXT("Menu:Help:&About")),
                m_command_set.about(),
                commands
            );

            connect_popup_menu_observer(*p_popup_menu, std::move(commands));
            return std::move(p_popup_menu);
        }

        void append_popup_menu(
            popup_menu_type&                 popup_menu,
            std::unique_ptr<popup_menu_type> p_child_popup_menu,
            commands_type&                   commands
        )
        const
        {
            popup_menu.insert(popup_menu.end(), std::move(p_child_popup_menu));
            commands.push_back(nullptr);
        }

        void append_menu_command(
            popup_menu_type&    popup_menu,
            string_type         text,
            const command_type& command,
            commands_type&      commands
        )
        const
        {
            std::unique_ptr<menu_command_type> p_menu_command(
                tetengo2::make_unique<menu_command_type>(std::move(text))
            );

            append_menu_command_impl(popup_menu, std::move(p_menu_command), command, commands);
        }

        void append_menu_command(
            popup_menu_type&    popup_menu,
            string_type         text,
            const command_type& command,
            commands_type&      commands,
            shortcut_key_type   shortcut_key
        )
        const
        {
            std::unique_ptr<menu_command_type> p_menu_command(
                tetengo2::make_unique<menu_command_type>(std::move(text), std::move(shortcut_key))
            );

            append_menu_command_impl(popup_menu, std::move(p_menu_command), command, commands);
        }

        void append_menu_command_impl(
            popup_menu_type&                   popup_menu,
            std::unique_ptr<menu_command_type> p_menu_command,
            const command_type&                command,
            commands_type&                     commands
        )
        const
        {
            p_menu_command->menu_observer_set().selected().connect(
                boost::mpl::at<
                    main_window_message_type_list_type, message::main_window::type::menu_command_selected
                >::type(command, m_model, m_main_window)
            );

            popup_menu.insert(popup_menu.end(), std::move(p_menu_command));
            commands.push_back(&command);
        }

        void append_menu_separator(popup_menu_type& popup_menu, commands_type& commands)
        const
        {
            std::unique_ptr<menu_separator_type> p_menu_separator(tetengo2::make_unique<menu_separator_type>());
            popup_menu.insert(popup_menu.end(), std::move(p_menu_separator));
            commands.push_back(nullptr);
        }

        void connect_popup_menu_observer(popup_menu_type& popup_menu, commands_type commands)
        const
        {
            popup_menu.menu_observer_set().selected().connect(
                boost::mpl::at<
                    main_window_message_type_list_type, message::main_window::type::popup_menu_selected
                >::type(popup_menu, std::move(commands), m_model)
            );
        }


    };


    main_window_menu_builder::main_window_menu_builder(
        const command_set_type&     command_set,
        model_type&                 model,
        main_window_type&           main_window,
        const message_catalog_type& message_catalog
    )
    :
    m_p_impl(tetengo2::make_unique<impl>(command_set, model, main_window, message_catalog))
    {}

    main_window_menu_builder::~main_window_menu_builder()
    TETENGO2_CPP11_NOEXCEPT
    {}

    std::unique_ptr<main_window_menu_builder::menu_bar_type> main_window_menu_builder::build()
    const
    {
        return m_p_impl->build();
    }


}
