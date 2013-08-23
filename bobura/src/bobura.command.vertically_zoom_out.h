/*! \file
    \brief The definition of bobura::command::vertically_zoom_out.

    Copyright (C) 2007-2013 kaoru

    $Id$
*/

#if !defined(BOBURA_COMMAND_VERTICALLYZOOMOUT_H)
#define BOBURA_COMMAND_VERTICALLYZOOMOUT_H

//#include <memory>

//#include <boost/mpl/at.hpp>

#include <tetengo2.stdalt.h>

#include "bobura.command.command_base.h"


namespace bobura { namespace command
{
    /*!
        \brief The class for a vertical zoom-out command.
    */
    class vertically_zoom_out : public command_base
    {
    public:
        // types

        //! The base type.
        typedef command_base base_type;

        //! The diagram view type.
        typedef boost::mpl::at<view_type_list, type::view::view>::type diagram_view_type;


        // constructors and destructor

        /*!
            \brief Creates a vertical zoom-out command.

            \param diagram_view A diagram view.
        */
        explicit vertically_zoom_out(diagram_view_type& diagram_view);

        /*!
            \brief Destroys the vertical zoom-out command.
        */
        virtual ~vertically_zoom_out()
        TETENGO2_STDALT_NOEXCEPT;


    private:
        // types

        class impl;


        // variables

        const std::unique_ptr<impl> m_p_impl;


        // virtual functions

        virtual void execute_impl(model_type& model, abstract_window_type& parent)
        const override;


    };


}}


#endif
