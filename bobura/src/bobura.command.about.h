/*! \file
    \brief The definition of bobura::command::about.

    Copyright (C) 2007-2012 kaoru

    $Id$
*/

#if !defined(BOBURA_COMMAND_ABOUT_H)
#define BOBURA_COMMAND_ABOUT_H

#include "bobura.command.command_base.h"


namespace bobura { namespace command
{
    /*!
        \brief The class template for an about command.

        \tparam Model          A model type.
        \tparam AbstractWindow An abstract window type.
        \tparam AboutDialog    An about dialog type.
    */
    template <typename Model, typename AbstractWindow, typename AboutDialog>
    class about : public command_base
    {
    public:
        // types

        //! The model type.
        typedef Model model_type;

        //! The abstract window type.
        typedef AbstractWindow abstract_window_type;

        //! The base type.
        typedef command_base base_type;

        //! The about dialog type.
        typedef AboutDialog about_dialog_type;

        //! The message catalog type.
        typedef typename about_dialog_type::message_catalog_type message_catalog_type;

        //! The settings type.
        typedef typename about_dialog_type::settings_type settings_type;


        // constructors and destructor

        /*!
            \brief Creates an about command.

            \param message_catalog A message catalog.
            \param settings        Settings type.
        */
        about(const message_catalog_type& message_catalog, const settings_type& settings)
        :
        m_message_catalog(message_catalog),
        m_settings(settings)
        {}


    private:
        // variables

        const message_catalog_type& m_message_catalog;

        const settings_type& m_settings;


        // virtual functions

        virtual bool enabled_impl(const model_type& model)
        const
        {
            return true;
        }

        virtual void execute_impl(model_type& model, abstract_window_type& parent)
        const
        {
            about_dialog_type(parent, m_message_catalog, m_settings).do_modal();
        }


    };


}}


#endif
