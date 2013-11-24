/*! \file
    \brief The definition of bobura::view::diagram::train_line.

    Copyright (C) 2007-2013 kaoru

    $Id$
*/

#if !defined(BOBURA_VIEW_DIAGRAM_TRAINLINE_H)
#define BOBURA_VIEW_DIAGRAM_TRAINLINE_H

#include <cassert>
//#include <cmath>
#include <limits>
#include <numeric>
#include <sstream>
#include <stdexcept>
//#include <utility>
#include <vector>

#include <boost/format.hpp>
#include <boost/math/constants/constants.hpp>
#include <boost/optional.hpp>
#include <boost/range/adaptors.hpp>
//#include <boost/rational.hpp>
#include <boost/throw_exception.hpp>

#include <tetengo2.gui.measure.h>
#include <tetengo2.stdalt.h>
#include <tetengo2.text.h>

#include "bobura.view.diagram.item.h"
#include "bobura.view.diagram.utility.h"


namespace bobura { namespace view { namespace diagram
{
     /*!
        \brief The class template for a train line fragment in the diagram view.

        \tparam Model          A model type.
        \tparam Selection      A selection type.
        \tparam Canvas         A canvas type.
        \tparam MessageCatalog A message catalog type.
    */
    template <typename Model, typename Selection, typename Canvas, typename MessageCatalog>
    class train_line_fragment : public item<Selection, Canvas>
    {
    public:
        // types

        //! The model type.
        typedef Model model_type;

        //! The train type.
        typedef typename model_type::timetable_type::train_type train_type;

        //! The stop index type.
        typedef typename train_type::stops_type::size_type stop_index_type;

        //! The selection type.
        typedef Selection selection_type;

        //! The canvas type.
        typedef Canvas canvas_type;

        //! The string type.
        typedef typename canvas_type::string_type string_type;

        //! The position type.
        typedef typename canvas_type::position_type position_type;

        //! The base type.
        typedef item<selection_type, canvas_type> base_type;

        //! The message catalog type.
        typedef MessageCatalog message_catalog_type;


        // constructors and destructor

        /*!
            \brief Creates a train line fragment.

            \param train                A train.
            \param departure_stop_index A departure stop index.
            \param selection            A selection.
            \param departure            A departure position.
            \param arrival              A arrival position.
            \param draw_train_name      Set true to draw the train name.
            \param message_catalog      A message catalog.
        */
        train_line_fragment(
            const train_type&           train,
            const stop_index_type       departure_stop_index,
            selection_type&             selection,
            position_type               departure,
            position_type               arrival,
            const bool                  draw_train_name,
            const message_catalog_type& message_catalog
        )
        :
        base_type(selection),
        m_p_train(&train),
        m_departure_stop_index(departure_stop_index),
        m_departure(std::move(departure)),
        m_arrival(std::move(arrival)),
        m_draw_train_name(draw_train_name),
        m_p_message_catalog(&message_catalog)
        {}

        /*!
            \brief Moves a train line fragment.

            \param another Another train line fragment.
        */
        train_line_fragment(train_line_fragment&& another)
        :
        base_type(another.selection()),
        m_p_train(another.m_p_train),
        m_departure_stop_index(another.m_departure_stop_index),
        m_departure(std::move(another.m_departure)),
        m_arrival(std::move(another.m_arrival)),
        m_draw_train_name(another.m_draw_train_name),
        m_p_message_catalog(another.m_p_message_catalog)
        {}

        /*!
            \brief Destroys the train line fragment.
        */
        virtual ~train_line_fragment()
        TETENGO2_STDALT_NOEXCEPT
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

            m_p_train = another.m_p_train;
            m_departure_stop_index = another.m_departure_stop_index;
            m_departure = std::move(another.m_departure);
            m_arrival = std::move(another.m_arrival);
            m_draw_train_name = another.m_draw_train_name;
            m_p_message_catalog = another.m_p_message_catalog;
            base_type::operator=(std::move(another));

            return *this;
        }


    private:
        // types

        typedef typename train_type::direction_type direction_type;

        typedef typename tetengo2::gui::position<position_type>::left_type left_type;

        typedef typename tetengo2::gui::position<position_type>::top_type top_type;

