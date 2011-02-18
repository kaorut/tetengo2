/*! \file
    \brief The definition of stub_tetengo2::gui::menu_separator.

    Copyright (C) 2007-2011 kaoru

    $Id$
*/

#if !defined(STUBTETENGO2_GUI_MENUSEPARATOR_H)
#define STUBTETENGO2_GUI_MENUSEPARATOR_H

#include "stub_tetengo2.gui.menu.h"
#include "tetengo2.cpp0x.h"


namespace stub_tetengo2 { namespace gui
{
    template <typename Traits>
    class menu_separator : public menu<Traits>
    {
    private:
    public:
        // types

        typedef Traits traits_type;

        typedef menu<traits_type> base_type;


        // constructors and destructor

        menu_separator()
        :
        base_type(typename menu_separator::string_type())
        {}

        virtual ~menu_separator()
        TETENGO2_CPP0X_NOEXCEPT
        {}


    };


}}

#endif
