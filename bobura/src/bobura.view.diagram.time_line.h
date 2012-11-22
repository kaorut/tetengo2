/*! \file
    \brief The definition of bobura::view::diagram::time_line.

    Copyright (C) 2007-2012 kaoru

    $Id$
*/

#if !defined(BOBURA_VIEW_DIAGRAM_TIMELINE_H)
#define BOBURA_VIEW_DIAGRAM_TIMELINE_H

#include <algorithm>
#include <cassert>
//#include <memory>
//#include <utility>
#include <vector>

#include <tetengo2.cpp11.h>
#include <tetengo2.gui.measure.h>
#include <tetengo2.text.h>
#include <tetengo2.unique.h>

#include "bobura.view.diagram.item.h"


namespace bobura { namespace view { namespace diagram
{
     /*!
        \brief The class template for a time line in the diagram view.

        \tparam Model  A model type.
        \tparam Canvas A canvas type.
    */
    template <typename Model, typename Canvas>
    class time_line : public item<Canvas>
    {
    public:
        // types

        //! The model type.
        typedef Model model_type;

        //! The canvas type.
        typedef Canvas canvas_type;

        //! The position type.
        typedef typename canvas_type::position_type position_type;

        //! The dimension type.
        typedef typename canvas_type::dimension_type dimension_type;


        // constructors and destructor

        /*!
            \brief Creates a time line.

            \param model            A model.
            \param canvas           A canvas.
            \param canvas_dimension A canvas dimension.
        */
        time_line(const model_type& model, canvas_type& canvas, const dimension_type& canvas_dimension)
        :
        m_position(left_type(0), top_type(0)),
        m_dimension(width_type(0), height_type(0))
        {

        }

        /*!
            \brief Destroys the time line.
        */
        virtual ~time_line()
        TETENGO2_CPP11_NOEXCEPT
        {}


    private:
        // types

        typedef typename canvas_type::string_type string_type;

        typedef typename canvas_type::font_type font_type;

        typedef typename canvas_type::color_type color_type;

        typedef typename tetengo2::gui::position<position_type>::left_type left_type;

        typedef typename tetengo2::gui::position<position_type>::top_type top_type;

        typedef typename tetengo2::gui::dimension<dimension_type>::width_type width_type;

        typedef typename tetengo2::gui::dimension<dimension_type>::height_type height_type;


        // static functions


        // variables

        position_type m_position;

        dimension_type m_dimension;


        // virtual functions

        virtual void draw_on_impl(canvas_type& canvas)
        const
        {

        }


    };


     /*!
        \brief The class template for a time line list in the diagram view.

        \tparam Model  A model type.
        \tparam Canvas A canvas type.
    */
    template <typename Model, typename Canvas>
    class time_line_list : public item<Canvas>
    {
    public:
        // types

        //! The model type.
        typedef Model model_type;

        //! The canvas type.
        typedef Canvas canvas_type;

        //! The position type.
        typedef typename canvas_type::position_type position_type;

        //! The dimension type.
        typedef typename canvas_type::dimension_type dimension_type;


        // constructors and destructor

        /*!
            \brief Creates a time line list.

            \param model               A model.
            \param canvas              A canvas.
            \param canvas_dimension    A canvas dimension.
            \param scroll_bar_position A scroll bar position.
        */
        time_line_list(
            const model_type&     model,
            canvas_type&          canvas,
            const dimension_type& canvas_dimension,
            const position_type&  scroll_bar_position
        )
        :
        m_p_time_lines(create_time_lines(model, canvas, canvas_dimension, scroll_bar_position))
        {}

        /*!
            \brief Destroys the time line list.
        */
        virtual ~time_line_list()
        TETENGO2_CPP11_NOEXCEPT
        {}


    private:
        // types

        typedef time_line<model_type, canvas_type> time_line_type;


        // static functions

        std::vector<std::unique_ptr<time_line_type>> create_time_lines(
            const model_type&     model,
            canvas_type&          canvas,
            const dimension_type& canvas_dimension,
            const position_type&  scroll_bar_position
        )
        {
            std::vector<std::unique_ptr<time_line_type>> p_time_lines;

            return std::move(p_time_lines);
        }


        // variables

        std::vector<std::unique_ptr<time_line_type>> m_p_time_lines;


        // virtual functions

        virtual void draw_on_impl(canvas_type& canvas)
        const
        {

        }


    };


}}}


#endif
