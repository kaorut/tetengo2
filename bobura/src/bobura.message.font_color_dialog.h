/*! \file
    \brief The definition of bobura::message::font_color_dialog.

    Copyright (C) 2007-2012 kaoru

    $Id$
*/

#if !defined(BOBURA_MESSAGE_FONTCOLORDIALOG_H)
#define BOBURA_MESSAGE_FONTCOLORDIALOG_H

#include <limits>
#include <memory>
#include <utility>

#include <boost/optional.hpp>

#include <tetengo2.gui.measure.h>
#include <tetengo2.unique.h>
#include <tetengo2.text.h>


namespace bobura { namespace message { namespace font_color_dialog
{
    /*!
        \brief The class template for a selection change observer of the category list box.

        \tparam Size    A size type.
        \tparam ListBox A list box type.
    */
    template <typename Size, typename ListBox>
    class category_list_box_selection_changed
    {
    public:
        // types

        //! The size type.
        typedef Size size_type;

        //! The list box type.
        typedef ListBox list_box_type;

        //! The update type.
        typedef std::function<void (const boost::optional<size_type>&)> update_type;


        // constructors and destructor

        /*!
            \brief Create a selection change observer of the category list box.

            \param current_category_index A current category index.
            \param list_box               A list box type.
            \param update                 A update function.
        */
        category_list_box_selection_changed(
            boost::optional<size_type>& current_category_index,
            const list_box_type&        list_box,
            const update_type           update
        )
        :
        m_current_category_index(current_category_index),
        m_list_box(list_box),
        m_update(update)
        {}


        // functions

        /*!
            \brief Called when the selection of the category list box is changed.
        */
        void operator()()
        const
        {
            const boost::optional<size_type> previous_category_index = m_current_category_index;
            m_current_category_index = m_list_box.selected_item_index();
            m_update(previous_category_index);
        }


    private:
        // variables

        boost::optional<size_type>& m_current_category_index;

        const list_box_type& m_list_box;

        update_type m_update;


    };


    /*!
        \brief The class template for a paint observer of the sample picture box.

        \tparam IntSize        A integer size type.
        \tparam Canvas         A canvas type.
        \tparam MessageCatalog A message catalog type.
    */
    template <typename IntSize, typename Canvas, typename MessageCatalog>
    class sample_picture_box_paint
    {
    public:
        // types

        //! The integer size type.
        typedef IntSize int_size_type;

        //! The canvas type.
        typedef Canvas canvas_type;

        //! The font type.
        typedef typename Canvas::font_type font_type;

        //! The color type.
        typedef typename Canvas::color_type color_type;

        //! The internal font and color type.
        typedef std::pair<boost::optional<font_type>, boost::optional<color_type>> internal_font_color_type;

        //! The dimension type.
        typedef typename Canvas::dimension_type dimension_type;

        //! The message catalog type.
        typedef MessageCatalog message_catalog_type;


        // constructors and destructor

        /*!
            \brief Creates a paint observer of the sample picture box.

            \param font_color_list        A font and color list.
            \param current_category_index A current category index.
            \param canvas_dimension       A canvas dimension.
            \param message_catalog        A message catalog.
        */
        sample_picture_box_paint(
            const std::vector<internal_font_color_type>& font_color_list,
            const boost::optional<int_size_type>&        current_category_index,
            const dimension_type&                        canvas_dimension,
            const message_catalog_type&                  message_catalog
        )
        :
        m_font_color_list(font_color_list),
        m_current_category_index(current_category_index),
        m_canvas_dimension(canvas_dimension),
        m_message_catalog(message_catalog)
        {}


        // functions

