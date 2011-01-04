/*! \file
    \brief The definition of bobura::command::nop.

    Copyright (C) 2007-2011 kaoru

    $Id$
*/

#if !defined(BOBURA_COMMAND_NOP_H)
#define BOBURA_COMMAND_NOP_H


namespace bobura { namespace command
{
    /*!
        \brief The class for a no-operation command.
    */
    class nop
    {
    public:
        // functions

        /*!
            \brief Executes the command.
        */
        void operator()()
        const
        {}


    };


}}


#endif
