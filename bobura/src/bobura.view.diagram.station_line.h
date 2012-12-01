/*! \file
    \brief The definition of bobura::view::diagram::station_line.

    Copyright (C) 2007-2012 kaoru

    $Id$
*/

#if !defined(BOBURA_VIEW_DIAGRAM_STATIONLINE_H)
#define BOBURA_VIEW_DIAGRAM_STATIONLINE_H

#include <algorithm>
#include <cassert>
//#include <utility>
#include <vector>

#include <boost/foreach.hpp>
#include <boost/lexical_cast.hpp>

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

        //! The position type.
        typedef typename canvas_type::position_type position_type;

        //! The left type.
        typedef typename tetengo2::gui::position<position_type>::left_type left_type;

        //! The top type.
        typedef typename tetengo2::gui::position<position_type>::top_type top_type;


        // constructors and destructor

        /*!
            \brief Creates a station line.

            \param left A left position.
            \param top  A top position.
        */
        station_line(const left_type& left, const top_type& top)
        :
        m_left(left),
        m_top(top)
        {}

        /*!
            \brief Moves a station line.

            \param another Another station line.
        */
        station_line(station_line&& another)
        :
        m_left(std::move(another.m_left)),
        m_top(std::move(another.m_top))
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

            m_left = std::move(another.m_left);
            m_top = std::move(another.m_top);

            return *this;
        }


    private:
        // variables

        left_type m_left;

        top_type m_top;


        // virtual functions

        virtual void draw_on_impl(canvas_type& canvas)
        const
        {

        }


    };


     /*!
        \brief The class template for a station line list in the diagram view.

        \tparam Model  A model type.
        \tparam Canvas A canvas type.
    */
    template <typename Model, typename Canvas>
    class station_line_list : public item<Canvas>
    {
    public:
        // types

        //! The model type.
        typedef Model model_type;
        
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
            \brief Creates a station line list.

            \param model                A model.
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
        station_line_list(
            const model_type&            model,
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
        m_station_lines(
            make_station_lines(
                model,
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


        // static functions

        std::vector<station_line_type> make_station_lines(
            const model_type&            model,
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
            return std::vector<station_line_type>();
        }


        // variables

        std::vector<station_line_type> m_station_lines;


        // virtual functions

        virtual void draw_on_impl(canvas_type& canvas)
        const
        {
            BOOST_FOREACH (const station_line_type& station_line, m_station_lines)
            {
                station_line.draw_on(canvas);
            }
        }


    };


}}}


#endif
