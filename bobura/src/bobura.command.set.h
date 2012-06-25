/*! \file
    \brief The definition of bobura::command::set.

    Copyright (C) 2007-2012 kaoru

    $Id$
*/

#if !defined(BOBURA_COMMAND_SET_H)
#define BOBURA_COMMAND_SET_H

//#include <memory>

//#include <boost/mpl/at.hpp>
//#include <boost/noncopyable.hpp>

#include <tetengo2.unique.h>

#include "bobura.command.about.h"
#include "bobura.command.command_base.h"
#include "bobura.command.exit.h"
#include "bobura.command.file_property.h"
#include "bobura.command.horizontally_zoom_in.h"
#include "bobura.command.horizontally_zoom_out.h"
#include "bobura.command.nop.h"


namespace bobura { namespace command
{
    /*!
        \brief The class template for a command set.

        \tparam Reader          A reader type.
        \tparam NewFile         A file initialization type.
        \tparam LoadFromFile    A file loading type.
        \tparam SaveToFile      A file saving type.
        \tparam DiagramView     A diagram view type.
        \tparam Settings        A settings type.
        \tparam MessageCatalog  A message catalog type.
    */
    template <
        typename NewFile,
        typename LoadFromFile,
        typename SaveToFile,
        typename DiagramView,
        typename Settings,
        typename MessageCatalog
    >
    class set : private boost::noncopyable
    {
    public:
        // types

        //! The file initialization type.
        typedef NewFile new_file_type;

        //! The file loading type.
        typedef LoadFromFile load_from_file_type;

        //! The file saving type.
        typedef SaveToFile save_to_file_type;

        //! The diagram view type.
        typedef DiagramView diagram_view_type;

        //! The settings type.
        typedef Settings settings_type;

        //! The message catalog type.
        typedef MessageCatalog message_catalog_type;

        //! The command type.
        typedef command_base command_type;

        //! The command pointer type.
        typedef std::unique_ptr<command_type> command_ptr_type;


        // constructors

        /*!
            \brief Creates a command set.

            \param new_file                   A file initialization.
            \param load_from_file             A file loading.
            \param reload                     A file reloading.
            \param save_to_file               A file saving.
            \param ask_file_path_save_to_file A file saving after file path query.
            \param diagram_view               A diagram view.
            \param settings                   Settings.
            \param message_catalog            A message catalog.
        */
        set(
            const new_file_type&          new_file,
            const load_from_file_type&    load_from_file,
            const load_from_file_type&    reload,
            const save_to_file_type&      save_to_file,
            const save_to_file_type&      ask_file_path_save_to_file,
            diagram_view_type&            diagram_view,
            const settings_type&          settings,
            const message_catalog_type&   message_catalog
        )
        :
        //m_p_load_from_file(create_load_from_file(load_from_file)),
        //m_p_new_file(create_new_file(new_file)),
        //m_p_reload(create_load_from_file(reload)),
        //m_p_save_to_file(create_save_to_file(save_to_file)),
        //m_p_ask_file_path_and_save_to_file(create_save_to_file(ask_file_path_save_to_file))
        m_p_about(create_about(message_catalog, settings)),
        m_p_exit(create_exit()),
        m_p_file_property(create_file_property(message_catalog)),
        m_p_horizontally_zoom_in(create_horizontally_zoom_in(diagram_view)),
        m_p_horizontally_zoom_out(create_horizontally_zoom_out(diagram_view)),
        m_p_load_from_file(create_nop()),
        m_p_new_file(create_nop()),
        m_p_nop(create_nop()),
        m_p_reload(create_nop()),
        m_p_save_to_file(create_nop()),
        m_p_ask_file_path_and_save_to_file(create_nop())
        {}


        // functions

        /*!
            \brief Returns the command about.

            \return The command.
        */
        const command_type& about()
        const
        {
            return *m_p_about;
        }

        /*!
            \brief Returns the command exit.

            \return The command.
        */
        const command_type& exit()
        const
        {
            return *m_p_exit;
        }

