/*! \file
    \brief The definition of bobura::command::about.

    Copyright (C) 2007-2010 kaoru

    $Id$
*/

#if !defined(BOBURA_COMMAND_ABOUT_H)
#define BOBURA_COMMAND_ABOUT_H


namespace bobura { namespace command
{
    /*!
        \brief The class template for an about command.

        \tparam AboutDialog An about dialog type.
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


        // constructors and destructor

        /*!
            \brief Creates an about command.

            \param parent A parent window.
        */
        explicit about(abstract_window_type& parent)
        :
        m_p_parent(&parent)
        {}


        // functions

        /*!
            \brief Executes the command.
        */
        void operator()()
        {
            about_dialog_type(*m_p_parent).do_modal();
        }


    private:
        // variables

        abstract_window_type* m_p_parent;


    };


}}


#endif