        /*!
            \brief Called when the canvas needs to be repainted.

            \param canvas A canvas.
        */
        void operator()(canvas_type& canvas)
        const
        {
            assert(m_font_color_list[0].second);
            std::unique_ptr<background_type> p_background =
                tetengo2::make_unique<solid_background_type>(*m_font_color_list[0].second);
            canvas.set_background(std::move(p_background));
            canvas.fill_rectangle(position_type(0, 0), m_canvas_dimension);

            if (!m_current_category_index || *m_current_category_index == 0)
                return;

            assert(m_font_color_list[*m_current_category_index].first);
            canvas.set_font(*m_font_color_list[*m_current_category_index].first);
            canvas.set_color(
                m_font_color_list[*m_current_category_index].second ?
                *m_font_color_list[*m_current_category_index].second : color_type(0x40, 0x40, 0x40)
            );

            const string_type text(m_message_catalog.get(TETENGO2_TEXT("Dialog:FontAndColor:SAMPLE")));

            const std::pair<top_type, top_type> text_and_line_tops = sample_text_and_line_tops(canvas, text);

            canvas.draw_text(text, position_type(1, text_and_line_tops.first));

            canvas.set_line_width(width_type(size_type(1, 12)));
            canvas.set_line_style(canvas_type::line_style_type::solid);
            canvas.draw_line(
                position_type(0, text_and_line_tops.second),
                position_type(
                    left_type::from(tetengo2::gui::dimension<dimension_type>::width(m_canvas_dimension)),
                    text_and_line_tops.second
                )
            );
        }


    private:
        // types

        typedef typename canvas_type::string_type string_type;

        typedef typename canvas_type::position_type position_type;

        typedef typename tetengo2::gui::position<position_type>::left_type left_type;

        typedef typename tetengo2::gui::position<position_type>::top_type top_type;

        typedef typename tetengo2::gui::dimension<dimension_type>::width_type width_type;

        typedef typename width_type::value_type size_type;

        typedef typename tetengo2::gui::dimension<dimension_type>::height_type height_type;

        typedef typename canvas_type::background_type background_type;

        typedef typename canvas_type::solid_background_type solid_background_type;


        // variables

        const std::vector<internal_font_color_type>& m_font_color_list;

        const boost::optional<int_size_type>& m_current_category_index;

        const dimension_type m_canvas_dimension;

        const message_catalog_type& m_message_catalog;


        // functions

        std::pair<top_type, top_type> sample_text_and_line_tops(const canvas_type& canvas, const string_type& text)
        const
        {
            const height_type canvas_height = tetengo2::gui::dimension<dimension_type>::height(m_canvas_dimension);
            const height_type text_height =
                tetengo2::gui::dimension<dimension_type>::height(canvas.calc_text_dimension(text));

            if (canvas_height > text_height)
            {
                const top_type text_top = top_type::from((canvas_height - text_height) / 2);
                const top_type line_top = text_top + top_type::from(text_height);
                return std::make_pair(text_top, line_top);
            }
            else
            {
                const top_type line_top = top_type::from(canvas_height);
                const top_type text_top = line_top - top_type::from(text_height);
                return std::make_pair(text_top, line_top);
            }
        }


    };


    /*!
        \brief The class template for a mouse click observer of the OK button.

        \tparam Dialog A dialog type.
    */
    template <typename Dialog>
    class ok_button_mouse_clicked
    {
    public:
        // types

        //! The dialog type.
        typedef Dialog dialog_type;


        // constructors and destructor

        /*!
            \brief Creates a mouse click observer of the OK button.

            \param dialog A dialog.
        */
        explicit ok_button_mouse_clicked(dialog_type& dialog)
        :
        m_dialog(dialog)
        {}


        // functions

        /*!
            \brief Called when the OK button is clicked.
        */
        void operator()()
        const
        {
            m_dialog.set_result(dialog_type::result_type::accepted);
            m_dialog.close();
        }


    private:
        // variables

        dialog_type& m_dialog;


    };


    /*!
        \brief The class template for a mouse click observer of the cancel button.

        \tparam Dialog A dialog type.
    */
    template <typename Dialog>
    class cancel_button_mouse_clicked
    {
    public:
        // types

        //! The dialog type.
        typedef Dialog dialog_type;


        // constructors and destructor

        /*!
            \brief Creates a mouse click observer of the cancel button.

            \param dialog A dialog.
        */
        explicit cancel_button_mouse_clicked(dialog_type& dialog)
        :
        m_dialog(dialog)
        {}


        // functions

        /*!
            \brief Called when the cancel button is clicked.
        */
        void operator()()
        const
        {
            m_dialog.set_result(dialog_type::result_type::canceled);
            m_dialog.close();
        }


    private:
        // variables

        dialog_type& m_dialog;


    };


}}}


#endif
