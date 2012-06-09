/*! \file
    \brief The definition of bobura::diagram_view.

    Copyright (C) 2007-2012 kaoru

    $Id$
*/

#if !defined(BOBURA_DIAGRAMVIEW_H)
#define BOBURA_DIAGRAMVIEW_H

#include <algorithm>
#include <iterator>
#include <numeric>
//#include <utility>
#include <vector>

#include <boost/lexical_cast.hpp>
#include <boost/noncopyable.hpp>
#include <boost/rational.hpp>

#include <tetengo2.cpp11.h>
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
        m_station_intervals(),
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
            draw_trains(canvas, canvas_dimension, scroll_bar_position);
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
            \brief Updates the station intervals.
        */
        void update_station_intervals()
        {
            m_station_intervals = m_model.timetable().station_intervals();
            if (m_station_intervals.empty())
            {
                m_station_positions.clear();
                m_dimension =
                    dimension_type(tetengo2::gui::dimension<dimension_type>::width(m_dimension), height_type(0));
                return;
            }
            
            std::vector<top_type> positions;
            positions.reserve(m_station_intervals.size());
            std::transform(
                m_station_intervals.begin(),
                m_station_intervals.end(),
                std::back_inserter(positions),
                to_station_position()
            );

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

        typedef typename model_type::timetable_type::station_intervals_type station_intervals_type;

        typedef typename model_type::timetable_type::train_type train_type;

        typedef typename model_type::timetable_type::trains_type trains_type;

        typedef typename train_type::stop_type stop_type;

        typedef typename stop_type::time_type time_type;

        typedef typename time_type::time_span_type time_span_type;

        typedef typename train_type::stops_type::size_type stop_index_type;


        class to_station_position
        {
        public:
            to_station_position()
            :
            m_sum(0)
            {}

            top_type operator()(const time_span_type& interval)
            {
                const time_span_type position = m_sum;
                m_sum += interval;
                return top_type(typename top_type::value_type(position.seconds(), 60));
            }

        private:
            time_span_type m_sum;

        };


        // static functions

        template <typename To, typename From>
        static To to_rational(const From& from)
        {
            return To(typename To::value_type(from.value().numerator(), from.value().denominator()));
        }

        static bool has_time(const stop_type& stop)
        {
            return stop.arrival() != time_type::uninitialized() || stop.departure() != time_type::uninitialized();
        }

        static const time_type& get_departure_time(const stop_type& stop)
        {
            assert(has_time(stop));
            if (stop.departure() != time_type::uninitialized())
                return stop.departure();
            else
                return stop.arrival();
        }

        static const time_type& get_arrival_time(const stop_type& stop)
        {
            assert(has_time(stop));
            if (stop.arrival() != time_type::uninitialized())
                return stop.arrival();
            else
                return stop.departure();
        }


        // variables

        const model_type& m_model;

        dimension_type m_dimension;

        width_type m_station_header_width;

        height_type m_time_header_height;

        station_intervals_type m_station_intervals;

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

        void draw_trains(
            canvas_type&          canvas,
            const dimension_type& canvas_dimension,
            const position_type&  scroll_bar_position
        )
        const
        {
            draw_trains_impl(m_model.timetable().down_trains(), true, canvas, canvas_dimension, scroll_bar_position);
            draw_trains_impl(m_model.timetable().up_trains(), false, canvas, canvas_dimension, scroll_bar_position);
        }

        void draw_trains_impl(
            const trains_type&    trains,
            const bool            down,
            canvas_type&          canvas,
            const dimension_type& canvas_dimension,
            const position_type&  scroll_bar_position
        )
        const
        {
            std::for_each(
                trains.begin(),
                trains.end(),
                TETENGO2_CPP11_BIND(
                    &diagram_view::draw_train,
                    this,
                    tetengo2::cpp11::placeholders_1(),
                    down,
                    tetengo2::cpp11::ref(canvas),
                    tetengo2::cpp11::cref(canvas_dimension),
                    tetengo2::cpp11::cref(scroll_bar_position)
                )
            );
        }

        void draw_train(
            const train_type&     train,
            const bool            down,
            canvas_type&          canvas,
            const dimension_type& canvas_dimension,
            const position_type&  scroll_bar_position
        )
        const
        {
            if (down)
                draw_down_train(train, canvas, canvas_dimension, scroll_bar_position);
            else
                draw_up_train(train, canvas, canvas_dimension, scroll_bar_position);
        }

        void draw_down_train(
            const train_type&     train,
            canvas_type&          canvas,
            const dimension_type& canvas_dimension,
            const position_type&  scroll_bar_position
        )
        const
        {
            for (stop_index_type from = 0; from < train.stops().size() - 1; )
            {
                if (!has_time(train.stops()[from]))
                {
                    ++from;
                    continue;
                }

                stop_index_type to = from + 1;
                for (; to < train.stops().size(); ++to)
                {
                    if (has_time(train.stops()[to]))
                    {
                        const time_type& departure_time = get_departure_time(train.stops()[from]);
                        const time_type& estimated_arrival_time = estimate_arrival_time(departure_time, from, to);
                        const time_type& arrival_time = get_arrival_time(train.stops()[to]);

                        draw_train_line(
                            from,
                            departure_time,
                            to,
                            std::min(estimated_arrival_time, arrival_time),
                            canvas,
                            canvas_dimension,
                            scroll_bar_position
                        );

                        break;
                    }
                }

                from = to;
            }
        }

        void draw_up_train(
            const train_type&     train,
            canvas_type&          canvas,
            const dimension_type& canvas_dimension,
            const position_type&  scroll_bar_position
        )
        const
        {

        }

        time_type estimate_arrival_time(
            const time_type&      departure_time,
            const stop_index_type departure_stop_index,
            const stop_index_type arrival_stop_index
        )
        const
        {
            const time_span_type travel_time =
                std::accumulate(
                    m_station_intervals.begin() + departure_stop_index,
                    m_station_intervals.begin() + arrival_stop_index,
                    time_span_type(0)
                );
            return departure_time + travel_time;
        }

        void draw_train_line(
            const stop_index_type departure_station_index,
            const time_type&      departure_time,
            const stop_index_type arrival_station_index,
            const time_type&      arrival_time,
            canvas_type&          canvas,
            const dimension_type& canvas_dimension,
            const position_type&  scroll_bar_position
        )
        const
        {
            const left_type horizontal_scroll_bar_position =
                tetengo2::gui::position<position_type>::left(scroll_bar_position);
            const top_type vertical_scroll_bar_position =
                tetengo2::gui::position<position_type>::top(scroll_bar_position);

            const position_type departure(
                time_to_left(departure_time, horizontal_scroll_bar_position),
                station_index_to_top(departure_station_index, vertical_scroll_bar_position)
            );
            const position_type arrival(
                time_to_left(arrival_time, horizontal_scroll_bar_position),
                station_index_to_top(arrival_station_index, vertical_scroll_bar_position)
            );

            canvas.draw_line(departure, arrival, size_type(typename size_type::value_type(1, 6)));
        }

        left_type time_to_left(const time_type& time, const left_type& horizontal_scroll_bar_position)
        const
        {
            typename left_type::value_type left_value(time.seconds_from_midnight());
            left_value /= 180;
            return
                left_type(left_value) -
                horizontal_scroll_bar_position +
                to_rational<left_type>(m_station_header_width);
        }

        top_type station_index_to_top(
            const stop_index_type station_index,
            const top_type&       vertical_scroll_bar_position
        )
        const
        {
            return
                m_station_positions[station_index] -
                vertical_scroll_bar_position +
                to_rational<top_type>(m_time_header_height);
        }


    };


}

#endif
