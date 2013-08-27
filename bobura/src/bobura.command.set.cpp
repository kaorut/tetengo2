/*! \file
    \brief The definition of bobura::command::set.

    Copyright (C) 2007-2013 kaoru

    $Id$
*/

//#include <memory>
//#include <vector>

//#include <boost/mpl/at.hpp>

#include <tetengo2.stdalt.h>

#include "bobura.command.about.h"
#include "bobura.command.command_base.h"
#include "bobura.command.exit.h"
#include "bobura.command.file_property.h"
#include "bobura.command.font_color.h"
#include "bobura.command.horizontally_zoom_in.h"
#include "bobura.command.horizontally_zoom_out.h"
#include "bobura.command.load_from_file.h"
#include "bobura.command.new_file.h"
#include "bobura.command.nop.h"
#include "bobura.command.save_to_file.h"
#include "bobura.command.set_horizontal_scale.h"
#include "bobura.command.set_vertical_scale.h"
#include "bobura.command.train_kind.h"
#include "bobura.command.vertically_zoom_in.h"
#include "bobura.command.vertically_zoom_out.h"
#include "bobura.type_list.h"

#include "bobura.command.set.h"


namespace bobura { namespace command
{
    class set::impl
    {
    public:
        // types

        typedef set::size_type size_type;

        typedef set::new_file_type new_file_type;

        typedef set::load_from_file_type load_from_file_type;

        typedef set::path_type path_type;

        typedef set::save_to_file_type save_to_file_type;

        typedef set::diagram_view_type diagram_view_type;

        typedef set::settings_type settings_type;

        typedef set::message_catalog_type message_catalog_type;

        typedef set::command_type command_type;

        typedef set::parameter_type parameter_type;


        // constructors and destructor

        impl(
            const new_file_type&          new_file,
            const load_from_file_type&    load_from_file,
            const load_from_file_type&    reload,
            const save_to_file_type&      save_to_file,
            const save_to_file_type&      ask_file_path_and_save_to_file,
            diagram_view_type&            diagram_view,
            const settings_type&          settings,
            const message_catalog_type&   message_catalog
        )
        :
        m_p_about(create_about(message_catalog, settings)),
        m_p_exit(create_exit()),
        m_p_file_property(create_file_property(message_catalog)),
        m_p_font_color(create_font_color(message_catalog)),
        m_p_horizontally_zoom_in(create_horizontally_zoom_in(diagram_view)),
        m_p_horizontally_zoom_out(create_horizontally_zoom_out(diagram_view)),
        m_p_load_from_file(create_load_from_file(load_from_file)),
        m_p_new_file(create_new_file(new_file)),
        m_p_nop(create_nop()),
        m_p_reload(create_load_from_file(reload)),
        m_p_save_to_file(create_save_to_file(save_to_file)),
        m_p_ask_file_path_and_save_to_file(create_save_to_file(ask_file_path_and_save_to_file)),
        m_p_set_horizontal_scale(create_set_horizontal_scale(diagram_view)),
        m_p_set_vertical_scale(create_set_vertical_scale(diagram_view)),
        m_p_train_kind(create_train_kind(message_catalog)),
        m_p_vertically_zoom_in(create_vertically_zoom_in(diagram_view)),
        m_p_vertically_zoom_out(create_vertically_zoom_out(diagram_view))
        {}


        // functions

        const command_type& about()
        const
        {
            return *m_p_about;
        }

        const command_type& exit()
        const
        {
            return *m_p_exit;
        }

        const command_type& file_property()
        const
        {
            return *m_p_file_property;
        }

        const command_type& font_color()
        const
        {
            return *m_p_font_color;
        }

        const command_type& horizontally_zoom_in()
        const
        {
            return *m_p_horizontally_zoom_in;
        }

        const command_type& horizontally_zoom_out()
        const
        {
            return *m_p_horizontally_zoom_out;
        }

        const command_type& load_from_file()
        const
        {
            return *m_p_load_from_file;
        }

        std::unique_ptr<parameter_type> create_load_from_file_parameter(const path_type& path)
        const
        {
            return tetengo2::stdalt::make_unique<command::load_from_file::parameter_type>(path);
        }

