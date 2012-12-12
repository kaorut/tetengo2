/*! \file
    \brief The definition of bobura::view::diagram::station_line.

    Copyright (C) 2007-2012 kaoru

    $Id$
*/

#if !defined(BOBURA_VIEW_DIAGRAM_STATIONLINE_H)
#define BOBURA_VIEW_DIAGRAM_STATIONLINE_H

#include <algorithm>
#include <cassert>
#include <stdexcept>
//#include <utility>
#include <vector>

#include <boost/foreach.hpp>
#include <boost/throw_exception.hpp>

#include <tetengo2.cpp11.h>
#include <tetengo2.gui.measure.h>

#include "bobura.view.diagram.item.h"
#include "bobura.view.diagram.utility.h"


namespace bobura { namespace view { namespace diagram
{
     /*!
        \brief The class template for a station line in the diagram view.

        \tparam Canvas A canvas type.
    */
    template <typename Canvas>
    class station_line : public item<Canvas>
    {
    public:
        // types

        //! The canvas type.
        typedef Canvas canvas_type;

        //! The string type.
        typedef typename canvas_type::string_type string_type;

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


        // constructors and destructor

        /*!
            \brief Creates a station line.

            \param right          A right position.
            \param top            A top position.
            \param name           A name.
            \param name_dimension A name dimension.
            \param font           A font.
            \param color          A color.
        */
        station_line(
            const left_type&   right,
            top_type&&         top,
            const string_type& name,
            dimension_type&&   name_dimension,
            const font_type&   font,
            const color_type&  color
        )
        :
        m_right(right),
        m_top(std::forward<top_type>(top)),
        m_p_name(&name),
        m_name_dimension(std::forward<dimension_type>(name_dimension)),
        m_p_font(&font),
        m_p_color(&color)
        {}

        /*!
            \brief Moves a station line.

            \param another Another station line.
        */
        station_line(station_line&& another)
        :
        m_right(std::move(another.m_right)),
        m_top(std::move(another.m_top)),
        m_p_name(another.m_p_name),
        m_name_dimension(std::move(another.m_name_dimension)),
        m_p_font(another.m_p_font),
        m_p_color(another.m_p_color)
        {}

        /*!
            \brief Destroys the station line.
        */
        virtual ~station_line()
        TETENGO2_CPP11_NOEXCEPT
        {}


        // functions

        /*!
            \brief Assigns a station line.

            \param another Another station line.

            \return This station line.
        */
        station_line& operator=(station_line&& another)
        {
            if (&another == this)
                return *this;

            m_right = std::move(another.m_right);
            m_top = std::move(another.m_top);
            m_p_name = another.m_p_name;
            m_name_dimension = std::move(another.m_name_dimension);
            m_p_font = another.m_p_font;
            m_p_color = another.m_p_color;

            return *this;
        }


    private:
        // variables

        left_type m_right;

        top_type m_top;

        const string_type* m_p_name;

        dimension_type m_name_dimension;

        const font_type* m_p_font;

        const color_type* m_p_color;


        // virtual functions

        virtual void draw_on_impl(canvas_type& canvas)
        const
        {
            canvas.set_font(*m_p_font);
            canvas.set_color(*m_p_color);

            canvas.draw_line(position_type(left_type(0), m_top), position_type(m_right, m_top));

            canvas.draw_text(
                *m_p_name,
                position_type(
                    left_type(0),
                    m_top - top_type::from(tetengo2::gui::dimension<dimension_type>::height(m_name_dimension))
                )
            );
        }


    };


     /*!
        \brief The class template for a station line list in the diagram view.

        \tparam Model               A model type.
        \tparam Canvas              A canvas type.
        \tparam StationGradeTypeSet A station grade type set type.
    */
    template <typename Model, typename Canvas, typename StationGradeTypeSet>
    class station_line_list : public item<Canvas>
    {
    public:
        // types

        //! The model type.
        typedef Model model_type;
        
        //! The time type.
        typedef typename model_type::timetable_type::train_type::stop_type::time_type time_type;

        //! The time span type.
        typedef typename time_type::time_span_type time_span_type;

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

        //! The station grade type set type.
        typedef StationGradeTypeSet station_grade_type_set_type;


        // constructors and destructor

        /*!
            \brief Creates a station line list.

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
            \param station_positions    Station positions.
        */
        station_line_list(
            const model_type&            model,
            const time_span_type&        time_offset,
            canvas_type&                 canvas,
            const dimension_type&        canvas_dimension,
            const dimension_type&        timetable_dimension,
            const position_type&         scroll_bar_position,
            const left_type&             station_header_right,
            const top_type&              header_bottom,
            const height_type&           time_header_height,
            const horizontal_scale_type& horizontal_scale,
            const vertical_scale_type&   vertical_scale,
            const std::vector<top_type>& station_positions
        )
        :
        m_station_lines(
            make_station_lines(
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
                station_positions
            )
        )
        {}

