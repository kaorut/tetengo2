/*! \file
    \brief The definition of tetengo2::detail::windows::gdiplus::drawing.

    Copyright (C) 2007-2019 kaoru

    $Id$
*/

#if !defined(TETENGO2_DETAIL_WINDOWS_GDIPLUS_DRAWING_H)
#define TETENGO2_DETAIL_WINDOWS_GDIPLUS_DRAWING_H

#include <cstdint>
#include <memory>
#include <vector>

#include <tetengo2/detail/base/drawing.h>
#include <tetengo2/detail/base/widget.h>
#include <tetengo2/gui/drawing/color.h>
#include <tetengo2/gui/type_list.h>
#include <tetengo2/stdalt.h>
#include <tetengo2/type_list.h>

namespace tetengo2 { namespace gui {
    class icon;

    namespace drawing {
        class background;
        class font;
        class picture;
    }
}}


namespace tetengo2::detail::windows::gdiplus {
    /*!
        \brief The class for a detail implementation of a drawing.
    */
    class drawing : public base::drawing
    {
    public:
        // types

        //! The background details type.
        using background_details_type = base::drawing::background_details_type;

        //! The background details pointer type.
        using background_details_ptr_type = base::drawing::background_details_ptr_type;

        //! The picture details type.
        using picture_details_type = base::drawing::picture_details_type;

        //! The picture details pointer type.
        using picture_details_ptr_type = base::drawing::picture_details_ptr_type;

        //! The canvas details type.
        using canvas_details_type = base::drawing::canvas_details_type;

        //! The canvas details pointer type.
        using canvas_details_ptr_type = base::drawing::canvas_details_ptr_type;


        // static functions

        /*!
            \brief Returns the instance.

            \return The instance.
        */
        static const drawing& instance();


        // constructors and destructors

        /*!
            \brief Destroys the detail implementation.
        */
        virtual ~drawing();


    private:
        // types

        class impl;


        // variables

        const std::unique_ptr<impl> m_p_impl;


        // constructors

        drawing();


        // virtual functions

        virtual std::unique_ptr<canvas_details_type>
        create_canvas_impl(const base::widget::widget_details_type& widget_details) const override;

        virtual std::unique_ptr<canvas_details_type> create_canvas_impl(std::intptr_t canvas_handle) const override;

        virtual void begin_transaction_impl(
            canvas_details_type&                  canvas,
            const gui::type_list::dimension_type& dimension) const override;

        virtual void end_transaction_impl(canvas_details_type& canvas) const override;

        virtual std::unique_ptr<background_details_type>
        create_solid_background_impl(const gui::drawing::color& color) const override;

        virtual std::unique_ptr<background_details_type> create_transparent_background_impl() const override;

        virtual std::unique_ptr<picture_details_type>
        create_picture_impl(const gui::type_list::dimension_type& dimension) const override;

        virtual std::unique_ptr<picture_details_type>
        read_picture_impl(const tetengo2::stdalt::filesystem::path& path) const override;

        virtual gui::type_list::dimension_type
        picture_dimension_impl(const picture_details_type& picture) const override;

        virtual void draw_line_impl(
            canvas_details_type&                       canvas,
            const gui::type_list::position_type&       from,
            const gui::type_list::position_type&       to,
            const gui::type_list::dimension_unit_type& width,
            int                                        style,
            const gui::drawing::color&                 color) const override;

        virtual void draw_focus_indication_impl(
            canvas_details_type&                  canvas,
            const gui::type_list::position_type&  position,
            const gui::type_list::dimension_type& dimension) const override;

        virtual void draw_rectangle_impl(
            canvas_details_type&                       canvas,
            const gui::type_list::position_type&       position,
            const gui::type_list::dimension_type&      dimension,
            const gui::type_list::dimension_unit_type& width,
            int                                        style,
            const gui::drawing::color&                 color) const override;

        virtual void fill_rectangle_impl(
            canvas_details_type&                  canvas,
            const gui::type_list::position_type&  position,
            const gui::type_list::dimension_type& dimension,
            const gui::drawing::background&       background) const override;

        virtual void draw_polygon_impl(
            canvas_details_type&                              canvas,
            const std::vector<gui::type_list::position_type>& positions,
            const gui::type_list::dimension_unit_type&        width,
            int                                               style,
            const gui::drawing::color&                        color) const override;

        virtual void fill_polygon_impl(
            canvas_details_type&                              canvas,
            const std::vector<gui::type_list::position_type>& positions,
            const gui::drawing::background&                   background) const override;

        virtual gui::drawing::font make_dialog_font_impl() const override;

        virtual gui::type_list::dimension_type calc_text_dimension_impl(
            const canvas_details_type&                 canvas,
            const gui::drawing::font&                  font,
            const type_list::string_type&              text,
            const gui::type_list::dimension_unit_type& max_width) const override;

        virtual gui::type_list::dimension_type calc_vertical_text_dimension_impl(
            const canvas_details_type&    canvas,
            const gui::drawing::font&     font,
            const type_list::string_type& text) const override;

        virtual void draw_text_impl(
            canvas_details_type&                       canvas,
            const gui::drawing::font&                  font,
            const type_list::string_type&              text,
            const gui::type_list::position_type&       position,
            const gui::type_list::dimension_unit_type& max_width,
            const gui::drawing::color&                 color,
            double                                     angle) const override;

        virtual void draw_vertical_text_impl(
            canvas_details_type&                 canvas,
            const gui::drawing::font&            font,
            const type_list::string_type&        text,
            const gui::type_list::position_type& position,
            const gui::drawing::color&           color) const override;

        virtual void paint_picture_impl(
            canvas_details_type&                  canvas,
            const gui::drawing::picture&          picture,
            const gui::type_list::position_type&  position,
            const gui::type_list::dimension_type& dimension) const override;

        virtual void paint_icon_impl(
            canvas_details_type&                 canvas,
            const gui::icon&                     icon,
            const gui::type_list::position_type& position) const override;
    };
}


#endif