        const command_type& new_file()
        const
        {
            return *m_p_new_file;
        }

        const command_type& nop()
        const
        {
            return *m_p_nop;
        }

        const command_type& reload()
        const
        {
            return *m_p_reload;
        }

        const command_type& save_to_file()
        const
        {
            return *m_p_save_to_file;
        }

        const command_type& ask_file_path_and_save_to_file()
        const
        {
            return *m_p_ask_file_path_and_save_to_file;
        }

        const command_type& set_horizontal_scale(const size_type index)
        const
        {
            return *m_p_set_horizontal_scale[index];
        }

        const command_type& set_vertical_scale(const size_type index)
        const
        {
            return *m_p_set_vertical_scale[index];
        }

        const command_type& train_kind()
        const
        {
            return *m_p_train_kind;
        }

        const command_type& vertically_zoom_in()
        const
        {
            return *m_p_vertically_zoom_in;
        }

        const command_type& vertically_zoom_out()
        const
        {
            return *m_p_vertically_zoom_out;
        }


    private:
        // types

        typedef std::unique_ptr<command_type> command_ptr_type;

        typedef boost::mpl::at<view_type_list, type::view::scale_list>::type scale_list_type;


        // static functions

        static command_ptr_type create_about(
            const message_catalog_type& message_catalog,
            const settings_type&        settings
        )
        {
            return tetengo2::stdalt::make_unique<command::about>(message_catalog, settings);
        }

        static command_ptr_type create_exit()
        {
            return tetengo2::stdalt::make_unique<command::exit>();
        }

        static command_ptr_type create_file_property(const message_catalog_type& message_catalog)
        {
            return tetengo2::stdalt::make_unique<command::file_property>(message_catalog);
        }

        static command_ptr_type create_font_color(const message_catalog_type& message_catalog)
        {
            return tetengo2::stdalt::make_unique<command::font_color>(message_catalog);
        }

        static command_ptr_type create_horizontally_zoom_in(diagram_view_type& diagram_view)
        {
            return tetengo2::stdalt::make_unique<command::horizontally_zoom_in>(diagram_view);
        }

        static command_ptr_type create_horizontally_zoom_out(diagram_view_type& diagram_view)
        {
            return tetengo2::stdalt::make_unique<command::horizontally_zoom_out>(diagram_view);
        }

        static command_ptr_type create_load_from_file(const load_from_file_type& load_from_file)
        {
            return tetengo2::stdalt::make_unique<command::load_from_file>(load_from_file);
        }

        static command_ptr_type create_new_file(const new_file_type& new_file)
        {
            return tetengo2::stdalt::make_unique<command::new_file>(new_file);
        }

        static command_ptr_type create_nop()
        {
            return tetengo2::stdalt::make_unique<command::nop>();
        }

        static command_ptr_type create_save_to_file(const save_to_file_type& save_to_file)
        {
            return tetengo2::stdalt::make_unique<command::save_to_file>(save_to_file);
        }

        static std::vector<command_ptr_type> create_set_horizontal_scale(diagram_view_type& diagram_view)
        {
            const scale_list_type scale_list;

            std::vector<command_ptr_type> commands;
            commands.reserve(scale_list.size());

            for (size_type i = 0; i < scale_list.size(); ++i)
            {
                commands.push_back(
                    tetengo2::stdalt::make_unique<command::set_horizontal_scale>(diagram_view, scale_list.at(i))
                );
            }

            return commands;
        }

        static std::vector<command_ptr_type> create_set_vertical_scale(diagram_view_type& diagram_view)
        {
            const scale_list_type scale_list;

            std::vector<command_ptr_type> commands;
            commands.reserve(scale_list.size());

            for (size_type i = 0; i < scale_list.size(); ++i)
            {
                commands.push_back(
                    tetengo2::stdalt::make_unique<command::set_vertical_scale>(diagram_view, scale_list.at(i))
                );
            }

            return commands;
        }

        static command_ptr_type create_train_kind(const message_catalog_type& message_catalog)
        {
            return tetengo2::stdalt::make_unique<command::train_kind>(message_catalog);
        }

