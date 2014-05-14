/*! \file
    \brief The definition of tetengo2::gui::widget::label.

    Copyright (C) 2007-2014 kaoru

    $Id$
*/

#if !defined(TETENGO2_GUI_WIDGET_LABEL_H)
#define TETENGO2_GUI_WIDGET_LABEL_H

#include <cstddef>
#include <utility>

#include <boost/predef.h>

#include <tetengo2/gui/measure.h>
#include <tetengo2/gui/widget/control.h>
#include <tetengo2/stdalt.h>


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
        using traits_type = Traits;

        //! The detail implementation type of a widget.
        using widget_details_type = WidgetDetails;

        //! The detail implementation type of a message handler.
        using message_handler_details_type = MessageHandlerDetails;

        //! The base type.
        using base_type = control<typename traits_type::base_type, widget_details_type, message_handler_details_type>;

        //! The canvas type.
        using canvas_type = typename base_type::canvas_type;

        //! The position type.
        using position_type = typename base_type::position_type;

        //! The dimension type.
        using dimension_type = typename base_type::dimension_type;

        //! The width type.
        using width_type = typename gui::dimension<dimension_type>::width_type;

        //! The string type.
        using string_type = typename base_type::string_type;

        //! The widget type.
        using widget_type = typename base_type::base_type;

        //! The mouse observer set type.
        using mouse_observer_set_type = typename base_type::mouse_observer_set_type;

        //! The keyboard observer set type.
        using keyboard_observer_set_type = typename base_type::keyboard_observer_set_type;

        //! The detail implementation type.
        using details_type = typename widget_details_type::widget_details_type;
        

        // constructors and destructor

        /*!
            \brief Creates a label.

            \param parent A parent widget.
        */
        explicit label(widget_type& parent)
        :
#if BOOST_COMP_MSVC
#   pragma warning(push)
#   pragma warning(disable: 4355)
#endif
        base_type(
            base_type::scroll_bar_style_type::none,
            message_handler_details_type::make_label_message_handler_map(*this, message_handler_map_type()),
            widget_details_type::create_label(parent)
        )
#if BOOST_COMP_MSVC
#   pragma warning(pop)
#endif
        {
            this->initialize(this);
        }

        /*!
            \brief Destroys the label.
        */
        virtual ~label()
        TETENGO2_STDALT_DESTRUCTOR_DEFAULT_IMPLEMENTATION


        // functions

        /*!
            \brief Fit the dimension to the dimension of the text.
        */
        void fit_to_content()
        {
            if (this->text().empty()) return;

            this->set_client_dimension(calc_text_dimension());
        }

        /*!
            \brief Fit the dimension to the dimension of the text.

            \param max_width A maximum width.
        */
        void fit_to_content(width_type max_width)
        {
            if (this->text().empty() || max_width == width_type(0)) return;

            auto one_line_dimension = calc_text_dimension();
            const width_type line_count(gui::dimension<dimension_type>::width(one_line_dimension) / max_width);
            if (line_count <= width_type(1))
            {
                this->set_client_dimension(std::move(one_line_dimension));
                return;
            }

            const auto int_line_count = ceil<std::size_t>(line_count);
            auto height = gui::dimension<dimension_type>::height(one_line_dimension) * int_line_count;
            this->set_client_dimension(dimension_type(std::move(max_width), std::move(height)));
        }


    private:
        // types

        using message_handler_map_type = typename message_handler_details_type::message_handler_map_type;


        // functions

        dimension_type calc_text_dimension()
        const
        {
            return
                widget_details_type::template use_canvas<dimension_type>(
                    *this, [this](const canvas_type& canvas) { return canvas.calc_text_dimension(this->text()); }
                );
        }


    };


}}}


#endif
