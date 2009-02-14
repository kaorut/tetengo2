/*! \file
    \brief The definition of concept_tetengo2::gui::Widget.

    Copyright (C) 2007-2009 kaoru

    $Id$
*/

#if !defined(CONCEPTTETENGO2_GUI_WIDGET_H)
#define CONCEPTTETENGO2_GUI_WIDGET_H

#include <memory>
#include <utility>

#include <boost/concept_check.hpp>


namespace concept_tetengo2 { namespace gui
{
    /*!
        \brief The concept check class template for a widget.

        \tparam Type A type.
    */
    template <typename Type>
    class Widget
    {
#if !defined(DOCUMENTATION)
    public:
        // typedef checks

        typedef typename Type::handle_type handle_type;

        typedef typename Type::canvas_type canvas_type;

        typedef typename Type::alert_type alert_type;

        typedef typename Type::difference_type difference_type;

        typedef typename Type::size_type size_type;

        typedef typename Type::position_type position_type;

        typedef typename Type::dimension_type dimension_type;

        typedef typename Type::string_type string_type;

        typedef
            typename Type::encode_from_native_type encode_from_native_type;

        typedef typename Type::encode_to_native_type encode_to_native_type;

        typedef typename Type::paint_observer_type paint_observer_type;


        // usage checks

        BOOST_CONCEPT_USAGE(Widget)
        {
            m_object.parent().handle();

            m_object.set_enabled(bool());

            m_object.set_visible(bool());
            
            m_object.set_position(
                std::make_pair(difference_type(), difference_type())
            );

            m_object.set_dimension(std::make_pair(size_type(), size_type()));

            m_object.set_text(string_type());

            std::auto_ptr<paint_observer_type> p_paint_observer;
            m_object.add_paint_observer(p_paint_observer);

            const_constraints(m_object);
        }

        void const_constraints(const Type& object)
        {
            const handle_type handle = object.handle();
            boost::ignore_unused_variable_warning(handle);

            const bool has_parent = object.has_parent();
            boost::ignore_unused_variable_warning(has_parent);

            object.parent().handle();

            const bool enabled = object.enabled();
            boost::ignore_unused_variable_warning(enabled);

            const bool visible = object.visible();
            boost::ignore_unused_variable_warning(visible);

            const position_type& position = object.position();
            boost::ignore_unused_variable_warning(position);

            const dimension_type& dimension = object.dimension();
            boost::ignore_unused_variable_warning(dimension);

            const string_type text = object.text();
            boost::ignore_unused_variable_warning(text);
        }

        
    private:
        // variables

        Type& m_object;


#endif
    };


}}

#endif
