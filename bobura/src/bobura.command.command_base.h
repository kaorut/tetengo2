/*! \file
    \brief The definition of bobura::command::command_base.

    Copyright (C) 2007-2012 kaoru

    $Id$
*/

#if !defined(BOBURA_COMMAND_COMMANDBASE_H)
#define BOBURA_COMMAND_COMMANDBASE_H


namespace bobura { namespace command
{
    /*!
        \brief The class for a command base.
    */
    class command_base
    {
    public:
        // functions

        /*!
            \brief Returns the enabled status.

            \retval true  When the command is enabled.
            \retval false Otherwise.
        */
        bool enabled()
        const
        {
            return enabled_impl();
        }


    private:
        // virtual functions

        virtual bool enabled_impl()
        const = 0;


    };


}}


#endif
