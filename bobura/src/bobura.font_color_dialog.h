/*! \file
    \brief The definition of bobura::font_color_dialog.

    Copyright (C) 2007-2012 kaoru

    $Id$
*/

#if !defined(BOBURA_FONTCOLORDIALOG_H)
#define BOBURA_FONTCOLORDIALOG_H

//#include <memory>
//#include <utility>

#include <boost/mpl/at.hpp>

#include <tetengo2.gui.measure.h>
#include <tetengo2.text.h>
#include <tetengo2.unique.h>

#include "bobura.message.type_list.h"


namespace bobura
{
    /*!
        \brief The class template for the font and color dialog.

        \tparam Dialog                         A dialog type.
        \tparam MessageCatalog                 A message catalog type.
        \tparam Label                          A label type.
        \tparam ListBox                        A list box type.
        \tparam TextBox                        A text box type.
        \tparam Button                         A button type.
        \tparam PictureBox                     A picture box type.
        \tparam TransparentBackground          A transparent background type.
        \tparam FontColorDialogMessageTypeList A message type.
    */
    template <
        typename Dialog,
        typename MessageCatalog,
        typename Label,
        typename ListBox,
        typename TextBox,
        typename Button,
        typename PictureBox,
        typename TransparentBackground,
        typename FontColorDialogMessageTypeList
    >
    class font_color_dialog : public Dialog
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

        //! The text box type.
        typedef TextBox text_box_type;

        //! The button type.
        typedef Button button_type;

        //! The picture box type.
        typedef PictureBox picture_box_type;

        //! The transparent background type.
        typedef TransparentBackground transparent_background_type;

        //! The message type list type.
        typedef FontColorDialogMessageTypeList file_property_dialog_message_type_list_type;


        // constructors and destructor

        /*!
            \brief Creates a font and color dialog.

            \param parent          A parent window.
            \param message_catalog A message catalog.
        */
        font_color_dialog(abstract_window_type& parent, const message_catalog_type& message_catalog)
        :
        base_type(parent),
        m_message_catalog(message_catalog),
        //m_company_name(),
        m_p_category_label(),
        m_p_category_list_box(),
        m_p_font_text_box(),
        m_p_font_button(),
        m_p_color_button(),
        m_p_sample_label(),
        m_p_sample_picture_box(),
        m_p_ok_button(),
        m_p_cancel_button()
        {
            initialize_dialog(parent);
        }

        /*!
            \brief Destroys the font and color dialog.
        */
        virtual ~font_color_dialog()
        {}


        // functions

        ///*!
        //    \brief Returns the company name.

        //    \return The company name.
        //*/
        //const string_type& company_name()
        //const
        //{
        //    return m_company_name;
        //}

        ///*!
        //    \brief Sets a company name.

        //    \tparam S A string type.

        //    \param company_name A company name.
        //*/
        //template <typename S>
        //void set_company_name(S&& company_name)
        //{
        //    m_company_name = std::forward<S>(company_name);
        //    if (!m_p_category_list_box->destroyed())
        //        m_p_category_list_box->set_text(m_company_name);
        //}


    private:
        // types

        typedef typename font_color_dialog::dimension_type dimension_type;

        typedef typename tetengo2::gui::dimension<dimension_type>::width_type width_type;

        typedef typename tetengo2::gui::dimension<dimension_type>::height_type height_type;

        typedef typename font_color_dialog::position_type position_type;

        typedef typename tetengo2::gui::position<position_type>::left_type left_type;

        typedef typename tetengo2::gui::position<position_type>::top_type top_type;


        // variables

        const message_catalog_type& m_message_catalog;

        //string_type m_company_name;

        std::unique_ptr<label_type> m_p_category_label;

        std::unique_ptr<list_box_type> m_p_category_list_box;

        std::unique_ptr<text_box_type> m_p_font_text_box;

        std::unique_ptr<button_type> m_p_font_button;

        std::unique_ptr<button_type> m_p_color_button;

        std::unique_ptr<label_type> m_p_sample_label;

        std::unique_ptr<picture_box_type> m_p_sample_picture_box;

        std::unique_ptr<button_type> m_p_ok_button;

        std::unique_ptr<button_type> m_p_cancel_button;


        // virtual functions

