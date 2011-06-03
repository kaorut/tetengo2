/*! \file
    \brief The definition of tetengo2::gui::link_label.

    Copyright (C) 2007-2011 kaoru

    $Id$
*/

#if !defined(TETENGO2_GUI_LINKLABEL_H)
#define TETENGO2_GUI_LINKLABEL_H

//#include <stdexcept>

#include "tetengo2.cpp0x.h"
#include "tetengo2.gui.label.h"
#include "tetengo2.gui.measure.h"


namespace tetengo2 { namespace gui
{
    /*!
        \brief The class template for a link label.

        \tparam Traits                A traits type.
        \tparam WidgetDetails         A detail implementation type of a
                                      widget.
        \tparam MessageHandlerDetails A detail implementation type of a
                                      message handler.
   */
    template <
        typename Traits,
        typename WidgetDetails,
        typename MessageHandlerDetails
    >
    class link_label :
        public label<
            typename Traits::base_type, WidgetDetails, MessageHandlerDetails
        >
    {
    public:
        // types

        //! The traits type.
        typedef Traits traits_type;

        //! The detail implementation type of a widget.
        typedef WidgetDetails widget_details_type;

        //! The detail implementation type of a message handler.
        typedef MessageHandlerDetails message_handler_details_type;

        //! The base type.
        typedef
            label<
                typename traits_type::base_type,
                widget_details_type,
                message_handler_details_type
            >
            base_type;

        //! The widget type.
        typedef typename base_type::base_type::base_type widget_type;

        //! The detail implementation type.
        typedef
            typename widget_details_type::widget_details_type details_type;

        //! The detail implementation pointer type.
        typedef
            typename widget_details_type::widget_details_ptr_type
            details_ptr_type;


        // constructors and destructor

        /*!
            \brief Creates a link label.

            \param parent A parent widget.

            \throw std::runtime_error When a link label cannot be created.
        */
        explicit link_label(widget_type& parent)
        :
        base_type(parent)
        {}

        /*!
            \brief Destroys the link label.
        */
        virtual ~link_label()
        TETENGO2_CPP0X_NOEXCEPT
        {}


        // functions


    };


}}


#endif
