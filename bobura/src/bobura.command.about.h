/*! \file
    \brief The definition of bobura::command::about.

    Copyright (C) 2007-2012 kaoru

    $Id$
*/

#if !defined(BOBURA_COMMAND_ABOUT_H)
#define BOBURA_COMMAND_ABOUT_H


namespace bobura { namespace command
{
    /*!
        \brief The class template for an about command.

        \tparam Model          A model type.
        \tparam AbstractWindow An abstract window type.
        \tparam AboutDialog    An about dialog type.
    */
    template <typename Model, typename AbstractWindow, typename AboutDialog>
    class about
    {
    public:
        // types

        //! The model type.
        typedef Model model_type;

        //! The abstract window type.
        typedef AbstractWindow abstract_window_type;

        //! The about dialog type.
        typedef AboutDialog about_dialog_type;

        //! The message catalog type.
        typedef
            typename about_dialog_type::message_catalog_type
            message_catalog_type;

        //! The settings type.
        typedef typename about_dialog_type::settings_type settings_type;


        // constructors and destructor

        /*!
            \brief Creates an about command.

            \param parent          A parent window.
            \param message_catalog A message catalog.
            \param settings        Settings type.
        */
        about(
            abstract_window_type&       parent,
            const message_catalog_type& message_catalog,
            const settings_type&        settings
        )
        :
        m_parent(parent),
        m_message_catalog(message_catalog),
        m_settings(settings)
        {}


        // functions

        /*!
            \brief Executes the command.

            \param model  A model.
            \param parent A parent window.
        */
        void operator()(model_type& model, abstract_window_type& parent)
        {
            about_dialog_type(
                m_parent, m_message_catalog, m_settings
            ).do_modal();
        }


    private:
        // variables

        abstract_window_type& m_parent;

        const message_catalog_type& m_message_catalog;

        const settings_type& m_settings;


    };


}}


#endif
