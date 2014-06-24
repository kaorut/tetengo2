/*! \file
    \brief The definition of tetengo2::gui::menu::traits.

    Copyright (C) 2007-2014 kaoru

    $Id$
*/

#if !defined(TETENGO2_GUI_MENU_TRAITS_H)
#define TETENGO2_GUI_MENU_TRAITS_H


namespace tetengo2 { namespace gui { namespace menu
{
    /*!
        \brief The traits class template for a menu.

        \tparam String            A string type.
        \tparam Encoder           An encoder type.
   */
    template <typename String, typename Encoder>
    struct traits
    {
        //types

        //! The string type.
        using string_type = String;

        //! The encoder type.
        using encoder_type = Encoder;


    };




}}}


#endif
