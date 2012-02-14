/*! \file
    \brief The definition of bobura::command::new_file.

    Copyright (C) 2007-2012 kaoru

    $Id$
*/

#if !defined(BOBURA_COMMAND_NEWFILE_H)
#define BOBURA_COMMAND_NEWFILE_H

#include <tetengo2.unique.h>


namespace bobura { namespace command
{
    /*!
        \brief The class template for a new-file command.

        \tparam AbstractWindow  An abstract window type.
        \tparam Model           A model type.
        \tparam ConfirmFileSave A file save confirmation type.
    */
    template <
        typename AbstractWindow,
        typename Model,
        typename ConfirmFileSave
    >
    class new_file
    {
    public:
        // types

        //! The abstract window type.
        typedef AbstractWindow abstract_window_type;

        //! The model type.
        typedef Model model_type;

        //! The file save confirmation type.
        typedef ConfirmFileSave confirm_file_save_type;


        // constructors and destructor

        /*!
            \brief Creates a new-file command.

            \param parent            A parent window.
            \param confirm_file_save A file save confirmation.
            \param model             A model.
        */
        new_file(
            abstract_window_type&         parent,
            const confirm_file_save_type& confirm_file_save,
            model_type&                   model
        )
        :
        m_parent(parent),
        m_confirm_file_save(confirm_file_save),
        m_model(model)
        {}


        // functions

        /*!
            \brief Executes the command.
        */
        void operator()()
        const
        {
            if (m_confirm_file_save(m_parent))
                return;

            m_model.reset_timetable(
                tetengo2::make_unique<timetable_type>(string_type()),
                path_type()
            );
        }


    private:
        // types

        typedef typename model_type::path_type path_type;

        typedef typename model_type::timetable_type timetable_type;

        typedef typename timetable_type::string_type string_type;


        // variables

        abstract_window_type& m_parent;

        const confirm_file_save_type& m_confirm_file_save;

        model_type& m_model;


    };


}}


#endif
