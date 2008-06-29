/*! \file
    \brief The definition of tetengo2::gui::WidgetConcept.

    Copyright (C) 2007-2008 kaoru

    $Id$
*/

#if !defined(TETENGO2_GUI_WIDGETCONCEPT_H)
#define TETENGO2_GUI_WIDGETCONCEPT_H

#include <memory>

#include <boost/concept_check.hpp>


namespace tetengo2 { namespace gui
{
    /*!
        \brief The concept check class template for widgets.

        \tparam Widget A widget type.
    */
    template <typename Widget>
    class WidgetConcept
    {
#if !defined(DOCUMENTATION)
    public:
        // typedef checks

        typedef typename Widget::handle_type handle_type;

        typedef typename Widget::canvas_type canvas_type;

        typedef typename Widget::alert_type alert_type;

        typedef typename Widget::string_type string_type;

        typedef
            typename Widget::encode_from_native_type encode_from_native_type;

        typedef
            typename Widget::encode_to_native_type encode_to_native_type;

        typedef typename Widget::paint_observer_type paint_observer_type;


        // usage checks

        BOOST_CONCEPT_USAGE(WidgetConcept)
        {
            m_widget.set_visible(bool());
            
            m_widget.set_text(string_type());

            std::auto_ptr<paint_observer_type> p_paint_observer;
            m_widget.add_paint_observer(p_paint_observer);

            const_constraints(m_widget);
        }

        void const_constraints(const Widget& widget)
        {
            const handle_type handle = widget.handle();
            boost::ignore_unused_variable_warning(handle);

            const bool visible = widget.visible();
            boost::ignore_unused_variable_warning(visible);

            const string_type text = widget.text();
            boost::ignore_unused_variable_warning(text);
        }

        
    private:
        // variables

        Widget m_widget;


#endif
    };


}}

#endif