        virtual void set_result_impl()
        {
            //m_company_name = m_p_category_list_box->text();
        }


        // functions

        void initialize_dialog(const abstract_window_type& parent)
        {
            set_text(m_message_catalog.get(TETENGO2_TEXT("Dialog:FontAndColor:Fonts And Colors")));

            m_p_category_label = create_category_label();
            m_p_category_list_box = create_category_list_box();
            m_p_font_text_box = create_font_text_box();
            m_p_font_button = create_font_button();
            m_p_color_button = create_color_button();
            m_p_sample_label = create_sample_label();
            m_p_sample_picture_box = create_sample_picture_box();
            m_p_ok_button = create_ok_button();
            m_p_cancel_button = create_cancel_button();

            locate_controls();

            insert_category_list_box_items();
        }

        std::unique_ptr<label_type> create_category_label()
        {
            std::unique_ptr<label_type> p_label = tetengo2::make_unique<label_type>(*this);

            p_label->set_text(m_message_catalog.get(TETENGO2_TEXT("Dialog:FontAndColor:C&ategories:")));
            std::unique_ptr<background_type> p_background(tetengo2::make_unique<transparent_background_type>());
            p_label->set_background(std::move(p_background));

            return std::move(p_label);
        }

        std::unique_ptr<list_box_type> create_category_list_box()
        {
            std::unique_ptr<list_box_type> p_list_box =
                tetengo2::make_unique<list_box_type>(*this, list_box_type::scroll_bar_style_type::vertical);

            return std::move(p_list_box);
        }

        std::unique_ptr<text_box_type> create_font_text_box()
        {
            std::unique_ptr<text_box_type> p_text_box =
                tetengo2::make_unique<text_box_type>(*this, list_box_type::scroll_bar_style_type::none);

            p_text_box->set_read_only(true);

            return std::move(p_text_box);
        }

        std::unique_ptr<button_type> create_font_button()
        {
            std::unique_ptr<button_type> p_button =
                tetengo2::make_unique<button_type>(*this, button_type::style_type::normal);

            p_button->set_text(m_message_catalog.get(TETENGO2_TEXT("Dialog:FontAndColor:&Font...")));
            //p_button->mouse_observer_set().clicked().connect(
            //    typename boost::mpl::at<
            //        file_property_dialog_message_type_list_type,
            //        message::font_color_dialog::type::ok_button_mouse_clicked
            //    >::type(*this)
            //);

            return std::move(p_button);
        }

        std::unique_ptr<button_type> create_color_button()
        {
            std::unique_ptr<button_type> p_button =
                tetengo2::make_unique<button_type>(*this, button_type::style_type::normal);

            p_button->set_text(m_message_catalog.get(TETENGO2_TEXT("Dialog:FontAndColor:&Color...")));
            //p_button->mouse_observer_set().clicked().connect(
            //    typename boost::mpl::at<
            //        file_property_dialog_message_type_list_type,
            //        message::font_color_dialog::type::ok_button_mouse_clicked
            //    >::type(*this)
            //);

            return std::move(p_button);
        }

        std::unique_ptr<label_type> create_sample_label()
        {
            std::unique_ptr<label_type> p_label = tetengo2::make_unique<label_type>(*this);

            p_label->set_text(m_message_catalog.get(TETENGO2_TEXT("Dialog:FontAndColor:&Sample:")));
            std::unique_ptr<background_type> p_background(tetengo2::make_unique<transparent_background_type>());
            p_label->set_background(std::move(p_background));

            return std::move(p_label);
        }

        std::unique_ptr<picture_box_type> create_sample_picture_box()
        {
            std::unique_ptr<picture_box_type> p_picture_box =
                tetengo2::make_unique<picture_box_type>(*this, list_box_type::scroll_bar_style_type::none);

            return std::move(p_picture_box);
        }

        std::unique_ptr<button_type> create_ok_button()
        {
            std::unique_ptr<button_type> p_button =
                tetengo2::make_unique<button_type>(*this, button_type::style_type::default_);

            p_button->set_text(m_message_catalog.get(TETENGO2_TEXT("Common:OK")));
            p_button->mouse_observer_set().clicked().connect(
                typename boost::mpl::at<
                    file_property_dialog_message_type_list_type,
                    message::font_color_dialog::type::ok_button_mouse_clicked
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
                    file_property_dialog_message_type_list_type,
                    message::font_color_dialog::type::cancel_button_mouse_clicked
                >::type(*this)
            );

            return std::move(p_button);
        }

