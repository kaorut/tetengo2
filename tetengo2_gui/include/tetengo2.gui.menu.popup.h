/*! \file
    \brief The definition of tetengo2::gui::menu::popup.

    Copyright (C) 2007-2012 kaoru

    $Id$
*/

#if !defined(TETENGO2_GUI_MENU_POPUP_H)
#define TETENGO2_GUI_MENU_POPUP_H

//#include <utility>

#include "tetengo2.cpp11.h"
#include "tetengo2.gui.menu.abstract_popup.h"


namespace tetengo2 { namespace gui { namespace menu
{
    /*!
        \brief The class template for a popup menu.

        \tparam Traits      A traits type.
        \tparam MenuDetails A detail implementation type of a menu.
   */
    template <typename Traits, typename MenuDetails>
    class popup : public abstract_popup<Traits, MenuDetails>
    {
    public:
        // types

        //! The traits type.
        typedef Traits traits_type;

        //! The detail implementation type of a menu.
        typedef MenuDetails menu_details_type;

        //! The base type.
        typedef abstract_popup<traits_type, menu_details_type> base_type;


        // constructors and destructor

        /*!
            \brief Creates a popup menu.

            \tparam S A string type.

            \param text A text.
        */
        template <typename S>
        explicit popup(S&& text)
        :
        base_type(std::forward<S>(text), menu_details_type::create_popup_menu())
        {}

        /*!
            \brief Destroys the popup menu.
        */
        virtual ~popup()
        TETENGO2_CPP11_NOEXCEPT
        {}


    private:
        // types

        typedef typename base_type::style_type style_type;


        // virtual functions

        virtual const style_type& style_impl()
        const
        {
            return menu_details_type::popup_menu_style();
        }


    };


}}}


#endif
