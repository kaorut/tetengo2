/*! \file
    \brief The definition of bobura::diagram_view.

    Copyright (C) 2007-2012 kaoru

    $Id$
*/

#if !defined(BOBURA_DIAGRAMVIEW_H)
#define BOBURA_DIAGRAMVIEW_H

#include <algorithm>
#include <cassert>
#include <cmath>
//#include <iterator>
//#include <memory>
#include <numeric>
#include <sstream>
#include <stdexcept>
//#include <utility>
#include <vector>

#include <boost/format.hpp>
#include <boost/lexical_cast.hpp>
#include <boost/noncopyable.hpp>
#include <boost/rational.hpp>
#include <boost/throw_exception.hpp>

#include <tetengo2.cpp11.h>
#include <tetengo2.gui.measure.h>
#include <tetengo2.unique.h>


namespace bobura
{
   /*!
        \brief The class template for a diagram view.

        \tparam Header              A header type.
        \tparam TimeLineList        A time line list type.
        \tparam Model               A model type.
        \tparam Canvas              A canvas type.
        \tparam SolidBackground     A solid background type.
        \tparam StationGradeTypeSet A station grade type set type.
        \tparam MessageCatalog      A message catalog type.
    */
    template <
        typename Header,
        typename TimeLineList,
        typename Model,
        typename Canvas,
        typename SolidBackground,
        typename StationGradeTypeSet,
        typename MessageCatalog
    >
    class diagram_view : private boost::noncopyable
    {
    public:
        // types

        //! The header type.
        typedef Header header_type;

        //! The time line list type.
        typedef TimeLineList time_line_list_type;

        //! The model type.
        typedef Model model_type;

        //! The canvas type.
        typedef Canvas canvas_type;

        //! The size type.
        typedef typename canvas_type::size_type size_type;

        //! The position type.
        typedef typename canvas_type::position_type position_type;

        //! The left type.
        typedef typename tetengo2::gui::position<position_type>::left_type left_type;

        //! The top type.
        typedef typename tetengo2::gui::position<position_type>::top_type top_type;

        //! The dimension type.
        typedef typename canvas_type::dimension_type dimension_type;

        //! The width type.
        typedef typename tetengo2::gui::dimension<dimension_type>::width_type width_type;

        //! The height type.
        typedef typename tetengo2::gui::dimension<dimension_type>::height_type height_type;

        //! The horizontal scale type.
        typedef typename width_type::value_type horizontal_scale_type;

        //! The vertical scale type.
        typedef typename height_type::value_type vertical_scale_type;

        //! The string type.
        typedef typename canvas_type::string_type string_type;

        //! The solid background type.
        typedef SolidBackground solid_background_type;

        //! The station grade type set type.
        typedef StationGradeTypeSet station_grade_type_set_type;

        //! The message catalog type.
        typedef MessageCatalog message_catalog_type;


        // constructors and destructor

        /*!
            \brief Creates a diagram view.

            \param model           A model.
            \param message_catalog A message catalog.
        */
        diagram_view(const model_type& model, const message_catalog_type& message_catalog)
        :
        m_p_header(),
        m_p_time_line_list(),
        m_model(model),
        m_message_catalog(message_catalog),
        m_horizontal_scale(1),
        m_vertical_scale(1),
        m_dimension(width_type(0), height_type(0)),
        m_station_header_width(8),
        m_time_header_height(3),
        m_time_offset(time_span_type(3, 0, 0)),
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
        void draw_on(
            canvas_type&          canvas,
            const dimension_type& canvas_dimension,
            const position_type&  scroll_bar_position
        )
        {
            clear_background(canvas, canvas_dimension);

            draw_header(canvas, canvas_dimension);
            draw_time_lines(canvas, canvas_dimension, scroll_bar_position);
            draw_station_lines(canvas, canvas_dimension, scroll_bar_position);
            draw_trains(canvas, canvas_dimension, scroll_bar_position);
        }

        /*!
            \brief Returns the horizontal scale.

            \return The horizontal scale.
        */
        const horizontal_scale_type& horizontal_scale()
        const
        {
            return m_horizontal_scale;
        }

