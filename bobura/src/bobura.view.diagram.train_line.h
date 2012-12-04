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
        \brief The class template for a train line in the diagram view.

        \tparam Canvas A canvas type.
    */
    template <typename Canvas>
    class train_line : public item<Canvas>
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
            \brief Creates a train line.

            \param right          A right position.
            \param top            A top position.
        */
        train_line(const left_type& right, top_type&& top)
        :
        m_right(right),
        m_top(std::forward<top_type>(top))
        {}

        /*!
            \brief Moves a train line.

            \param another Another train line.
        */
        train_line(train_line&& another)
        :
        m_right(std::move(another.m_right)),
        m_top(std::move(another.m_top))
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
        */
        train_line_list(
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
            const vertical_scale_type&   vertical_scale
        )
        :
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
                vertical_scale
            )
        )
        {}

        /*!
            \brief Moves a train line list.

            \param another Another train line list.
        */
        train_line_list(train_line_list&& another)
        :
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

            m_train_lines = std::move(another.m_train_lines);

            return *this;
        }


    private:
        // types

        typedef train_line<canvas_type> train_line_type;


        // static functions

        std::vector<train_line_type> make_train_lines(
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
            const vertical_scale_type&   vertical_scale
        )
        {
            return std::vector<train_line_type>();
        }


        // variables

        std::vector<train_line_type> m_train_lines;


        // virtual functions

        virtual void draw_on_impl(canvas_type& canvas)
        const
        {
            BOOST_FOREACH (const train_line_type& train_line, m_train_lines)
            {
                train_line.draw_on(canvas);
            }
        }


    };


}}}


#endif
