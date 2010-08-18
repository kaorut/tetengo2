/*! \file
    \brief The definition of stub_tetengo2::gui::popup_menu.

    Copyright (C) 2007-2010 kaoru

    $Id$
*/

#if !defined(STUBTETENGO2_GUI_POPUPMENU_H)
#define STUBTETENGO2_GUI_POPUPMENU_H

//#include <cstddef>

#include "stub_tetengo2.gui.abstract_popup_menu.h"


namespace stub_tetengo2 { namespace gui
{
    template <typename Traits>
    class popup_menu : public abstract_popup_menu<Traits>
    {
    public:
        // types

        typedef Traits traits_type;

        typedef abstract_popup_menu<traits_type> base_type;


        // constructors and destructor

        explicit popup_menu(const typename popup_menu::string_type& text)
        :
        base_type(NULL, text)
        {}

        virtual ~popup_menu()
        throw ()
        {}


    };


}}

#endif
