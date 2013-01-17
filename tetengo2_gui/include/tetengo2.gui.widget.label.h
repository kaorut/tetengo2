/*! \file
    \brief The definition of tetengo2::gui::widget::label.

    Copyright (C) 2007-2013 kaoru

    $Id$
*/

#if !defined(TETENGO2_GUI_WIDGET_LABEL_H)
#define TETENGO2_GUI_WIDGET_LABEL_H

#include <cmath>
#include <cstddef>
#include <limits>
#include <type_traits>
#include <utility>

#include <boost/rational.hpp>

#include "tetengo2.cpp11.h"
#include "tetengo2.gui.measure.h"
#include "tetengo2.gui.widget.control.h"


namespace tetengo2 { namespace gui { namespace widget
{
    /*!
        \brief The class template for a label.

        \tparam Traits                A traits type.
        \tparam WidgetDetails         A detail implementation type of a widget.
        \tparam MessageHandlerDetails A detail implementation type of a message handler.
   */
    template <typename Traits, typename WidgetDetails, typename MessageHandlerDetails>
    class label : public control<typename Traits::base_type, WidgetDetails, MessageHandlerDetails>
    {
    public:
        // types

        //! The traits type.
        typedef Traits traits_type;

        //! The detail implementation type of a widget.
        typedef WidgetDetails widget_details_type;

        //! The detail implementation type of a message handler.
        typedef MessageHandlerDetails message_handler_details_type;

        //! The base type.
        typedef control<typename traits_type::base_type, widget_details_type, message_handler_details_type> base_type;

        //! The canvas type.
        typedef typename base_type::canvas_type canvas_type;

        //! The position type.
        typedef typename base_type::position_type position_type;

        //! The dimension type.
        typedef typename base_type::dimension_type dimension_type;

        //! The width type.
        typedef typename tetengo2::gui::dimension<dimension_type>::width_type width_type;

        //! The height type.
        typedef typename tetengo2::gui::dimension<dimension_type>::height_type height_type;

        //! The string type.
        typedef typename base_type::string_type string_type;

        //! The widget type.
        typedef typename base_type::base_type widget_type;

        //! The keyboard observer set type.
        typedef typename base_type::keyboard_observer_set_type keyboard_observer_set_type;

        //! The detail implementation type.
        typedef typename widget_details_type::widget_details_type details_type;
        
        //! The detail implementation pointer type.
        typedef typename widget_details_type::widget_details_ptr_type details_ptr_type;


        // constructors and destructor

        /*!
            \brief Creates a label.

            \param parent A parent widget.
        */
        explicit label(widget_type& parent)
        :
#if defined(_MSC_VER)
#   pragma warning(push)
#   pragma warning(disable: 4355)
#endif
        base_type(
            base_type::scroll_bar_style_type::none,
            message_handler_details_type::make_label_message_handler_map(*this, message_handler_map_type()),
            widget_details_type::create_label(parent)
        )
#if defined(_MSC_VER)
#   pragma warning(pop)
#endif
        {
            initialize(this);
        }

        /*!
            \brief Destroys the label.
        */
        virtual ~label()
        TETENGO2_CPP11_NOEXCEPT
        {}


        // functions

        /*!
            \brief Fit the dimension to the dimension of the text.
        */
        void fit_to_content()
        {
            if (this->text().empty()) return;

            set_client_dimension(calc_text_dimension());
        }

        /*!
            \brief Fit the dimension to the dimension of the text.

            \param max_width A maximum width.
        */
        void fit_to_content(width_type max_width)
        {
            if (this->text().empty() || max_width == width_type(0)) return;

            dimension_type one_line_dimension = calc_text_dimension();
            const width_type line_count =
                tetengo2::gui::dimension<dimension_type>::width(one_line_dimension) / max_width;
            if (line_count <= width_type(1))
            {
                set_client_dimension(std::move(one_line_dimension));
                return;
            }

            const std::size_t int_line_count =
                static_cast<std::size_t>(std::ceil(to_double(line_count)));
            height_type height = tetengo2::gui::dimension<dimension_type>::height(one_line_dimension) * int_line_count;
            set_client_dimension(dimension_type(std::move(max_width), std::move(height)));
        }


    private:
        // types

        typedef typename message_handler_details_type::message_handler_map_type message_handler_map_type;

        struct call_calc_text_dimension_type
        {
            const string_type& m_text;

            explicit call_calc_text_dimension_type(const string_type& text)
            :
            m_text(text)
            {}

            dimension_type operator()(const canvas_type& canvas)
            const
            {
                return canvas.calc_text_dimension(m_text);
            }

        };


        // static functions

        template <typename T>
        double to_double(const T value, typename std::enable_if<std::is_integral<T>::value>::type* = NULL)
        {
            return static_cast<double>(value);
        }

        template <typename T>
        double to_double(const T value, typename std::enable_if<!std::is_integral<T>::value>::type* = NULL)
        {
            return boost::rational_cast<double>(value.value());
        }


        // functions

        dimension_type calc_text_dimension()
        const
        {
            return
                widget_details_type::template use_canvas<dimension_type>(
                    *this, call_calc_text_dimension_type(this->text())
                );
        }


    };


}}}


#endif
