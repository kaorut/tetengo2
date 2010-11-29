/*! \file
    \brief The definition of stub_tetengo2::gui::control.

    Copyright (C) 2007-2010 kaoru

    $Id$
*/

#if !defined(STUBTETENGO2_GUI_CONTROL_H)
#define STUBTETENGO2_GUI_CONTROL_H

#include "stub_tetengo2.gui.widget.h"
#include "tetengo2.cpp0x_keyword.h"


namespace stub_tetengo2 { namespace gui
{
    template <typename Traits>
    class control : public widget<typename Traits::base_type>
    {
    public:
        // types

        typedef Traits traits_type;

        typedef widget<typename traits_type::base_type> base_type;


        // constructors and destructor

        explicit control(const handle_type handle)
        :
        base_type()
        {}

        virtual ~control()
        TETENGO2_NOEXCEPT
        {}


    };


}}

#endif
