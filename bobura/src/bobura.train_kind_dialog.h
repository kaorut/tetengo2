/*! \file
    \brief The definition of bobura::train_kind_dialog.

    Copyright (C) 2007-2013 kaoru

    $Id$
*/

#if !defined(BOBURA_TRAINKINDDIALOG_H)
#define BOBURA_TRAINKINDDIALOG_H

//#include <memory>
#include <sstream>
#include <stdexcept>
//#include <utility>
#include <vector>

#include <boost/format.hpp>
#include <boost/mpl/at.hpp>
#include <boost/optional.hpp>
#include <boost/throw_exception.hpp>

#include <tetengo2.cpp11.h>
#include <tetengo2.gui.measure.h>
#include <tetengo2.text.h>
#include <tetengo2.unique.h>

#include "bobura.message.type_list.h"


namespace bobura
{
    /*!
        \brief The class template for the train kind dialog.

        \tparam Dialog                         A dialog type.
        \tparam MessageCatalog                 A message catalog type.
        \tparam Label                          A label type.
        \tparam ListBox                        A list box type.
        \tparam TextBox                        A text box type.
        \tparam DropdownBox                    A dropdown box type.
        \tparam Button                         A button type.
        \tparam PictureBox                     A picture box type.
        \tparam Font                           A font type.
        \tparam Color                          A color type.
        \tparam TransparentBackground          A transparent background type.
        \tparam TrainKindDialogMessageTypeList A message type list type.
    */
    template <
        typename Dialog,
        typename MessageCatalog,
        typename Label,
        typename ListBox,
        typename TextBox,
        typename DropdownBox,
        typename Button,
        typename PictureBox,
        typename TrainKind,
        typename TransparentBackground,
        typename TrainKindDialogMessageTypeList
    >
    class train_kind_dialog : public Dialog
    {
    public:
        // types

        //! The base type.
        typedef Dialog base_type;

        //! The abstract window type.
        typedef typename base_type::base_type abstract_window_type;

        //! The string type.
        typedef typename base_type::string_type string_type;

        //! The background type.
        typedef typename base_type::background_type background_type;

        //! The message catalog type.
        typedef MessageCatalog message_catalog_type;

        //! The label type.
        typedef Label label_type;

        //! The list box type.
        typedef ListBox list_box_type;

        //! The integer size type.
        typedef typename list_box_type::int_size_type int_size_type;

        //! The text box type.
        typedef TextBox text_box_type;

        //! The dropdown box type.
        typedef DropdownBox dropdown_box_type;

        //! The button type.
        typedef Button button_type;

        //! The picture box type.
        typedef PictureBox picture_box_type;

        //! The train kind type.
        typedef TrainKind train_kind_type;

        //! The transparent background type.
        typedef TransparentBackground transparent_background_type;

        //! The message type list type.
        typedef TrainKindDialogMessageTypeList train_kind_dialog_message_type_list_type;


        // constructors and destructor

        /*!
            \brief Creates a train kind dialog.

            \param parent          A parent window.
            \param message_catalog A message catalog.
        */
        train_kind_dialog(abstract_window_type& parent, const message_catalog_type& message_catalog)
        :
        base_type(parent),
        m_message_catalog(message_catalog),
        m_p_train_kind_label(),
        m_p_train_kind_list_box(),
        m_p_add_button(),
        m_p_delete_button(),
        m_p_up_button(),
        m_p_down_button(),
        m_p_name_label(),
        m_p_name_text_box(),
        m_p_abbreviation_label(),
        m_p_abbreviation_text_box(),
        m_p_color_button(),
        m_p_weight_label(),
        m_p_weight_dropdown_box(),
        m_p_line_style_label(),
        m_p_line_style_dropdown_box(),
        m_p_sample_picture_box(),
        m_p_apply_button(),
        m_p_ok_button(),
        m_p_cancel_button()
        {
            initialize_dialog(parent);
        }

