/*! \file
    \brief The definition of bobura::command::nop.

    Copyright (C) 2007-2012 kaoru

    $Id$
*/

#if !defined(BOBURA_COMMAND_NOP_H)
#define BOBURA_COMMAND_NOP_H


namespace bobura { namespace command
{
    /*!
        \brief The class template for a no-operation command.

        \tparam Model          A model type.
        \tparam AbstractWindow An abstract window type.
    */
    template <typename Model, typename AbstractWindow>
    class nop
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
            return true;
        }

        /*!
            \brief Executes the command.

            \param model  A model.
            \param parent A parent window.
        */
        void operator()(model_type& model, abstract_window_type& parent)
        const
        {}


    };


}}


#endif