        typedef typename canvas_type::dimension_type dimension_type;

        typedef typename tetengo2::gui::dimension<dimension_type>::width_type width_type;

        typedef typename tetengo2::gui::dimension<dimension_type>::height_type height_type;

        typedef typename canvas_type::size_type size_type;

        typedef std::pair<double, double> geo_vector_type;


        // static functions

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

        static double calculate_train_name_angle(const position_type& departure, const position_type& arrival)
        {
            const auto height =
                tetengo2::gui::position<position_type>::top(arrival) -
                tetengo2::gui::position<position_type>::top(departure);
            const auto width =
                tetengo2::gui::position<position_type>::left(arrival) -
                tetengo2::gui::position<position_type>::left(departure);

            return
                std::atan2(boost::rational_cast<double>(height.value()), boost::rational_cast<double>(width.value()));
        }

        static position_type calculate_train_name_position(
            const position_type& departure,
            const string_type&   train_name,
            const double         angle,
            const direction_type direction,
            const canvas_type&   canvas
        )
        {
            const auto text_dimension = canvas.calc_text_dimension(train_name);
            const auto& text_height = tetengo2::gui::dimension<dimension_type>::height(text_dimension);

            if (direction == direction_type::down)
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
                    const auto left_diff = boost::rational_cast<double>(text_height.value()) / std::sin(angle);
                    const auto left =
                        tetengo2::gui::position<position_type>::left(departure) +
                        typename left_type::value_type(
                            static_cast<typename left_type::value_type::int_type>(left_diff * 0x10000), 0x10000
                        );

                    return position_type(left, tetengo2::gui::position<position_type>::top(departure));
                }
            }
            else
            {
                const auto left_diff = boost::rational_cast<double>(text_height.value()) * std::sin(angle);
                const auto left =
                    tetengo2::gui::position<position_type>::left(departure) +
                    typename left_type::value_type(
                        static_cast<typename left_type::value_type::int_type>(left_diff * 0x10000), 0x10000
                    );

                const auto top_diff = boost::rational_cast<double>(text_height.value()) * std::cos(angle);
                const auto top =
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
            const auto p = to_geo_vector(point);
            const auto lsb = to_geo_vector(line_segment_begin);
            const auto lse = to_geo_vector(line_segment_end);

            auto d = 0.0;
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

        const train_type* m_p_train;

        stop_index_type m_departure_stop_index;

        position_type m_departure;

        position_type m_arrival;

        bool m_draw_train_name;

        const message_catalog_type* m_p_message_catalog;


        // virtual functions

        virtual void draw_on_impl(canvas_type& canvas)
        const override
        {
            draw_selectable_line(canvas, m_departure, m_arrival, this->selected());
            if (m_draw_train_name)
                draw_train_name(canvas);
        }

        virtual base_type* p_item_by_position_impl(const position_type& position)
        override
        {
            return
                calculate_distance(position, m_departure, m_arrival) <= selected_line_margin<size_type>() ?
                this : nullptr;
        }

        virtual bool selected_impl()
        const override
        {
            return
                this->selection().selected(*m_p_train, boost::none) ||
                this->selection().selected(*m_p_train, boost::make_optional(m_departure_stop_index));
        }

        virtual void select_impl(const bool switch_selection_style)
        override
        {
            const auto whole_selected = this->selection().selected(*m_p_train, boost::none);
            const auto this_fragment_selected =
                this->selection().selected(*m_p_train, boost::make_optional(m_departure_stop_index));
            const auto any_fragment_selected =
                this->selection().selected(
                    *m_p_train, boost::make_optional(std::numeric_limits<stop_index_type>::max())
                );

            auto select_fragment = false;
            if (switch_selection_style)
                select_fragment = whole_selected || (!this_fragment_selected && any_fragment_selected);
            else
                select_fragment = this_fragment_selected;
            this->selection().select(
                *m_p_train, boost::make_optional(select_fragment, m_departure_stop_index)
            );
        }


        // functions

        void draw_train_name(canvas_type& canvas)
        const
        {
            const auto train_name = make_train_name(*m_p_train, *m_p_message_catalog);
            const auto train_name_angle = calculate_train_name_angle(m_departure, m_arrival);
            canvas.draw_text(
                train_name,
                calculate_train_name_position(
                    m_departure, train_name, train_name_angle, m_p_train->direction(), canvas
                ),
                train_name_angle
            );
        }


    };