        /*!
            \brief Returns the command file property.

            \return The command.
        */
        const command_type& file_property()
        const
        {
            return *m_p_file_property;
        }

        /*!
            \brief Returns the command horizontal zoom-in.

            \return The command.
        */
        const command_type& horizontally_zoom_in()
        const
        {
            return *m_p_horizontally_zoom_in;
        }

        /*!
            \brief Returns the command horizontal zoom-out.

            \return The command.
        */
        const command_type& horizontally_zoom_out()
        const
        {
            return *m_p_horizontally_zoom_out;
        }

        /*!
            \brief Returns the command load-from-file.

            \return The command.
        */
        const command_type& load_from_file()
        const
        {
            return *m_p_load_from_file;
        }

        /*!
            \brief Returns the command new-file.

            \return The command.
        */
        const command_type& new_file()
        const
        {
            return *m_p_new_file;
        }

        /*!
            \brief Returns the command nop.

            \return The command.
        */
        const command_type& nop()
        const
        {
            return *m_p_nop;
        }

        /*!
            \brief Returns the command reload.

            \return The command.
        */
        const command_type& reload()
        const
        {
            return *m_p_reload;
        }

        /*!
            \brief Returns the command save-to-file.

            \return The command.
        */
        const command_type& save_to_file()
        const
        {
            return *m_p_save_to_file;
        }

        /*!
            \brief Returns the command save-to-file, in which a file selection
                   dialog is shown.

            \return The command.
        */
        const command_type& ask_file_path_and_save_to_file()
        const
        {
            return *m_p_ask_file_path_and_save_to_file;
        }


    private:
        // static functions

        static command_ptr_type create_about(
            const message_catalog_type& message_catalog,
            const settings_type&        settings
        )
        {
            return tetengo2::make_unique<bobura::command::about>(message_catalog, settings);
        }

        static command_ptr_type create_exit()
        {
            return tetengo2::make_unique<bobura::command::exit>();
        }

        static command_ptr_type create_file_property(const message_catalog_type& message_catalog)
        {
            return tetengo2::make_unique<bobura::command::file_property>(message_catalog);
        }

        static command_ptr_type create_horizontally_zoom_in(diagram_view_type& diagram_view)
        {
            return tetengo2::make_unique<bobura::command::horizontally_zoom_in>(diagram_view);
        }

        static command_ptr_type create_horizontally_zoom_out(diagram_view_type& diagram_view)
        {
            return tetengo2::make_unique<bobura::command::horizontally_zoom_out>(diagram_view);
        }

        //static command_ptr_type create_load_from_file(const load_from_file_type& load_from_file)
        //{
        //    return tetengo2::make_unique<typename boost::mpl::at<type_list_type, type::load_from_file>::type>(
        //        load_from_file
        //    );
        //}

        //static command_ptr_type create_new_file(const new_file_type& new_file)
        //{
        //    return tetengo2::make_unique<typename boost::mpl::at<type_list_type, type::new_file>::type>(new_file);
        //}

        static command_ptr_type create_nop()
        {
            return tetengo2::make_unique<bobura::command::nop>();
        }

        //static command_ptr_type create_save_to_file(const save_to_file_type& save_to_file)
        //{
        //    return tetengo2::make_unique<typename boost::mpl::at<type_list_type, type::save_to_file>::type>(
        //        save_to_file
        //    );
        //}


        // variables

        const command_ptr_type m_p_about;

        const command_ptr_type m_p_exit;

        const command_ptr_type m_p_file_property;

        const command_ptr_type m_p_horizontally_zoom_in;

        const command_ptr_type m_p_horizontally_zoom_out;

        const command_ptr_type m_p_load_from_file;

        const command_ptr_type m_p_new_file;

        const command_ptr_type m_p_nop;

        const command_ptr_type m_p_reload;

        const command_ptr_type m_p_save_to_file;

        const command_ptr_type m_p_ask_file_path_and_save_to_file;


    };


}}


#endif
