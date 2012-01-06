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
    class command : public menu<Traits, MenuDetails>
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
            \brief Creates a menu command.

            \tparam S A string type.

            \param text A text.
        */
        template <typename S>
        explicit command(S&& text)
        :
        base_type(std::forward<S>(text), menu_details_type::create_menu())
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
