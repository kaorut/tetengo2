/*! \file
    \brief The definition of bobura::command::open_www_tetengo_org.

    Copyright (C) 2007-2014 kaoru

    $Id$
*/

#if !defined(BOBURA_COMMAND_OPENWWWTETENGOORG_H)
#define BOBURA_COMMAND_OPENWWWTETENGOORG_H

//#include <memory>

#include <tetengo2.stdalt.h>

#include "bobura.command.command_base.h"


namespace bobura { namespace command
{
    /*!
        \brief The class template for an open-www.tetengo.org command.
    */
    class open_www_tetengo_org : public command_base
    {
    public:
        // types

        //! The base type.
        typedef command_base base_type;


        // constructors and destructor

        /*!
            \brief Create an open-www.tetengo.org command.
        */
        open_www_tetengo_org();

        /*!
            \brief Destroys the open-www.tetengo.org command.
        */
        virtual ~open_www_tetengo_org()
        TETENGO2_STDALT_NOEXCEPT;


    private:
        // types

        class impl;


        // variables

        const std::unique_ptr<impl> m_p_impl;


        // virtual functions

        virtual void execute_impl(model_type& model, abstract_window_type& parent)
        const override;


    };


}}


#endif
