/*! \file
    \brief The definition of bobura::command::nop.

    Copyright (C) 2007-2010 kaoru

    $Id$
*/

#if !defined(BOBURA_COMMAND_NOP_H)
#define BOBURA_COMMAND_NOP_H

#include <tetengo2.assignable.h>
#include <tetengo2.swappable.h>


namespace bobura { namespace command
{
    /*!
        \brief The class for a no-operation command.
    */
    class nop :
        public tetengo2::assignable<nop>,
        private tetengo2::swappable<nop>
    {
    public:
        // constructors and destructor

        /*!
            \brief Creates a no-operation command.
        */
        nop()
        {}

        /*!
            \brief Copies an nop command.

            \param another Another nop command.
        */
        nop(const nop& another)
        {}

        /*!
            \brief Destroys the no-operation command.
        */
        ~nop()
        throw ()
        {}


        // functions

        /*!
            \brief Swaps the members with another nop command.

            \param another Another nop command.
        */
        void swap(nop& another)
        throw ()
        {}

        /*!
            \brief Assigns another nop command.

            \param another Another nop command.

            \return This object.
        */
        nop& operator=(const nop& another)
        {
            return assign(another);
        }

        /*!
            \brief Executes the command.
        */
        void operator()()
        const
        {}


    };


}}


#endif
