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
        \brief The class template for a command base.

        \tparam Model          A model type.
        \tparam AbstractWindow An abstract window type.
    */
    template <typename Model, typename AbstractWindow>
    class command_base
    {
    public:
        // types

        //! The model type.
        typedef Model model_type;

        //! The abstract window type.
        typedef AbstractWindow abstract_window_type;


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

        /*!
            \brief Executes the command.

            \param model  A model.
            \param parent A parent window.
        */
        void execute(model_type& model, abstract_window_type& parent)
        const
        {
            execute_impl(model, parent);
        }


    private:
        // virtual functions

        virtual bool enabled_impl()
        const = 0;

        virtual void execute_impl(model_type& model, abstract_window_type& parent)
        const = 0;


    };


}}


#endif