        static command_ptr_type create_vertically_zoom_in(diagram_view_type& diagram_view)
        {
            return tetengo2::stdalt::make_unique<command::vertically_zoom_in>(diagram_view);
        }

        static command_ptr_type create_vertically_zoom_out(diagram_view_type& diagram_view)
        {
            return tetengo2::stdalt::make_unique<command::vertically_zoom_out>(diagram_view);
        }


        // variables

        const command_ptr_type m_p_about;

        const command_ptr_type m_p_exit;

        const command_ptr_type m_p_file_property;

        const command_ptr_type m_p_font_color;

        const command_ptr_type m_p_horizontally_zoom_in;

        const command_ptr_type m_p_horizontally_zoom_out;

        const command_ptr_type m_p_load_from_file;

        const command_ptr_type m_p_new_file;

        const command_ptr_type m_p_nop;

        const command_ptr_type m_p_reload;

        const command_ptr_type m_p_save_to_file;

        const command_ptr_type m_p_ask_file_path_and_save_to_file;

        const std::vector<command_ptr_type> m_p_set_horizontal_scale;

        const std::vector<command_ptr_type> m_p_set_vertical_scale;

        const command_ptr_type m_p_train_kind;

        const command_ptr_type m_p_vertically_zoom_in;

        const command_ptr_type m_p_vertically_zoom_out;


    };


    set::set(
        const new_file_type&          new_file,
        const load_from_file_type&    load_from_file,
        const load_from_file_type&    reload,
        const save_to_file_type&      save_to_file,
        const save_to_file_type&      ask_file_path_and_save_to_file,
        diagram_view_type&            diagram_view,
        const settings_type&          settings,
        const message_catalog_type&   message_catalog
    )
    :
    m_p_impl(
        tetengo2::stdalt::make_unique<impl>(
            new_file,
            load_from_file,
            reload,
            save_to_file,
            ask_file_path_and_save_to_file,
            diagram_view,
            settings,
            message_catalog
        )
    )
    {}

    set::~set()
    TETENGO2_STDALT_NOEXCEPT
    {}

    const set::command_type& set::about()
    const
    {
        return m_p_impl->about();
    }

    const set::command_type& set::exit()
    const
    {
        return m_p_impl->exit();
    }

    const set::command_type& set::file_property()
    const
    {
        return m_p_impl->file_property();
    }

    const set::command_type& set::font_color()
    const
    {
        return m_p_impl->font_color();
    }

    const set::command_type& set::horizontally_zoom_in()
    const
    {
        return m_p_impl->horizontally_zoom_in();
    }

    const set::command_type& set::horizontally_zoom_out()
    const
    {
        return m_p_impl->horizontally_zoom_out();
    }

    const set::command_type& set::load_from_file()
    const
    {
        return m_p_impl->load_from_file();
    }

    std::unique_ptr<set::parameter_type> set::create_load_from_file_parameter(const path_type& path)
    const
    {
        return m_p_impl->create_load_from_file_parameter(path);
    }

    const set::command_type& set::new_file()
    const
    {
        return m_p_impl->new_file();
    }

    const set::command_type& set::nop()
    const
    {
        return m_p_impl->nop();
    }

    const set::command_type& set::reload()
    const
    {
        return m_p_impl->reload();
    }

    const set::command_type& set::save_to_file()
    const
    {
        return m_p_impl->save_to_file();
    }

    const set::command_type& set::ask_file_path_and_save_to_file()
    const
    {
        return m_p_impl->ask_file_path_and_save_to_file();
    }

    const set::command_type& set::set_horizontal_scale(const size_type index)
    const
    {
        return m_p_impl->set_horizontal_scale(index);
    }

    const set::command_type& set::set_vertical_scale(const size_type index)
    const
    {
        return m_p_impl->set_vertical_scale(index);
    }

    const set::command_type& set::train_kind()
    const
    {
        return m_p_impl->train_kind();
    }

    const set::command_type& set::vertically_zoom_in()
    const
    {
        return m_p_impl->vertically_zoom_in();
    }

    const set::command_type& set::vertically_zoom_out()
    const
    {
        return m_p_impl->vertically_zoom_out();
    }


}}
