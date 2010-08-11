/*! \file
    \brief The definition of tetengo2::gui::button_traits.

    Copyright (C) 2007-2010 kaoru

    $Id$
*/

#if !defined(TETENGO2_GUI_BUTTONTRAITS_H)
#define TETENGO2_GUI_BUTTONTRAITS_H


namespace tetengo2 { namespace gui
{
    /*!
        \brief The traits class template for a button.
 
        \tparam WidgetTraits A traits type for a GUI widget.
   */
    template <typename WidgetTraits>
    struct button_traits
    {
        //types

        //! \reutrn The base type.
        typedef WidgetTraits base_type;


    };


}}


#endif
