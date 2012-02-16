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
        \tparam Model           A model type.
        \tparam Reader          A reader type.
        \tparam Writer          A writer type.
        \tparam MainWindow      A main window type.
        \tparam ConfirmFileSave A file save confirmation type.
        \tparam Settings        A settings type.
        \tparam MessageCatalog  A message catalog type.
    */
    template <
        typename TypeList,
        typename Model,
        typename Reader,
        //typename Writer,
        typename MainWindow,
        typename ConfirmFileSave,
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
        typedef
            typename boost::mpl::at<type_list_type, type::command>::type
            command_type;

        //! The model type.
        typedef Model model_type;

        //! The reader type.
        typedef Reader reader_type;

        //! The writer type.
        //typedef Writer writer_type;

        //! The main window type.
        typedef MainWindow main_window_type;

        //! The file save confirmation type.
        typedef ConfirmFileSave confirm_file_save_type;

        //! The settings type.
        typedef Settings settings_type;

        //! The message catalog type.
        typedef MessageCatalog message_catalog_type;


        // constructors

        /*!
            \brief Creates a command set.

            \param model             A model.
            \param reader            A reader.
            \param writer            A writer.
            \param main_window       A main window.
            \param confirm_file_save A file save confirmation.
            \param settings          Settings.
            \param message_catalog   A message catalog.
        */
        set(
            model_type&                   model,
            reader_type&                  reader,
            //writer_type&                  writer,
            main_window_type&             main_window,
            const confirm_file_save_type& confirm_file_save,
            const settings_type&          settings,
            const message_catalog_type&   message_catalog
        )
        :
        m_about(make_about(main_window, message_catalog, settings)),
        m_exit(make_exit(main_window)),
        m_file_property(
            make_file_property(main_window, model, message_catalog)
        ),
        m_load_from_file(
            make_load_from_file(
                main_window, confirm_file_save, model, reader, message_catalog
            )
        ),
        m_new_file(make_new_file(main_window, confirm_file_save, model)),
        m_nop(make_nop()),
        m_save_to_file(
            make_save_to_file(main_window, model, /*writer, */message_catalog)
        )
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
            \brief Returns the command save-to-file.

            \return The command.
        */
        const command_type& save_to_file()
        const
        {
            return m_save_to_file;
        }


    private:
        // static functions

        static command_type make_about(
            main_window_type&           main_window,
            const message_catalog_type& message_catalog,
            const settings_type&        settings
        )
        {
            return typename boost::mpl::at<type_list_type, type::about>::type(
                main_window, message_catalog, settings
            );
        }

        static command_type make_exit(main_window_type& main_window)
        {
            return typename boost::mpl::at<type_list_type, type::exit>::type(
                main_window
            );
        }

        static command_type make_file_property(
            main_window_type&           main_window,
            model_type&                 model,
            const message_catalog_type& message_catalog
        )
        {
            return typename boost::mpl::at<
                type_list_type, type::file_property
            >::type(main_window, model, message_catalog);
        }

        static command_type make_load_from_file(
            main_window_type&             main_window,
            const confirm_file_save_type& confirm_file_save,
            model_type&                   model,
            reader_type&                  reader,
            const message_catalog_type&   message_catalog
        )
        {
            return typename boost::mpl::at<
                type_list_type, type::load_from_file
            >::type(
                main_window, confirm_file_save, model, reader, message_catalog
            );
        }

        static command_type make_new_file(
            main_window_type&             main_window,
            const confirm_file_save_type& confirm_file_save,
            model_type&                   model
        )
        {
            return typename boost::mpl::at<
                type_list_type, type::new_file
            >::type(main_window, confirm_file_save, model);
        }

        static command_type make_nop()
        {
            return typename boost::mpl::at<type_list_type, type::nop>::type();
        }

        static command_type make_save_to_file(
            main_window_type&             main_window,
            model_type&                   model,
            //writer_type&                  writer,
            const message_catalog_type&   message_catalog
        )
        {
            return typename boost::mpl::at<
                type_list_type, type::save_to_file
            >::type(
                main_window, model, /*writer, */message_catalog
            );
        }


        // variables

        const command_type m_about;

        const command_type m_exit;

        const command_type m_file_property;

        const command_type m_load_from_file;

        const command_type m_new_file;

        const command_type m_nop;

        const command_type m_save_to_file;

    };


}}


#endif
