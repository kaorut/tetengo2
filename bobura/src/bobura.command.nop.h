/*! \file
    \brief The definition of bobura::command::nop.

    Copyright (C) 2007-2009 kaoru

    $Id$
*/

#if !defined(BOBURA_COMMAND_NOP_H)
#define BOBURA_COMMAND_NOP_H

#include <algorithm>


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

        /*!
            \brief Copies an nop command.

            \param another Another nop command object.
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
            \brief Swaps the members with another nop command object.

            \param another Another nop command object.
        */
        void swap(nop& another)
        throw ()
        {}

        /*!
            \brief Assigns another nop command object.

            \param another Another nop command object.

            \return this object.
        */
        nop& operator=(const nop& another)
        {
            nop(another).swap(*this);
            return *this;
        }

        /*!
            \brief Executes the command.
        */
        void operator()()
        const
        {}


    };


}}

namespace std
{
    /*!
        \brief Swaps two nop objects.

        \param nop1 A nop object #1.
        \param nop2 A nop object #2.
    */
    template <typename Name, typename Grade>
    void swap(bobura::command::nop& nop1, bobura::command::nop& nop2)
    throw ()
    {
        nop1.swap(nop2);
    }


}

#endif
