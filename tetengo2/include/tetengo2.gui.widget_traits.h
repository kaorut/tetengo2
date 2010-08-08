/*! \file
    \brief The definition of tetengo2::gui::widget_traits.

    Copyright (C) 2007-2010 kaoru

    $Id$
*/

#if !defined(TETENGO2_GUI_WIDGETTRAITS_H)
#define TETENGO2_GUI_WIDGETTRAITS_H

#include <utility>


namespace tetengo2 { namespace gui
{
    /*!
        \brief The traits class template for a GUI widget.
 
        \tparam Handle           A handle type to the native interface.
        \tparam Canvas           A canvas type.
        \tparam Alert            An alerting unary functor type.
        \tparam Difference       A difference type.
        \tparam Size             A size type.
        \tparam String           A string type.
        \tparam Encoder          An encoder type.
        \tparam Font             A font type.
        \tparam PaintObserverSet A paint observer set type.
        \tparam MouseObserverSet A mouse observer set type.
   */
    template <
        typename Handle,
        typename Canvas,
        typename Alert,
        typename Difference,
        typename Size,
        typename String,
        typename Encoder,
        typename Font,
        typename PaintObserverSet,
        typename MouseObserverSet
    >
    struct widget_traits
    {
        // types

        //! \return The handle type.
        typedef Handle handle_type;

        //! \return The canvas type.
        typedef Canvas canvas_type;

        //! \return The alerting unary functor type.
        typedef Alert alert_type;

        //! \return The difference type.
        typedef Difference difference_type;

        //! \return The size type.
        typedef Size size_type;

        //! \return The position type.
        typedef std::pair<difference_type, difference_type> position_type;

        //! \return The dimension type.
        typedef std::pair<size_type, size_type> dimension_type;

        //! \return The string type.
        typedef String string_type;

        //! \return The encoder type.
        typedef Encoder encoder_type;

        //! \return The font type.
        typedef Font font_type;

        //! \return The paint observer set type.
        typedef PaintObserverSet paint_observer_set_type;

        //! \return The mouse observer set type.
        typedef MouseObserverSet mouse_observer_set_type;


    };


}}


#endif
