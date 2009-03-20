/*! \file
    \brief The definition of concept_tetengo2::gui::Canvas.

    Copyright (C) 2007-2009 kaoru

    $Id$
*/

#if !defined(CONCEPTTETENGO2_GUI_CANVAS_H)
#define CONCEPTTETENGO2_GUI_CANVAS_H

#include <boost/concept_check.hpp>


namespace concept_tetengo2 { namespace gui
{
    /*!
        \brief The concept check class template for a canvas.

        \tparam Type A type.
    */
    template <typename Type>
    class Canvas
    {
#if !defined(DOCUMENTATION)
    public:
        // typedef checks

        typedef typename Type::handle_type handle_type;

        typedef typename Type::size_type size_type;

        typedef typename Type::point_type point_type;

        typedef typename Type::rectangle_type rectangle_type;

        typedef typename Type::string_type string_type;

        typedef typename Type::encode_to_native_type encode_to_native_type;

        typedef typename Type::window_handle_type window_handle_type;

        typedef typename Type::font_type font_type;


        // usage checks

        BOOST_CONCEPT_USAGE(Canvas)
        {
            m_object.set_font(m_font);

            m_object.draw_text(string_type(), point_type());

            const_constraints(m_object);
        }

        void const_constraints(const Type& object)
        {
            const handle_type handle = object.handle();
            boost::ignore_unused_variable_warning(handle);

            const font_type& font = object.font();
            boost::ignore_unused_variable_warning(font);
        }

        
    private:
        // variables

        Type m_object;

        const font_type m_font;


#endif
    };


}}

#endif
