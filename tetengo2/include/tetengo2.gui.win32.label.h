/*! \file
    \brief The definition of tetengo2::gui::win32::label.

    Copyright (C) 2007-2011 kaoru

    $Id$
*/

#if !defined(TETENGO2_GUI_WIN32_LABEL_H)
#define TETENGO2_GUI_WIN32_LABEL_H

//#include <stdexcept>

//#include <boost/bind.hpp>
#include <boost/ref.hpp>

#include "tetengo2.cpp0x.h"
#include "tetengo2.gui.measure.h"
#include "tetengo2.gui.win32.control.h"


namespace tetengo2 { namespace gui { namespace win32
{
    /*!
        \brief The class template for a label for Win32 platforms.
 
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
    class label : public control<typename Traits::base_type, WidgetDetails>
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
            control<typename traits_type::base_type, widget_details_type>
            base_type;

        //! The widget type.
        typedef typename base_type::base_type widget_type;

        //! The detail implementation type.
        typedef
            typename widget_details_type::widget_details_type details_type;

        //! The detail implementation pointer type.
        typedef
            typename widget_details_type::widget_details_ptr_type
            details_ptr_type;


        // constructors and destructor

        /*!
            \brief Creates a label.

            \param parent A parent widget.

            \throw std::runtime_error When a label cannot be created.
        */
        explicit label(widget_type& parent)
        :
        base_type(
            message_handler_map_type(),
            widget_details_type::create_label(parent)
        )
        {
            initialize(this);
        }

        /*!
            \brief Destroys the label.
        */
        virtual ~label()
        TETENGO2_CPP0X_NOEXCEPT
        {}


        // functions

        /*!
            \brief Fit the dimension to the dimension of the text.
        */
        void fit_to_content()
        {
            set_client_dimension(calc_text_dimension());
        }


    private:
        // functions

        dimension_type calc_text_dimension()
        const
        {
            return widget_details_type::use_canvas<
                canvas_type, dimension_type
            >(
                *this,
                boost::bind(
                    &canvas_type::calc_text_dimension, _1, boost::cref(text())
                )
            );
        }


    };


}}}

#endif
