/*! \file
    \brief The definition of bobura::view::diagram::header.

    Copyright (C) 2007-2012 kaoru

    $Id$
*/

#if !defined(BOBURA_VIEW_DIAGRAM_HEADER_H)
#define BOBURA_VIEW_DIAGRAM_HEADER_H

#include <algorithm>

#include <boost/noncopyable.hpp>

#include <tetengo2.cpp11.h>
#include <tetengo2.gui.measure.h>
#include <tetengo2.text.h>

#include "bobura.view.diagram.item.h"


namespace bobura { namespace view { namespace diagram
{
     /*!
        \brief The class template for a header in the diagram view.

        \tparam Model  A model type.
        \tparam Canvas A canvas type.
    */
    template <typename Model, typename Canvas>
    class header : public item<Canvas>
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

            \param model            A model.
            \param canvas           A canvas.
            \param canvas_dimension A canvas dimension.
        */
        header(const model_type& model, canvas_type& canvas, const dimension_type& canvas_dimension)
        :
        m_model(model),
        m_company_line_name(make_company_line_name(model)),
        m_company_line_name_position(left_type(0), top_type(0)),
        m_company_line_name_dimension(width_type(0), height_type(0)),
        m_note(make_note(model)),
        m_note_position(left_type(0), top_type(0)),
        m_note_dimension(width_type(0), height_type(0)),
        m_position(left_type(0), top_type(0)),
        m_dimension(width_type(0), height_type(0))
        {
            calculate_positions_and_dimensions(
                model,
                canvas,
                canvas_dimension,
                m_company_line_name,
                m_note,
                m_company_line_name_position,
                m_company_line_name_dimension,
                m_note_position,
                m_note_dimension,
                m_position,
                m_dimension
            );
        }

        /*!
            \brief Destroys the header.
        */
        virtual ~header()
        TETENGO2_CPP11_NOEXCEPT
        {}


        // functions

        /*!
            \brief Draws to the canvas.

            \param canvas A canvas.
        */
        /*!
            \brief Returns the dimension.

            \return The dimension.
        */
        const dimension_type& dimension()
        const
        {
            return m_dimension;
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
            const model_type&     model,
            canvas_type&          canvas,
            const dimension_type& canvas_dimension,
            const string_type&    company_line_name,
            const string_type&    note,
            position_type&        company_line_name_position,
            dimension_type&       company_line_name_dimension,
            position_type&        note_position,
            dimension_type&       note_dimension,
            position_type&        position,
            dimension_type&       dimension
        )
        {
            const width_type canvas_width = tetengo2::gui::dimension<dimension_type>::width(canvas_dimension);

            canvas.set_font(model.timetable().font_color_set().company_line_name().font());
            canvas.set_color(model.timetable().font_color_set().company_line_name().color());
            const dimension_type company_line_name_dimension_ = canvas.calc_text_dimension(company_line_name);
            const width_type company_line_name_width =
                tetengo2::gui::dimension<dimension_type>::width(company_line_name_dimension_);
            const height_type company_line_name_height =
                company_line_name.empty() ?
                height_type(0) : tetengo2::gui::dimension<dimension_type>::height(company_line_name_dimension_);

            canvas.set_font(model.timetable().font_color_set().note().font());
            canvas.set_color(model.timetable().font_color_set().note().color());
            const dimension_type note_dimension_ = canvas.calc_text_dimension(note);
            const width_type note_width = tetengo2::gui::dimension<dimension_type>::width(note_dimension_);
            const height_type note_height =
                note.empty() ? height_type(0) : tetengo2::gui::dimension<dimension_type>::height(note_dimension_);

            position_type company_line_name_position_(left_type(0), top_type(0));
            position_type note_position_(left_type(0), top_type(0));
            width_type header_width(0);
            height_type header_height(0);
            if (company_line_name_width + note_width <= canvas_width)
            {
                header_width = canvas_width;

                const top_type height_diff =
                    top_type::from(company_line_name_height) - top_type::from(note_height);
                if (height_diff > 0)
                {
                    const top_type note_top(height_diff / top_type(2));
                    company_line_name_position_ = position_type(left_type(0), top_type(0));
                    note_position_ = position_type(left_type::from(canvas_width - note_width), note_top);
                    header_height = company_line_name_height;
                }
                else
                {
                    const top_type company_line_name_top((top_type(0) - height_diff) / top_type(2));
                    company_line_name_position_ = position_type(left_type(0), company_line_name_top);
                    note_position_ = position_type(left_type::from(canvas_width - note_width), top_type(0));
                    header_height = note_height;
                }
            }
            else
            {
                company_line_name_position_ = position_type(left_type(0), top_type(0));
                note_position_ = position_type(left_type(0), top_type::from(company_line_name_height));
                header_width = std::max(company_line_name_width, note_width);
                header_height = company_line_name_height + note_height;
            }

            company_line_name_position = company_line_name_position_;
            company_line_name_dimension = company_line_name_dimension_;
            note_position = note_position_;
            note_dimension = note_dimension_;
            position = position_type(left_type(0), top_type(0));
            dimension = dimension_type(header_width, header_height);
        }


        // variables

        const model_type& m_model;

        const string_type m_company_line_name;

        position_type m_company_line_name_position;

        dimension_type m_company_line_name_dimension;

        const string_type m_note;

        position_type m_note_position;

        dimension_type m_note_dimension;

        position_type m_position;

        dimension_type m_dimension;


        // virtual functions

        virtual void draw_on_impl(canvas_type& canvas)
        const
        {
            canvas.set_font(m_model.timetable().font_color_set().company_line_name().font());
            canvas.set_color(m_model.timetable().font_color_set().company_line_name().color());
            canvas.draw_text(m_company_line_name, m_company_line_name_position);

            canvas.set_font(m_model.timetable().font_color_set().note().font());
            canvas.set_color(m_model.timetable().font_color_set().note().color());
            canvas.draw_text(m_note, m_note_position);
        }


    };


}}}


#endif
