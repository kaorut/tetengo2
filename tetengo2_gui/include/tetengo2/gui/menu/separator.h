/*! \file
    \brief The definition of tetengo2::gui::menu::separator.

    Copyright (C) 2007-2014 kaoru

    $Id$
*/

#if !defined(TETENGO2_GUI_MENU_SEPARATOR_H)
#define TETENGO2_GUI_MENU_SEPARATOR_H

#include <tetengo2/gui/menu/menu_base.h>
#include "tetengo2.stdalt.h"


namespace tetengo2 { namespace gui { namespace menu
{
    /*!
        \brief The class template for a menu separator.

        The text is empty.

        \tparam Traits      A traits type.
        \tparam MenuDetails A detail implementation type of a menu.
   */
    template <typename Traits, typename MenuDetails>
    class separator : public menu_base<Traits, MenuDetails>
    {
    public:
        // types

        //! The traits type.
        using traits_type = Traits;

        //! The detail implementation type of a menu.
        using menu_details_type = MenuDetails;

        //! The base type.
        using base_type = menu_base<traits_type, menu_details_type>;


        // constructors and destructor

        /*!
            \brief Creates a menu separator.
        */
        separator()
        :
        base_type(string_type(), menu_details_type::create_menu())
        {}

        /*!
            \brief Destroys the menu separator.
        */
        virtual ~separator()
        TETENGO2_STDALT_DESTRUCTOR_DEFAULT_IMPLEMENTATION


    private:
        // types

        using string_type = typename base_type::string_type;

        using style_type = typename base_type::style_type;


        // virtual functions

        virtual const style_type& style_impl()
        const override
        {
            return menu_details_type::template menu_separator_style<base_type>();
        }


    };


}}}


#endif
