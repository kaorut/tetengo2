/*! \file
    \brief The definition of bobura::diagram_view.

    Copyright (C) 2007-2012 kaoru

    $Id$
*/

#if !defined(BOBURA_DIAGRAMVIEW_H)
#define BOBURA_DIAGRAMVIEW_H

#include <boost/noncopyable.hpp>
#include <boost/rational.hpp>

#include <tetengo2.gui.measure.h>


namespace bobura
{
   /*!
        \brief The class template for a diagram view.

        \tparam Model           A model type.
        \tparam Canvas          A canvas type.
        \tparam SolidBackground A solid background type.
    */
    template <typename Model, typename Canvas, typename SolidBackground>
    class diagram_view : private boost::noncopyable
    {
    public:
        // types

        //! The model type.
        typedef Model model_type;

        //! The canvas type.
        typedef Canvas canvas_type;

        //! The size type.
        typedef typename canvas_type::size_type size_type;

        //! The position type.
        typedef typename canvas_type::position_type position_type;

        //! The dimension type.
        typedef typename canvas_type::dimension_type dimension_type;

        //! The solid background type.
        typedef SolidBackground solid_background_type;


        // constructors and destructor

        /*!
            \brief Creates a diagram view.

            \param model A model.
        */
        explicit diagram_view(const model_type& model)
        :
        m_model(model)
        {}


        // functions

        /*!
            \brief Draws the view.

            \param canvas              A canvas.
            \param canvas_dimension    A canvas dimension.
            \param scroll_bar_position A scroll bar position.
        */
        void draw_to(
            canvas_type&          canvas,
            const dimension_type& canvas_dimension,
            const position_type&  scroll_bar_position
        )
        const
        {
            canvas.set_background(tetengo2::make_unique<const solid_background_type>(color_type(255, 255, 255)));
            canvas.fill_rectangle(position_type(left_type(0), top_type(0)), canvas_dimension);

            canvas.set_color(color_type(0x80, 0x80, 0x80, 0xFF));
            canvas.draw_line(
                position_type(left_type(0), to_rational<top_type>(time_header_height())),
                position_type(
                    to_rational<left_type>(tetengo2::gui::dimension<dimension_type>::width(canvas_dimension)),
                    to_rational<top_type>(time_header_height())
                ),
                size_type(typename size_type::value_type(1, 12))
            );
            canvas.draw_line(
                position_type(to_rational<left_type>(station_header_width()), top_type(0)),
                position_type(
                    to_rational<left_type>(station_header_width()),
                    to_rational<top_type>(tetengo2::gui::dimension<dimension_type>::height(canvas_dimension))
                ),
                size_type(typename size_type::value_type(1, 12))
            );

            canvas.draw_text(m_model.timetable().title(), position_type(left_type(0), top_type(0)));
        }

        /*!
            \brief Returns the dimension.

            \return The dimension.
        */
        dimension_type dimension()
        const
        {
            return dimension_type(width_type(64) - station_header_width(), height_type(48) - time_header_height());
        }

        /*!
            \brief Returns the page size.

            \param canvas_dimension A canvas dimension.

            \return The page size.
        */
        dimension_type page_size(const dimension_type& canvas_dimension)
        const
        {
            const dimension_type max_dimension = dimension();

            const width_type canvas_width = tetengo2::gui::dimension<dimension_type>::width(canvas_dimension);
            width_type page_width(0);
            if (canvas_width > station_header_width())
                page_width = canvas_width - station_header_width();
            else
                page_width = tetengo2::gui::dimension<dimension_type>::width(max_dimension) + width_type(1);

            const height_type canvas_height = tetengo2::gui::dimension<dimension_type>::height(canvas_dimension);
            height_type page_height(0);
            if (canvas_height > time_header_height())
                page_height = canvas_height - time_header_height();
            else
                page_height = tetengo2::gui::dimension<dimension_type>::height(max_dimension) + height_type(1);

            return dimension_type(std::move(page_width), std::move(page_height));
        }


    private:
        // types

        typedef typename tetengo2::gui::position<position_type>::left_type left_type;

        typedef typename tetengo2::gui::position<position_type>::top_type top_type;

        typedef typename solid_background_type::color_type color_type;

        typedef typename tetengo2::gui::dimension<dimension_type>::width_type width_type;

        typedef typename tetengo2::gui::dimension<dimension_type>::height_type height_type;


        // static functions

        static const width_type& station_header_width()
        {
            static const width_type singleton(8);
            return singleton;
        }

        static const height_type& time_header_height()
        {
            static const height_type singleton(2);
            return singleton;
        }

        template <typename To, typename From>
        static To to_rational(const From& from)
        {
            return To(typename To::value_type(from.value().numerator(), from.value().denominator()));
        }


        // variables

        const model_type& m_model;


    };


}

#endif