        /*!
            \brief Destroys the train kind dialog.
        */
        virtual ~train_kind_dialog()
        TETENGO2_CPP11_NOEXCEPT
        {}


        // functions

        ///*!
        //    \brief Returns the font of the train names.

        //    \return The font of the train names.

        //    \throw std::logic_error When the font has not been set.
        //*/
        //const font_type& train_name()
        //const
        //{
        //    return to_font(m_font_color_list[8]);
        //}

        ///*!
        //    \brief Sets a font of the train names.

        //    \param font  A font.
        //*/
        //void set_train_name(const font_type& font)
        //{
        //    m_font_color_list[8] = internal_font_color_type(boost::make_optional(font), boost::none);
        //}


    private:
        // types

        typedef typename train_kind_dialog::dimension_type dimension_type;

        typedef typename tetengo2::gui::dimension<dimension_type>::width_type width_type;

        typedef typename tetengo2::gui::dimension<dimension_type>::height_type height_type;

        typedef typename train_kind_dialog::position_type position_type;

        typedef typename tetengo2::gui::position<position_type>::left_type left_type;

        typedef typename tetengo2::gui::position<position_type>::top_type top_type;



        // variables

        const message_catalog_type& m_message_catalog;

        std::unique_ptr<label_type> m_p_train_kind_label;

        std::unique_ptr<list_box_type> m_p_train_kind_list_box;

        std::unique_ptr<button_type> m_p_add_button;

        std::unique_ptr<button_type> m_p_delete_button;

        std::unique_ptr<button_type> m_p_up_button;

        std::unique_ptr<button_type> m_p_down_button;

        std::unique_ptr<label_type> m_p_name_label;

        std::unique_ptr<text_box_type> m_p_name_text_box;

        std::unique_ptr<label_type> m_p_abbreviation_label;

        std::unique_ptr<text_box_type> m_p_abbreviation_text_box;

        std::unique_ptr<button_type> m_p_color_button;

        std::unique_ptr<label_type> m_p_weight_label;

        std::unique_ptr<dropdown_box_type> m_p_weight_dropdown_box;

        std::unique_ptr<label_type> m_p_line_style_label;

        std::unique_ptr<dropdown_box_type> m_p_line_style_dropdown_box;

        std::unique_ptr<label_type> m_p_sample_label;

        std::unique_ptr<picture_box_type> m_p_sample_picture_box;

        std::unique_ptr<button_type> m_p_apply_button;

        std::unique_ptr<button_type> m_p_ok_button;

        std::unique_ptr<button_type> m_p_cancel_button;


        // virtual functions

        virtual void do_modal_impl()
        {
            //m_p_category_list_box->select_item(0);
            //m_current_category_index = boost::make_optional<int_size_type>(0);
            //update(boost::none);
        }


        // functions

        void initialize_dialog(const abstract_window_type& parent)
        {
            set_text(m_message_catalog.get(TETENGO2_TEXT("Dialog:TrainKind:Train Kinds")));

            m_p_train_kind_label = create_train_kind_label();
            m_p_train_kind_list_box = create_train_kind_list_box();
            m_p_add_button = create_add_button();
            m_p_delete_button = create_delete_button();
            m_p_up_button = create_up_button();
            m_p_down_button = create_down_button();
            m_p_name_label = create_name_label();
            m_p_name_text_box = create_name_text_box();
            m_p_abbreviation_label = create_abbreviation_label();
            m_p_abbreviation_text_box = create_abbreviation_text_box();
            m_p_color_button = create_color_button();
            m_p_weight_label = create_weight_label();
            m_p_weight_dropdown_box = create_weight_dropdown_box();
            m_p_line_style_label = create_line_style_label();
            m_p_line_style_dropdown_box = create_line_style_dropdown_box();
            m_p_sample_label = create_sample_label();
            m_p_sample_picture_box = create_sample_picture_box();
            m_p_apply_button = create_apply_button();
            m_p_ok_button = create_ok_button();
            m_p_cancel_button = create_cancel_button();

            locate_controls();
        }

