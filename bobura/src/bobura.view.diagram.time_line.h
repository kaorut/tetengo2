/*! \file
    \brief The definition of bobura::view::diagram::time_line.

    Copyright (C) 2007-2013 kaoru

    $Id$
*/

#if !defined(BOBURA_VIEW_DIAGRAM_TIMELINE_H)
#define BOBURA_VIEW_DIAGRAM_TIMELINE_H

#include <algorithm>
#include <cassert>
//#include <cstddef>
//#include <utility>
#include <vector>

#include <boost/foreach.hpp>
#include <boost/lexical_cast.hpp>
#include <boost/optional.hpp>

#include <tetengo2.cpp11.h>
#include <tetengo2.gui.measure.h>
#include <tetengo2.text.h>

#include "bobura.view.diagram.item.h"
#include "bobura.view.diagram.utility.h"


namespace bobura { namespace view { namespace diagram
{
     /*!
        \brief The class template for a time line in the diagram view.

        \tparam Selection A selection type.
        \tparam Canvas    A canvas type.
        \tparam TimeTick  A time tick type.
    */
    template <typename Selection, typename Canvas, typename TimeTick>
    class time_line : public item<Selection, Canvas>
    {
    public:
        // types

        //! The selection type.
        typedef Selection selection_type;

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

        //! The base type.
        typedef item<selection_type, canvas_type> base_type;

        //! The time tick type.
        typedef TimeTick time_tick_type;


        // constructors and destructor

        /*!
            \brief Creates a time line.

            \param selection A selection.
            \param left      A left position.
            \param top       A top position.
            \param bottom    A bottom position.
            \param width     A width.
            \param hours     Hours.
        */
        time_line(
            selection_type&                 selection,
            left_type                       left,
            const top_type&                 top,
            const top_type&                 bottom,
            size_type                       width,
            boost::optional<time_tick_type> hours
        )
        :
        base_type(selection),
        m_left(std::move(left)),
        m_top(top),
        m_bottom(bottom),
        m_width(std::move(width)),
        m_hours(std::move(hours))
        {}

        /*!
            \brief Moves a time line.

            \param another Another time line.
        */
        time_line(time_line&& another)
        :
        base_type(another.selection()),
        m_left(std::move(another.m_left)),
        m_top(std::move(another.m_top)),
        m_bottom(std::move(another.m_bottom)),
        m_width(std::move(another.m_width)),
        m_hours(another.m_hours)
        {}

        /*!
            \brief Destroys the time line.
        */
        virtual ~time_line()
        TETENGO2_CPP11_NOEXCEPT
        {}


        // functions

        /*!
            \brief Assigns a time line.

            \param another Another time line.

            \return This time line.
        */
        time_line& operator=(time_line&& another)
        {
            if (&another == this)
                return *this;

            m_left = std::move(another.m_left);
            m_top = std::move(another.m_top);
            m_bottom = std::move(another.m_bottom);
            m_width = std::move(another.m_width);
            m_hours = another.m_hours;

            return *this;
        }


    private:
        // types

        typedef typename canvas_type::string_type string_type;


        // variables

        left_type m_left;

        top_type m_top;

        top_type m_bottom;

        size_type m_width;

        boost::optional<time_tick_type> m_hours;


        // virtual functions

        virtual void draw_on_impl(canvas_type& canvas)
        const
        {
            if (m_hours)
                canvas.draw_text(boost::lexical_cast<string_type>(*m_hours), position_type(m_left, m_top));

            canvas.set_line_style(canvas_type::line_style_type::solid);
            canvas.set_line_width(m_width);
            canvas.draw_line(position_type(m_left, m_top), position_type(m_left, m_bottom));
        }

        virtual base_type* p_item_by_position_impl(const position_type& position)
        {
            return NULL;
        }

        virtual bool selected_impl()
        const
        {
            return false;
        }

        virtual void select_impl()
        {}


    };


