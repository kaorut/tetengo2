/*! \file
    \brief The definition of bobura::application.

    Copyright (C) 2007-2012 kaoru

    $Id$
*/

//#include <memory>
//#include <utility>

//#include <boost/mpl/at.hpp>
//#include <boost/noncopyable.hpp>

#include <tetengo2.unique.h>

#include "bobura.message.type_list.h"
#define USE_TYPES_FOR_APPLICATION
#include "bobura.type_list.h"

#include "bobura.application.h"


namespace bobura
{
    namespace
    {
        typedef boost::mpl::at<common_type_list, type::settings>::type settings_type;

        typedef boost::mpl::at<model_type_list, type::model::model>::type model_type;

        typedef
            boost::mpl::at<application_type_list, type::application::model_message_type_list>::type
            model_message_type_list_type;

        typedef boost::mpl::at<view_type_list, type::view::view>::type view_type;

        typedef boost::mpl::at<locale_type_list, type::locale::message_catalog>::type message_catalog_type;

        typedef boost::mpl::at<load_save_type_list, type::load_save::confirm_file_save>::type confirm_file_save_type;

        typedef boost::mpl::at<load_save_type_list, type::load_save::new_file>::type new_file_type;

        typedef boost::mpl::at<load_save_type_list, type::load_save::load_from_file>::type load_from_file_type;

        typedef boost::mpl::at<load_save_type_list, type::load_save::save_to_file>::type save_to_file_type;

        typedef boost::mpl::at<application_type_list, type::application::command_set>::type command_set_type;

        typedef command_set_type::command_type command_type;

        typedef boost::mpl::at<main_window_type_list, type::main_window::main_window>::type main_window_type;

        typedef
            boost::mpl::at<main_window_type_list, type::main_window::message_type_list>::type
            main_window_message_type_list_type;

        typedef
            boost::mpl::at<main_window_type_list, type::main_window::diagram_picture_box_message_type_list>::type
            diagram_picture_box_message_type_list;

        typedef boost::mpl::at<ui_type_list, type::ui::menu_bar>::type menu_bar_type;

        typedef boost::mpl::at<ui_type_list, type::ui::menu_command>::type menu_command_type;

        typedef menu_command_type::base_type menu_base_type;

        typedef menu_base_type::shortcut_key_type shortcut_key_type;

        typedef shortcut_key_type::virtual_key_type virtual_key_type;

        typedef boost::mpl::at<ui_type_list, type::ui::popup_menu>::type popup_menu_type;

        typedef boost::mpl::at<ui_type_list, type::ui::menu_separator>::type menu_separator_type;

        typedef boost::mpl::at<ui_type_list, type::ui::message_loop>::type message_loop_type;

        typedef boost::mpl::at<ui_type_list, type::ui::message_loop_break>::type message_loop_break_type;

        typedef boost::mpl::at<ui_type_list, type::ui::gui_fixture>::type gui_fixture_type;


    }


    class application::impl : private boost::noncopyable
    {
    public:
        // constructors and destructor

        explicit impl(const settings_type& settings)
        :
        m_gui_fixture(),
        m_settings(settings),
        m_model(),
        m_view(m_model)
        {}


        // functions

        int run()
        {
            const message_catalog_type message_catalog;
            const command_set_holder_type command_set_holder(m_settings, m_model, message_catalog);

            main_window_type main_window(message_catalog, m_settings, command_set_holder.confirm_file_save()); 
            set_message_observers(main_window);
            main_window.set_menu_bar(build_main_window_menu(
                command_set_holder.command_set(), m_model, main_window, message_catalog)
            );
            main_window.set_visible(true);

            return message_loop_type(main_window)();
        }


    private:
        // types

        class command_set_holder_type : private boost::noncopyable
        {
        public:
            command_set_holder_type(
                const settings_type&        settings,
                model_type&                 model,
                const message_catalog_type& message_catalog
            )
            :
            m_save_to_file(false, message_catalog),
            m_ask_file_path_and_save_to_file(true, message_catalog),
            m_confirm_file_save(model, m_save_to_file, message_catalog),
            m_new_file(m_confirm_file_save),
            m_load_from_file(m_confirm_file_save, message_catalog),
            m_command_set(
                m_new_file,
                m_load_from_file,
                m_save_to_file,
                m_ask_file_path_and_save_to_file,
                settings,
                message_catalog
            )
            {}

            const confirm_file_save_type& confirm_file_save()
            const
            {
                return m_confirm_file_save;
            }

            const command_set_type& command_set()
            const
            {
                return m_command_set;
            }

        private:
            const save_to_file_type m_save_to_file;

            const save_to_file_type m_ask_file_path_and_save_to_file;

            const confirm_file_save_type m_confirm_file_save;

            const new_file_type m_new_file;

            const load_from_file_type m_load_from_file;

            const command_set_type m_command_set;

        };


        // static functions

