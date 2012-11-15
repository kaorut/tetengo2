/*! \file
    \brief The definition of bobura::view::diagram::header.

    Copyright (C) 2007-2012 kaoru

    $Id$
*/

#if !defined(BOBURA_VIEW_DIAGRAM_HEADER_H)
#define BOBURA_VIEW_DIAGRAM_HEADER_H

#include <boost/noncopyable.hpp>

#include <tetengo2.gui.measure.h>
#include <tetengo2.text.h>


namespace bobura { namespace view { namespace diagram
{
     /*!
        \brief The class template for a header in the diagram view.

        \tparam Model  A model type.
        \tparam Canvas A canvas type.
    */
    template <typename Model, typename Canvas>
    class header : boost::noncopyable
    {
    public:
        // types

        //! The model type.
        typedef Model model_type;

        //! The canvas type.
        typedef Canvas canvas_type;

        //! The position type.
        typedef typename canvas_type::position_type position_type;

        //! The dimension type.
        typedef typename canvas_type::dimension_type dimension_type;


        // constructors and destructor

        /*!
            \brief Creates a header.

            \param model  A model.
            \param canvas A canvas.
        */
        header(const model_type& model, const canvas_type& canvas)
        :
        m_company_line_name(make_company_line_name(model)),
        m_company_line_position(left_type(0), top_type(0)),
        m_company_line_dimension(width_type(0), height_type(0)),
        m_note(make_note(model)),
        m_note_position(left_type(0), top_type(0)),
        m_note_dimension(width_type(0), height_type(0)),
        m_position(left_type(0), top_type(0)),
        m_dimension(width_type(0), height_type(0))
        {
            calculate_positions_and_dimensions(
                canvas,
                m_company_line_position,
                m_company_line_dimension,
                m_note_position,
                m_note_dimension,
                m_position,
                m_dimension
            );
        }


        // functions

        /*!
            \brief Draws to the canvas.

            \param canvas A canvas.
        */
        void draw_to(canvas_type& canvas)
        const
        {

        }


    private:
        // types

        typedef typename canvas_type::string_type string_type;

        typedef typename tetengo2::gui::position<position_type>::left_type left_type;

        typedef typename tetengo2::gui::position<position_type>::top_type top_type;

        typedef typename tetengo2::gui::dimension<dimension_type>::width_type width_type;

        typedef typename tetengo2::gui::dimension<dimension_type>::height_type height_type;


        // static functions

        static string_type make_company_line_name(const model_type& model)
        {
            return
                model.timetable().company_name() +
                (model.timetable().company_name().empty() ? string_type() : string_type(TETENGO2_TEXT(" "))) +
                model.timetable().line_name();
        }

        static string_type make_note(const model_type& model)
        {
            return model.timetable().note();
        }

        static void calculate_positions_and_dimensions(
            const canvas_type& canvas,
            position_type&     company_line_position,
            dimension_type&    company_line_dimension,
            position_type&     note_position,
            dimension_type&    note_dimension,
            position_type&     position,
            dimension_type&    dimension
        )
        {

        }


        // variables

        const string_type m_company_line_name;

        position_type m_company_line_position;

        dimension_type m_company_line_dimension;

        const string_type m_note;

        position_type m_note_position;

        dimension_type m_note_dimension;

        position_type m_position;

        dimension_type m_dimension;


    };


}}}


#endif
