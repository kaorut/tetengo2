/*! \file
    \brief The definition of stub_tetengo2::gui::menu_command.

    Copyright (C) 2007-2010 kaoru

    $Id$
*/

#if !defined(STUBTETENGO2_GUI_MENUCOMMAND_H)
#define STUBTETENGO2_GUI_MENUCOMMAND_H

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

        explicit menu_command(const typename menu_command::string_type& text)
        :
        base_type(text)
        {}

        virtual ~menu_command()
        TETENGO2_NOEXCEPT
        {}


    };


}}

#endif
