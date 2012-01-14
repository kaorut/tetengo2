/*! \file
    \brief The definition of bobura::command::set.

    Copyright (C) 2007-2012 kaoru

    $Id$
*/

#if !defined(BOBURA_COMMAND_SET_H)
#define BOBURA_COMMAND_SET_H

#include <boost/mpl/at.hpp>
#include <boost/noncopyable.hpp>

#include "bobura.command.type_list.h"


namespace bobura { namespace command
{
    /*!
        \brief The class template for a command set.

        \tparam TypeList A command type list type.
    */
    template <typename TypeList>
    class set : private boost::noncopyable
    {
    public:
        // types

        //! The command type list type.
        typedef TypeList type_list_type;

        //! The command type.
        typedef
            typename boost::mpl::at<type_list_type, type::command>::type
            command_type;


        // constructors

        /*!
            \brief Creates a command set.
        */
        set()
        :
        m_nop(make_nop())
        {}


        // functions

        const command_type& nop()
        const
        {
            return m_nop;
        }


    private:
        // types

        const command_type m_nop;


        // static functions

        command_type make_nop()
        {
            return typename boost::mpl::at<type_list_type, type::nop>::type();
        }


    };


}}


#endif
