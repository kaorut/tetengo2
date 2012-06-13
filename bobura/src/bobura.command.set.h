/*! \file
    \brief The definition of bobura::command::set.

    Copyright (C) 2007-2012 kaoru

    $Id$
*/

#if !defined(BOBURA_COMMAND_SET_H)
#define BOBURA_COMMAND_SET_H

#include <boost/mpl/at.hpp>
#include <boost/noncopyable.hpp>

#include "bobura.command.type_list.h"


namespace bobura { namespace command
{
    /*!
        \brief The class template for a command set.

        \tparam TypeList        A command type list type.
        \tparam Reader          A reader type.
        \tparam NewFile         A file initialization type.
        \tparam LoadFromFile    A file loading type.
        \tparam SaveToFile      A file saving type.
        \tparam Settings        A settings type.
        \tparam MessageCatalog  A message catalog type.
    */
    template <
        typename TypeList,
        typename NewFile,
        typename LoadFromFile,
        typename SaveToFile,
        typename Settings,
        typename MessageCatalog
    >
    class set : private boost::noncopyable
    {
    public:
        // types

        //! The command type list type.
        typedef TypeList type_list_type;

        //! The command type.
        typedef typename boost::mpl::at<type_list_type, type::command>::type command_type;

        //! The file initialization type.
        typedef NewFile new_file_type;

        //! The file loading type.
        typedef LoadFromFile load_from_file_type;

        //! The file saving type.
        typedef SaveToFile save_to_file_type;

        //! The settings type.
        typedef Settings settings_type;

        //! The message catalog type.
        typedef MessageCatalog message_catalog_type;


        // constructors

        /*!
            \brief Creates a command set.

            \param new_file                   A file initialization.
            \param load_from_file             A file loading.
            \param load_from_file             A file reloading.
            \param save_to_file               A file saving.
            \param ask_file_path_save_to_file A file saving after file path query.
            \param settings                   Settings.
            \param message_catalog            A message catalog.
        */
        set(
            const new_file_type&          new_file,
            const load_from_file_type&    load_from_file,
            const load_from_file_type&    reload,
            const save_to_file_type&      save_to_file,
            const save_to_file_type&      ask_file_path_save_to_file,
            const settings_type&          settings,
            const message_catalog_type&   message_catalog
        )
        :
        m_about(make_about(message_catalog, settings)),
        m_exit(make_exit()),
        m_file_property(make_file_property(message_catalog)),
        m_load_from_file(make_load_from_file(load_from_file)),
        m_new_file(make_new_file(new_file)),
        m_nop(make_nop()),
        m_reload(make_load_from_file(reload)),
        m_save_to_file(make_save_to_file(save_to_file)),
        m_ask_file_path_and_save_to_file(make_save_to_file(ask_file_path_save_to_file))
        {}


        // functions

        /*!
            \brief Returns the command about.

            \return The command.
        */
        const command_type& about()
        const
        {
            return m_about;
        }

        /*!
            \brief Returns the command exit.

            \return The command.
        */
        const command_type& exit()
        const
        {
            return m_exit;
        }

        /*!
            \brief Returns the command file property.

            \return The command.
        */
        const command_type& file_property()
        const
        {
            return m_file_property;
        }

        /*!
            \brief Returns the command load-from-file.

            \return The command.
        */
        const command_type& load_from_file()
        const
        {
            return m_load_from_file;
        }

        /*!
            \brief Returns the command new-file.

            \return The command.
        */
        const command_type& new_file()
        const
        {
            return m_new_file;
        }

        /*!
            \brief Returns the command nop.

            \return The command.
        */
        const command_type& nop()
        const
        {
            return m_nop;
        }

        /*!
            \brief Returns the command reload.

            \return The command.
        */
        const command_type& reload()
        const
        {
            return m_reload;
        }

        /*!
            \brief Returns the command save-to-file.

            \return The command.
        */
        const command_type& save_to_file()
        const
        {
            return m_save_to_file;
        }

        /*!
            \brief Returns the command save-to-file, in which a file selection
                   dialog is shown.

            \return The command.
        */
        const command_type& ask_file_path_and_save_to_file()
        const
        {
            return m_ask_file_path_and_save_to_file;
        }


    private:
        // static functions

        static command_type make_about(const message_catalog_type& message_catalog, const settings_type& settings)
        {
            return typename boost::mpl::at<type_list_type, type::about>::type(message_catalog, settings);
        }

        static command_type make_exit()
        {
            return typename boost::mpl::at<type_list_type, type::exit>::type();
        }

        static command_type make_file_property(const message_catalog_type& message_catalog)
        {
            return typename boost::mpl::at<type_list_type, type::file_property>::type(message_catalog);
        }

        static command_type make_load_from_file(const load_from_file_type& load_from_file)
        {
            return typename boost::mpl::at<type_list_type, type::load_from_file>::type(load_from_file);
        }

        static command_type make_new_file(const new_file_type& new_file)
        {
            return typename boost::mpl::at<type_list_type, type::new_file>::type(new_file);
        }

        static command_type make_nop()
        {
            return typename boost::mpl::at<type_list_type, type::nop>::type();
        }

        static command_type make_save_to_file(const save_to_file_type& save_to_file)
        {
            return typename boost::mpl::at<type_list_type, type::save_to_file>::type(save_to_file);
        }


        // variables

        const command_type m_about;

        const command_type m_exit;

        const command_type m_file_property;

        const command_type m_load_from_file;

        const command_type m_new_file;

        const command_type m_nop;

        const command_type m_reload;

        const command_type m_save_to_file;

        const command_type m_ask_file_path_and_save_to_file;


    };


}}


#endif