        std::unique_ptr<label_type> create_train_kind_label()
        {
            std::unique_ptr<label_type> p_label = tetengo2::make_unique<label_type>(*this);

            p_label->set_text(m_message_catalog.get(TETENGO2_TEXT("Dialog:TrainKind:Train &Kinds:")));
            std::unique_ptr<background_type> p_background(tetengo2::make_unique<transparent_background_type>());
            p_label->set_background(std::move(p_background));

            return std::move(p_label);
        }

        std::unique_ptr<list_box_type> create_train_kind_list_box()
        {
            std::unique_ptr<list_box_type> p_list_box =
                tetengo2::make_unique<list_box_type>(*this, list_box_type::scroll_bar_style_type::vertical);

            //p_list_box->list_box_observer_set().selection_changed().connect(
            //    typename boost::mpl::at<
            //        font_color_dialog_message_type_list_type,
            //        message::font_color_dialog::type::category_list_box_selection_changed
            //    >::type(
            //        m_current_category_index,
            //        *p_list_box,
            //        TETENGO2_CPP11_BIND(&font_color_dialog::update, this, tetengo2::cpp11::placeholders_1())
            //    )
            //);

            return std::move(p_list_box);
        }

        std::unique_ptr<button_type> create_add_button()
        {
            std::unique_ptr<button_type> p_button = tetengo2::make_unique<button_type>(*this);

            p_button->set_text(m_message_catalog.get(TETENGO2_TEXT("Dialog:TrainKind:&Add")));
            //p_button->mouse_observer_set().clicked().connect(
            //    typename boost::mpl::at<
            //        train_kind_dialog_message_type_list_type,
            //        message::train_kind_dialog::type::ok_button_mouse_clicked
            //    >::type(*this)
            //);

            return std::move(p_button);
        }

        std::unique_ptr<button_type> create_delete_button()
        {
            std::unique_ptr<button_type> p_button = tetengo2::make_unique<button_type>(*this);

            p_button->set_text(m_message_catalog.get(TETENGO2_TEXT("Dialog:TrainKind:D&elete")));
            //p_button->mouse_observer_set().clicked().connect(
            //    typename boost::mpl::at<
            //        train_kind_dialog_message_type_list_type,
            //        message::train_kind_dialog::type::ok_button_mouse_clicked
            //    >::type(*this)
            //);

            return std::move(p_button);
        }

        std::unique_ptr<button_type> create_up_button()
        {
            std::unique_ptr<button_type> p_button = tetengo2::make_unique<button_type>(*this);

            p_button->set_text(m_message_catalog.get(TETENGO2_TEXT("Dialog:TrainKind:&Up")));
            //p_button->mouse_observer_set().clicked().connect(
            //    typename boost::mpl::at<
            //        train_kind_dialog_message_type_list_type,
            //        message::train_kind_dialog::type::ok_button_mouse_clicked
            //    >::type(*this)
            //);

            return std::move(p_button);
        }

        std::unique_ptr<button_type> create_down_button()
        {
            std::unique_ptr<button_type> p_button = tetengo2::make_unique<button_type>(*this);

            p_button->set_text(m_message_catalog.get(TETENGO2_TEXT("Dialog:TrainKind:&Down")));
            //p_button->mouse_observer_set().clicked().connect(
            //    typename boost::mpl::at<
            //        train_kind_dialog_message_type_list_type,
            //        message::train_kind_dialog::type::ok_button_mouse_clicked
            //    >::type(*this)
            //);

            return std::move(p_button);
        }

        std::unique_ptr<label_type> create_name_label()
        {
            std::unique_ptr<label_type> p_label = tetengo2::make_unique<label_type>(*this);

            p_label->set_text(m_message_catalog.get(TETENGO2_TEXT("Dialog:TrainKind:&Name:")));
            std::unique_ptr<background_type> p_background(tetengo2::make_unique<transparent_background_type>());
            p_label->set_background(std::move(p_background));

            return std::move(p_label);
        }

