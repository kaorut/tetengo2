/*! \file
    \brief The definition of bobura::message::train_kind_dialog.

    Copyright (C) 2007-2013 kaoru

    $Id$
*/

#if !defined(BOBURA_MESSAGE_TRAINKINDDIALOG_H)
#define BOBURA_MESSAGE_TRAINKINDDIALOG_H

#include <cassert>
//#include <functional>
//#include <memory>
#include <stdexcept>
//#include <utility>
#include <vector>

#include <boost/optional.hpp>
#include <boost/throw_exception.hpp>
#include <boost/utility.hpp>

#include <tetengo2.cpp11.h>
#include <tetengo2.gui.measure.h>
#include <tetengo2.unique.h>
#include <tetengo2.text.h>


namespace bobura { namespace message { namespace train_kind_dialog
{
    /*!
        \brief The class template for a selection change observer of the train kind list box.

        \tparam Size    A size type.
        \tparam ListBox A list box type.
    */
    template <typename Size, typename ListBox>
    class train_kind_list_box_selection_changed
    {
    public:
        // types

        //! The size type.
        typedef Size size_type;

        //! The list box type.
        typedef ListBox list_box_type;

        //! The update type.
        typedef std::function<void ()> update_type;


        // constructors and destructor

        /*!
            \brief Create a selection change observer of the train kind list box.

            \param current_train_kind_index A current train kind index.
            \param list_box                 A list box.
            \param update                   A update function.
        */
        train_kind_list_box_selection_changed(
            boost::optional<size_type>& current_train_kind_index,
            const list_box_type&        list_box,
            const update_type           update
        )
        :
        m_current_train_kind_index(current_train_kind_index),
        m_list_box(list_box),
        m_update(update)
        {}


        // functions

        /*!
            \brief Called when the selection of the train kind list box is changed.
        */
        void operator()()
        const
        {
            m_current_train_kind_index = m_list_box.selected_item_index();
            m_update();
        }


    private:
        // variables

        boost::optional<size_type>& m_current_train_kind_index;

        const list_box_type& m_list_box;

        update_type m_update;


    };


    /*!
        \brief The class template for a mouse click observer of the add button.

        \tparam InfoSet        An information set type.
        \tparam Size           A size type.
        \tparam MessageCatalog A message catalog type.
    */
    template <typename InfoSet, typename Size, typename MessageCatalog>
    class add_button_mouse_clicked
    {
    public:
        // types

        //! The information set type.
        typedef InfoSet info_set_type;

        //! The size type.
        typedef Size size_type;

        //! The message catalog type.
        typedef MessageCatalog message_catalog_type;

        //! The sync type.
        typedef std::function<void ()> sync_type;


        // constructors and destructor

        /*!
            \brief Creates a mouse click observer of the add button.

            \param info_sets                Information sets.
            \param current_train_kind_index A current train kind index.
            \param sync                     A sync function type.
            \param message_catalog          A message catalog.
        */
        add_button_mouse_clicked(
            std::vector<info_set_type>&       info_sets,
            const boost::optional<size_type>& current_train_kind_index,
            const sync_type                   sync,
            const message_catalog_type&       message_catalog
        )
        :
        m_info_sets(info_sets),
        m_current_train_kind_index(current_train_kind_index),
        m_sync(sync),
        m_message_catalog(message_catalog)
        {}


        // functions

        /*!
            \brief Called when the add button is clicked.
        */
        void operator()()
        const
        {
            const typename std::vector<info_set_type>::const_iterator insertion_position =
                m_current_train_kind_index ?
                boost::next(m_info_sets.begin(), *m_current_train_kind_index) : m_info_sets.end();

            m_info_sets.insert(
                tetengo2::cpp11::as_insertion_iterator(m_info_sets, insertion_position),
                info_set_type(
                    boost::none,
                    false,
                    train_kind_type(
                        m_message_catalog.get(TETENGO2_TEXT("Dialog:TrainKind:New Kind")),
                        string_type(),
                        color_type(0, 0, 0),
                        train_kind_type::weight_type::normal,
                        train_kind_type::line_style_type::solid
                    )
                )
            );

            m_sync();
        }


    private:
        // types

        typedef typename info_set_type::train_kind_type train_kind_type;

        typedef typename train_kind_type::string_type string_type;

        typedef typename train_kind_type::color_type color_type;


        // variables

        std::vector<info_set_type>& m_info_sets;

        const boost::optional<size_type>& m_current_train_kind_index;

        sync_type m_sync;

        const message_catalog_type& m_message_catalog;


    };


