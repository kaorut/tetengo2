/*! \file
    \brief The definition of bobura::command::save_to_file.

    Copyright (C) 2007-2012 kaoru

    $Id$
*/

#if !defined(BOBURA_COMMAND_SAVETOFILE_H)
#define BOBURA_COMMAND_SAVETOFILE_H


namespace bobura { namespace command
{
    /*!
        \brief The class template for a save-to-file command.

        \tparam MessageBox      A message box type.
        \tparam FileSaveDialog  A file save dialog type.
        \tparam Model           A model type.
        \tparam Writer          A writer type.
        \tparam MessageCatalog  A message catalog type.
    */
    template <
        typename MessageBox,
        typename FileSaveDialog,
        typename Model,
        typename Writer,
        typename MessageCatalog
    >
    class save_to_file
    {
    public:
        // types

        //! The message box type.
        typedef MessageBox message_box_type;

        //! The file save dialog type.
        typedef FileSaveDialog file_save_dialog_type;

        //! The abstract window type.
        typedef
            typename file_save_dialog_type::abstract_window_type
            abstract_window_type;

        //! The model type.
        typedef Model model_type;

        //! The writer type.
        typedef Writer writer_type;

        //! The message catalog type.
        typedef MessageCatalog message_catalog_type;


        // constructors and destructor

        /*!
            \brief Creates a save-to-file command.

            \param parent            A parent window.
            \param model             A model.
            \param writer            A writer.
            \param message_catalog   A message catalog.
        */
        save_to_file(
            abstract_window_type&         parent,
            model_type&                   model,
            writer_type&                  writer,
            const message_catalog_type&   message_catalog
        )
        :
        m_parent(parent),
        m_model(model),
        m_writer(writer),
        m_message_catalog(message_catalog)
        {}


        // functions

        /*!
            \brief Executes the command.
        */
        void operator()()
        const
        {

        }


    private:
        // types


        // variables

        abstract_window_type& m_parent;

        model_type& m_model;

        writer_type& m_writer;

        const message_catalog_type& m_message_catalog;


        // functions


    };


}}


#endif
