/*! \file
    \brief The definition of bobura::command::nop.

    Copyright (C) 2007-2010 kaoru

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
        // constructors and destructor

        /*!
            \brief Creates a no-operation command.
        */
        nop()
        {}


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