        std::unique_ptr<text_box_type> create_name_text_box()
        {
            std::unique_ptr<text_box_type> p_text_box =
                tetengo2::make_unique<text_box_type>(*this, list_box_type::scroll_bar_style_type::none);

            return std::move(p_text_box);
        }

        std::unique_ptr<label_type> create_abbreviation_label()
        {
            std::unique_ptr<label_type> p_label = tetengo2::make_unique<label_type>(*this);

            p_label->set_text(m_message_catalog.get(TETENGO2_TEXT("Dialog:TrainKind:A&bbreviation:")));
            std::unique_ptr<background_type> p_background(tetengo2::make_unique<transparent_background_type>());
            p_label->set_background(std::move(p_background));

            return std::move(p_label);
        }

        std::unique_ptr<text_box_type> create_abbreviation_text_box()
        {
            std::unique_ptr<text_box_type> p_text_box =
                tetengo2::make_unique<text_box_type>(*this, list_box_type::scroll_bar_style_type::none);

            return std::move(p_text_box);
        }

        std::unique_ptr<button_type> create_color_button()
        {
            std::unique_ptr<button_type> p_button = tetengo2::make_unique<button_type>(*this);

            p_button->set_text(m_message_catalog.get(TETENGO2_TEXT("Dialog:TrainKind:&Color...")));
            //p_button->mouse_observer_set().clicked().connect(
            //    typename boost::mpl::at<
            //        train_kind_dialog_message_type_list_type,
            //        message::train_kind_dialog::type::ok_button_mouse_clicked
            //    >::type(*this)
            //);

            return std::move(p_button);
        }

        std::unique_ptr<label_type> create_weight_label()
        {
            std::unique_ptr<label_type> p_label = tetengo2::make_unique<label_type>(*this);

            p_label->set_text(m_message_catalog.get(TETENGO2_TEXT("Dialog:TrainKind:Line &Weight:")));
            std::unique_ptr<background_type> p_background(tetengo2::make_unique<transparent_background_type>());
            p_label->set_background(std::move(p_background));

            return std::move(p_label);
        }

        std::unique_ptr<dropdown_box_type> create_weight_dropdown_box()
        {
            std::unique_ptr<dropdown_box_type> p_dropdown_box = tetengo2::make_unique<dropdown_box_type>(*this);

            p_dropdown_box->insert_item(
                p_dropdown_box->item_count(), m_message_catalog.get(TETENGO2_TEXT("Dialog:TrainKind:Normal"))
            );
            p_dropdown_box->insert_item(
                p_dropdown_box->item_count(), m_message_catalog.get(TETENGO2_TEXT("Dialog:TrainKind:Bold"))
            );

            return std::move(p_dropdown_box);
        }

        std::unique_ptr<label_type> create_line_style_label()
        {
            std::unique_ptr<label_type> p_label = tetengo2::make_unique<label_type>(*this);

            p_label->set_text(m_message_catalog.get(TETENGO2_TEXT("Dialog:TrainKind:Line &Style:")));
            std::unique_ptr<background_type> p_background(tetengo2::make_unique<transparent_background_type>());
            p_label->set_background(std::move(p_background));

            return std::move(p_label);
        }

        std::unique_ptr<dropdown_box_type> create_line_style_dropdown_box()
        {
            std::unique_ptr<dropdown_box_type> p_dropdown_box = tetengo2::make_unique<dropdown_box_type>(*this);

            p_dropdown_box->insert_item(
                p_dropdown_box->item_count(), m_message_catalog.get(TETENGO2_TEXT("Dialog:TrainKind:Solid"))
            );
            p_dropdown_box->insert_item(
                p_dropdown_box->item_count(), m_message_catalog.get(TETENGO2_TEXT("Dialog:TrainKind:Dashed"))
            );
            p_dropdown_box->insert_item(
                p_dropdown_box->item_count(), m_message_catalog.get(TETENGO2_TEXT("Dialog:TrainKind:Dotted"))
            );
            p_dropdown_box->insert_item(
                p_dropdown_box->item_count(), m_message_catalog.get(TETENGO2_TEXT("Dialog:TrainKind:Dot-Dashed"))
            );

            return std::move(p_dropdown_box);
        }

