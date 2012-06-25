/*! \file
    \brief The definition of bobura::command::exit.

    Copyright (C) 2007-2012 kaoru

    $Id$
*/

#if !defined(BOBURA_COMMAND_EXIT_H)
#define BOBURA_COMMAND_EXIT_H

#include "bobura.command.command_base.h"


namespace bobura { namespace command
{
    /*!
        \brief The class for an exit command.
    */
    class exit : public command_base
    {
    public:
        // types

        //! The base type.
        typedef command_base base_type;


        // constructors and destructor

        /*!
            \brief Creates an about command.
        */
        exit();

        /*!
            \brief Destroys the about command.
        */
        ~exit();


    private:
        // types

        class impl;


        // variables

        const std::unique_ptr<impl> m_p_impl;


        // virtual functions

        virtual bool enabled_impl(const model_type& model)
        const;

        virtual void execute_impl(model_type& model, abstract_window_type& parent)
        const;


    };


}}


#endif