     /*!
        \brief The class template for a train line in the diagram view.

        \tparam Model          A model type.
        \tparam Selection      A selection type.
        \tparam Canvas         A canvas type.
        \tparam MessageCatalog A message catalog type.
    */
    template <typename Model, typename Selection, typename Canvas, typename MessageCatalog>
    class train_line : public item<Selection, Canvas>
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

        //! The selection type.
        typedef Selection selection_type;

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

        //! The base type.
        typedef item<selection_type, canvas_type> base_type;

        //! The message catalog type.
        typedef MessageCatalog message_catalog_type;


        // constructors and destructor

        /*!
            \brief Creates a train line.

            \param train                A train.
            \param train_kind           A train kind.
            \param time_offset          A time offet.
            \param selection            A selection.
            \param canvas_dimension     A canvas dimension.
            \param scroll_bar_position  A scroll bar position.
            \param station_header_right A station header right position.
            \param header_bottom        A header bottom position.
            \param time_header_height   A time header height.
            \param horizontal_scale     A horizontal scale.
            \param station_intervals    Station intervals.
            \param station_positions    Station positions.
            \param message_catalog      A mesage catalog.
        */
        train_line(
            const train_type&             train,
            const train_kind_type&        train_kind,
            const time_span_type&         time_offset,
            selection_type&               selection,
            const dimension_type&         canvas_dimension,
            const position_type&          scroll_bar_position,
            const left_type&              station_header_right,
            const top_type&               header_bottom,
            const height_type&            time_header_height,
            const horizontal_scale_type&  horizontal_scale,
            const station_intervals_type& station_intervals,
            const std::vector<top_type>&  station_positions,
            const message_catalog_type&   message_catalog
        )
        :
        base_type(selection),
        m_p_train_kind(&train_kind),
        m_fragments(
            make_fragments(
                train,
                time_offset,
                selection,
                canvas_dimension,
                scroll_bar_position,
                station_header_right,
                header_bottom,
                time_header_height,
                horizontal_scale,
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
        base_type(another.selection()),
        m_p_train_kind(another.m_p_train_kind),
        m_fragments(std::move(another.m_fragments))
        {}

        /*!
            \brief Destroys the train line.
        */
        virtual ~train_line()
        TETENGO2_STDALT_NOEXCEPT
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
            base_type::operator=(std::move(another));

            return *this;
        }


    private:
        // types

        typedef
            train_line_fragment<model_type, selection_type, canvas_type, message_catalog_type>
            train_line_fragment_type;

        typedef typename train_type::direction_type direction_type;

        typedef typename canvas_type::size_type size_type;

        typedef typename canvas_type::string_type string_type;

        typedef typename train_type::stops_type::size_type stop_index_type;

        typedef typename train_type::stop_type stop_type;


        // static functions

        static std::vector<train_line_fragment_type> make_fragments(
            const train_type&             train,
            const time_span_type&         time_offset,
            selection_type&               selection,
            const dimension_type&         canvas_dimension,
            const position_type&          scroll_bar_position,
            const left_type&              station_header_right,
            const top_type&               header_bottom,
            const height_type&            time_header_height,
            const horizontal_scale_type&  horizontal_scale,
            const station_intervals_type& station_intervals,
            const std::vector<top_type>&  station_positions,
            const message_catalog_type&   message_catalog
        )
        {
            std::vector<train_line_fragment_type> fragments;

            auto train_name_drawn = false;
            if (train.direction() == direction_type::down)
            {
                for (stop_index_type i = 0; i + 1 < train.stops().size(); )
                {
                    const auto from = i;

                    if (!has_time(train.stops()[from]))
                    {
                        ++i;
                        continue;
                    }

                    auto j = i + 1;
                    for (; j < train.stops().size(); ++j)
                    {
                        const auto to = j;

                        if (has_time(train.stops()[to]))
                        {
                            const auto& departure_time = get_departure_time(train.stops()[from]);
                            const auto arrival_time =
                                estimate_arrival_time(station_intervals, departure_time, train.stops()[to], from, to);

                            make_fragment(
                                train,
                                from,
                                departure_time,
                                to,
                                arrival_time,
                                !train_name_drawn,
                                time_offset,
                                selection,
                                canvas_dimension,
                                scroll_bar_position,
                                station_header_right,
                                header_bottom,
                                time_header_height,
                                horizontal_scale,
                                station_positions,
                                message_catalog,
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
                    const auto from = i - 1;

                    if (!has_time(train.stops()[from]))
                    {
                        --i;
                        continue;
                    }

                    auto j = i - 1;
                    for (; j > 0; --j)
                    {
                        const auto to = j - 1;

                        if (has_time(train.stops()[to]))
                        {
                            const auto& departure_time = get_departure_time(train.stops()[from]);
                            const auto arrival_time =
                                estimate_arrival_time(station_intervals, departure_time, train.stops()[to], to, from);

                            make_fragment(
                                train,
                                from,
                                departure_time,
                                to,
                                arrival_time,
                                !train_name_drawn ,
                                time_offset,
                                selection,
                                canvas_dimension,
                                scroll_bar_position,
                                station_header_right,
                                header_bottom,
                                time_header_height,
                                horizontal_scale,
                                station_positions,
                                message_catalog,
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
            return stop.arrival().initialized() || stop.departure().initialized();
        }

        static const time_type& get_departure_time(const stop_type& stop)
        {
            assert(has_time(stop));
            if (stop.departure().initialized())
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
            if (to_stop.arrival().initialized())
                return to_stop.arrival();

            const auto departure_interval = to_stop.departure() - from_departure;
            const auto travel_time =
                std::accumulate(
                    station_intervals.begin() + upper_stop_index,
                    station_intervals.begin() + lower_stop_index,
                    time_span_type(0)
                );

            return departure_interval < travel_time ? to_stop.departure() : from_departure + travel_time;
        }

        static void make_fragment(
            const train_type&                      train,
            const stop_index_type                  departure_stop_index,
            const time_type&                       departure_time,
            const stop_index_type                  arrival_stop_index,
            const time_type&                       arrival_time,
            const bool                             draw_train_name,
            const time_span_type&                  time_offset,
            selection_type&                        selection,
            const dimension_type&                  canvas_dimension,
            const position_type&                   scroll_bar_position,
            const left_type&                       station_header_right,
            const top_type&                        header_bottom,
            const height_type&                     time_header_height,
            const horizontal_scale_type&           horizontal_scale,
            const std::vector<top_type>&           station_positions,
            const message_catalog_type&            message_catalog,
            std::vector<train_line_fragment_type>& fragments
        )
        {
            if (departure_time - time_offset <= arrival_time - time_offset)
            {
                make_fragment_impl(
                    train,
                    departure_stop_index,
                    departure_time,
                    false,
                    arrival_stop_index,
                    arrival_time,
                    false,
                    draw_train_name,
                    time_offset,
                    selection,
                    canvas_dimension,
                    scroll_bar_position,
                    station_header_right,
                    header_bottom,
                    time_header_height,
                    horizontal_scale,
                    station_positions,
                    message_catalog,
                    fragments
                );
            }
            else
            {
                make_fragment_impl(
                    train,
                    departure_stop_index,
                    departure_time,
                    true,
                    arrival_stop_index,
                    arrival_time,
                    false,
                    draw_train_name,
                    time_offset,
                    selection,
                    canvas_dimension,
                    scroll_bar_position,
                    station_header_right,
                    header_bottom,
                    time_header_height,
                    horizontal_scale,
                    station_positions,
                    message_catalog,
                    fragments
                );
                make_fragment_impl(
                    train,
                    departure_stop_index,
                    departure_time,
                    false,
                    arrival_stop_index,
                    arrival_time,
                    true,
                    draw_train_name,
                    time_offset,
                    selection,
                    canvas_dimension,
                    scroll_bar_position,
                    station_header_right,
                    header_bottom,
                    time_header_height,
                    horizontal_scale,
                    station_positions,
                    message_catalog,
                    fragments
                );
            }
        }

        static void make_fragment_impl(
            const train_type&                      train,
            const stop_index_type                  departure_stop_index,
            const time_type&                       departure_time,
            const bool                             previous_day_departure,
            const stop_index_type                  arrival_stop_index,
            const time_type&                       arrival_time,
            const bool                             next_day_arrival,
            const bool                             draw_train_name,
            const time_span_type&                  time_offset,
            selection_type&                        selection,
            const dimension_type&                  canvas_dimension,
            const position_type&                   scroll_bar_position,
            const left_type&                       station_header_right,
            const top_type&                        header_bottom,
            const height_type&                     time_header_height,
            const horizontal_scale_type&           horizontal_scale,
            const std::vector<top_type>&           station_positions,
            const message_catalog_type&            message_catalog,
            std::vector<train_line_fragment_type>& fragments
        )
        {
            const auto horizontal_scroll_bar_position =
                tetengo2::gui::position<position_type>::left(scroll_bar_position);
            const auto vertical_scroll_bar_position =
                tetengo2::gui::position<position_type>::top(scroll_bar_position);

            const auto horizontal_scale_left = left_type::from(width_type(horizontal_scale));
            const auto time_header_bottom = top_type::from(time_header_height);
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
                    departure_stop_index,
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
                    arrival_stop_index,
                    vertical_scroll_bar_position,
                    header_bottom,
                    time_header_bottom
                )
            );
            
            const auto left_bound = tetengo2::gui::position<position_type>::left(departure);
            if (left_bound > left_type::from(tetengo2::gui::dimension<dimension_type>::width(canvas_dimension)))
                return;
            const auto right_bound = tetengo2::gui::position<position_type>::left(arrival);
            if (right_bound < station_header_right)
                return;
            const auto upper_bound =
                departure_stop_index < arrival_stop_index ? 
                tetengo2::gui::position<position_type>::top(departure) :
                tetengo2::gui::position<position_type>::top(arrival);
            if (upper_bound > top_type::from(tetengo2::gui::dimension<dimension_type>::height(canvas_dimension)))
                return;
            const auto lower_bound =
                departure_stop_index < arrival_stop_index ? 
                tetengo2::gui::position<position_type>::top(arrival) :
                tetengo2::gui::position<position_type>::top(departure);
            if (lower_bound < header_bottom + time_header_bottom)
                return;

            fragments.push_back(
                train_line_fragment_type(
                    train,
                    departure_stop_index,
                    selection,
                    std::move(departure),
                    std::move(arrival),
                    draw_train_name,
                    message_catalog
                )
            );
        }

        static typename canvas_type::line_style_type translate_line_style(
            const typename train_kind_type::line_style_type line_style
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
        const override
        {
            canvas.set_color(m_p_train_kind->color());
            canvas.set_line_width(
                m_p_train_kind->weight() == train_kind_type::weight_type::bold ?
                bold_line_width<size_type>() : normal_line_width<size_type>()
            );
            canvas.set_line_style(translate_line_style(m_p_train_kind->line_style()));

            for (const auto& fragment: m_fragments)
                fragment.draw_on(canvas);
        }

        virtual base_type* p_item_by_position_impl(const position_type& position)
        override
        {
            for (auto& fragment: boost::adaptors::reverse(m_fragments))
            {
                auto* const p_item = fragment.p_item_by_position(position);
                if (p_item)
                    return p_item;
            }

            return nullptr;
        }


    };


     /*!
        \brief The class template for a train line list in the diagram view.

        \tparam Model          A model type.
        \tparam Selection      A selection type.
        \tparam Canvas         A canvas type.
        \tparam MessageCatalog A message catalog type.
    */
    template <typename Model, typename Selection, typename Canvas, typename MessageCatalog>
    class train_line_list : public item<Selection, Canvas>
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

        //! The selection type.
        typedef Selection selection_type;

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

        //! The base type.
        typedef item<selection_type, canvas_type> base_type;

        //! The message catalog type.
        typedef MessageCatalog message_catalog_type;


        // constructors and destructor

        /*!
            \brief Creates a train line list.

            \param model                A model.
            \param time_offset          A time offset.
            \param selection            A selection.
            \param canvas_dimension     A canvas dimension.
            \param scroll_bar_position  A scroll bar position.
            \param station_header_right A right position of the station header.
            \param header_bottom        A bottom position of the header.
            \param time_header_height   A time header height.
            \param horizontal_scale     A horizontal scale.
            \param station_intervals    Station intervals.
            \param station_positions    Station positions.
            \param message_catalog      A message catalog.
        */
        train_line_list(
            const model_type&             model,
            const time_span_type&         time_offset,
            selection_type&               selection,
            const dimension_type&         canvas_dimension,
            const position_type&          scroll_bar_position,
            const left_type&              station_header_right,
            const top_type&               header_bottom,
            const height_type&            time_header_height,
            const horizontal_scale_type&  horizontal_scale,
            const station_intervals_type& station_intervals,
            const std::vector<top_type>&  station_positions,
            const message_catalog_type&   message_catalog
        )
        :
        base_type(selection),
        m_p_font(&model.timetable().font_color_set().train_name()),
        m_train_lines(
            make_train_lines(
                model,
                time_offset,
                selection,
                canvas_dimension,
                scroll_bar_position,
                station_header_right,
                header_bottom,
                time_header_height,
                horizontal_scale,
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
        base_type(another.selection()),
        m_p_font(another.m_p_font),
        m_train_lines(std::move(another.m_train_lines))
        {}

        /*!
            \brief Destroys the train line list.
        */
        virtual ~train_line_list()
        TETENGO2_STDALT_NOEXCEPT
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
            base_type::operator=(std::move(another));

            return *this;
        }


    private:
        // types

        typedef train_line<model_type, selection_type, canvas_type, message_catalog_type> train_line_type;

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
            selection_type&               selection,
            const dimension_type&         canvas_dimension,
            const position_type&          scroll_bar_position,
            const left_type&              station_header_right,
            const top_type&               header_bottom,
            const height_type&            time_header_height,
            const horizontal_scale_type&  horizontal_scale,
            const station_intervals_type& station_intervals,
            const std::vector<top_type>&  station_positions,
            const message_catalog_type&   message_catalog
        )
        {
            std::vector<train_line_type> train_lines;

            make_train_lines_impl(
                model.timetable().down_trains(),
                model.timetable().train_kinds(),
                time_offset,
                selection,
                canvas_dimension,
                scroll_bar_position,
                station_header_right,
                header_bottom,
                time_header_height,
                horizontal_scale,
                station_intervals,
                station_positions,
                message_catalog,
                train_lines
            );
            make_train_lines_impl(
                model.timetable().up_trains(),
                model.timetable().train_kinds(),
                time_offset,
                selection,
                canvas_dimension,
                scroll_bar_position,
                station_header_right,
                header_bottom,
                time_header_height,
                horizontal_scale,
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
            const time_span_type&         time_offset,
            selection_type&               selection,
            const dimension_type&         canvas_dimension,
            const position_type&          scroll_bar_position,
            const left_type&              station_header_right,
            const top_type&               header_bottom,
            const height_type&            time_header_height,
            const horizontal_scale_type&  horizontal_scale,
            const station_intervals_type& station_intervals,
            const std::vector<top_type>&  station_positions,
            const message_catalog_type&   message_catalog,
            std::vector<train_line_type>& train_lines
        )
        {
            for (const auto& train: trains)
            {
                train_lines.push_back(
                    train_line_type(
                        train,
                        train_kinds[train.kind_index()],
                        time_offset,
                        selection,
                        canvas_dimension,
                        scroll_bar_position,
                        station_header_right,
                        header_bottom,
                        time_header_height,
                        horizontal_scale,
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
        const override
        {
            canvas.set_font(*m_p_font);

            for (const auto& train_line: m_train_lines)
                train_line.draw_on(canvas);
        }

        virtual base_type* p_item_by_position_impl(const position_type& position)
        override
        {
            for (auto& train_line: boost::adaptors::reverse(m_train_lines))
            {
                auto* const p_item = train_line.p_item_by_position(position);
                if (p_item)
                    return p_item;
            }

            return nullptr;
        }


    };


}}}


#endif
