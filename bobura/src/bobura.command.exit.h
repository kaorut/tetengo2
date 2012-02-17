/*! \file
    \brief The definition of bobura::command::exit.

    Copyright (C) 2007-2012 kaoru

    $Id$
*/

#if !defined(BOBURA_COMMAND_EXIT_H)
#define BOBURA_COMMAND_EXIT_H


namespace bobura { namespace command
{
    /*!
        \brief The class template for an exit command.

        \tparam Model          A model type.
        \tparam AbstractWindow An abstract window type.
    */
    template <typename Model, typename AbstractWindow>
    class exit
    {
    public:
        // types

        //! The model type.
        typedef Model model_type;

        //! The abstract window type.
        typedef AbstractWindow abstract_window_type;


        // constructors and destructor

        /*!
            \brief Creates an exit command.

            \param window A window.
        */
        explicit exit(abstract_window_type& window)
        :
        m_window(window)
        {}


        // functions

        /*!
            \brief Executes the command.

            \param model  A model.
            \param parent A parent window.
        */
        void operator()(model_type& model, abstract_window_type& parent)
        {
            m_window.close();
        }


    private:
        // variables

        abstract_window_type& m_window;


    };


}}


#endif
