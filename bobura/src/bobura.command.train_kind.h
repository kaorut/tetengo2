/*! \file
    \brief The definition of bobura::command::train_kind.

    Copyright (C) 2007-2013 kaoru

    $Id$
*/

#if !defined(BOBURA_COMMAND_TRAINKIND_H)
#define BOBURA_COMMAND_TRAINKIND_H

//#include <memory>

//#include <boost/mpl/at.hpp>

#include "bobura.command.command_base.h"


namespace bobura { namespace command
{
    /*!
        \brief The class template for a train kind command.
    */
    class train_kind : public command_base
    {
    public:
        // types

        //! The base type.
        typedef command_base base_type;

        //! The train kind dialog type.
        typedef boost::mpl::at<dialog_type_list, type::dialog::train_kind_dialog>::type train_kind_dialog_type;

        //! The dialog base type.
        typedef train_kind_dialog_type::base_type dialog_base_type;

        //! The message catalog type.
        typedef train_kind_dialog_type::message_catalog_type message_catalog_type;


        // constructors and destructor

        /*!
            \brief Create a train kind command.

            \param message_catalog A message catalog.
        */
        explicit train_kind(const message_catalog_type& message_catalog);

        /*!
            \brief Destroys a train kind command.
        */
        ~train_kind();


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
