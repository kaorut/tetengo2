/*! \file
    \brief The definition of bobura::diagram_view.

    Copyright (C) 2007-2012 kaoru

    $Id$
*/

#if !defined(BOBURA_DIAGRAMVIEW_H)
#define BOBURA_DIAGRAMVIEW_H

#include <algorithm>
#include <iterator>
//#include <utility>
#include <vector>

#include <boost/lexical_cast.hpp>
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

        //! The string type.
        typedef typename canvas_type::string_type string_type;

        //! The solid background type.
        typedef SolidBackground solid_background_type;


        // constructors and destructor

        /*!
            \brief Creates a diagram view.

            \param model A model.
        */
        explicit diagram_view(const model_type& model)
        :
        m_model(model),
        m_dimension(width_type(20 * 24), height_type(0)),
        m_station_header_width(8),
        m_time_header_height(3),
        m_station_positions()
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
            clear_background(canvas, canvas_dimension);

            draw_header(canvas);
            draw_time_lines(
                canvas, canvas_dimension, tetengo2::gui::position<position_type>::left(scroll_bar_position)
            );
            draw_station_lines(
                canvas, canvas_dimension, tetengo2::gui::position<position_type>::top(scroll_bar_position)
            );
        }

        /*!
            \brief Returns the dimension.

            \return The dimension.
        */
        const dimension_type& dimension()
        const
        {
            return m_dimension;
        }

        /*!
            \brief Returns the page size.

            \param canvas_dimension A canvas dimension.

            \return The page size.
        */
        dimension_type page_size(const dimension_type& canvas_dimension)
        const
        {
            const width_type canvas_width = tetengo2::gui::dimension<dimension_type>::width(canvas_dimension);
            const width_type page_width =
                canvas_width > m_station_header_width ? canvas_width - m_station_header_width : width_type(0);

            const height_type canvas_height = tetengo2::gui::dimension<dimension_type>::height(canvas_dimension);
            const height_type page_height =
                canvas_height > m_time_header_height ? canvas_height - m_time_header_height : height_type(0);

            return dimension_type(std::move(page_width), std::move(page_height));
        }

        /*!
            \brief Updates the station positions.
        */
        void update_station_positions()
        {
            const station_intervals_type intervals = m_model.timetable().station_intervals();
            if (intervals.empty())
            {
                m_station_positions.clear();
                m_dimension =
                    dimension_type(tetengo2::gui::dimension<dimension_type>::width(m_dimension), height_type(0));
                return;
            }
            
            std::vector<top_type> positions;
            positions.reserve(intervals.size());
            std::transform(intervals.begin(), intervals.end(), std::back_inserter(positions), to_station_position());

            m_station_positions = std::move(positions);
            m_dimension =
                dimension_type(
                    tetengo2::gui::dimension<dimension_type>::width(m_dimension),
                    to_rational<height_type>(m_station_positions.back())
                );
        }


    private:
        // types

        typedef typename tetengo2::gui::position<position_type>::left_type left_type;

        typedef typename tetengo2::gui::position<position_type>::top_type top_type;

        typedef typename solid_background_type::color_type color_type;

        typedef typename tetengo2::gui::dimension<dimension_type>::width_type width_type;

        typedef typename tetengo2::gui::dimension<dimension_type>::height_type height_type;

        typedef typename model_type::timetable_type::station_interval_type station_interval_type;

        typedef typename model_type::timetable_type::station_intervals_type station_intervals_type;

        class to_station_position
        {
        public:
            to_station_position()
            :
            m_sum(0)
            {}

            top_type operator()(const station_interval_type& interval)
            {
                const station_interval_type position = m_sum;
                m_sum += interval;
                return top_type(typename top_type::value_type(position.numerator(), position.denominator()));
            }

        private:
            station_interval_type m_sum;

        };


        // static functions

        template <typename To, typename From>
        static To to_rational(const From& from)
        {
            return To(typename To::value_type(from.value().numerator(), from.value().denominator()));
        }


        // variables

        const model_type& m_model;

        dimension_type m_dimension;

        width_type m_station_header_width;

        height_type m_time_header_height;

        std::vector<top_type> m_station_positions;


        // functions

        void clear_background(canvas_type& canvas, const dimension_type& canvas_dimension)
        const
        {
            canvas.set_background(tetengo2::make_unique<const solid_background_type>(color_type(255, 255, 255)));
            canvas.fill_rectangle(position_type(left_type(0), top_type(0)), canvas_dimension);
        }

        void draw_header(canvas_type& canvas)
        const
        {
            canvas.set_color(color_type(0x00, 0x00, 0x00, 0xFF));

            canvas.draw_text(m_model.timetable().title(), position_type(left_type(0), top_type(0)));
        }

        void draw_time_lines(
            canvas_type&          canvas,
            const dimension_type& canvas_dimension,
            const left_type&      horizontal_scroll_bar_position
        )
        const
        {
            const left_type canvas_right =
                to_rational<left_type>(tetengo2::gui::dimension<dimension_type>::width(canvas_dimension));
            const top_type canvas_bottom =
                to_rational<top_type>(tetengo2::gui::dimension<dimension_type>::height(canvas_dimension));
            const top_type station_position_bottom =
                to_rational<top_type>(
                    tetengo2::gui::dimension<dimension_type>::height(m_dimension) + m_time_header_height
                );
            const top_type line_bottom = std::min(canvas_bottom, station_position_bottom);

            canvas.set_color(color_type(0x80, 0x80, 0x80, 0xFF));

            typedef typename left_type::value_type::int_type left_int_type;
            const left_int_type int_scroll_position =
                boost::rational_cast<left_int_type>(horizontal_scroll_bar_position.value());
            const left_int_type int_left = int_scroll_position % 20;
            const left_int_type first_visible_hour = int_scroll_position / 20 + (int_left > 0 ? 1 : 0);
            left_int_type hour = first_visible_hour;
            for (
                left_type position = to_rational<left_type>(m_station_header_width) - left_type(int_left);
                position < canvas_right;
                position += left_type(20)
            )
            {
                if (position < to_rational<left_type>(m_station_header_width))
                    continue;

                canvas.draw_line(
                    position_type(position, top_type(1)),
                    position_type(position, line_bottom),
                    size_type(typename size_type::value_type(1, 12))
                );

                canvas.draw_text(boost::lexical_cast<string_type>(hour % 24), position_type(position, top_type(1)));
                ++hour;
            }

        }

        void draw_station_lines(
            canvas_type&          canvas,
            const dimension_type& canvas_dimension,
            const top_type&       vertical_scroll_bar_position
        )
        const
        {
            const left_type canvas_right =
                to_rational<left_type>(tetengo2::gui::dimension<dimension_type>::width(canvas_dimension));

            for (typename std::vector<top_type>::size_type i = 0; i < m_station_positions.size(); ++i)
            {
                const top_type& position = m_station_positions[i];
                const top_type line_position =
                    position + to_rational<top_type>(m_time_header_height) - vertical_scroll_bar_position;
                if (line_position < to_rational<top_type>(m_time_header_height))
                    continue;

                canvas.draw_line(
                    position_type(left_type(0), line_position),
                    position_type(canvas_right, line_position),
                    size_type(typename size_type::value_type(1, 12))
                );

                const string_type& station_name = m_model.timetable().station_locations()[i].station().name();
                const dimension_type station_name_dimension = canvas.calc_text_dimension(station_name);
                canvas.draw_text(
                    station_name,
                    position_type(
                        left_type(0),
                        line_position -
                            to_rational<top_type>(
                                tetengo2::gui::dimension<dimension_type>::height(station_name_dimension)
                            )
                    )
                );
            }
        }


    };


}

#endif
