/*! \file
    \brief The definition of stub_tetengo2::gui::button.

    Copyright (C) 2007-2009 kaoru

    $Id$
*/

#if !defined(STUBTETENGO2_GUI_BUTTON_H)
#define STUBTETENGO2_GUI_BUTTON_H

//#include <boost/concept_check.hpp>

#include "concept_tetengo2.gui.Widget.h"


namespace stub_tetengo2 { namespace gui
{
    template <typename Widget>
    class button : public Widget
    {
    private:
        // concept checks

        BOOST_CONCEPT_ASSERT((concept_tetengo2::gui::Widget<Widget>));

    public:
        // types

        typedef Widget widget_type;

        typedef typename widget_type::handle_type handle_type;

        typedef typename widget_type::canvas_type canvas_type;

        typedef typename widget_type::alert_type alert_type;

        typedef typename widget_type::difference_type difference_type;

        typedef typename widget_type::size_type size_type;

        typedef typename widget_type::position_type position_type;

        typedef typename widget_type::dimension_type dimension_type;

        typedef typename widget_type::string_type string_type;

        typedef
            typename widget_type::encode_from_native_type
            encode_from_native_type;

        typedef
            typename widget_type::encode_to_native_type
            encode_to_native_type;

        typedef typename widget_type::child_type child_type;

        typedef typename widget_type::paint_observer_type paint_observer_type;

        typedef typename widget_type::mouse_observer_type mouse_observer_type;


        // constructors and destructor

        button(const widget_type& parent)
        :
        widget_type(parent)
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


    };


}}

#endif