    /*!
        \brief The class template for a mouse click observer of the delete button.

        \tparam InfoSet An information set type.
        \tparam Size    A size type.
    */
    template <typename InfoSet, typename Size>
    class delete_button_mouse_clicked
    {
    public:
        // types

        //! The information set type.
        typedef InfoSet info_set_type;

        //! The size type.
        typedef Size size_type;

        //! The sync type.
        typedef std::function<void ()> sync_type;


        // constructors and destructor

        /*!
            \brief Creates a mouse click observer of the delete button.

            \param info_sets                Information sets.
            \param current_train_kind_index A current train kind index.
            \param sync                     A sync function type.
        */
        delete_button_mouse_clicked(
            std::vector<info_set_type>& info_sets,
            boost::optional<size_type>& current_train_kind_index,
            const sync_type             sync
        )
        :
        m_info_sets(info_sets),
        m_current_train_kind_index(current_train_kind_index),
        m_sync(sync)
        {}


        // functions

        /*!
            \brief Called when the delete button is clicked.
        */
        void operator()()
        const
        {
            assert(m_current_train_kind_index);
            assert(*m_current_train_kind_index < m_info_sets.size());
            const typename std::vector<info_set_type>::const_iterator deletion_position =
                boost::next(m_info_sets.begin(), *m_current_train_kind_index);

            m_info_sets.erase(tetengo2::cpp11::as_insertion_iterator(m_info_sets, deletion_position));
            if (*m_current_train_kind_index >= m_info_sets.size())
            {
                if (m_info_sets.empty())
                    m_current_train_kind_index = boost::none;
                else
                    m_current_train_kind_index = boost::make_optional(m_info_sets.size() - 1);
            }

            m_sync();
        }


    private:
        // variables

        std::vector<info_set_type>& m_info_sets;

        boost::optional<size_type>& m_current_train_kind_index;

        sync_type m_sync;


    };


    /*!
        \brief The class template for a mouse click observer of the up button.

        \tparam InfoSet An information set type.
        \tparam Size    A size type.
    */
    template <typename InfoSet, typename Size>
    class up_button_mouse_clicked
    {
    public:
        // types

        //! The information set type.
        typedef InfoSet info_set_type;

        //! The size type.
        typedef Size size_type;

        //! The sync type.
        typedef std::function<void ()> sync_type;


        // constructors and destructor

        /*!
            \brief Creates a mouse click observer of the up button.

            \param info_sets                Information sets.
            \param current_train_kind_index A current train kind index.
            \param sync                     A sync function type.
        */
        up_button_mouse_clicked(
            std::vector<info_set_type>& info_sets,
            boost::optional<size_type>& current_train_kind_index,
            const sync_type             sync
        )
        :
        m_info_sets(info_sets),
        m_current_train_kind_index(current_train_kind_index),
        m_sync(sync)
        {}


        // functions

        /*!
            \brief Called when the up button is clicked.
        */
        void operator()()
        const
        {
            assert(m_current_train_kind_index);
            assert(1 <= *m_current_train_kind_index && *m_current_train_kind_index < m_info_sets.size());

            std::swap(m_info_sets[*m_current_train_kind_index - 1], m_info_sets[*m_current_train_kind_index]);
            --(*m_current_train_kind_index);

            m_sync();
        }


    private:
        // variables

        std::vector<info_set_type>& m_info_sets;

        boost::optional<size_type>& m_current_train_kind_index;

        sync_type m_sync;


    };


    /*!
        \brief The class template for a mouse click observer of the down button.

        \tparam InfoSet An information set type.
        \tparam Size    A size type.
    */
    template <typename InfoSet, typename Size>
    class down_button_mouse_clicked
    {
    public:
        // types

        //! The information set type.
        typedef InfoSet info_set_type;

        //! The size type.
        typedef Size size_type;

        //! The sync type.
        typedef std::function<void ()> sync_type;


        // constructors and destructor

        /*!
            \brief Creates a mouse click observer of the down button.

            \param info_sets                Information sets.
            \param current_train_kind_index A current train kind index.
            \param sync                     A sync function type.
        */
        down_button_mouse_clicked(
            std::vector<info_set_type>& info_sets,
            boost::optional<size_type>& current_train_kind_index,
            const sync_type             sync
        )
        :
        m_info_sets(info_sets),
        m_current_train_kind_index(current_train_kind_index),
        m_sync(sync)
        {}


        // functions