     /*!
        \brief The class template for a time line list in the diagram view.

        \tparam Model     A model type.
        \tparam Selection A selection type.
        \tparam Canvas    A canvas type.
    */
    template <typename Model, typename Selection, typename Canvas>
    class time_line_list : public item<Selection, Canvas>
    {
    public:
        // types

        //! The model type.
        typedef Model model_type;
        
        //! The time type.
        typedef typename model_type::timetable_type::train_type::stop_type::time_type time_type;

        //! The time span type.
        typedef typename time_type::time_span_type time_span_type;

        //! The selection type.
        typedef Selection selection_type;

        //! The canvas type.
        typedef Canvas canvas_type;

        //! The font type.
        typedef typename canvas_type::font_type font_type;

        //! The color type.
        typedef typename canvas_type::color_type color_type;

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
        typedef item<selection_type, canvas_type> base_type;


        // constructors and destructor

        /*!
            \brief Creates a time line list.

            \param model                A model.
            \param time_offset          A time offset.
            \param selection            A selection.
            \param canvas               A canvas.
            \param canvas_dimension     A canvas dimension.
            \param timetable_dimension  A timetable dimension.
            \param scroll_bar_position  A scroll bar position.
            \param station_header_right A right position of the station header.
            \param header_bottom        A bottom position of the header.
            \param time_header_height   A time header height.
            \param horizontal_scale     A horizontal scale.
            \param vertical_scale       A vertical scale.
        */
        time_line_list(
            const model_type&            model,
            const time_span_type&        time_offset,
            selection_type&              selection,
            canvas_type&                 canvas,
            const dimension_type&        canvas_dimension,
            const dimension_type&        timetable_dimension,
            const position_type&         scroll_bar_position,
            const left_type&             station_header_right,
            const top_type&              header_bottom,
            const height_type&           time_header_height,
            const horizontal_scale_type& horizontal_scale,
            const vertical_scale_type&   vertical_scale
        )
        :
        base_type(selection),
        m_p_font(&model.timetable().font_color_set().time_line().font()),
        m_p_color(&model.timetable().font_color_set().time_line().color()),
        m_time_lines(
            make_time_lines(
                model,
                time_offset,
                selection,
                canvas,
                canvas_dimension,
                timetable_dimension,
                scroll_bar_position,
                station_header_right,
                header_bottom,
                time_header_height,
                horizontal_scale,
                vertical_scale
            )
        )
        {}

        /*!
            \brief Moves a time line list.

            \param another Another time line list.
        */
        time_line_list(time_line_list&& another)
        :
        base_type(another.selection()),
        m_p_font(another.m_p_font),
        m_p_color(another.m_p_color),
        m_time_lines(std::move(another.m_time_lines))
        {}

        /*!
            \brief Destroys the time line list.
        */
        virtual ~time_line_list()
        TETENGO2_CPP11_NOEXCEPT
        {}


        // functions

        /*!
            \brief Assigns a time line list.

            \param another Another time line list.

            \return This time line list.
        */
        time_line_list& operator=(time_line_list&& another)
        {
            if (&another == this)
                return *this;

            m_p_font = another.m_p_font;
            m_p_color = another.m_p_color;
            m_time_lines = std::move(another.m_time_lines);

            return *this;
        }


    private:
        // types

        typedef typename time_type::tick_type time_tick_type;

        typedef time_line<selection_type, canvas_type, time_tick_type> time_line_type;

        typedef typename canvas_type::size_type size_type;


        // static functions

