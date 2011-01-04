/*! \file
    \brief The definition of stub_tetengo2::gui::menu_command.

    Copyright (C) 2007-2011 kaoru

    $Id$
*/

#if !defined(STUBTETENGO2_GUI_MENUCOMMAND_H)
#define STUBTETENGO2_GUI_MENUCOMMAND_H

//#include <utility>

#include "stub_tetengo2.gui.menu.h"
#include "tetengo2.cpp0x_keyword.h"


namespace stub_tetengo2 { namespace gui
{
    template <typename Traits>
    class menu_command : public menu<Traits>
    {
    public:
        // types

        typedef Traits traits_type;

        typedef menu<traits_type> base_type;


        // constructors and destructor

        template <typename S>
        explicit menu_command(S&& text)
        :
        base_type(std::forward<S>(text))
        {}

        virtual ~menu_command()
        TETENGO2_NOEXCEPT
        {}


    };


}}

#endif
