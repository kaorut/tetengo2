/*! \file
    \brief The definition of tetengo2::gui::menu::command.

    Copyright (C) 2007-2012 kaoru

    $Id$
*/

#if !defined(TETENGO2_GUI_MENU_COMMAND_H)
#define TETENGO2_GUI_MENU_COMMAND_H

//#include <utility>

#include "tetengo2.cpp11.h"
#include "tetengo2.gui.menu.menu_base.h"


namespace tetengo2 { namespace gui { namespace menu
{
    /*!
        \brief The class template for a menu command.

        \tparam Traits      A traits type.
        \tparam MenuDetails A detail implementation type of a menu.
   */
    template <typename Traits, typename MenuDetails>
    class command : public menu_base<Traits, MenuDetails>
    {
    public:
        // types

        //! The traits type.
        typedef Traits traits_type;

        //! The detail implementation type of a menu.
        typedef MenuDetails menu_details_type;

        //! The base type.
        typedef menu_base<traits_type, menu_details_type> base_type;

        //! The shortcut key type.
        typedef typename base_type::shortcut_key_type shortcut_key_type;


        // constructors and destructor

        /*!
            \brief Creates a menu command.

            \tparam S A string type.

            \param text           A text.
            \param p_shortcut_key A unique pointer to a shortcut key.
        */
        template <typename S>
        command(
            S&&                                text,
            std::unique_ptr<shortcut_key_type> p_shortcut_key =
                std::unique_ptr<shortcut_key_type>()
        )
        :
        base_type(
            std::forward<S>(text),
            std::move(p_shortcut_key),
            menu_details_type::create_menu()
        )
        {}

        /*!
            \brief Destroys the menu command.
        */
        virtual ~command()
        TETENGO2_CPP11_NOEXCEPT
        {}


    private:
        // types

        typedef typename base_type::style_type style_type;


        // virtual functions

        virtual const style_type& style_impl()
        const
        {
            return menu_details_type::menu_command_style();
        }


    };


}}}


#endif
