/*! \file
    \brief The definition of bobura::main_window.

    Copyright (C) 2007-2014 kaoru

    $Id$
*/

//#include <cassert>
//#include <memory>
//#include <utility>

//#include <boost/mpl/at.hpp>
//#include <boost/noncopyable.hpp>
//#include <boost/optional.hpp>

#include <tetengo2.gui.measure.h>
#include <tetengo2.stdalt.h>
#include <tetengo2.text.h>
#include <tetengo2.utility.h>

#include "bobura.message.type_list.h"

#include "bobura.main_window.h"


namespace bobura
{
    class main_window::impl : private boost::noncopyable
    {
    public:
        // types

        typedef main_window::base_type base_type;

        typedef base_type::string_type string_type;

        typedef base_type::icon_type icon_type;

        typedef base_type::window_state_type window_state_type;

        typedef main_window::message_catalog_type message_catalog_type;

        typedef main_window::diagram_picture_box_type diagram_picture_box_type;

        typedef main_window::property_bar_type property_bar_type;

        typedef main_window::settings_type settings_type;

        typedef main_window::confirm_file_save_type confirm_file_save_type;


        // constructors and destructor

        impl(
            base_type&                    base,
            const message_catalog_type&   message_catalog,
            settings_type&                settings,
            const confirm_file_save_type& confirm_file_save
        )
        :
        m_base(base),
        m_message_catalog(message_catalog),
        m_p_diagram_picture_box(),
        m_p_property_bar(),
        m_settings(settings),
        m_confirm_file_save(confirm_file_save)
        {
            initialize_window();
        }


        // functions

        void set_title(const boost::optional<string_type>& document_name, const bool changed)
        {
            auto title = document_name ? *document_name : m_message_catalog.get(TETENGO2_TEXT("Common:Untitled"));
            if (changed)
                title += string_type(TETENGO2_TEXT(" *"));
            title += string_type(TETENGO2_TEXT(" - "));
            title += m_message_catalog.get(TETENGO2_TEXT("App:Bobura"));

            m_base.set_text(title);
        }

        const diagram_picture_box_type& diagram_picture_box()
        const
        {
            assert(m_p_diagram_picture_box);
            return *m_p_diagram_picture_box;
        }

        diagram_picture_box_type& diagram_picture_box()
        {
            assert(m_p_diagram_picture_box);
            return *m_p_diagram_picture_box;
        }

        const property_bar_type& property_bar()
        const
        {
            assert(m_p_property_bar);
            return *m_p_property_bar;
        }

        property_bar_type& property_bar()
        {
            assert(m_p_property_bar);
            return *m_p_property_bar;
        }


    private:
        // types

        typedef boost::mpl::at<ui_type_list, type::ui::message_loop_break>::type message_loop_break_type;

        typedef
            boost::mpl::at<main_window_type_list, type::main_window::message_type_list>::type
            message_type_list_type;

        typedef base_type::position_type position_type;

        typedef tetengo2::gui::position<position_type>::left_type left_type;

        typedef tetengo2::gui::position<position_type>::top_type top_type;

        typedef base_type::dimension_type dimension_type;


        // variables

        base_type& m_base;

        const message_catalog_type& m_message_catalog;

        std::unique_ptr<diagram_picture_box_type> m_p_diagram_picture_box;

        std::unique_ptr<property_bar_type> m_p_property_bar;

        settings_type& m_settings;

        const confirm_file_save_type& m_confirm_file_save;


        // functions

        void initialize_window()
        {
            m_p_diagram_picture_box = tetengo2::stdalt::make_unique<diagram_picture_box_type>(m_base);
            m_p_property_bar = tetengo2::stdalt::make_unique<property_bar_type>(m_base, m_settings, m_message_catalog);

            set_message_observers();

            set_window_icon();
            set_title(boost::none, false);
                
            auto dimension = m_settings.main_window_dimension();
            if (dimension)
                m_base.set_dimension(std::move(*dimension));
            const auto maximized = m_settings.main_window_maximized();
            if (maximized && *maximized)
                m_base.set_window_state(window_state_type::maximized);
            else
                m_base.set_window_state(window_state_type::normal);
        }

        void set_message_observers()
        {
            m_base.focus_observer_set().got_focus().connect(
                [this]() { this->m_p_diagram_picture_box->set_focus(); }
            );
            m_base.paint_observer_set().paint_background().connect(
                [](base_type::canvas_type&) { return true; }
            );
            m_base.window_observer_set().closing().connect(
                boost::mpl::at<message_type_list_type, message::main_window::type::window_closing>::type(
                    m_base, m_confirm_file_save, [this]() { this->save_settings(); }
                )
            );
            m_base.window_observer_set().destroyed().connect([](){ return message_loop_break_type()(0); });
        }

        void set_window_icon()
        {
            auto p_icon =
                tetengo2::stdalt::make_unique<icon_type>(
                    m_settings.image_directory_path() / string_type(TETENGO2_TEXT("bobura_app.ico"))
                );
            m_base.set_icon(std::move(p_icon));
        }

        void save_settings()
        {
            m_settings.set_main_window_dimension(m_base.normal_dimension());
            m_settings.set_main_window_maximized(m_base.window_state() == window_state_type::maximized);

            m_p_property_bar->save_settings();
        }


    };


    main_window::main_window(
        const message_catalog_type&   message_catalog,
        settings_type&                settings,
        const confirm_file_save_type& confirm_file_save
    )
    :
    base_type(base_type::scroll_bar_style_type::none, true),
    m_p_impl(tetengo2::stdalt::make_unique<impl>(*this, message_catalog, settings, confirm_file_save))
    {}

    main_window::~main_window()
    TETENGO2_STDALT_NOEXCEPT
    {}

    void main_window::set_title(const boost::optional<string_type>& document_name, const bool changed)
    {
        m_p_impl->set_title(document_name, changed);
    }

    const main_window::diagram_picture_box_type& main_window::diagram_picture_box()
    const
    {
        return m_p_impl->diagram_picture_box();
    }

    main_window::diagram_picture_box_type& main_window::diagram_picture_box()
    {
        return m_p_impl->diagram_picture_box();
    }

    const main_window::property_bar_type& main_window::property_bar()
    const
    {
        return m_p_impl->property_bar();
    }

    main_window::property_bar_type& main_window::property_bar()
    {
        return m_p_impl->property_bar();
    }


}
