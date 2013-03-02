/*! \file
    \brief The definition of bobura::view::diagram::train_line.

    Copyright (C) 2007-2013 kaoru

    $Id$
*/

#if !defined(BOBURA_VIEW_DIAGRAM_TRAINLINE_H)
#define BOBURA_VIEW_DIAGRAM_TRAINLINE_H

#include <cassert>
//#include <cmath>
#include <numeric>
#include <sstream>
#include <stdexcept>
//#include <utility>
#include <vector>

#include <boost/foreach.hpp>
#include <boost/format.hpp>
#include <boost/math/constants/constants.hpp>
//#include <boost/rational.hpp>
#include <boost/throw_exception.hpp>

#include <tetengo2.cpp11.h>
#include <tetengo2.gui.measure.h>
#include <tetengo2.text.h>

#include "bobura.view.diagram.item.h"
#include "bobura.view.diagram.utility.h"


namespace bobura { namespace view { namespace diagram
{
     /*!
        \brief The class template for a train line fragment in the diagram view.

        \tparam Canvas A canvas type.
    */
    template <typename Canvas>
    class train_line_fragment : public item<Canvas>
    {
    public:
        // types

        //! The canvas type.
        typedef Canvas canvas_type;

        //! The string type.
        typedef typename canvas_type::string_type string_type;

        //! The position type.
        typedef typename canvas_type::position_type position_type;

        //! The base type.
        typedef item<canvas_type> base_type;


        // constructors and destructor

        /*!
            \brief Creates a train line fragment.

            \param departure  A departure position.
            \param arrival    A arrival position.
            \param train_name A train name.
            \param down       Set true for a down train.
        */
        train_line_fragment(
            position_type      departure,
            position_type      arrival,
            const string_type& train_name,
            const bool         down
        )
        :
        m_departure(std::move(departure)),
        m_arrival(std::move(arrival)),
        m_train_name(train_name),
        m_down(down),
        m_selected(false)
        {}

        /*!
            \brief Moves a train line fragment.

            \param another Another train line fragment.
        */
        train_line_fragment(train_line_fragment&& another)
        :
        m_departure(std::move(another.m_departure)),
        m_arrival(std::move(another.m_arrival)),
        m_train_name(std::move(another.m_train_name)),
        m_down(another.m_down),
        m_selected(another.m_selected)
        {}

        /*!
            \brief Destroys the train line fragment.
        */
        virtual ~train_line_fragment()
        TETENGO2_CPP11_NOEXCEPT
        {}


        // functions

        /*!
            \brief Assigns a train line fragment.

            \param another Another train line fragment.

            \return This train line fraqment.
        */
        train_line_fragment& operator=(train_line_fragment&& another)
        {
            if (&another == this)
                return *this;

            m_departure = std::move(another.m_departure);
            m_arrival = std::move(another.m_arrival);
            m_train_name = std::move(another.m_train_name);
            m_down = another.m_down;

            return *this;
        }


    private:
        // types

        typedef typename tetengo2::gui::position<position_type>::left_type left_type;

        typedef typename tetengo2::gui::position<position_type>::top_type top_type;

        typedef typename canvas_type::dimension_type dimension_type;

        typedef typename tetengo2::gui::dimension<dimension_type>::width_type width_type;

        typedef typename tetengo2::gui::dimension<dimension_type>::height_type height_type;

        typedef typename canvas_type::size_type size_type;

        typedef std::pair<double, double> geo_vector_type;


        // static functions

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
                if (
                    -boost::math::constants::pi<double>() / 8 < angle &&
                    angle < boost::math::constants::pi<double>() / 8
                )
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

        static size_type calculate_distance(
            const position_type& point,
            const position_type& line_segment_begin,
            const position_type& line_segment_end
        )
        {
            const geo_vector_type p = to_geo_vector(point);
            const geo_vector_type lsb = to_geo_vector(line_segment_begin);
            const geo_vector_type lse = to_geo_vector(line_segment_end);

            double d = 0.0;
            if      (geo_dot(geo_minus(lse, lsb), geo_minus(p, lsb)) < 0.0)
                d = geo_abs(geo_minus(p, lsb));
            else if (geo_dot(geo_minus(lsb, lse), geo_minus(p, lse)) < 0.0)
                d = geo_abs(geo_minus(p, lse));
            else
                d = std::abs(geo_cross(geo_minus(lse, lsb), geo_minus(p, lsb))) / geo_abs(geo_minus(lse, lsb));

            return to_size(d);
        }

