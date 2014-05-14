/*! \file
    \brief The definition of tetengo2::gui::menu::popup.

    Copyright (C) 2007-2014 kaoru

    $Id$
*/

#if !defined(TETENGO2_GUI_MENU_POPUP_H)
#define TETENGO2_GUI_MENU_POPUP_H

#include <utility>

#include <tetengo2/gui/menu/abstract_popup.h>
#include "tetengo2.stdalt.h"


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
        using traits_type = Traits;

        //! The detail implementation type of a menu.
        using menu_details_type = MenuDetails;

        //! The base type.
        using base_type = abstract_popup<traits_type, menu_details_type>;

        //! The string type.
        using string_type = typename base_type::string_type;


        // constructors and destructor

        /*!
            \brief Creates a popup menu.

            \param text A text.
        */
        explicit popup(string_type text)
        :
        base_type(std::move(text), menu_details_type::create_popup_menu())
        {}

        /*!
            \brief Destroys the popup menu.
        */
        virtual ~popup()
        TETENGO2_STDALT_DESTRUCTOR_DEFAULT_IMPLEMENTATION


    private:
        // types

        using style_type = typename base_type::style_type;


        // virtual functions

        virtual const style_type& style_impl()
        const override
        {
            return menu_details_type::template popup_menu_style<typename base_type::base_type>();
        }


    };


}}}


#endif
