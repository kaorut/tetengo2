/*! \file
    \brief The definition of stub_tetengo2::gui::button.

    Copyright (C) 2007-2010 kaoru

    $Id$
*/

#if !defined(STUBTETENGO2_GUI_BUTTON_H)
#define STUBTETENGO2_GUI_BUTTON_H

#include "stub_tetengo2.gui.control.h"
#include "tetengo2.cpp0x_keyword.h"


namespace stub_tetengo2 { namespace gui
{
    template <typename Traits>
    class button : public control<typename Traits::base_type>
    {
    public:
        // types

        typedef Traits traits_type;

        typedef control<typename traits_type::base_type> base_type;

        typedef typename base_type::base_type widget_type;

        enum style_type
        {
            style_normal,
            style_default,
            style_cancel
        };


        // constructors and destructor

        explicit button(
            widget_type&     parent,
            const style_type style = style_normal
        )
        :
        base_type(),
        m_style(style)
        {}

        virtual ~button()
        TETENGO2_NOEXCEPT
        {}


        // functions

        style_type style()
        const
        {
            return m_style;
        }


    private:
        // variables

        const style_type m_style;


    };


}}

#endif