        /*!
            \brief Moves a station line list.

            \param another Another station line list.
        */
        station_line_list(station_line_list&& another)
        :
        m_station_lines(std::move(another.m_station_lines))
        {}

        /*!
            \brief Destroys the station line list.
        */
        virtual ~station_line_list()
        TETENGO2_CPP11_NOEXCEPT
        {}


        // functions

        /*!
            \brief Assigns a station line list.

            \param another Another station line list.

            \return This station line list.
        */
        station_line_list& operator=(station_line_list&& another)
        {
            if (&another == this)
                return *this;

            m_station_lines = std::move(another.m_station_lines);

            return *this;
        }


    private:
        // types

        typedef station_line<canvas_type> station_line_type;

        typedef typename model_type::timetable_type timetable_type;

        typedef typename timetable_type::font_color_set_type font_color_set_type;

        typedef typename font_color_set_type::font_color_type font_color_type;

        typedef typename timetable_type::station_location_type station_location_type;

        typedef typename station_location_type::station_type station_type;

        typedef typename station_type::grade_type station_grade_type;

        typedef typename canvas_type::size_type size_type;

        typedef typename canvas_type::string_type string_type;


        // static functions

        std::vector<station_line_type> make_station_lines(
            const model_type&            model,
            const time_span_type&        time_offset,
            canvas_type&                 canvas,
            const dimension_type&        canvas_dimension,
            const dimension_type&        timetable_dimension,
            const position_type&         scroll_bar_position,
            const left_type&             station_header_right,
            const top_type&              header_bottom,
            const height_type&           time_header_height,
            const horizontal_scale_type& horizontal_scale,
            const vertical_scale_type&   vertical_scale,
            const std::vector<top_type>& station_positions
        )
        {
            const left_type canvas_right =
                left_type::from(tetengo2::gui::dimension<dimension_type>::width(canvas_dimension));
            const left_type horizontal_scale_left = left_type::from(width_type(horizontal_scale));
            const left_type last_time_position =
                time_to_left(
                    time_type(24 * 60 * 60 + time_offset.seconds()),
                    time_offset,
                    1,
                    tetengo2::gui::position<position_type>::left(scroll_bar_position),
                    station_header_right,
                    horizontal_scale_left
                );
            const left_type line_right = std::min(canvas_right, last_time_position);

            const top_type canvas_top = header_bottom + top_type::from(time_header_height);
            const top_type canvas_bottom =
                top_type::from(tetengo2::gui::dimension<dimension_type>::height(canvas_dimension));

            std::vector<station_line_type> station_lines;
            station_lines.reserve(station_positions.size());
            for (typename std::vector<top_type>::size_type i = 0; i < station_positions.size(); ++i)
            {
                const top_type& position = station_positions[i];
                top_type line_position =
                    position + canvas_top - tetengo2::gui::position<position_type>::top(scroll_bar_position);
                if (line_position < canvas_top)
                    continue;
                if (line_position > canvas_bottom)
                    break;

                const font_color_type& font_color =
                    select_station_font_color(model, model.timetable().station_locations()[i].station().grade());
                const string_type& station_name = model.timetable().station_locations()[i].station().name();
                canvas.set_font(font_color.font());
                dimension_type station_name_dimension = canvas.calc_text_dimension(station_name);

                station_lines.push_back(
                    station_line_type(
                        line_right,
                        std::move(line_position),
                        station_name,
                        std::move(station_name_dimension),
                        font_color.font(),
                        font_color.color()
                    )
                );
            }
            tetengo2::cpp11::shrink_to_fit(station_lines);

            return std::move(station_lines);
        }

        static const font_color_type& select_station_font_color(
            const model_type&         model,
            const station_grade_type& grade
        )
        {
            if      (&grade == &station_grade_type_set_type::local_type::instance())
                return model.timetable().font_color_set().local_station();
            else if (&grade == &station_grade_type_set_type::principal_type::instance())
                return model.timetable().font_color_set().principal_station();
            else if (&grade == &station_grade_type_set_type::local_terminal_type::instance())
                return model.timetable().font_color_set().local_terminal_station();
            else if (&grade == &station_grade_type_set_type::principal_terminal_type::instance())
                return model.timetable().font_color_set().principal_terminal_station();

            assert(false);
            BOOST_THROW_EXCEPTION(std::invalid_argument("Unknown station grade."));
        }


        // variables

        std::vector<station_line_type> m_station_lines;


        // virtual functions

        virtual void draw_on_impl(canvas_type& canvas)
        const
        {
            canvas.set_line_width(size_type(typename size_type::value_type(1, 12)));
            canvas.set_line_style(canvas_type::line_style_type::solid);

            BOOST_FOREACH (const station_line_type& station_line, m_station_lines)
            {
                station_line.draw_on(canvas);
            }
        }


    };


}}}


#endif
