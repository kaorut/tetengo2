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
 
        \tparam ControlTraits A traits type for a control.
   */
    template <typename ControlTraits>
    struct label_traits
    {
        //types

        //! The base type.
        typedef ControlTraits base_type;


    };


}}


#endif
