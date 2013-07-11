/*! \file
    \brief The definition of bobura::application.

    Copyright (C) 2007-2013 kaoru

    $Id$
*/

//#include <cassert>

//#include <boost/mpl/at.hpp>
//#include <boost/noncopyable.hpp>

#include <tetengo2.stdalt.h>

#include "bobura.main_window_menu_builder.h"
#include "bobura.message.type_list.h"

#include "bobura.application.h"


namespace bobura
{
    namespace
    {
        typedef boost::mpl::at<setting_type_list, type::setting::settings>::type settings_type;

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

        typedef boost::mpl::at<main_window_type_list, type::main_window::command_set>::type command_set_type;

        typedef boost::mpl::at<main_window_type_list, type::main_window::main_window>::type main_window_type;

        typedef
            boost::mpl::at<main_window_type_list, type::main_window::diagram_picture_box>::type
            diagram_picture_box_type;

        typedef
            boost::mpl::at<main_window_type_list, type::main_window::message_type_list>::type
            main_window_message_type_list_type;

        typedef
            boost::mpl::at<main_window_type_list, type::main_window::diagram_picture_box_message_type_list>::type
            diagram_picture_box_message_type_list;

        typedef boost::mpl::at<ui_type_list, type::ui::message_loop>::type message_loop_type;

        typedef boost::mpl::at<ui_type_list, type::ui::gui_fixture>::type gui_fixture_type;


    }


    class application::impl : private boost::noncopyable
    {
    public:
        // constructors and destructor

        explicit impl(settings_type& settings)
        :
        m_gui_fixture(),
        m_settings(settings),
        m_model()
        {}


        // functions

        int run()
        {
            const message_catalog_type message_catalog;
            view_type view(m_model, message_catalog);
            const command_set_holder_type command_set_holder(m_settings, m_model, view, message_catalog);

            main_window_type main_window(message_catalog, m_settings, command_set_holder.confirm_file_save()); 
            set_message_observers(view, main_window);
            m_model.reset_timetable();
            main_window.set_menu_bar(
                main_window_menu_builder(
                    command_set_holder.command_set(), m_model, main_window, message_catalog
                ).build()
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
                settings_type&              settings,
                model_type&                 model,
                view_type&                  view,
                const message_catalog_type& message_catalog
            )
            :
            m_save_to_file(false, message_catalog),
            m_ask_file_path_and_save_to_file(true, message_catalog),
            m_confirm_file_save(model, m_save_to_file, message_catalog),
            m_new_file(m_confirm_file_save),
            m_reload(false, m_confirm_file_save, message_catalog),
            m_load_from_file(true, m_confirm_file_save, message_catalog),
            m_command_set(
                m_new_file,
                m_load_from_file,
                m_reload,
                m_save_to_file,
                m_ask_file_path_and_save_to_file,
                view,
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

            const load_from_file_type m_reload;

            const load_from_file_type m_load_from_file;

            const command_set_type m_command_set;

        };


        // variables

        const gui_fixture_type m_gui_fixture;

        settings_type& m_settings;

        model_type m_model;


        // functions

        void set_message_observers(view_type& view, main_window_type& main_window)
        {
            m_model.observer_set().reset().connect(
                boost::mpl::at<model_message_type_list_type, message::timetable_model::type::reset>::type(
                    m_model, view, main_window
                )
            );
            m_model.observer_set().changed().connect(
                boost::mpl::at<model_message_type_list_type, message::timetable_model::type::changed>::type(
                    m_model, view, main_window
                )
            );

            main_window.size_observer_set().resized().connect(
                boost::mpl::at<main_window_message_type_list_type, message::main_window::type::window_resized>::type(
                    view, main_window, main_window.diagram_picture_box(), main_window.property_bar()
                )
            );

            main_window.diagram_picture_box().mouse_observer_set().pressed().connect(
                boost::mpl::at<
                    diagram_picture_box_message_type_list, message::diagram_picture_box::type::mouse_pressed
                >::type(
                    main_window.diagram_picture_box(),
                    [&main_window]() { main_window.diagram_picture_box().set_mouse_capture(); },
                    view
                )
            );
            main_window.diagram_picture_box().mouse_observer_set().released().connect(
                boost::mpl::at<
                    diagram_picture_box_message_type_list, message::diagram_picture_box::type::mouse_released
                >::type([&main_window]() { return main_window.diagram_picture_box().release_mouse_capture(); }, view)
            );
            main_window.diagram_picture_box().mouse_observer_set().moved().connect(
                boost::mpl::at<
                    diagram_picture_box_message_type_list, message::diagram_picture_box::type::mouse_moved
                >::type(main_window.diagram_picture_box(), view)
            );
            main_window.diagram_picture_box().mouse_observer_set().wheeled().connect(
                boost::mpl::at<
                    diagram_picture_box_message_type_list, message::diagram_picture_box::type::mouse_wheeled
                >::type(main_window.diagram_picture_box(), view)
            );
            main_window.diagram_picture_box().fast_paint_observer_set().paint().connect(
                boost::mpl::at<
                    diagram_picture_box_message_type_list, message::diagram_picture_box::type::paint_paint
                >::type(main_window.diagram_picture_box(), view)
            );
            assert(main_window.diagram_picture_box().vertical_scroll_bar());
            main_window.diagram_picture_box().vertical_scroll_bar()->scroll_bar_observer_set().scrolling().connect(
                boost::mpl::at<
                    diagram_picture_box_message_type_list, message::diagram_picture_box::type::scroll_bar_scrolled
                >::type(main_window.diagram_picture_box(), view)
            );
            main_window.diagram_picture_box().vertical_scroll_bar()->scroll_bar_observer_set().scrolled().connect(
                boost::mpl::at<
                    diagram_picture_box_message_type_list, message::diagram_picture_box::type::scroll_bar_scrolled
                >::type(main_window.diagram_picture_box(), view)
            );
            assert(main_window.diagram_picture_box().horizontal_scroll_bar());
            main_window.diagram_picture_box().horizontal_scroll_bar()->scroll_bar_observer_set().scrolling().connect(
                boost::mpl::at<
                    diagram_picture_box_message_type_list, message::diagram_picture_box::type::scroll_bar_scrolled
                >::type(main_window.diagram_picture_box(), view)
            );
            main_window.diagram_picture_box().horizontal_scroll_bar()->scroll_bar_observer_set().scrolled().connect(
                boost::mpl::at<
                    diagram_picture_box_message_type_list, message::diagram_picture_box::type::scroll_bar_scrolled
                >::type(main_window.diagram_picture_box(), view)
            );
        }

    };


    application::application(settings_type& settings)
    :
    m_p_impl(tetengo2::stdalt::make_unique<impl>(settings))
    {}

    application::~application()
    TETENGO2_STDALT_NOEXCEPT
    {}

    int application::run()
    {
        return m_p_impl->run();
    }


}
