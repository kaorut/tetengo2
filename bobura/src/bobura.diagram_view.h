/*! \file
    \brief The definition of bobura::diagram_view.

    Copyright (C) 2007-2013 kaoru

    $Id$
*/

#if !defined(BOBURA_DIAGRAMVIEW_H)
#define BOBURA_DIAGRAMVIEW_H

#include <algorithm>
#include <cassert>
//#include <iterator>
//#include <memory>
//#include <utility>
#include <vector>

#include <boost/noncopyable.hpp>

#include <tetengo2.cpp11.h>
#include <tetengo2.gui.measure.h>
#include <tetengo2.unique.h>


namespace bobura
{
   /*!
        \brief The class template for a diagram view.

        \tparam Header          A header type.
        \tparam TimeLineList    A time line list type.
        \tparam StationLineList A station line list type.
        \tparam TrainLineList   A train line list type.
        \tparam Model           A model type.
        \tparam Canvas          A canvas type.
        \tparam SolidBackground A solid background type.
        \tparam MessageCatalog  A message catalog type.
    */
    template <
        typename Header,
        typename TimeLineList,
        typename StationLineList,
        typename TrainLineList,
        typename Model,
        typename Canvas,
        typename SolidBackground,
        typename MessageCatalog
    >
    class diagram_view : private boost::noncopyable
    {
    public:
        // types

        //! The header type.
        typedef Header header_type;

        //! The item type.
        typedef typename header_type::base_type item_type;

        //! The time line list type.
        typedef TimeLineList time_line_list_type;

        //! The station line list type.
        typedef StationLineList station_line_list_type;

        //! The train line list type.
        typedef TrainLineList train_line_list_type;

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

        //! The solid background type.
        typedef SolidBackground solid_background_type;

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
        m_model(model),
        m_message_catalog(message_catalog),
        m_horizontal_scale(1),
        m_vertical_scale(1),
        m_dimension(width_type(0), height_type(0)),
        m_header_height(0),
        m_time_header_height(3),
        m_station_header_width(8),
        m_time_offset(time_span_type(3, 0, 0)),
        m_station_intervals(),
        m_station_positions(),
        m_p_header(),
        m_p_time_line_list(),
        m_p_station_line_list(),
        m_p_train_line_list()
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

            ensure_items_created(canvas, canvas_dimension, scroll_bar_position);
            m_p_header->draw_on(canvas);
            m_p_time_line_list->draw_on(canvas);
            m_p_station_line_list->draw_on(canvas);
            m_p_train_line_list->draw_on(canvas);
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

            \param scale A horizontal scale.
        */
        void set_horizontal_scale(horizontal_scale_type scale)
        {
            m_horizontal_scale = std::move(scale);
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

            \param scale A vertical scale.
        */
        void set_vertical_scale(vertical_scale_type scale)
        {
            m_vertical_scale = std::move(scale);
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
            \brief Update the dimension.
        */
        void update_dimension()
        {
            const width_type width(20 * 24 * m_horizontal_scale);

            m_station_intervals = m_model.timetable().station_intervals();
            if (m_station_intervals.empty())
            {
                m_station_positions.clear();
                m_dimension = dimension_type(width, height_type(0));

                m_p_header.reset();
                m_p_time_line_list.reset();
                m_p_station_line_list.reset();
                m_p_train_line_list.reset();

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

            m_p_header.reset();
            m_p_time_line_list.reset();
            m_p_station_line_list.reset();
            m_p_train_line_list.reset();
        }

        /*!
            \brief Returns the page size.

            \param canvas_dimension A canvas dimension.

            \return The page size.
        */
        dimension_type page_size(const dimension_type& canvas_dimension)
        const
        {
            const width_type& canvas_width = tetengo2::gui::dimension<dimension_type>::width(canvas_dimension);
            const width_type& header_width = m_station_header_width;
            width_type page_width = canvas_width > header_width ? canvas_width - header_width : width_type(0);

            const height_type& canvas_height = tetengo2::gui::dimension<dimension_type>::height(canvas_dimension);
            const height_type& header_height = m_header_height + m_time_header_height;
            height_type page_height = canvas_height > header_height ? canvas_height - header_height : height_type(0);

            return dimension_type(std::move(page_width), std::move(page_height));
        }


    private:
        // types

        typedef typename model_type::timetable_type timetable_type;

        typedef typename timetable_type::station_intervals_type station_intervals_type;

        typedef typename timetable_type::train_type train_type;

        typedef typename train_type::stop_type stop_type;

        typedef typename stop_type::time_type time_type;

        typedef typename time_type::time_span_type time_span_type;

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


        // variables

        const model_type& m_model;

        const message_catalog_type& m_message_catalog;

        horizontal_scale_type m_horizontal_scale;

        vertical_scale_type m_vertical_scale;

        dimension_type m_dimension;

        height_type m_header_height;

        height_type m_time_header_height;

        width_type m_station_header_width;

        time_span_type m_time_offset;

        station_intervals_type m_station_intervals;

        std::vector<top_type> m_station_positions;

        std::unique_ptr<header_type> m_p_header;

        std::unique_ptr<time_line_list_type> m_p_time_line_list;

        std::unique_ptr<station_line_list_type> m_p_station_line_list;

        std::unique_ptr<train_line_list_type> m_p_train_line_list;


        // functions

        void clear_background(canvas_type& canvas, const dimension_type& canvas_dimension)
        const
        {
            canvas.set_background(
                tetengo2::make_unique<const solid_background_type>(m_model.timetable().font_color_set().background())
            );
            canvas.fill_rectangle(position_type(left_type(0), top_type(0)), canvas_dimension);
        }

        void ensure_items_created(
            canvas_type&          canvas,
            const dimension_type& canvas_dimension,
            const position_type&  scroll_bar_position
        )
        {
            if (m_p_header)
            {
                assert(m_p_time_line_list && m_p_station_line_list && m_p_train_line_list);
                return;
            }

            m_p_header = tetengo2::make_unique<header_type>(m_model, canvas, canvas_dimension);
            m_header_height = tetengo2::gui::dimension<dimension_type>::height(m_p_header->dimension());
            m_p_time_line_list =
                tetengo2::make_unique<time_line_list_type>(
                    m_model,
                    m_time_offset,
                    canvas,
                    canvas_dimension,
                    m_dimension,
                    scroll_bar_position,
                    left_type::from(m_station_header_width),
                    top_type::from(m_header_height),
                    m_time_header_height,
                    m_horizontal_scale,
                    m_vertical_scale
                );
            m_p_station_line_list =
                tetengo2::make_unique<station_line_list_type>(
                    m_model,
                    m_time_offset,
                    canvas,
                    canvas_dimension,
                    m_dimension,
                    scroll_bar_position,
                    left_type::from(m_station_header_width),
                    top_type::from(m_header_height),
                    m_time_header_height,
                    m_horizontal_scale,
                    m_vertical_scale,
                    m_station_positions
                );
            m_p_train_line_list.reset(
                new train_line_list_type(
                    m_model,
                    m_time_offset,
                    canvas,
                    canvas_dimension,
                    m_dimension,
                    scroll_bar_position,
                    left_type::from(m_station_header_width),
                    top_type::from(m_header_height),
                    m_time_header_height,
                    m_horizontal_scale,
                    m_vertical_scale,
                    m_station_intervals,
                    m_station_positions,
                    m_message_catalog
                )
            );
        }


    };


}

#endif