        std::unique_ptr<label_type> create_sample_label()
        {
            std::unique_ptr<label_type> p_label = tetengo2::make_unique<label_type>(*this);

            p_label->set_text(m_message_catalog.get(TETENGO2_TEXT("Dialog:TrainKind:Sa&mple:")));
            std::unique_ptr<background_type> p_background(tetengo2::make_unique<transparent_background_type>());
            p_label->set_background(std::move(p_background));

            return std::move(p_label);
        }

        std::unique_ptr<picture_box_type> create_sample_picture_box()
        {
            std::unique_ptr<picture_box_type> p_picture_box =
                tetengo2::make_unique<picture_box_type>(*this, list_box_type::scroll_bar_style_type::none);

            //p_picture_box->fast_paint_observer_set().paint().connect(
            //    typename boost::mpl::at<
            //        font_color_dialog_message_type_list_type,
            //        message::font_color_dialog::type::sample_picture_box_paint
            //    >::type(
            //        m_font_color_list, m_current_category_index, p_picture_box->client_dimension(), m_message_catalog
            //    )
            //);

            return std::move(p_picture_box);
        }

        std::unique_ptr<button_type> create_apply_button()
        {
            std::unique_ptr<button_type> p_button = tetengo2::make_unique<button_type>(*this);

            p_button->set_text(m_message_catalog.get(TETENGO2_TEXT("Dialog:TrainKind:A&pply")));
            //p_button->mouse_observer_set().clicked().connect(
            //    typename boost::mpl::at<
            //        train_kind_dialog_message_type_list_type,
            //        message::train_kind_dialog::type::ok_button_mouse_clicked
            //    >::type(*this)
            //);

            return std::move(p_button);
        }

        std::unique_ptr<button_type> create_ok_button()
        {
            std::unique_ptr<button_type> p_button =
                tetengo2::make_unique<button_type>(*this, button_type::style_type::default_);

            p_button->set_text(m_message_catalog.get(TETENGO2_TEXT("Common:OK")));
            p_button->mouse_observer_set().clicked().connect(
                typename boost::mpl::at<
                    train_kind_dialog_message_type_list_type,
                    message::train_kind_dialog::type::ok_button_mouse_clicked
                >::type(*this)
            );

            return std::move(p_button);
        }

        std::unique_ptr<button_type> create_cancel_button()
        {
            std::unique_ptr<button_type> p_button =
                tetengo2::make_unique<button_type>(*this, button_type::style_type::cancel);

            p_button->set_text(m_message_catalog.get(TETENGO2_TEXT("Common:Cancel")));
            p_button->mouse_observer_set().clicked().connect(
                typename boost::mpl::at<
                    train_kind_dialog_message_type_list_type,
                    message::train_kind_dialog::type::cancel_button_mouse_clicked
                >::type(*this)
            );

            return std::move(p_button);
        }

