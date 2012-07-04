/*! \file
    \brief The definition of bobura::command::set_vertical_scale.

    Copyright (C) 2007-2012 kaoru

    $Id$
*/

#if !defined(BOBURA_COMMAND_SETVERTICALSCALE_H)
#define BOBURA_COMMAND_SETVERTICALSCALE_H

//#include <memory>

//#include <boost/mpl/at.hpp>

#include "bobura.basic_type_list.h"
#include "bobura.command.command_base.h"


namespace bobura { namespace command
{
    /*!
        \brief The class for a set-vertical-scale command.
    */
    class set_vertical_scale : public command_base
    {
    public:
        // types

        //! The base type.
        typedef command_base base_type;

        //! The diagram view type.
        typedef boost::mpl::at<view_type_list, type::view::view>::type diagram_view_type;

        //! The scale list type.
        typedef boost::mpl::at<view_type_list, type::view::scale_list>::type scale_list_type;

        //! The scale type.
        typedef scale_list_type::scale_type scale_type;


        // constructors and destructor

        /*!
            \brief Creates a set-vertical-scale command.

            \param diagram_view A diagram view.
            \param scale        A scale.
        */
        set_vertical_scale(diagram_view_type& diagram_view, const scale_type& scale);

        /*!
            \brief Destroys the set-vertical-scale command.
        */
        ~set_vertical_scale();


    private:
        // types

        class impl;


        // variables

        const std::unique_ptr<impl> m_p_impl;


        // virtual functions

        virtual void execute_impl(model_type& model, abstract_window_type& parent)
        const;


    };


}}


#endif