        static std::unique_ptr<menu_bar_type> build_main_window_menu(
            const command_set_type&     command_set,
            model_type&                 model,
            main_window_type&           main_window,
            const message_catalog_type& message_catalog
        )
        {
            std::unique_ptr<menu_bar_type> p_menu_bar(tetengo2::make_unique<menu_bar_type>());

            {
                std::unique_ptr<menu_base_type> p_popup_menu(
                    tetengo2::make_unique<popup_menu_type>(message_catalog.get(TETENGO2_TEXT("Menu:&File")))
                );

                append_menu_command(
                    *p_popup_menu,
                    message_catalog.get(TETENGO2_TEXT("Menu:File:&New")),
                    command_set.new_file(),
                    model,
                    main_window,
                    shortcut_key_type(virtual_key_type::char_n(), false, true, false)
                );
                append_menu_command(
                    *p_popup_menu,
                    message_catalog.get(TETENGO2_TEXT("Menu:File:&Open...")),
                    command_set.load_from_file(),
                    model,
                    main_window,
                    shortcut_key_type(virtual_key_type::char_o(), false, true, false)
                );
                append_menu_command(
                    *p_popup_menu,
                    message_catalog.get(TETENGO2_TEXT("Menu:File:&Save")),
                    command_set.save_to_file(),
                    model,
                    main_window,
                    shortcut_key_type(virtual_key_type::char_s(), false, true, false)
                );
                append_menu_command(
                    *p_popup_menu,
                    message_catalog.get(TETENGO2_TEXT("Menu:File:Save &As...")),
                    command_set.ask_file_path_and_save_to_file(),
                    model,
                    main_window
                );
                append_menu_separator(*p_popup_menu);
                append_menu_command(
                    *p_popup_menu,
                    message_catalog.get(TETENGO2_TEXT("Menu:File:P&roperty...")),
                    command_set.file_property(),
                    model,
                    main_window
                );
                append_menu_separator(*p_popup_menu);
                append_menu_command(
                    *p_popup_menu,
                    message_catalog.get(TETENGO2_TEXT("Menu:File:E&xit")),
                    command_set.exit(),
                    model,
                    main_window
                );

                p_menu_bar->insert(p_menu_bar->end(), std::move(p_popup_menu));
            }
            {
                std::unique_ptr<menu_base_type> p_popup_menu(
                    tetengo2::make_unique<popup_menu_type>(message_catalog.get(TETENGO2_TEXT("Menu:&Help")))
                );

                append_menu_command(
                    *p_popup_menu,
                    message_catalog.get(TETENGO2_TEXT("Menu:Help:&About")),
                    command_set.about(),
                    model,
                    main_window
                );

                p_menu_bar->insert(p_menu_bar->end(), std::move(p_popup_menu));
            }

            return std::move(p_menu_bar);
        }

        static void append_menu_command(
            menu_base_type&               popup_menu,
            menu_base_type::string_type&& text,
            const command_type&           command,
            model_type&                   model,
            main_window_type&             main_window
        )
        {
            std::unique_ptr<menu_base_type> p_menu_command(
                tetengo2::make_unique<menu_command_type>(std::forward<menu_base_type::string_type>(text))
            );

            p_menu_command->menu_observer_set().selected().connect(
                boost::mpl::at<main_window_message_type_list_type, message::main_window::type::menu_selected>::type(
                    command, model, main_window
                )
            );

            popup_menu.insert(popup_menu.end(), std::move(p_menu_command));
        }

        static void append_menu_command(
            menu_base_type&               popup_menu,
            menu_base_type::string_type&& text,
            const command_type&           command,
            model_type&                   model,
            main_window_type&             main_window,
            shortcut_key_type&&           shortcut_key
        )
        {
            std::unique_ptr<menu_base_type> p_menu_command(
                tetengo2::make_unique<menu_command_type>(
                    std::forward<menu_base_type::string_type>(text), std::forward<shortcut_key_type>(shortcut_key)
                )
            );

            p_menu_command->menu_observer_set().selected().connect(
                boost::mpl::at<main_window_message_type_list_type, message::main_window::type::menu_selected>::type(
                    command, model, main_window
                )
            );

            popup_menu.insert(popup_menu.end(), std::move(p_menu_command));
        }

        static void append_menu_separator(menu_base_type& popup_menu)
        {
            std::unique_ptr<menu_base_type> p_menu_separator(tetengo2::make_unique<menu_separator_type>());
            popup_menu.insert(popup_menu.end(), std::move(p_menu_separator));
        }


        // variables

        const gui_fixture_type m_gui_fixture;

        const settings_type& m_settings;

        model_type m_model;

        const view_type m_view;


        // functions

        void set_message_observers(main_window_type& main_window)
        {
            m_model.observer_set().reset().connect(
                boost::mpl::at<model_message_type_list_type, message::timetable_model::type::reset>::type(
                    m_model, main_window
                )
            );
            m_model.observer_set().changed().connect(
                boost::mpl::at<model_message_type_list_type, message::timetable_model::type::changed>::type(
                    m_model, main_window
                )
            );

            main_window.window_observer_set().resized().connect(
                boost::mpl::at<main_window_message_type_list_type, message::main_window::type::window_resized>::type(
                    m_view, main_window, main_window.diagram_picture_box()
                )
            );
            main_window.diagram_picture_box().fast_paint_observer_set().paint().connect(
                boost::mpl::at<
                    diagram_picture_box_message_type_list, message::diagram_picture_box::type::paint_paint
                >::type(main_window.diagram_picture_box(), m_view)
            );
        }

    };


    application::application(const settings_type& settings)
    :
    m_p_impl(tetengo2::make_unique<impl>(settings))
    {}

    application::~application()
    {}

    int application::run()
    {
        return m_p_impl->run();
    }


}
