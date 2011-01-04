/*! \file
    \brief The definition of bobura::command::about.

    Copyright (C) 2007-2011 kaoru

    $Id$
*/

#if !defined(BOBURA_COMMAND_ABOUT_H)
#define BOBURA_COMMAND_ABOUT_H


namespace bobura { namespace command
{
    /*!
        \brief The class template for an about command.

        \tparam AboutDialog    An about dialog type.
    */
    template <typename AboutDialog>
    class about
    {
    public:
        // types

        //! The about dialog type.
        typedef AboutDialog about_dialog_type;

        //! The abstract window type.
        typedef
            typename about_dialog_type::abstract_window_type
            abstract_window_type;

        //! The message catalog type.
        typedef
            typename about_dialog_type::message_catalog_type
            message_catalog_type;


        // constructors and destructor

        /*!
            \brief Creates an about command.

            \param parent          A parent window.
            \param message_catalog A message catalog.
        */
        about(
            abstract_window_type&       parent,
            const message_catalog_type& message_catalog
        )
        :
        m_p_parent(&parent),
        m_p_message_catalog(&message_catalog)
        {}


        // functions

        /*!
            \brief Executes the command.
        */
        void operator()()
        {
            about_dialog_type(*m_p_parent, *m_p_message_catalog).do_modal();
        }


    private:
        // variables

        abstract_window_type* m_p_parent;

        const message_catalog_type* m_p_message_catalog;


    };


}}


#endif
