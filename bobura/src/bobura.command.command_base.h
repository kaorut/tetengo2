/*! \file
    \brief The definition of bobura::command::command_base.

    Copyright (C) 2007-2013 kaoru

    $Id$
*/

#if !defined(BOBURA_COMMAND_COMMANDBASE_H)
#define BOBURA_COMMAND_COMMANDBASE_H

//#include <boost/mpl/at.hpp>

#include <tetengo2.stdalt.h>

#include "bobura.basic_type_list.h"


namespace bobura { namespace command
{
    /*!
        \brief The command parameter base type.
    */
    class parameter_base
    {
    public:
        // constructor and destructors

        /*!
            \brief Destroys the command parameter base.
        */
        virtual ~parameter_base()
        TETENGO2_STDALT_NOEXCEPT = 0;


        // functions

        /*!
            \brief Returns the derived instance.

            \tparam D A derived type.

            \return The derived instance.
        */
        template <typename D>
        const D& as()
        const
        {
            return dynamic_cast<const D&>(*this);
        }

        /*!
            \brief Returns the derived instance.

            \tparam D A derived type.

            \return The derived instance.
        */
        template <typename D>
        D& as()
        {
            return dynamic_cast<D&>(*this);
        }


    protected:
        // constructors

        /*!
            \brief Creates a command parameter base.
        */
        parameter_base();


    };

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
        enum class state_type
        {
            default_, //!< Default state.
            checked,  //!< Checked state.
            selected, //!< Selected state.
        };


        // constructors and destructor

        /*!
            \brief Destroys the command base.
        */
        virtual ~command_base()
        TETENGO2_STDALT_NOEXCEPT;


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
        state_type state()
        const;

        /*!
            \brief Executes the command.

            \param model  A model.
            \param parent A parent window.
        */
        void execute(model_type& model, abstract_window_type& parent)
        const;

        /*!
            \brief Executes the command.

            \param model     A model.
            \param parent    A parent window.
            \param parameter A parameter.
        */
        void execute(model_type& model, abstract_window_type& parent, const parameter_base& parameter)
        const;


    private:
        // virtual functions

        virtual bool enabled_impl(const model_type& model)
        const;

        virtual state_type state_impl()
        const;

        virtual void execute_impl(model_type& model, abstract_window_type& parent)
        const = 0;

        virtual void execute_impl(model_type& model, abstract_window_type& parent, const parameter_base& parameter)
        const;


    };


}}


#endif
