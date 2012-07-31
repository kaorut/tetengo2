/*! \file
    \brief The definition of bobura::command::command_base.

    Copyright (C) 2007-2012 kaoru

    $Id$
*/

#if !defined(BOBURA_COMMAND_COMMANDBASE_H)
#define BOBURA_COMMAND_COMMANDBASE_H

//#include <boost/mpl/at.hpp>

#include "bobura.basic_type_list.h"

namespace bobura { namespace command
{
    /*!
        \brief The class for a command base.
    */
    class command_base
    {
    public:
        // types

        //! The model type.
        typedef boost::mpl::at<model_type_list, type::model::model>::type model_type;

        //! The abstract window type.
        typedef boost::mpl::at<ui_type_list, type::ui::abstract_window>::type abstract_window_type;

        //! The state type.
        struct state_type { enum enum_t //!< Scoped enum.
        {
            default_, //!< Default state.
            checked,  //!< Checked state.
            selected, //!< Selected state.
        };};


        // functions

        /*!
            \brief Returns the enabled status.

            \param model A model.

            \retval true  When the command is enabled.
            \retval false Otherwise.
        */
        bool enabled(const model_type& model)
        const;

        /*!
            \brief Returns the state.

            \return The state.
        */
        state_type::enum_t state()
        const;

        /*!
            \brief Executes the command.

            \param model  A model.
            \param parent A parent window.
        */
        void execute(model_type& model, abstract_window_type& parent)
        const;


    private:
        // virtual functions

        virtual bool enabled_impl(const model_type& model)
        const;

        virtual state_type::enum_t state_impl()
        const;

        virtual void execute_impl(model_type& model, abstract_window_type& parent)
        const = 0;


    };


}}


#endif
