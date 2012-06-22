/*! \file
    \brief The definition of bobura::main_window_menu_builder.

    Copyright (C) 2007-2012 kaoru

    $Id$
*/

#include <memory>
#include <utility>

#include <tetengo2.unique.h>

#include "bobura.main_window_menu_builder.h"


namespace bobura
{
    namespace
    {
        typedef boost::mpl::at<ui_type_list, type::ui::menu_command>::type menu_command_type;

        typedef boost::mpl::at<ui_type_list, type::ui::popup_menu>::type popup_menu_type;

        typedef menu_command_type::base_type menu_base_type;

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
            p_menu_bar->insert(p_menu_bar->end(), build_view_menu());
            p_menu_bar->insert(p_menu_bar->end(), build_help_menu());

            return std::move(p_menu_bar);
        }


    private:
        // types

        typedef command_set_type::command_type command_type;


        // variables

        const command_set_type& m_command_set;

        model_type& m_model;

        main_window_type& m_main_window;

        const message_catalog_type& m_message_catalog;


        // functions

        std::unique_ptr<popup_menu_type> build_file_menu()
        const
        {
            std::unique_ptr<popup_menu_type> p_popup_menu(
                tetengo2::make_unique<popup_menu_type>(m_message_catalog.get(TETENGO2_TEXT("Menu:&File")))
            );
            std::vector<const command_type*> commands;

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

            p_popup_menu->menu_observer_set().selected().connect(
                boost::mpl::at<
                    main_window_message_type_list_type, message::main_window::type::popup_menu_selected
                >::type(*p_popup_menu, std::move(commands), m_model)
            );
            return std::move(p_popup_menu);
        }

        std::unique_ptr<popup_menu_type> build_view_menu()
        const
        {
            std::unique_ptr<popup_menu_type> p_popup_menu(
                tetengo2::make_unique<popup_menu_type>(m_message_catalog.get(TETENGO2_TEXT("Menu:&View")))
            );
            std::vector<const command_type*> commands;

            commands.push_back(&m_command_set.nop());
            p_popup_menu->insert(p_popup_menu->end(), build_horizontal_zoom_menu());
            commands.push_back(&m_command_set.nop());
            p_popup_menu->insert(p_popup_menu->end(), build_vertical_zoom_menu());

            p_popup_menu->menu_observer_set().selected().connect(
                boost::mpl::at<
                    main_window_message_type_list_type, message::main_window::type::popup_menu_selected
                >::type(*p_popup_menu, std::move(commands), m_model)
            );
            return std::move(p_popup_menu);
        }

        std::unique_ptr<popup_menu_type> build_horizontal_zoom_menu()
        const
        {
            std::unique_ptr<popup_menu_type> p_popup_menu(
                tetengo2::make_unique<popup_menu_type>(
                    m_message_catalog.get(TETENGO2_TEXT("Menu:View:&Horizontal Zoom"))
                )
            );
            std::vector<const command_type*> commands;

            append_menu_command(
                *p_popup_menu,
                m_message_catalog.get(TETENGO2_TEXT("Menu:View:Horizontal Zoom:Zoom &In")),
                m_command_set.nop(),
                commands,
                shortcut_key_type(virtual_key_type::right(), true, false, false)
            );
            append_menu_command(
                *p_popup_menu,
                m_message_catalog.get(TETENGO2_TEXT("Menu:View:Horizontal Zoom:Zoom &Out")),
                m_command_set.nop(),
                commands,
                shortcut_key_type(virtual_key_type::left(), true, false, false)
            );

            p_popup_menu->menu_observer_set().selected().connect(
                boost::mpl::at<
                    main_window_message_type_list_type, message::main_window::type::popup_menu_selected
                >::type(*p_popup_menu, std::move(commands), m_model)
            );
            return std::move(p_popup_menu);
        }