        /*!
            \brief Called when the down button is clicked.
        */
        void operator()()
        const
        {
            assert(m_current_train_kind_index);
            assert(*m_current_train_kind_index + 1 < m_info_sets.size());

            std::swap(m_info_sets[*m_current_train_kind_index], m_info_sets[*m_current_train_kind_index + 1]);
            ++(*m_current_train_kind_index);

            m_sync();
        }


    private:
        // variables

        std::vector<info_set_type>& m_info_sets;

        boost::optional<size_type>& m_current_train_kind_index;

        sync_type m_sync;


    };


    /*!
        \brief The class template for a change observer of the name text box.
    */
    class name_text_box_changed
    {
    public:
        // types

        //! The apply type.
        typedef std::function<void ()> apply_type;


        // constructors and destructor

        /*!
            \brief Create a change observer of the name text box.

            \param apply An apply function
        */
        explicit name_text_box_changed(const apply_type apply)
        :
        m_apply(apply)
        {}


        // functions

        /*!
            \brief Called when the name text box is changed.
        */
        void operator()()
        const
        {
            m_apply();
        }


    private:
        // variables

        apply_type m_apply;


    };


    /*!
        \brief The class template for a change observer of the abbreviation text box.
    */
    class abbreviation_text_box_changed
    {
    public:
        // types

        //! The apply type.
        typedef std::function<void ()> apply_type;


        // constructors and destructor

        /*!
            \brief Create a change observer of the abbreviation text box.

            \param apply An apply function
        */
        explicit abbreviation_text_box_changed(const apply_type apply)
        :
        m_apply(apply)
        {}


        // functions

        /*!
            \brief Called when the abbreviation text box is changed.
        */
        void operator()()
        const
        {
            m_apply();
        }


    private:
        // variables

        apply_type m_apply;


    };


    /*!
        \brief The class template for a mouse click observer of the color button.

        \tparam Dialog      A dialog type.
        \tparam ColorDialog A color dialog type.
    */
    template <typename Dialog, typename ColorDialog>
    class color_button_mouse_clicked
    {
    public:
        // types

        //! The dialog type.
        typedef Dialog dialog_type;

        //! The color dialog type.
        typedef ColorDialog color_dialog_type;

        //! The color type.
        typedef typename color_dialog_type::color_type color_type;

        //! The apply type.
        typedef std::function<void ()> apply_type;


        // constructors and destructor

        /*!
            \brief Creates a mouse click observer of the color button.

            \param dialog A dialog,
            \param color  A color.
            \param apply  An apply function.
        */
        color_button_mouse_clicked(dialog_type& dialog, color_type& color, const apply_type apply)
        :
        m_dialog(dialog),
        m_color(color),
        m_apply(apply)
        {}


        // functions

        /*!
            \brief Called when the font button is clicked.
        */
        void operator()()
        const
        {
            color_dialog_type color_dialog(m_color, m_dialog);

            const auto ok = color_dialog.do_modal();
            if (!ok)
                return;

            m_color = color_dialog.result();

            m_apply();
        }


    private:
        // variables

        dialog_type& m_dialog;

        color_type& m_color;

        apply_type m_apply;


    };


    /*!
        \brief The class template for a selection change observer of the weight dropdown box.
    */
    class weight_dropdown_box_selection_changed
    {
    public:
        // types

        //! The apply type.
        typedef std::function<void ()> apply_type;


        // constructors and destructor

        /*!
            \brief Create a selection change observer of the weight dropdown box.

            \param apply An apply function
        */
        explicit weight_dropdown_box_selection_changed(const apply_type apply)
        :
        m_apply(apply)
        {}


        // functions

        /*!
            \brief Called when the selection of the weight dropdown box is changed.
        */
        void operator()()
        const
        {
            m_apply();
        }


    private:
        // variables

        apply_type m_apply;


    };


    /*!
        \brief The class template for a selection change observer of the line style dropdown box.
    */
    class line_style_dropdown_box_selection_changed
    {
    public:
        // types

        //! The apply type.
        typedef std::function<void ()> apply_type;


        // constructors and destructor

        /*!
            \brief Create a selection change observer of the line style dropdown box.

            \param apply An apply function
        */
        explicit line_style_dropdown_box_selection_changed(const apply_type apply)
        :
        m_apply(apply)
        {}


        // functions

        /*!
            \brief Called when the selection of the line style dropdown box is changed.
        */
        void operator()()
        const
        {
            m_apply();
        }


    private:
        // variables

        apply_type m_apply;


    };


    /*!
        \brief The class template for a paint observer of the sample picture box.

        \tparam InfoSet An information set type.
        \tparam IntSize An integer size type.
        \tparam Canvas  A canvas type.
    */
    template <typename InfoSet, typename IntSize, typename Canvas>
    class sample_picture_box_paint
    {
    public:
        // types