        /*!
            \brief Sets a horizontal scale.

            \tparam HS A horizontal scale type.

            \param scale A horizontal scale.
        */
        template <typename HS>
        void set_horizontal_scale(HS&& scale)
        {
            m_horizontal_scale = std::forward<HS>(scale);
            update_dimension();
        }

        /*!
            \brief Returns the vertical scale.

            \return The vertical scale.
        */
        const vertical_scale_type& vertical_scale()
        const
        {
            return m_vertical_scale;
        }

        /*!
            \brief Sets a vertical scale.

            \tparam VS A vertical scale type.

            \param scale A vertical scale.
        */
        template <typename VS>
        void set_vertical_scale(VS&& scale)
        {
            m_vertical_scale = std::forward<VS>(scale);
            update_dimension();
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
            \brief Updates the dimension.
        */
        void update_dimension()
        {
            const width_type width(20 * 24 * m_horizontal_scale);

            m_station_intervals = m_model.timetable().station_intervals();
            if (m_station_intervals.empty())
            {
                m_station_positions.clear();
                m_dimension = dimension_type(width, height_type(0));
                return;
            }
            
            std::vector<top_type> positions;
            positions.reserve(m_station_intervals.size());
            std::transform(
                m_station_intervals.begin(),
                m_station_intervals.end(),
                std::back_inserter(positions),
                to_station_position(m_vertical_scale)
            );

            m_station_positions = std::move(positions);
            m_dimension = dimension_type(width, height_type::from(m_station_positions.back()));
        }

        /*!
            \brief Update the dimension and redraw the canvas to recalculate the dimension.

            \param canvas              A canvas.
            \param canvas_dimension    A canvas dimension.
            \param scroll_bar_position A scroll bar position.
        */
        void update_and_recalculate_dimension(
            canvas_type&          canvas,
            const dimension_type& canvas_dimension,
            const position_type&  scroll_bar_position
        )
        {
            update_dimension();
            draw_on(canvas, canvas_dimension, scroll_bar_position);
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
            const width_type header_width = m_station_header_width;
            width_type page_width = canvas_width > header_width ? canvas_width - header_width : width_type(0);

            const height_type canvas_height = tetengo2::gui::dimension<dimension_type>::height(canvas_dimension);
            const height_type header_height_ = height_type::from(header_bottom()) + m_time_header_height;
            height_type page_height = canvas_height > header_height_ ? canvas_height - header_height_ : height_type(0);

            return dimension_type(std::move(page_width), std::move(page_height));
        }


    private:
        // types

        typedef typename solid_background_type::color_type color_type;

        typedef typename model_type::timetable_type timetable_type;

        typedef typename timetable_type::font_color_set_type font_color_set_type;

        typedef typename font_color_set_type::font_color_type font_color_type;

        typedef typename timetable_type::station_intervals_type station_intervals_type;

        typedef typename timetable_type::station_location_type station_location_type;

        typedef typename station_location_type::station_type station_type;

        typedef typename station_type::grade_type station_grade_type;

        typedef typename timetable_type::train_type train_type;

        typedef typename timetable_type::trains_type trains_type;

        typedef typename timetable_type::train_kind_type train_kind_type;

        typedef typename train_type::stop_type stop_type;

        typedef typename stop_type::time_type time_type;

        typedef typename time_type::time_span_type time_span_type;

        typedef typename train_type::stops_type::size_type stop_index_type;

        class call_draw_train
        {
        public:
            call_draw_train(
                diagram_view&         self,
                const bool            down,
                canvas_type&          canvas,
                const dimension_type& canvas_dimension,
                const position_type&  scroll_bar_position
            )
            :
            m_self(self),
            m_down(down),
            m_canvas(canvas),
            m_canvas_dimension(canvas_dimension),
            m_scroll_bar_position(scroll_bar_position)
            {}

            void operator()(const train_type& train)
            const
            {
                m_self.draw_train(
                    train,
                    m_down,
                    m_canvas,
                    m_canvas_dimension,
                    m_scroll_bar_position
                );
            }

        private:
            diagram_view& m_self;

            const bool m_down;

            canvas_type& m_canvas;

            const dimension_type& m_canvas_dimension;

            const position_type& m_scroll_bar_position;

        };

        class to_station_position
        {
        public:
            explicit to_station_position(const vertical_scale_type& vertical_scale)
            :
            m_vertical_scale(vertical_scale),
            m_sum(0)
            {}

            top_type operator()(const time_span_type& interval)
            {
                const time_span_type position = m_sum;
                m_sum += interval;
                return
                    top_type(typename top_type::value_type(position.seconds(), 60)) *
                    top_type::from(height_type(m_vertical_scale)).value();
            }

        private:
            const vertical_scale_type& m_vertical_scale;

            time_span_type m_sum;

        };


        // static functions

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

        static double calculate_train_name_angle(const position_type& departure, const position_type& arrival)
        {
            const top_type height =
                tetengo2::gui::position<position_type>::top(arrival) -
                tetengo2::gui::position<position_type>::top(departure);
            const left_type width =
                tetengo2::gui::position<position_type>::left(arrival) -
                tetengo2::gui::position<position_type>::left(departure);

            return
                std::atan2(boost::rational_cast<double>(height.value()), boost::rational_cast<double>(width.value()));
        }

        static position_type calculate_train_name_position(
            const position_type& departure,
            const string_type&   train_name,
            const double         angle,
            const bool           down,
            const canvas_type&   canvas
        )
        {
            const dimension_type text_dimension = canvas.calc_text_dimension(train_name);
            const height_type text_height = tetengo2::gui::dimension<dimension_type>::height(text_dimension);

            if (down)
            {
                if (-pi() / 8 < angle && angle < pi() / 8)
                {
                    return
                        position_type(
                            tetengo2::gui::position<position_type>::left(departure),
                            tetengo2::gui::position<position_type>::top(departure) - text_height
                        );
                }
                else
                {
                    const double left_diff = boost::rational_cast<double>(text_height.value()) / std::sin(angle);
                    const left_type left =
                        tetengo2::gui::position<position_type>::left(departure) +
                        typename left_type::value_type(
                            static_cast<typename left_type::value_type::int_type>(left_diff * 0x10000), 0x10000
                        );

                    return position_type(left, tetengo2::gui::position<position_type>::top(departure));
                }
            }
            else
            {
                const double left_diff = boost::rational_cast<double>(text_height.value()) * std::sin(angle);
                const left_type left =
                    tetengo2::gui::position<position_type>::left(departure) +
                    typename left_type::value_type(
                        static_cast<typename left_type::value_type::int_type>(left_diff * 0x10000), 0x10000
                    );

                const double top_diff = boost::rational_cast<double>(text_height.value()) * std::cos(angle);
                const top_type top =
                    tetengo2::gui::position<position_type>::top(departure) -
                    typename top_type::value_type(
                        static_cast<typename top_type::value_type::int_type>(top_diff * 0x10000), 0x10000
                    );

                return position_type(left, top);
            }
        }

        static double pi()
        {
            return 3.14159265358979323846264338327950288;
        }


        // variables

        std::unique_ptr<header_type> m_p_header;

        std::unique_ptr<time_line_list_type> m_p_time_line_list;

        const model_type& m_model;

        const message_catalog_type& m_message_catalog;

        horizontal_scale_type m_horizontal_scale;

        vertical_scale_type m_vertical_scale;

        dimension_type m_dimension;

        width_type m_station_header_width;

        height_type m_time_header_height;

        time_span_type m_time_offset;

        station_intervals_type m_station_intervals;

        std::vector<top_type> m_station_positions;


        // functions

        void clear_background(canvas_type& canvas, const dimension_type& canvas_dimension)
        const
        {
            canvas.set_background(
                tetengo2::make_unique<const solid_background_type>(m_model.timetable().font_color_set().background())
            );
            canvas.fill_rectangle(position_type(left_type(0), top_type(0)), canvas_dimension);
        }

        void draw_header(canvas_type& canvas, const dimension_type& canvas_dimension)
        {
            m_p_header = tetengo2::make_unique<header_type>(m_model, canvas, canvas_dimension);
            m_p_header->draw_on(canvas);
        }

        top_type header_bottom()
        const
        {
            return
                m_p_header ?
                top_type::from(tetengo2::gui::dimension<dimension_type>::height(m_p_header->dimension())) :
                top_type(0);
        }

        void draw_time_lines(
            canvas_type&          canvas,
            const dimension_type& canvas_dimension,
            const position_type&  scroll_bar_position
        )
        {
            m_p_time_line_list =
                tetengo2::make_unique<time_line_list_type>(
                    m_model,
                    m_time_offset,
                    canvas,
                    canvas_dimension,
                    m_dimension,
                    scroll_bar_position,
                    left_type::from(m_station_header_width),
                    header_bottom(),
                    m_time_header_height,
                    m_horizontal_scale,
                    m_vertical_scale
                );
            m_p_time_line_list->draw_on(canvas);
        }

        void draw_station_lines(
            canvas_type&          canvas,
            const dimension_type& canvas_dimension,
            const position_type&  scroll_bar_position
        )
        {
            const left_type canvas_right =
                left_type::from(tetengo2::gui::dimension<dimension_type>::width(canvas_dimension));
            const left_type last_time_position =
                time_to_left(
                    time_type(24 * 60 * 60 + m_time_offset.seconds()),
                    true,
                    tetengo2::gui::position<position_type>::left(scroll_bar_position)
                );
            const left_type line_right = std::min(canvas_right, last_time_position);

            const top_type canvas_top = header_bottom() + top_type::from(m_time_header_height);
            const top_type canvas_bottom =
                top_type::from(tetengo2::gui::dimension<dimension_type>::height(canvas_dimension));

            canvas.set_line_width(size_type(typename size_type::value_type(1, 12)));
            canvas.set_line_style(canvas_type::line_style_type::solid);

            for (typename std::vector<top_type>::size_type i = 0; i < m_station_positions.size(); ++i)
            {
                const top_type& position = m_station_positions[i];
                const top_type line_position =
                    position + canvas_top - tetengo2::gui::position<position_type>::top(scroll_bar_position);
                if (line_position < canvas_top)
                    continue;
                if (line_position > canvas_bottom)
                    break;

                const font_color_type& font_color =
                    select_station_font_color(m_model.timetable().station_locations()[i].station().grade());
                canvas.set_font(font_color.font());
                canvas.set_color(font_color.color());

                const string_type& station_name = m_model.timetable().station_locations()[i].station().name();
                const dimension_type station_name_dimension = canvas.calc_text_dimension(station_name);

                canvas.draw_line(
                    position_type(left_type(0), line_position), position_type(line_right, line_position)
                );

                canvas.draw_text(
                    station_name,
                    position_type(
                        left_type(0),
                        line_position -
                            top_type::from(tetengo2::gui::dimension<dimension_type>::height(station_name_dimension))
                    )
                );
            }
        }

        const font_color_type& select_station_font_color(const station_grade_type& grade)
        {
            if      (&grade == &station_grade_type_set_type::local_type::instance())
                return m_model.timetable().font_color_set().local_station();
            else if (&grade == &station_grade_type_set_type::principal_type::instance())
                return m_model.timetable().font_color_set().principal_station();
            else if (&grade == &station_grade_type_set_type::local_terminal_type::instance())
                return m_model.timetable().font_color_set().local_terminal_station();
            else if (&grade == &station_grade_type_set_type::principal_terminal_type::instance())
                return m_model.timetable().font_color_set().principal_terminal_station();
            else
            {
                assert(false);
                BOOST_THROW_EXCEPTION(std::invalid_argument("Unknown station grade."));
            }
        }

        void draw_trains(
            canvas_type&          canvas,
            const dimension_type& canvas_dimension,
            const position_type&  scroll_bar_position
        )
        {
            canvas.set_font(m_model.timetable().font_color_set().train_name());

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
        {
            std::for_each(
                trains.begin(),
                trains.end(),
                call_draw_train(*this, down, canvas, canvas_dimension, scroll_bar_position)
            );
        }

        void draw_train(
            const train_type&     train,
            const bool            down,
            canvas_type&          canvas,
            const dimension_type& canvas_dimension,
            const position_type&  scroll_bar_position
        )
        {
            const train_kind_type& train_kind = m_model.timetable().train_kinds()[train.kind_index()];
            canvas.set_color(train_kind.color());
            canvas.set_line_width(
                train_kind.weight() == train_kind_type::weight_type::bold ?
                size_type(typename size_type::value_type(1, 6)) : size_type(typename size_type::value_type(1, 12))
            );
            canvas.set_line_style(translate_line_style(train_kind.line_style()));

            bool train_name_drawn = false;
            if (down)
            {
                for (stop_index_type i = 0; i < train.stops().size() - 1; )
                {
                    const stop_index_type from = i;

                    if (!has_time(train.stops()[from]))
                    {
                        ++i;
                        continue;
                    }

                    stop_index_type j = i + 1;
                    for (; j < train.stops().size(); ++j)
                    {
                        const stop_index_type to = j;

                        if (has_time(train.stops()[to]))
                        {
                            const time_type& departure_time = get_departure_time(train.stops()[from]);
                            const time_type arrival_time =
                                estimate_arrival_time(departure_time, train.stops()[to], from, to);

                            draw_train_line(
                                from,
                                departure_time,
                                to,
                                arrival_time,
                                !train_name_drawn ? make_train_name(train) : string_type(),
                                down,
                                canvas,
                                canvas_dimension,
                                scroll_bar_position
                            );

                            if (!train_name_drawn)
                                train_name_drawn = true;

                            break;
                        }
                    }

                    i = j;
                }
            }
            else
            {
                for (stop_index_type i = train.stops().size(); i > 1; )
                {
                    const stop_index_type from = i - 1;

                    if (!has_time(train.stops()[from]))
                    {
                        --i;
                        continue;
                    }

                    stop_index_type j = i - 1;
                    for (; j > 0; --j)
                    {
                        const stop_index_type to = j - 1;

                        if (has_time(train.stops()[to]))
                        {
                            const time_type& departure_time = get_departure_time(train.stops()[from]);
                            const time_type arrival_time =
                                estimate_arrival_time(departure_time, train.stops()[to], to, from);

                            draw_train_line(
                                from,
                                departure_time,
                                to,
                                arrival_time,
                                !train_name_drawn ? make_train_name(train) : string_type(),
                                down,
                                canvas,
                                canvas_dimension,
                                scroll_bar_position
                            );

                            if (!train_name_drawn)
                                train_name_drawn = true;

                            break;
                        }
                    }

                    i = j;
                }
            }
        }

        typename canvas_type::line_style_type::enum_t translate_line_style(
            const typename train_kind_type::line_style_type::enum_t line_style
        )
        const
        {
            switch (line_style)
            {
            case train_kind_type::line_style_type::solid:
                return canvas_type::line_style_type::solid;
            case train_kind_type::line_style_type::dashed:
                return canvas_type::line_style_type::dashed;
            case train_kind_type::line_style_type::dotted:
                return canvas_type::line_style_type::dotted;
            case train_kind_type::line_style_type::dot_dashed:
                return canvas_type::line_style_type::dot_dashed;
            default:
                assert(false);
                BOOST_THROW_EXCEPTION(std::invalid_argument("Unknown line style."));
            }
        }

        time_type estimate_arrival_time(
            const time_type&      from_departure,
            const stop_type&      to_stop,
            const stop_index_type upper_stop_index,
            const stop_index_type lower_stop_index
        )
        const
        {
            if (to_stop.arrival() != time_type::uninitialized())
                return to_stop.arrival();

            const time_span_type departure_interval = to_stop.departure() - from_departure;
            const time_span_type travel_time =
                std::accumulate(
                    m_station_intervals.begin() + upper_stop_index,
                    m_station_intervals.begin() + lower_stop_index,
                    time_span_type(0)
                );

            return departure_interval < travel_time ? to_stop.departure() : from_departure + travel_time;
        }

        string_type make_train_name(const train_type& train)
        const
        {
            std::basic_ostringstream<typename string_type::value_type> name;

            name << train.number();
            name << string_type(TETENGO2_TEXT(" "));
            if (train.name_number().empty())
            {
                name << train.name();
            }
            else
            {
                name <<
                    boost::basic_format<typename string_type::value_type>(
                        m_message_catalog.get(string_type(TETENGO2_TEXT("Diagram:%1% No. %2%")))
                    ) % train.name() % train.name_number();
            }

            return name.str();
        }

        void draw_train_line(
            const stop_index_type departure_station_index,
            const time_type&      departure_time,
            const stop_index_type arrival_station_index,
            const time_type&      arrival_time,
            const string_type&    train_name,
            const bool            down,
            canvas_type&          canvas,
            const dimension_type& canvas_dimension,
            const position_type&  scroll_bar_position
        )
        {
            if (departure_time - m_time_offset < arrival_time - m_time_offset)
            {
                draw_train_line_impl(
                    departure_station_index,
                    departure_time,
                    false,
                    arrival_station_index,
                    arrival_time,
                    train_name,
                    false,
                    down,
                    canvas,
                    canvas_dimension,
                    scroll_bar_position
                );
            }
            else
            {
                draw_train_line_impl(
                    departure_station_index,
                    departure_time,
                    true,
                    arrival_station_index,
                    arrival_time,
                    train_name,
                    false,
                    down,
                    canvas,
                    canvas_dimension,
                    scroll_bar_position
                );
                draw_train_line_impl(
                    departure_station_index,
                    departure_time,
                    false,
                    arrival_station_index,
                    arrival_time,
                    train_name,
                    true,
                    down,
                    canvas,
                    canvas_dimension,
                    scroll_bar_position
                );
            }
        }

        void draw_train_line_impl(
            const stop_index_type departure_station_index,
            const time_type&      departure_time,
            const bool            previous_day_departure,
            const stop_index_type arrival_station_index,
            const time_type&      arrival_time,
            const string_type&    train_name,
            const bool            next_day_arrival,
            const bool            down,
            canvas_type&          canvas,
            const dimension_type& canvas_dimension,
            const position_type&  scroll_bar_position
        )
        {
            const left_type horizontal_scroll_bar_position =
                tetengo2::gui::position<position_type>::left(scroll_bar_position);
            const top_type vertical_scroll_bar_position =
                tetengo2::gui::position<position_type>::top(scroll_bar_position);

            const position_type departure(
                time_to_left(departure_time, previous_day_departure ? -1 : 0, horizontal_scroll_bar_position),
                station_index_to_top(departure_station_index, vertical_scroll_bar_position)
            );
            const position_type arrival(
                time_to_left(arrival_time, next_day_arrival ? 1 : 0, horizontal_scroll_bar_position),
                station_index_to_top(arrival_station_index, vertical_scroll_bar_position)
            );
            
            const left_type left_bound = tetengo2::gui::position<position_type>::left(departure);
            if (left_bound > left_type::from(tetengo2::gui::dimension<dimension_type>::width(canvas_dimension)))
                return;
            const left_type right_bound = tetengo2::gui::position<position_type>::left(arrival);
            if (right_bound < left_type::from(m_station_header_width))
                return;
            const top_type upper_bound =
                departure_station_index < arrival_station_index ? 
                tetengo2::gui::position<position_type>::top(departure) :
                tetengo2::gui::position<position_type>::top(arrival);
            if (upper_bound > top_type::from(tetengo2::gui::dimension<dimension_type>::height(canvas_dimension)))
                return;
            const top_type lower_bound =
                departure_station_index < arrival_station_index ? 
                tetengo2::gui::position<position_type>::top(arrival) :
                tetengo2::gui::position<position_type>::top(departure);
            if (lower_bound < header_bottom() + top_type::from(m_time_header_height))
                return;

            canvas.draw_line(departure, arrival);

            if (!train_name.empty())
            {
                const double train_name_angle = calculate_train_name_angle(departure, arrival);
                canvas.draw_text(
                    train_name,
                    calculate_train_name_position(departure, train_name, train_name_angle, down, canvas),
                    train_name_angle
                );
            }
        }

        left_type time_to_left(
            const time_type& time,
            const int        previous_or_next_day,
            const left_type& horizontal_scroll_bar_position
        )
        const
        {
            typename left_type::value_type left_value(time.seconds_from_midnight());
            left_value -= m_time_offset.seconds();
            if (left_value < 0)
                left_value += time_span_type::seconds_of_whole_day();
            left_value += previous_or_next_day * time_span_type::seconds_of_whole_day();
            left_value /= 180;
            left_value *= left_type::from(width_type(m_horizontal_scale)).value();
            return left_type(left_value) - horizontal_scroll_bar_position + left_type::from(m_station_header_width);
        }

        top_type station_index_to_top(
            const stop_index_type station_index,
            const top_type&       vertical_scroll_bar_position
        )
        const
        {
            const top_type canvas_top = header_bottom() + top_type::from(m_time_header_height);
            return m_station_positions[station_index] + canvas_top - vertical_scroll_bar_position;
        }


    };


}

#endif
