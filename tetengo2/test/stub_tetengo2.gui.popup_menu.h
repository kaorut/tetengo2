/*! \file
    \brief The definition of stub_tetengo2::gui::popup_menu.

    Copyright (C) 2007-2011 kaoru

    $Id$
*/

#if !defined(STUBTETENGO2_GUI_POPUPMENU_H)
#define STUBTETENGO2_GUI_POPUPMENU_H

//#include <cstddef>
//#include <utility>

#include "stub_tetengo2.gui.abstract_popup_menu.h"
#include "tetengo2.cpp0x.h"


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

        template <typename S>
        explicit popup_menu(S&& text)
        :
        base_type(NULL, std::forward<S>(text))
        {}

        virtual ~popup_menu()
        TETENGO2_CPP0X_NOEXCEPT
        {}


    };


}}

#endif