        void locate_controls()
        {
            this->set_client_dimension(dimension_type(width_type(46), height_type(28)));

            const left_type train_kind_label_left(2);

            m_p_train_kind_label->fit_to_content();
            m_p_train_kind_label->set_position(position_type(train_kind_label_left, top_type(1)));

            const width_type list_box_width(20);
            const height_type list_box_height(19);
            m_p_train_kind_list_box->set_dimension(dimension_type(list_box_width, list_box_height));
            m_p_train_kind_list_box->set_position(
                position_type(
                    train_kind_label_left,
                    tetengo2::gui::position<position_type>::top(m_p_train_kind_label->position()) +
                        top_type::from(
                            tetengo2::gui::dimension<dimension_type>::height(m_p_train_kind_label->dimension())
                        )
                )
            );

            const width_type list_box_button_width(typename width_type::value_type(9, 2));
            left_type list_box_button_left(
                train_kind_label_left + left_type::from(list_box_width) - left_type::from(list_box_button_width)
            );
            const top_type list_box_button_top(
                tetengo2::gui::position<position_type>::top(m_p_train_kind_list_box->position()) +
                    top_type::from(list_box_height)
            );
            m_p_down_button->set_dimension(dimension_type(list_box_button_width, height_type(2)));
            m_p_down_button->set_position(position_type(list_box_button_left, list_box_button_top));

            list_box_button_left -=
                left_type::from(list_box_button_width) + left_type(typename left_type::value_type(1, 4));
            m_p_up_button->set_dimension(dimension_type(list_box_button_width, height_type(2)));
            m_p_up_button->set_position(position_type(list_box_button_left, list_box_button_top));

            list_box_button_left -=
                left_type::from(list_box_button_width) + left_type(typename left_type::value_type(1, 2));
            m_p_delete_button->set_dimension(dimension_type(list_box_button_width, height_type(2)));
            m_p_delete_button->set_position(position_type(list_box_button_left, list_box_button_top));

            list_box_button_left -=
                left_type::from(list_box_button_width) + left_type(typename left_type::value_type(1, 4));
            m_p_add_button->set_dimension(dimension_type(list_box_button_width, height_type(2)));
            m_p_add_button->set_position(position_type(list_box_button_left, list_box_button_top));

            const left_type name_label_left(24);
            m_p_name_label->fit_to_content();
            m_p_name_label->set_position(position_type(name_label_left, top_type(1)));

            const left_type name_text_box_left(32);
            m_p_name_text_box->set_dimension(dimension_type(width_type(12), height_type(2)));
            m_p_name_text_box->set_position(position_type(name_text_box_left, top_type(1)));

            m_p_abbreviation_label->fit_to_content();
            m_p_abbreviation_label->set_position(position_type(name_label_left, top_type(4)));

            m_p_abbreviation_text_box->set_dimension(dimension_type(width_type(12), height_type(2)));
            m_p_abbreviation_text_box->set_position(position_type(name_text_box_left, top_type(4)));

            m_p_color_button->set_dimension(dimension_type(width_type(8), height_type(2)));
            m_p_color_button->set_position(position_type(name_text_box_left, top_type(7)));

            m_p_weight_label->fit_to_content();
            m_p_weight_label->set_position(position_type(name_label_left, top_type(10)));

            m_p_weight_dropdown_box->set_dimension(dimension_type(width_type(12), height_type(2)));
            m_p_weight_dropdown_box->set_position(position_type(name_text_box_left, top_type(10)));

            m_p_line_style_label->fit_to_content();
            m_p_line_style_label->set_position(position_type(name_label_left, top_type(13)));

            m_p_line_style_dropdown_box->set_dimension(dimension_type(width_type(12), height_type(2)));
            m_p_line_style_dropdown_box->set_position(position_type(name_text_box_left, top_type(13)));

            m_p_sample_label->fit_to_content();
            m_p_sample_label->set_position(position_type(name_label_left, top_type(16)));

            m_p_sample_picture_box->set_dimension(dimension_type(width_type(20), height_type(3)));
            m_p_sample_picture_box->set_position(
                position_type(
                    name_label_left,
                    tetengo2::gui::position<position_type>::top(m_p_sample_label->position()) +
                        top_type::from(tetengo2::gui::dimension<dimension_type>::height(m_p_sample_label->dimension()))
                )
            );

            m_p_apply_button->set_dimension(dimension_type(width_type(8), height_type(2)));
            m_p_apply_button->set_position(position_type(left_type(36), top_type(21)));

            m_p_ok_button->set_dimension(dimension_type(width_type(8), height_type(2)));
            m_p_ok_button->set_position(position_type(left_type(27), top_type(25)));

            m_p_cancel_button->set_dimension(dimension_type(width_type(8), height_type(2)));
            m_p_cancel_button->set_position(position_type(left_type(36), top_type(25)));
        }


    };


}

#endif