        static geo_vector_type to_geo_vector(const position_type& position)
        {
            return
                geo_vector_type(
                    boost::rational_cast<double>(tetengo2::gui::position<position_type>::left(position).value()),
                    boost::rational_cast<double>(tetengo2::gui::position<position_type>::top(position).value())
                );
        }

        static size_type to_size(const double value)
        {
            return
                size_type(
                    typename size_type::value_type(typename size_type::value_type::int_type(value * 256.0), 256)
                );
        }

        static geo_vector_type geo_minus(const geo_vector_type& v1, const geo_vector_type& v2)
        {
            return geo_vector_type(v1.first - v2.first, v1.second - v2.second);
        }

        static double geo_abs(const geo_vector_type& v)
        {
            return std::sqrt(v.first * v.first + v.second * v.second);
        }

        static double geo_dot(const geo_vector_type& v1, const geo_vector_type& v2)
        {
            return v1.first * v2.first + v1.second * v2.second;
        }

        static double geo_cross(const geo_vector_type& v1, const geo_vector_type& v2)
        {
            return v1.first * v2.second - v1.second * v2.first;
        }


        // variables

        position_type m_departure;

        position_type m_arrival;

        string_type m_train_name;

        bool m_down;

        bool m_selected;


        // virtual functions

        virtual void draw_on_impl(canvas_type& canvas)
        const
        {
            size_type original_line_width = canvas.line_width();
            if (m_selected)
                canvas.set_line_width(original_line_width * 4);
            canvas.draw_line(m_departure, m_arrival);
            if (m_selected)
                canvas.set_line_width(std::move(original_line_width));

            if (!m_train_name.empty())
            {
                const double train_name_angle = calculate_train_name_angle(m_departure, m_arrival);
                canvas.draw_text(
                    m_train_name,
                    calculate_train_name_position(m_departure, m_train_name, train_name_angle, m_down, canvas),
                    train_name_angle
                );
            }
        }

        virtual base_type* p_item_by_position_impl(const position_type& position)
        {
            if (calculate_distance(position, m_departure, m_arrival) <= size_type(1))
                return this;
            else
                return NULL;
        }

        virtual bool selected_impl()
        const
        {
            return m_selected;
        }

        virtual void set_selected_impl(const bool selected)
        {
            m_selected = selected;
        }


    };


     /*!
        \brief The class template for a train line in the diagram view.

        \tparam Model          A model type.
        \tparam Canvas         A canvas type.
        \tparam MessageCatalog A message catalog type.
    */
    template <typename Model, typename Canvas, typename MessageCatalog>
    class train_line : public item<Canvas>
    {
    public:
        // types

        //! The model type.
        typedef Model model_type;

        //! The train type.
        typedef typename model_type::timetable_type::train_type train_type;

        //! The time type.
        typedef typename train_type::stop_type::time_type time_type;

        //! The time span type.
        typedef typename time_type::time_span_type time_span_type;

        //! The train kind type.
        typedef typename model_type::timetable_type::train_kind_type train_kind_type;

        //! The station intervals type.
        typedef typename model_type::timetable_type::station_intervals_type station_intervals_type;

        //! The canvas type.
        typedef Canvas canvas_type;

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

        //! The base type.
        typedef item<canvas_type> base_type;

        //! The message catalog type.
        typedef MessageCatalog message_catalog_type;


        // constructors and destructor

        /*!
            \brief Creates a train line.

            \param train                A train.
            \param train_kind           A train kind.
            \param down                 Set true for a down train.
            \param time_offset          A time offet.
            \param canvas               A canva.
            \param canvas_dimension     A canvas dimension.
            \param scroll_bar_position  A scroll bar position.
            \param station_header_right A station header right position.
            \param header_bottom        A header bottom position.
            \param time_header_height   A time header height.
            \param horizontal_scale     A horizontal scale.
            \param vertical_scale       A vertical scale.
            \param station_intervals    Station intervals.
            \param station_positions    Station positions.
            \param message_catalog      A mesage catalog.
        */
        train_line(
            const train_type&             train,
            const train_kind_type&        train_kind,
            const bool                    down,
            const time_span_type&         time_offset,
            canvas_type&                  canvas,
            const dimension_type&         canvas_dimension,
            const position_type&          scroll_bar_position,
            const left_type&              station_header_right,
            const top_type&               header_bottom,
            const height_type&            time_header_height,
            const horizontal_scale_type&  horizontal_scale,
            const vertical_scale_type&    vertical_scale,
            const station_intervals_type& station_intervals,
            const std::vector<top_type>&  station_positions,
            const message_catalog_type&   message_catalog
        )
        :
        m_p_train_kind(&train_kind),
        m_fragments(
            make_fragments(
                train,
                train_kind,
                down,
                time_offset,
                canvas,
                canvas_dimension,
                scroll_bar_position,
                station_header_right,
                header_bottom,
                time_header_height,
                horizontal_scale,
                vertical_scale,
                station_intervals,
                station_positions,
                message_catalog
            )
        )
        {}