        //! The information set type.
        typedef InfoSet info_set_type;

        //! The integer size type.
        typedef IntSize int_size_type;

        //! The canvas type.
        typedef Canvas canvas_type;

        //! The font type.
        typedef typename Canvas::font_type font_type;

        //! The color type.
        typedef typename Canvas::color_type color_type;

        //! The dimension type.
        typedef typename Canvas::dimension_type dimension_type;


        // constructors and destructor

        /*!
            \brief Creates a paint observer of the sample picture box.

            \param info_sets                Information sets.
            \param current_train_kind_index A current train kind index.
            \param font                     A font.
            \param background_color         A background color.
            \param canvas_dimension         A canvas dimension.
        */
        sample_picture_box_paint(
            const std::vector<info_set_type>&     info_sets,
            const boost::optional<int_size_type>& current_train_kind_index,
            const font_type&                      font,
            const color_type&                     background_color,
            const dimension_type&                 canvas_dimension
        )
        :
        m_info_sets(info_sets),
        m_current_train_kind_index(current_train_kind_index),
        m_font(font),
        m_background_color(background_color),
        m_canvas_dimension(canvas_dimension)
        {}


        // functions

        /*!
            \brief Called when the canvas needs to be repainted.

            \param canvas A canvas.
        */
        void operator()(canvas_type& canvas)
        const
        {
            auto p_background = tetengo2::make_unique<solid_background_type>(m_background_color);
            canvas.set_background(std::move(p_background));
            canvas.fill_rectangle(position_type(left_type(0), top_type(0)), m_canvas_dimension);

            if (!m_current_train_kind_index)
                return;

            const auto& train_kind = m_info_sets[*m_current_train_kind_index].train_kind();

            canvas.set_font(fixed_size_font(m_font));
            canvas.set_color(train_kind.color());

            const auto& text = train_kind.abbreviation().empty() ? train_kind.name() : train_kind.abbreviation();
            const std::pair<top_type, top_type> text_and_line_tops = sample_text_and_line_tops(canvas, text);
            canvas.draw_text(text, position_type(left_type(1), text_and_line_tops.first));

            auto line_width =
                train_kind.weight() == train_kind_type::weight_type::bold ?
                width_type(size_type(1, 6)) : width_type(size_type(1, 12));
            canvas.set_line_width(std::move(line_width));
            
            canvas.set_line_style(to_canvas_line_style(train_kind.line_style()));
            canvas.draw_line(
                position_type(left_type(0), text_and_line_tops.second),
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

        typedef typename info_set_type::train_kind_type train_kind_type;


        // static functions

        static font_type fixed_size_font(const font_type& base)
        {
            return
                font_type(
                    base.family(),
                    font_type::dialog_font().size(),
                    base.bold(),
                    base.italic(),
                    base.underline(),
                    base.strikeout()
                );
        }

        static typename canvas_type::line_style_type to_canvas_line_style(
            const typename train_kind_type::line_style_type line_style
        )
        {
            switch (line_style)
            {
            case train_kind_type::line_style_type::solid:
                return canvas_type::line_style_type::solid;
            case train_kind_type::line_style_type::dashed:
                return canvas_type::line_style_type::dashed;
            case train_kind_type::line_style_type::dotted:
                return canvas_type::line_style_type::dotted;
            case train_kind_type::line_style_type::dot_dashed:
                return canvas_type::line_style_type::dot_dashed;
            default:
                assert(false);
                BOOST_THROW_EXCEPTION(std::invalid_argument("Unknown line style."));
            }
        }


        // variables

        const std::vector<info_set_type>& m_info_sets;

        const boost::optional<int_size_type>& m_current_train_kind_index;

        const font_type& m_font;

        const color_type& m_background_color;

        const dimension_type m_canvas_dimension;


        // functions

        std::pair<top_type, top_type> sample_text_and_line_tops(const canvas_type& canvas, const string_type& text)
        const
        {
            const auto& canvas_height = tetengo2::gui::dimension<dimension_type>::height(m_canvas_dimension);
            const auto& text_height =
                tetengo2::gui::dimension<dimension_type>::height(canvas.calc_text_dimension(text));

            if (canvas_height > text_height)
            {
                const auto text_top = top_type::from((canvas_height - text_height) / 2);
                const auto line_top = text_top + top_type::from(text_height);
                return std::make_pair(text_top, line_top);
            }
            else
            {
                const auto line_top = top_type::from(canvas_height);
                const auto text_top = line_top - top_type::from(text_height);
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
