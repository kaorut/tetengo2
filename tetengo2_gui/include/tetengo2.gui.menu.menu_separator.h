/*! \file
    \brief The definition of tetengo2::gui::menu::menu_separator.

    Copyright (C) 2007-2011 kaoru

    $Id$
*/

#if !defined(TETENGO2_GUI_MENU_MENUSEPARATOR_H)
#define TETENGO2_GUI_MENU_MENUSEPARATOR_H

#include "tetengo2.cpp11.h"
#include "tetengo2.gui.menu.menu.h"


namespace tetengo2 { namespace gui { namespace menu
{
    /*!
        \brief The class template for a menu separator.

        The text is empty.

        \tparam Traits      A traits type.
        \tparam MenuDetails A detail implementation type of a menu.
   */
    template <typename Traits, typename MenuDetails>
    class menu_separator : public menu<Traits, MenuDetails>
    {
    public:
        // types

        //! The traits type.
        typedef Traits traits_type;

        //! The detail implementation type of a menu.
        typedef MenuDetails menu_details_type;

        //! The base type.
        typedef menu<traits_type, menu_details_type> base_type;


        // constructors and destructor

        /*!
            \brief Creates a menu separator.
        */
        menu_separator()
        :
        base_type(string_type(), menu_details_type::create_menu())
        {}

        /*!
            \brief Destroys the menu separator.
        */
        virtual ~menu_separator()
        TETENGO2_CPP11_NOEXCEPT
        {}


    private:
        // types

        typedef typename base_type::string_type string_type;

        typedef typename base_type::style_type style_type;


        // virtual functions

        virtual const style_type& style_impl()
        const
        {
            return menu_details_type::menu_separator_style();
        }


    };


}}}


#endif
