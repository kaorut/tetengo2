/*! \file
    \brief The definition of tetengo2::gui::widget::label.

    Copyright (C) 2007-2015 kaoru

    $Id$
*/

#if !defined(TETENGO2_GUI_WIDGET_LABEL_H)
#define TETENGO2_GUI_WIDGET_LABEL_H

#include <cstddef>
#include <utility>

#include <boost/predef.h>

#include <tetengo2/gui/measure.h>
#include <tetengo2/gui/widget/control.h>


namespace tetengo2 { namespace gui { namespace widget
{
    /*!
        \brief The class template for a label.

        \tparam Traits        A traits type.
        \tparam DetailsTraits A detail implementation type traits.
    */
    template <typename Traits, typename DetailsTraits>
    class label : public control<Traits, DetailsTraits>
    {
    public:
        // types

        //! The traits type.
        using traits_type = Traits;

        //! The details traits type.
        using details_traits_type = DetailsTraits;

        //! The widget details type.
        using widget_details_type = typename details_traits_type::widget_details_type;

        //! The message handler details type.
        using message_handler_details_type = typename details_traits_type::message_handler_details_type;

        //! The base type.
        using base_type = control<traits_type, details_traits_type>;

        //! The widget type.
        using widget_type = typename base_type::base_type;

        //! The canvas type.
        using canvas_type = typename base_type::canvas_type;

        //! The dimension type.
        using dimension_type = typename base_type::dimension_type;

        //! The width type.
        using width_type = typename gui::dimension<dimension_type>::width_type;


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
            message_handler_details_type::make_label_message_handler_map(*this, message_handler_map_type{}),
            widget_details_type::create_label(parent)
        )
#if BOOST_COMP_MSVC
#   pragma warning(pop)
#endif
        {
            base_type::initialize(this);
        }

        /*!
            \brief Destroys the label.
        */
        virtual ~label()
        = default;


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
            if (this->text().empty() || max_width == width_type{ 0 }) return;

            auto one_line_dimension = calc_text_dimension();
            const width_type line_count{ gui::dimension<dimension_type>::width(one_line_dimension) / max_width };
            if (line_count <= width_type{ 1 })
            {
                this->set_client_dimension(std::move(one_line_dimension));
                return;
            }

            const auto int_line_count = ceil<std::size_t>(line_count);
            auto height = gui::dimension<dimension_type>::height(one_line_dimension) * int_line_count;
            this->set_client_dimension(dimension_type{ std::move(max_width), std::move(height) });
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
