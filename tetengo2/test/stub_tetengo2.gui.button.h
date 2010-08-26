/*! \file
    \brief The definition of stub_tetengo2::gui::button.

    Copyright (C) 2007-2010 kaoru

    $Id$
*/

#if !defined(STUBTETENGO2_GUI_BUTTON_H)
#define STUBTETENGO2_GUI_BUTTON_H

#include "stub_tetengo2.gui.widget.h"


namespace stub_tetengo2 { namespace gui
{
    template <typename Traits>
    class button : public widget<typename Traits::base_type>
    {
    public:
        // types

        typedef Traits traits_type;

        typedef widget<typename traits_type::base_type> base_type;

        enum style_type
        {
            style_normal,
            style_default,
            style_cancel
        };


        // constructors and destructor

        button(base_type& parent, const style_type style = style_normal)
        :
        base_type(parent),
        m_style(style)
        {}

        virtual ~button()
        throw ()
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


        // virtual functions

        virtual typename button::handle_type handle_impl()
        const
        {
            return 0;
        }


    };


}}

#endif