        /*!
            \brief Moves a train line.

            \param another Another train line.
        */
        train_line(train_line&& another)
        :
        m_p_train_kind(another.m_p_train_kind),
        m_fragments(std::move(another.m_fragments))
        {}

        /*!
            \brief Destroys the train line.
        */
        virtual ~train_line()
        TETENGO2_CPP11_NOEXCEPT
        {}


        // functions

        /*!
            \brief Assigns a train line.

            \param another Another train line.

            \return This train line.
        */
        train_line& operator=(train_line&& another)
        {
            if (&another == this)
                return *this;

            m_p_train_kind = another.m_p_train_kind;
            m_fragments = std::move(another.m_fragments);

            return *this;
        }


    private:
        // types

        typedef train_line_fragment<canvas_type> train_line_fragment_type;

        typedef typename canvas_type::size_type size_type;

        typedef typename canvas_type::string_type string_type;

        typedef typename train_type::stops_type::size_type stop_index_type;

        typedef typename train_type::stop_type stop_type;


        // static functions

        static std::vector<train_line_fragment_type> make_fragments(
            const train_type&             train,
            const train_kind_type&        train_kind,
            const bool                    down,
            const time_span_type&         time_offset,
            canvas_type&                  canvas,
            const dimension_type&         canvas_dimension,
            const position_type&          scroll_bar_position,
            const left_type&              station_header_right,
            const top_type&               header_bottom,
            const height_type&            time_header_height,
            const horizontal_scale_type&  horizontal_scale,
            const vertical_scale_type&    vertical_scale,
            const station_intervals_type& station_intervals,
            const std::vector<top_type>&  station_positions,
            const message_catalog_type&   message_catalog
        )
        {
            std::vector<train_line_fragment_type> fragments;

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
                                estimate_arrival_time(station_intervals, departure_time, train.stops()[to], from, to);

                            make_fragment(
                                from,
                                departure_time,
                                to,
                                arrival_time,
                                !train_name_drawn ? make_train_name(train, message_catalog) : string_type(),
                                down,
                                time_offset,
                                canvas,
                                canvas_dimension,
                                scroll_bar_position,
                                station_header_right,
                                header_bottom,
                                time_header_height,
                                horizontal_scale,
                                vertical_scale,
                                station_positions,
                                fragments
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
                                estimate_arrival_time(station_intervals, departure_time, train.stops()[to], to, from);

                            make_fragment(
                                from,
                                departure_time,
                                to,
                                arrival_time,
                                !train_name_drawn ? make_train_name(train, message_catalog) : string_type(),
                                down,
                                time_offset,
                                canvas,
                                canvas_dimension,
                                scroll_bar_position,
                                station_header_right,
                                header_bottom,
                                time_header_height,
                                horizontal_scale,
                                vertical_scale,
                                station_positions,
                                fragments
                            );

                            if (!train_name_drawn)
                                train_name_drawn = true;

                            break;
                        }
                    }

                    i = j;
                }
            }

            return std::move(fragments);
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

        static time_type estimate_arrival_time(
            const station_intervals_type& station_intervals,
            const time_type&              from_departure,
            const stop_type&              to_stop,
            const stop_index_type         upper_stop_index,
            const stop_index_type         lower_stop_index
        )
        {
            if (to_stop.arrival() != time_type::uninitialized())
                return to_stop.arrival();

            const time_span_type departure_interval = to_stop.departure() - from_departure;
            const time_span_type travel_time =
                std::accumulate(
                    station_intervals.begin() + upper_stop_index,
                    station_intervals.begin() + lower_stop_index,
                    time_span_type(0)
                );

            return departure_interval < travel_time ? to_stop.departure() : from_departure + travel_time;
        }

