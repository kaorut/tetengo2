/*! \file
    \brief The definition of stub_tetengo2::gui::container.

    Copyright (C) 2007-2009 kaoru

    $Id$
*/

#if !defined(STUBTETENGO2_GUI_CONTAINER_H)
#define STUBTETENGO2_GUI_CONTAINER_H

#include <vector>

//#include <boost/concept_check.hpp>

#include "concept_tetengo2.gui.Widget.h"


namespace stub_tetengo2 { namespace gui
{
    template <typename Widget>
    class container : public Widget
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

        typedef
            typename widget_type::paint_observer_type paint_observer_type;

        typedef std::vector<widget_type*> widgets_type;

        typedef std::vector<const widget_type*> const_widgets_type;


        // constructors and destructor

        virtual ~container()
        throw ()
        {}


        // functions

        const widgets_type children()
        {
            return widgets_type();
        }

        const const_widgets_type children()
        const
        {
            return const_widgets_type();
        }


    protected:
        // constructors

        container()
        {}


    };


}}

#endif