        void locate_controls()
        {
            this->set_client_dimension(dimension_type(width_type(46), height_type(22)));

            const left_type category_label_left(2);

            m_p_category_label->fit_to_content();
            m_p_category_label->set_position(position_type(category_label_left, top_type(1)));

            m_p_category_list_box->set_dimension(dimension_type(width_type(16), height_type(16)));
            m_p_category_list_box->set_position(
                position_type(
                    category_label_left,
                    tetengo2::gui::position<position_type>::top(m_p_category_label->position()) +
                        top_type::from(
                            tetengo2::gui::dimension<dimension_type>::height(m_p_category_label->dimension())
                        )
                )
            );

            const left_type font_text_box_left(20);
            
            m_p_font_text_box->set_dimension(dimension_type(width_type(16), height_type(2)));
            m_p_font_text_box->set_position(position_type(font_text_box_left, top_type(2)));

            m_p_font_button->set_dimension(dimension_type(width_type(8), height_type(2)));
            m_p_font_button->set_position(position_type(font_text_box_left + left_type(16), top_type(2)));

            m_p_color_button->set_dimension(dimension_type(width_type(8), height_type(2)));
            m_p_color_button->set_position(position_type(font_text_box_left + left_type(16), top_type(5)));

            m_p_sample_label->fit_to_content();
            m_p_sample_label->set_position(position_type(font_text_box_left, top_type(8)));

            m_p_sample_picture_box->set_dimension(dimension_type(width_type(24), height_type(8)));
            m_p_sample_picture_box->set_position(
                position_type(
                    font_text_box_left,
                    tetengo2::gui::position<position_type>::top(m_p_sample_label->position()) +
                        top_type::from(
                            tetengo2::gui::dimension<dimension_type>::height(m_p_sample_label->dimension())
                        )
                )
            );

            m_p_ok_button->set_dimension(dimension_type(width_type(8), height_type(2)));
            m_p_ok_button->set_position(position_type(left_type(27), top_type(19)));

            m_p_cancel_button->set_dimension(dimension_type(width_type(8), height_type(2)));
            m_p_cancel_button->set_position(position_type(left_type(36), top_type(19)));
        }

        void insert_category_list_box_items()
        {
            m_p_category_list_box->insert_item(
                m_p_category_list_box->item_count(),
                m_message_catalog.get(TETENGO2_TEXT("Dialog:FontAndColor:Background"))
            );
            m_p_category_list_box->insert_item(
                m_p_category_list_box->item_count(),
                m_message_catalog.get(TETENGO2_TEXT("Dialog:FontAndColor:Company and Line Names"))
            );
            m_p_category_list_box->insert_item(
                m_p_category_list_box->item_count(),
                m_message_catalog.get(TETENGO2_TEXT("Dialog:FontAndColor:Note"))
            );
            m_p_category_list_box->insert_item(
                m_p_category_list_box->item_count(),
                m_message_catalog.get(TETENGO2_TEXT("Dialog:FontAndColor:Time Lines"))
            );
            m_p_category_list_box->insert_item(
                m_p_category_list_box->item_count(),
                m_message_catalog.get(TETENGO2_TEXT("Dialog:FontAndColor:Local Stations"))
            );
            m_p_category_list_box->insert_item(
                m_p_category_list_box->item_count(),
                m_message_catalog.get(TETENGO2_TEXT("Dialog:FontAndColor:Principal Stations"))
            );
            m_p_category_list_box->insert_item(
                m_p_category_list_box->item_count(),
                m_message_catalog.get(TETENGO2_TEXT("Dialog:FontAndColor:Local Terminal Stations"))
            );
            m_p_category_list_box->insert_item(
                m_p_category_list_box->item_count(),
                m_message_catalog.get(TETENGO2_TEXT("Dialog:FontAndColor:Principal Terminal Stations"))
            );
            m_p_category_list_box->insert_item(
                m_p_category_list_box->item_count(),
                m_message_catalog.get(TETENGO2_TEXT("Dialog:FontAndColor:Train Names"))
            );
        }


    };


}

#endif
