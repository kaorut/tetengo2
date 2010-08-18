/*! \file
    \brief The definition of stub_tetengo2::gui::main_menu.

    Copyright (C) 2007-2010 kaoru

    $Id$
*/

#if !defined(STUBTETENGO2_GUI_MAINMENU_H)
#define STUBTETENGO2_GUI_MAINMENU_H

//#include <cstddef>

#include "stub_tetengo2.gui.abstract_popup_menu.h"


namespace stub_tetengo2 { namespace gui
{
    template <typename Traits>
    class main_menu : public abstract_popup_menu<Traits>
    {
    public:
        // types

        typedef Traits traits_type;

        typedef abstract_popup_menu<traits_type> base_type;


        // constructors and destructor

        main_menu()
        :
        base_type(NULL, typename main_menu::string_type())
        {}

        virtual ~main_menu()
        throw ()
        {}


    };


}}

#endif
