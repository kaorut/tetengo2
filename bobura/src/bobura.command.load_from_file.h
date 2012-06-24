/*! \file
    \brief The definition of bobura::command::load_from_file.

    Copyright (C) 2007-2012 kaoru

    $Id$
*/

#if !defined(BOBURA_COMMAND_LOADFROMFILE_H)
#define BOBURA_COMMAND_LOADFROMFILE_H

#include "bobura.command.command_base.h"


namespace bobura { namespace command
{
    /*!
        \brief The class template for a load-from-file command.

        \tparam Model           A model type.
        \tparam AbstractWindow  An abstract window type.
        \tparam LoadFromFile    A file loading type.
    */
    template <typename Model, typename AbstractWindow, typename LoadFromFile>
    class load_from_file : public command_base
    {
    public:
        // types

        //! The model type.
        typedef Model model_type;

        //! The abstract window type.
        typedef AbstractWindow abstract_window_type;

        //! The base type.
        typedef command_base base_type;

        //! The file loading type.
        typedef LoadFromFile load_from_file_type;


        // constructors and destructor

        /*!
            \brief Creates a load-from-file command.

            \param load_from_file A file loading.
        */
        explicit load_from_file(const load_from_file_type& load_from_file)
        :
        m_load_from_file(load_from_file)
        {}


    private:
        // variables

        const load_from_file_type& m_load_from_file;


        // virtual functions

        virtual bool enabled_impl(const model_type& model)
        const
        {
            return m_load_from_file.reloadable(model);
        }

        /*!
            \brief Executes the command.

            \param model  A model.
            \param parent A parent window.
        */
        virtual void execute_impl(model_type& model, abstract_window_type& parent)
        const
        {
            m_load_from_file(model, parent);
        }


    };


}}


#endif
