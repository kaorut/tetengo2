/*! \file
    \brief The definition of bobura::command::new_file.

    Copyright (C) 2007-2012 kaoru

    $Id$
*/

#if !defined(BOBURA_COMMAND_NEWFILE_H)
#define BOBURA_COMMAND_NEWFILE_H

#include "bobura.command.command_base.h"


namespace bobura { namespace command
{
    /*!
        \brief The class template for a new-file command.

        \tparam Model          A model type.
        \tparam AbstractWindow An abstract window type.
        \tparam NewFile        A file initialization type.
    */
    template <typename Model, typename AbstractWindow, typename NewFile>
    class new_file : public command_base<Model, AbstractWindow>
    {
    public:
        // types

        //! The model type.
        typedef Model model_type;

        //! The abstract window type.
        typedef AbstractWindow abstract_window_type;

        //! The base type.
        typedef command_base<model_type, abstract_window_type> base_type;

        //! The file initialization type.
        typedef NewFile new_file_type;


        // constructors and destructor

        /*!
            \brief Creates a new-file command.

            \param new_file A file initialization type.
        */
        explicit new_file(const new_file_type& new_file)
        :
        m_new_file(new_file)
        {}


    private:
        // variables

        const new_file_type& m_new_file;


        // virtual functions

        virtual bool enabled_impl(const model_type& model)
        const
        {
            return true;
        }

        virtual void execute_impl(model_type& model, abstract_window_type& parent)
        const
        {
            m_new_file(model, parent);
        }


    };


}}


#endif
