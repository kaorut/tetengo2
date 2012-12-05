/*! \file
    \brief The definition of bobura::view::diagram::train_line.

    Copyright (C) 2007-2012 kaoru

    $Id$
*/

#if !defined(BOBURA_VIEW_DIAGRAM_TRAINLINE_H)
#define BOBURA_VIEW_DIAGRAM_TRAINLINE_H

//#include <utility>
#include <vector>

#include <boost/foreach.hpp>

#include <tetengo2.cpp11.h>
#include <tetengo2.gui.measure.h>

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

        //! The position type.
        typedef typename canvas_type::position_type position_type;

        //! The left type.
        typedef typename tetengo2::gui::position<position_type>::left_type left_type;

        //! The top type.
        typedef typename tetengo2::gui::position<position_type>::top_type top_type;


        // constructors and destructor

        /*!
            \brief Creates a train line fragment.

            \param right A right position.
            \param top   A top position.
        */
        train_line_fragment(const left_type& right, top_type&& top)
        :
        m_right(right),
        m_top(std::forward<top_type>(top))
        {}

        /*!
            \brief Moves a train line fragment.

            \param another Another train line fragment.
        */
        train_line_fragment(train_line_fragment&& another)
        :
        m_right(std::move(another.m_right)),
        m_top(std::move(another.m_top))
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

            m_right = std::move(another.m_right);
            m_top = std::move(another.m_top);

            return *this;
        }


    private:
        // variables

        left_type m_right;

        top_type m_top;


        // virtual functions

        virtual void draw_on_impl(canvas_type& canvas)
        const
        {

        }


    };


     /*!
        \brief The class template for a train line in the diagram view.

        \tparam Model  A model type.
        \tparam Canvas A canvas type.
    */
    template <typename Model, typename Canvas>
    class train_line : public item<Canvas>
    {
    public:
        // types

        //! The model type.
        typedef Model model_type;

        //! The train type.
        typedef typename model_type::timetable_type::train_type train_type;

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


        // constructors and destructor

        /*!
            \brief Creates a train line.

            \param train      A train.
            \param train_kind A train kind.
            \param down       Set true for a down train.
        */
        train_line(
            const train_type&             train,
            const train_kind_type&        train_kind,
            const bool                    down,
            const station_intervals_type& station_intervals
        )
        :
        m_p_train_kind(&train_kind),
        m_fragments(make_fragments(train, down, station_intervals))
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

        typedef typename train_type::stops_type::size_type stop_index_type;

        typedef typename train_type::stop_type stop_type;

        typedef typename train_type::stop_type::time_type time_type;

        typedef typename time_type::time_span_type time_span_type;


        // static functions

        static std::vector<train_line_fragment_type> make_fragments(
            const train_type&             train,
            const bool                    down,
            const station_intervals_type& station_intervals
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

                            //draw_train_line(
                            //    from,
                            //    departure_time,
                            //    to,
                            //    arrival_time,
                            //    !train_name_drawn ? make_train_name(train) : string_type(),
                            //    down,
                            //    canvas,
                            //    canvas_dimension,
                            //    scroll_bar_position
                            //);

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

                            //draw_train_line(
                            //    from,
                            //    departure_time,
                            //    to,
                            //    arrival_time,
                            //    !train_name_drawn ? make_train_name(train) : string_type(),
                            //    down,
                            //    canvas,
                            //    canvas_dimension,
                            //    scroll_bar_position
                            //);

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


    };


     /*!
        \brief The class template for a train line list in the diagram view.

        \tparam Model  A model type.
        \tparam Canvas A canvas type.
    */
    template <typename Model, typename Canvas>
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
            const station_intervals_type& station_intervals
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
                station_intervals
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

        typedef train_line<model_type, canvas_type> train_line_type;

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
            const station_intervals_type& station_intervals
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
            std::vector<train_line_type>& train_lines
        )
        {
            BOOST_FOREACH (const train_type& train, trains)
            {
                train_lines.emplace_back(train, train_kinds[train.kind_index()], down, station_intervals);
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


    };


}}}


#endif
