/*! \file
    \brief The definition of tetengo2::gui::label_traits.

    Copyright (C) 2007-2010 kaoru

    $Id$
*/

#if !defined(TETENGO2_GUI_LABELTRAITS_H)
#define TETENGO2_GUI_LABELTRAITS_H


namespace tetengo2 { namespace gui
{
    /*!
        \brief The traits class template for a label.
 
        \tparam WidgetTraits A traits type for a GUI widget.
   */
    template <typename WidgetTraits>
    struct label_traits
    {
        //types

        //! The base type.
        typedef WidgetTraits base_type;


    };


}}


#endif
