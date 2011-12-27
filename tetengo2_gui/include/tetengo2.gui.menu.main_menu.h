/*! \file
    \brief The definition of tetengo2::gui::main_menu.

    Copyright (C) 2007-2011 kaoru

    $Id$
*/

#if !defined(TETENGO2_GUI_MAINMENU_H)
#define TETENGO2_GUI_MAINMENU_H

#include "tetengo2.cpp11.h"
#include "tetengo2.gui.menu.abstract_popup_menu.h"


namespace tetengo2 { namespace gui
{
    /*!
        \brief The class template for a main menu.

        \tparam Traits      A traits type.
        \tparam MenuDetails A detail implementation type of a menu.
   */
    template <typename Traits, typename MenuDetails>
    class main_menu : public abstract_popup_menu<Traits, MenuDetails>
    {
    public:
        // types

        //! The traits type.
        typedef Traits traits_type;

        //! The detail implementation type of a menu.
        typedef MenuDetails menu_details_type;

        //! The base type.
        typedef abstract_popup_menu<traits_type, menu_details_type> base_type;


        // constructors and destructor

        /*!
            \brief Creates a main menu.
        */
        main_menu()
        :
        base_type(string_type(), menu_details_type::create_main_menu())
        {}

        /*!
            \brief Destroys the main menu.
        */
        virtual ~main_menu()
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
            return menu_details_type::main_menu_style();
        }


    };


}}


#endif
