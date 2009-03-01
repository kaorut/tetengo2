/*! \file
    \brief The definition of concept_bobura::command::CommandTypeList.

    Copyright (C) 2007-2009 kaoru

    $Id$
*/

#if !defined(CONCEPTBOBURA_COMMAND_COMMANDTYPELIST_H)
#define CONCEPTBOBURA_COMMAND_COMMANDTYPELIST_H

#include <boost/concept_check.hpp>


namespace concept_bobura { namespace command
{
    /*!
        \brief The concept check class template for a command type list.

        \tparam Type A type.
    */
    template <typename Type>
    class CommandTypeList
    {
#if !defined(DOCUMENTATION)
    public:
        // typedef checks

        typedef typename Type::command_type command_type;

        typedef typename Type::about_type about_type;

        typedef typename Type::exit_type exit_type;

        typedef typename Type::nop_type nop_type;


        // usage checks

        BOOST_CONCEPT_USAGE(CommandTypeList)
        {}

        
#endif
    };


}}

#endif