        std::vector<time_line_type> make_time_lines(
            const model_type&            model,
            const time_span_type&        time_offset,
            selection_type&              selection,
            canvas_type&                 canvas,
            const dimension_type&        canvas_dimension,
            const dimension_type&        timetable_dimension,
            const position_type&         scroll_bar_position,
            const left_type&             station_header_right,
            const top_type&              header_bottom,
            const height_type&           time_header_height,
            const horizontal_scale_type& horizontal_scale,
            const vertical_scale_type&   vertical_scale
        )
        {
            const left_type canvas_left = station_header_right;
            const left_type canvas_right =
                left_type::from(tetengo2::gui::dimension<dimension_type>::width(canvas_dimension));

            const top_type canvas_top = header_bottom + top_type::from(time_header_height);
            const top_type canvas_bottom =
                top_type::from(tetengo2::gui::dimension<dimension_type>::height(canvas_dimension));
            const top_type station_position_bottom =
                top_type::from(tetengo2::gui::dimension<dimension_type>::height(timetable_dimension)) +
                canvas_top -
                tetengo2::gui::position<position_type>::top(scroll_bar_position);
            const top_type line_bottom = std::min(canvas_bottom, station_position_bottom);

            const left_type horizontal_scale_left = left_type::from(width_type(horizontal_scale));
            const left_type minute_interval =
                time_to_left(
                    time_type(60), time_offset, 0, left_type(0), station_header_right, horizontal_scale_left
                ) -
                time_to_left(time_type(0), time_offset, 0, left_type(0), station_header_right, horizontal_scale_left);

            typedef typename time_type::hours_minutes_seconds_type hours_minutes_seconds_type;
            std::vector<time_line_type> time_lines;
            time_lines.reserve(24 * 60);
            for (time_tick_type i = 0; i <= 24 * 60; ++i)
            {
                const time_type time(i * 60 + time_offset.seconds());
                const hours_minutes_seconds_type hours_minutes_seconds = time.hours_minutes_seconds();
                const time_tick_type hours = hours_minutes_seconds.hours();
                const time_tick_type minutes = hours_minutes_seconds.minutes();
                assert(hours_minutes_seconds.seconds() == 0);

                left_type position =
                    time_to_left(
                        time,
                        time_offset,
                        i == 24 * 60,
                        tetengo2::gui::position<position_type>::left(scroll_bar_position),
                        station_header_right,
                        horizontal_scale_left
                    );
                if (position < canvas_left)
                    continue;
                if (position > canvas_right)
                    break;

                if (minutes == 0)
                {
                    time_lines.push_back(
                        time_line_type(
                            selection,
                            std::move(position),
                            header_bottom,
                            line_bottom,
                            size_type(typename size_type::value_type(1, 12)),
                            boost::make_optional(hours)
                        )
                    );
                }
                else if (minutes % 10 == 0)
                {
                    if (minute_interval >= typename left_type::value_type(4, 12 * 10))
                    {
                        time_lines.push_back(
                            time_line_type(
                                selection,
                                std::move(position),
                                canvas_top,
                                line_bottom,
                                size_type(typename size_type::value_type(1, 24)),
                                boost::none
                            )
                        );
                    }
                }
                else if (minutes % 2 == 0)
                {
                    if (minute_interval >= typename left_type::value_type(4, 12 * 2))
                    {
                        time_lines.push_back(
                            time_line_type(
                                selection,
                                std::move(position),
                                canvas_top,
                                line_bottom,
                                size_type(typename size_type::value_type(1, 48)),
                                boost::none
                            )
                        );
                    }
                }
                else
                {
                    if (minute_interval >= typename left_type::value_type(4, 12))
                    {
                        time_lines.push_back(
                            time_line_type(
                                selection,
                                std::move(position),
                                canvas_top,
                                line_bottom,
                                size_type(typename size_type::value_type(1, 48)),
                                boost::none
                            )
                        );
                    }
                }
            }
            tetengo2::cpp11::shrink_to_fit(time_lines);

            return std::move(time_lines);
        }


        // variables

        const font_type* m_p_font;

        const color_type* m_p_color;

        std::vector<time_line_type> m_time_lines;


        // virtual functions

        virtual void draw_on_impl(canvas_type& canvas)
        const
        {
            canvas.set_font(*m_p_font);
            canvas.set_color(*m_p_color);

            BOOST_FOREACH (const time_line_type& time_line, m_time_lines)
            {
                time_line.draw_on(canvas);
            }
        }

        virtual base_type* p_item_by_position_impl(const position_type& position)
        {
            return NULL;
        }

        virtual bool selected_impl()
        const
        {
            return false;
        }

        virtual void select_impl()
        {}


    };


}}}


#endif