        std::unique_ptr<popup_menu_type> build_vertical_zoom_menu()
        const
        {
            std::unique_ptr<popup_menu_type> p_popup_menu(
                tetengo2::make_unique<popup_menu_type>(
                    m_message_catalog.get(TETENGO2_TEXT("Menu:View:&Vertical Zoom"))
                )
            );
            std::vector<const command_type*> commands;

            append_menu_command(
                *p_popup_menu,
                m_message_catalog.get(TETENGO2_TEXT("Menu:View:Vertical Zoom:Zoom &In")),
                m_command_set.nop(),
                commands,
                shortcut_key_type(virtual_key_type::down(), true, false, false)
            );
            append_menu_command(
                *p_popup_menu,
                m_message_catalog.get(TETENGO2_TEXT("Menu:View:Vertical Zoom:Zoom &Out")),
                m_command_set.nop(),
                commands,
                shortcut_key_type(virtual_key_type::up(), true, false, false)
            );

            p_popup_menu->menu_observer_set().selected().connect(
                boost::mpl::at<
                    main_window_message_type_list_type, message::main_window::type::popup_menu_selected
                >::type(*p_popup_menu, std::move(commands), m_model)
            );
            return std::move(p_popup_menu);
        }

        std::unique_ptr<popup_menu_type> build_help_menu()
        const
        {
            std::unique_ptr<popup_menu_type> p_popup_menu(
                tetengo2::make_unique<popup_menu_type>(m_message_catalog.get(TETENGO2_TEXT("Menu:&Help")))
            );
            std::vector<const command_type*> commands;

            append_menu_command(
                *p_popup_menu,
                m_message_catalog.get(TETENGO2_TEXT("Menu:Help:&About")),
                m_command_set.about(),
                commands
            );

            p_popup_menu->menu_observer_set().selected().connect(
                boost::mpl::at<
                    main_window_message_type_list_type, message::main_window::type::popup_menu_selected
                >::type(*p_popup_menu, std::move(commands), m_model)
            );
            return std::move(p_popup_menu);
        }

        void append_menu_command(
            menu_base_type&                   popup_menu,
            menu_base_type::string_type&&     text,
            const command_type&               command,
            std::vector<const command_type*>& commands
        )
        const
        {
            std::unique_ptr<menu_base_type> p_menu_command(
                tetengo2::make_unique<menu_command_type>(std::forward<menu_base_type::string_type>(text))
            );

            p_menu_command->menu_observer_set().selected().connect(
                boost::mpl::at<
                    main_window_message_type_list_type, message::main_window::type::menu_command_selected
                >::type(command, m_model, m_main_window)
            );

            popup_menu.insert(popup_menu.end(), std::move(p_menu_command));
            commands.push_back(&command);
        }

        void append_menu_command(
            menu_base_type&                   popup_menu,
            menu_base_type::string_type&&     text,
            const command_type&               command,
            std::vector<const command_type*>& commands,
            shortcut_key_type&&               shortcut_key
        )
        const
        {
            std::unique_ptr<menu_base_type> p_menu_command(
                tetengo2::make_unique<menu_command_type>(
                    std::forward<menu_base_type::string_type>(text), std::forward<shortcut_key_type>(shortcut_key)
                )
            );

            p_menu_command->menu_observer_set().selected().connect(
                boost::mpl::at<
                    main_window_message_type_list_type, message::main_window::type::menu_command_selected
                >::type(command, m_model, m_main_window)
            );

            popup_menu.insert(popup_menu.end(), std::move(p_menu_command));
            commands.push_back(&command);
        }

        void append_menu_separator(menu_base_type& popup_menu, std::vector<const command_type*>& commands)
        const
        {
            std::unique_ptr<menu_base_type> p_menu_separator(tetengo2::make_unique<menu_separator_type>());
            popup_menu.insert(popup_menu.end(), std::move(p_menu_separator));
            commands.push_back(NULL);
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
    {}

    std::unique_ptr<main_window_menu_builder::menu_bar_type> main_window_menu_builder::build()
    const
    {
        return m_p_impl->build();
    }


}
