/*! \file
    \brief The definition of bobura::command::command_base.

    Copyright (C) 2007-2012 kaoru

    $Id$
*/

#if !defined(BOBURA_COMMAND_COMMANDBASE_H)
#define BOBURA_COMMAND_COMMANDBASE_H

#include <boost/mpl/at.hpp>


namespace bobura { namespace command
{
    /*!
        \brief The class for a command base.
    */
    class command_base
    {
    public:
        // types

        //! The model type.
        typedef int model_type;

        //! The abstract window type.
        typedef int abstract_window_type;


        // functions

        /*!
            \brief Returns the enabled status.

            \param model A model.

            \retval true  When the command is enabled.
            \retval false Otherwise.
        */
        bool enabled(const model_type& model)
        const;

        /*!
            \brief Executes the command.

            \param model  A model.
            \param parent A parent window.
        */
        void execute(model_type& model, abstract_window_type& parent)
        const;


    private:
        // virtual functions

        virtual bool enabled_impl(const model_type& model)
        const = 0;

        virtual void execute_impl(model_type& model, abstract_window_type& parent)
        const = 0;


    };


}}


#endif
