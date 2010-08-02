/*! \file
    \brief The definition of stub_tetengo2::gui::button.

    Copyright (C) 2007-2010 kaoru

    $Id$
*/

#if !defined(STUBTETENGO2_GUI_BUTTON_H)
#define STUBTETENGO2_GUI_BUTTON_H


namespace stub_tetengo2 { namespace gui
{
    template <typename Widget>
    class button : public Widget
    {
    public:
        // types

        typedef Widget base_type;

        typedef typename base_type::handle_type handle_type;

        typedef typename base_type::canvas_type canvas_type;

        typedef typename base_type::alert_type alert_type;

        typedef typename base_type::difference_type difference_type;

        typedef typename base_type::size_type size_type;

        typedef typename base_type::position_type position_type;

        typedef typename base_type::dimension_type dimension_type;

        typedef typename base_type::string_type string_type;

        typedef typename base_type::encoder_type encoder_type;

        typedef typename base_type::child_type child_type;

        typedef
            typename base_type::paint_observer_set_type
            paint_observer_set_type;

        typedef typename base_type::mouse_observer_type mouse_observer_type;

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

        virtual handle_type handle()
        const
        {
            return 0;
        }

        virtual style_type style()
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