        static string_type make_train_name(const train_type& train, const message_catalog_type& message_catalog)
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
                        message_catalog.get(TETENGO2_TEXT("Diagram:%1% No. %2%"))
                    ) % train.name() % train.name_number();
            }

            return name.str();
        }

        static void make_fragment(
            const stop_index_type                  departure_station_index,
            const time_type&                       departure_time,
            const stop_index_type                  arrival_station_index,
            const time_type&                       arrival_time,
            const string_type&                     train_name,
            const bool                             down,
            const time_span_type&                  time_offset,
            canvas_type&                           canvas,
            const dimension_type&                  canvas_dimension,
            const position_type&                   scroll_bar_position,
            const left_type&                       station_header_right,
            const top_type&                        header_bottom,
            const height_type&                     time_header_height,
            const horizontal_scale_type&           horizontal_scale,
            const vertical_scale_type&             vertical_scale,
            const std::vector<top_type>&           station_positions,
            std::vector<train_line_fragment_type>& fragments
        )
        {
            if (departure_time - time_offset <= arrival_time - time_offset)
            {
                make_fragment_impl(
                    departure_station_index,
                    departure_time,
                    false,
                    arrival_station_index,
                    arrival_time,
                    false,
                    train_name,
                    down,
                    time_offset,
                    canvas,
                    canvas_dimension,
                    scroll_bar_position,
                    station_header_right,
                    header_bottom,
                    time_header_height,
                    horizontal_scale,
                    vertical_scale,
                    station_positions,
                    fragments
                );
            }
            else
            {
                make_fragment_impl(
                    departure_station_index,
                    departure_time,
                    true,
                    arrival_station_index,
                    arrival_time,
                    false,
                    train_name,
                    down,
                    time_offset,
                    canvas,
                    canvas_dimension,
                    scroll_bar_position,
                    station_header_right,
                    header_bottom,
                    time_header_height,
                    horizontal_scale,
                    vertical_scale,
                    station_positions,
                    fragments
                );
                make_fragment_impl(
                    departure_station_index,
                    departure_time,
                    false,
                    arrival_station_index,
                    arrival_time,
                    true,
                    train_name,
                    down,
                    time_offset,
                    canvas,
                    canvas_dimension,
                    scroll_bar_position,
                    station_header_right,
                    header_bottom,
                    time_header_height,
                    horizontal_scale,
                    vertical_scale,
                    station_positions,
                    fragments
                );
            }
        }

        static void make_fragment_impl(
            const stop_index_type                  departure_station_index,
            const time_type&                       departure_time,
            const bool                             previous_day_departure,
            const stop_index_type                  arrival_station_index,
            const time_type&                       arrival_time,
            const bool                             next_day_arrival,
            const string_type&                     train_name,
            const bool                             down,
            const time_span_type&                  time_offset,
            canvas_type&                           canvas,
            const dimension_type&                  canvas_dimension,
            const position_type&                   scroll_bar_position,
            const left_type&                       station_header_right,
            const top_type&                        header_bottom,
            const height_type&                     time_header_height,
            const horizontal_scale_type&           horizontal_scale,
            const vertical_scale_type&             vertical_scale,
            const std::vector<top_type>&           station_positions,
            std::vector<train_line_fragment_type>& fragments
        )
        {
            const left_type horizontal_scroll_bar_position =
                tetengo2::gui::position<position_type>::left(scroll_bar_position);
            const top_type vertical_scroll_bar_position =
                tetengo2::gui::position<position_type>::top(scroll_bar_position);

            const left_type horizontal_scale_left = left_type::from(width_type(horizontal_scale));
            const top_type time_header_bottom = top_type::from(time_header_height);
            position_type departure(
                time_to_left(
                    departure_time,
                    time_offset,
                    previous_day_departure ? -1 : 0,
                    horizontal_scroll_bar_position,
                    station_header_right,
                    horizontal_scale_left
                ),
                station_index_to_top(
                    station_positions,
                    departure_station_index,
                    vertical_scroll_bar_position,
                    header_bottom,
                    time_header_bottom
                )
            );
            position_type arrival(
                time_to_left(
                    arrival_time,
                    time_offset,
                    next_day_arrival ? 1 : 0,
                    horizontal_scroll_bar_position,
                    station_header_right,
                    horizontal_scale_left
                ),
                station_index_to_top(
                    station_positions,
                    arrival_station_index,
                    vertical_scroll_bar_position,
                    header_bottom,
                    time_header_bottom
                )
            );
            
            const left_type left_bound = tetengo2::gui::position<position_type>::left(departure);
            if (left_bound > left_type::from(tetengo2::gui::dimension<dimension_type>::width(canvas_dimension)))
                return;
            const left_type right_bound = tetengo2::gui::position<position_type>::left(arrival);
            if (right_bound < station_header_right)
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
            if (lower_bound < header_bottom + time_header_bottom)
                return;

            fragments.emplace_back(std::move(departure), std::move(arrival), train_name, down);
        }

        static typename canvas_type::line_style_type::enum_t translate_line_style(
            const typename train_kind_type::line_style_type::enum_t line_style
        )
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


        // variables

        const train_kind_type* m_p_train_kind;

        std::vector<train_line_fragment_type> m_fragments;


        // virtual functions

        virtual void draw_on_impl(canvas_type& canvas)
        const
        {
            canvas.set_color(m_p_train_kind->color());
            canvas.set_line_width(
                m_p_train_kind->weight() == train_kind_type::weight_type::bold ?
                size_type(typename size_type::value_type(1, 6)) : size_type(typename size_type::value_type(1, 12))
            );
            canvas.set_line_style(translate_line_style(m_p_train_kind->line_style()));

            BOOST_FOREACH (const train_line_fragment_type& fragment, m_fragments)
            {
                fragment.draw_on(canvas);
            }
        }

        virtual base_type* p_item_by_position_impl(const position_type& position)
        {
            BOOST_FOREACH (train_line_fragment_type& fragment, m_fragments)
            {
                base_type* const p_item = fragment.p_item_by_position(position);
                if (p_item)
                    return p_item;
            }

            return NULL;
        }

        virtual bool selected_impl()
        const
        {
            return false;
        }

        virtual void set_selected_impl(const bool selected)
        {}


    };


     /*!
        \brief The class template for a train line list in the diagram view.

        \tparam Model          A model type.
        \tparam Canvas         A canvas type.
        \tparam MessageCatalog A message catalog type.
    */
    template <typename Model, typename Canvas, typename MessageCatalog>
    class train_line_list : public item<Canvas>
    {
    public:
        // types

        //! The model type.
        typedef Model model_type;
        
        //! The time type.
        typedef typename model_type::timetable_type::train_type::stop_type::time_type time_type;

        //! The time span type.
        typedef typename time_type::time_span_type time_span_type;

        //! The station intervals type.
        typedef typename model_type::timetable_type::station_intervals_type station_intervals_type;

        //! The canvas type.
        typedef Canvas canvas_type;

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

        //! The base type.
        typedef item<canvas_type> base_type;

        //! The message catalog type.
        typedef MessageCatalog message_catalog_type;


        // constructors and destructor

        /*!
            \brief Creates a train line list.

            \param model                A model.
            \param time_offset          A time offset.
            \param canvas               A canvas.
            \param canvas_dimension     A canvas dimension.
            \param timetable_dimension  A timetable dimension.
            \param scroll_bar_position  A scroll bar position.
            \param station_header_right A right position of the station header.
            \param header_bottom        A bottom position of the header.
            \param time_header_height   A time header height.
            \param horizontal_scale     A horizontal scale.
            \param vertical_scale       A vertical scale.
            \param station_intervals    Station intervals.
            \param station_positions    Station positions.
            \param message_catalog      A message catalog.
        */
        train_line_list(
            const model_type&             model,
            const time_span_type&         time_offset,
            canvas_type&                  canvas,
            const dimension_type&         canvas_dimension,
            const dimension_type&         timetable_dimension,
            const position_type&          scroll_bar_position,
            const left_type&              station_header_right,
            const top_type&               header_bottom,
            const height_type&            time_header_height,
            const horizontal_scale_type&  horizontal_scale,
            const vertical_scale_type&    vertical_scale,
            const station_intervals_type& station_intervals,
            const std::vector<top_type>&  station_positions,
            const message_catalog_type&   message_catalog
        )
        :
        m_p_font(&model.timetable().font_color_set().train_name()),
        m_train_lines(
            make_train_lines(
                model,
                time_offset,
                canvas,
                canvas_dimension,
                timetable_dimension,
                scroll_bar_position,
                station_header_right,
                header_bottom,
                time_header_height,
                horizontal_scale,
                vertical_scale,
                station_intervals,
                station_positions,
                message_catalog
            )
        )
        {}

        /*!
            \brief Moves a train line list.

            \param another Another train line list.
        */
        train_line_list(train_line_list&& another)
        :
        m_p_font(another.m_p_font),
        m_train_lines(std::move(another.m_train_lines))
        {}

        /*!
            \brief Destroys the train line list.
        */
        virtual ~train_line_list()
        TETENGO2_CPP11_NOEXCEPT
        {}


        // functions

        /*!
            \brief Assigns a train line list.

            \param another Another train line list.

            \return This train line list.
        */
        train_line_list& operator=(train_line_list&& another)
        {
            if (&another == this)
                return *this;

            m_p_font = another.m_p_font;
            m_train_lines = std::move(another.m_train_lines);

            return *this;
        }


    private:
        // types

        typedef train_line<model_type, canvas_type, message_catalog_type> train_line_type;

        typedef typename model_type::timetable_type timetable_type;

        typedef typename timetable_type::trains_type trains_type;

        typedef typename timetable_type::train_type train_type;

        typedef typename timetable_type::train_kinds_type train_kinds_type;

        typedef typename timetable_type::train_kind_type train_kind_type;

        typedef typename canvas_type::font_type font_type;


        // static functions

        std::vector<train_line_type> make_train_lines(
            const model_type&             model,
            const time_span_type&         time_offset,
            canvas_type&                  canvas,
            const dimension_type&         canvas_dimension,
            const dimension_type&         timetable_dimension,
            const position_type&          scroll_bar_position,
            const left_type&              station_header_right,
            const top_type&               header_bottom,
            const height_type&            time_header_height,
            const horizontal_scale_type&  horizontal_scale,
            const vertical_scale_type&    vertical_scale,
            const station_intervals_type& station_intervals,
            const std::vector<top_type>&  station_positions,
            const message_catalog_type&   message_catalog
        )
        {
            std::vector<train_line_type> train_lines;

            make_train_lines_impl(
                model.timetable().down_trains(),
                model.timetable().train_kinds(),
                true,
                time_offset,
                canvas,
                canvas_dimension,
                timetable_dimension,
                scroll_bar_position,
                station_header_right,
                header_bottom,
                time_header_height,
                horizontal_scale,
                vertical_scale,
                station_intervals,
                station_positions,
                message_catalog,
                train_lines
            );
            make_train_lines_impl(
                model.timetable().up_trains(),
                model.timetable().train_kinds(),
                false,
                time_offset,
                canvas,
                canvas_dimension,
                timetable_dimension,
                scroll_bar_position,
                station_header_right,
                header_bottom,
                time_header_height,
                horizontal_scale,
                vertical_scale,
                station_intervals,
                station_positions,
                message_catalog,
                train_lines
            );

            return std::move(train_lines);
        }

        void make_train_lines_impl(
            const trains_type&            trains,
            const train_kinds_type&       train_kinds,
            const bool                    down,
            const time_span_type&         time_offset,
            canvas_type&                  canvas,
            const dimension_type&         canvas_dimension,
            const dimension_type&         timetable_dimension,
            const position_type&          scroll_bar_position,
            const left_type&              station_header_right,
            const top_type&               header_bottom,
            const height_type&            time_header_height,
            const horizontal_scale_type&  horizontal_scale,
            const vertical_scale_type&    vertical_scale,
            const station_intervals_type& station_intervals,
            const std::vector<top_type>&  station_positions,
            const message_catalog_type&   message_catalog,
            std::vector<train_line_type>& train_lines
        )
        {
            BOOST_FOREACH (const train_type& train, trains)
            {
                train_lines.push_back(
                    train_line_type(
                        train,
                        train_kinds[train.kind_index()],
                        down,
                        time_offset,
                        canvas,
                        canvas_dimension,
                        scroll_bar_position,
                        station_header_right,
                        header_bottom,
                        time_header_height,
                        horizontal_scale,
                        vertical_scale,
                        station_intervals,
                        station_positions,
                        message_catalog
                    )
                );
            }
        }


        // variables

        const font_type* m_p_font;

        std::vector<train_line_type> m_train_lines;


        // virtual functions

        virtual void draw_on_impl(canvas_type& canvas)
        const
        {
            canvas.set_font(*m_p_font);

            BOOST_FOREACH (const train_line_type& train_line, m_train_lines)
            {
                train_line.draw_on(canvas);
            }
        }

        virtual base_type* p_item_by_position_impl(const position_type& position)
        {
            BOOST_FOREACH (train_line_type& train_line, m_train_lines)
            {
                base_type* const p_item = train_line.p_item_by_position(position);
                if (p_item)
                    return p_item;
            }

            return NULL;
        }

        virtual bool selected_impl()
        const
        {
            return false;
        }

        virtual void set_selected_impl(const bool selected)
        {}


    };


}}}


#endif
