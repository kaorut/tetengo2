/*! \file
    \brief The definition of bobura::font_color_dialog.

    Copyright (C) 2007-2012 kaoru

    $Id$
*/

#if !defined(BOBURA_FONTCOLORDIALOG_H)
#define BOBURA_FONTCOLORDIALOG_H

//#include <memory>
#include <stdexcept>
//#include <utility>
#include <vector>

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
        \brief The class template for the font and color dialog.

        \tparam Dialog                         A dialog type.
        \tparam MessageCatalog                 A message catalog type.
        \tparam Label                          A label type.
        \tparam ListBox                        A list box type.
        \tparam TextBox                        A text box type.
        \tparam Button                         A button type.
        \tparam PictureBox                     A picture box type.
        \tparam Font                           A font type.
        \tparam Color                          A color type.
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
        typename Font,
        typename Color,
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

        //! The integer size type.
        typedef typename list_box_type::int_size_type int_size_type;

        //! The text box type.
        typedef TextBox text_box_type;

        //! The button type.
        typedef Button button_type;

        //! The picture box type.
        typedef PictureBox picture_box_type;

        //! The font type.
        typedef Font font_type;

        //! The color type.
        typedef Color color_type;

        typedef std::pair<const font_type&, const color_type&> font_color_type;

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
        m_font_color_list(9, internal_font_color_type(boost::none, boost::none)),
        m_current_category_index(),
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

        /*!
            \brief Returns the color of the background.

            \return The color of the background.

            \throw std::logic_error When the color has not been set.
        */
        const color_type& background()
        const
        {
            return to_color(m_font_color_list[0]);
        }

        /*!
            \brief Sets a color of the background.

            \param color A color.
        */
        void set_background(const color_type& color)
        {
            m_font_color_list[0] = internal_font_color_type(boost::none, boost::make_optional(color));
        }

        /*!
            \brief Returns the font and color of the company and the line names.

            \return The font and color of the company and the line names.

            \throw std::logic_error When the font and color have not been set.
        */
        font_color_type company_line_name()
        const
        {
            return to_font_color(m_font_color_list[1]);
        }

        /*!
            \brief Sets a font and color of the company and the line names.

            \param font  A font.
            \param color A color.
        */
        void set_company_line_name(const font_type& font, const color_type& color)
        {
            m_font_color_list[1] = internal_font_color_type(boost::make_optional(font), boost::make_optional(color));
        }

        /*!
            \brief Returns the font and color of the note.

            \return The font and color of the note.

            \throw std::logic_error When the font and color have not been set.
        */
        font_color_type note()
        const
        {
            return to_font_color(m_font_color_list[2]);
        }

        /*!
            \brief Sets a font and color of the note.

            \param font  A font.
            \param color A color.
        */
        void set_note(const font_type& font, const color_type& color)
        {
            m_font_color_list[2] = internal_font_color_type(boost::make_optional(font), boost::make_optional(color));
        }

        /*!
            \brief Returns the font and color of the time lines.

            \return The font and color of the time lines.

            \throw std::logic_error When the font and color have not been set.
        */
        font_color_type time_line()
        const
        {
            return to_font_color(m_font_color_list[3]);
        }

        /*!
            \brief Sets a font and color of the time lines.

            \param font  A font.
            \param color A color.
        */
        void set_time_line(const font_type& font, const color_type& color)
        {
            m_font_color_list[3] = internal_font_color_type(boost::make_optional(font), boost::make_optional(color));
        }

        /*!
            \brief Returns the font and color of the local stations.

            \return The font and color of the local stations.

            \throw std::logic_error When the font and color have not been set.
        */
        font_color_type local_station()
        const
        {
            return to_font_color(m_font_color_list[4]);
        }

        /*!
            \brief Sets a font and color of the local stations.

            \param font  A font.
            \param color A color.
        */
        void set_local_station(const font_type& font, const color_type& color)
        {
            m_font_color_list[4] = internal_font_color_type(boost::make_optional(font), boost::make_optional(color));
        }

        /*!
            \brief Returns the font and color of the principal stations.

            \return The font and color of the principal stations.

            \throw std::logic_error When the font and color have not been set.
        */
        font_color_type principal_station()
        const
        {
            return to_font_color(m_font_color_list[5]);
        }

        /*!
            \brief Sets a font and color of the principal stations.

            \param font  A font.
            \param color A color.
        */
        void set_principal_station(const font_type& font, const color_type& color)
        {
            m_font_color_list[5] = internal_font_color_type(boost::make_optional(font), boost::make_optional(color));
        }

        /*!
            \brief Returns the font and color of the local terminal stations.

            \return The font and color of the local terminal stations.

            \throw std::logic_error When the font and color have not been set.
        */
        font_color_type local_terminal_station()
        const
        {
            return to_font_color(m_font_color_list[6]);
        }

        /*!
            \brief Sets a font and color of the local terminal stations.

            \param font  A font.
            \param color A color.
        */
        void set_local_terminal_station(const font_type& font, const color_type& color)
        {
            m_font_color_list[6] = internal_font_color_type(boost::make_optional(font), boost::make_optional(color));
        }

        /*!
            \brief Returns the font and color of the principal terminal stations.

            \return The font and color of the principal terminal stations.

            \throw std::logic_error When the font and color have not been set.
        */
        font_color_type principal_terminal_station()
        const
        {
            return to_font_color(m_font_color_list[7]);
        }

        /*!
            \brief Sets a font and color of the principal terminal stations.

            \param font  A font.
            \param color A color.
        */
        void set_principal_terminal_station(const font_type& font, const color_type& color)
        {
            m_font_color_list[7] = internal_font_color_type(boost::make_optional(font), boost::make_optional(color));
        }

        /*!
            \brief Returns the font of the train names.

            \return The font of the train names.

            \throw std::logic_error When the font has not been set.
        */
        const font_type& train_name()
        const
        {
            return to_font(m_font_color_list[8]);
        }

        /*!
            \brief Sets a font of the train names.

            \param font  A font.
            \param color A color.
        */
        void set_train_name(const font_type& font)
        {
            m_font_color_list[8] = internal_font_color_type(boost::make_optional(font), boost::none);
        }


    private:
        // types

        typedef typename font_color_dialog::dimension_type dimension_type;

        typedef typename tetengo2::gui::dimension<dimension_type>::width_type width_type;

        typedef typename tetengo2::gui::dimension<dimension_type>::height_type height_type;

        typedef typename font_color_dialog::position_type position_type;

        typedef typename tetengo2::gui::position<position_type>::left_type left_type;

        typedef typename tetengo2::gui::position<position_type>::top_type top_type;

        typedef std::pair<boost::optional<font_type>, boost::optional<color_type>> internal_font_color_type;


        // static functions

        static const font_type& to_font(const internal_font_color_type& internal_font_color)
        {
            if (!internal_font_color.first)
                BOOST_THROW_EXCEPTION(std::logic_error("The font has not been set."));

            return *internal_font_color.first;
        }

        static const color_type& to_color(const internal_font_color_type& internal_font_color)
        {
            if (!internal_font_color.second)
                BOOST_THROW_EXCEPTION(std::logic_error("The color has not been set."));

            return *internal_font_color.second;
        }

        static font_color_type to_font_color(const internal_font_color_type& internal_font_color)
        {
            if (!internal_font_color.first || !internal_font_color.second)
                BOOST_THROW_EXCEPTION(std::logic_error("The font and/or the color have not been set."));

            return font_color_type(*internal_font_color.first, *internal_font_color.second);
        }


        // variables

        const message_catalog_type& m_message_catalog;

        std::vector<internal_font_color_type> m_font_color_list;

        boost::optional<int_size_type> m_current_category_index;

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

        virtual void do_modal_impl()
        {
            m_p_category_list_box->select_item(0);
            m_current_category_index = boost::make_optional<int_size_type>(0);
            update(boost::none);
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

            p_list_box->list_box_observer_set().selection_changed().connect(
                typename boost::mpl::at<
                    file_property_dialog_message_type_list_type,
                    message::font_color_dialog::type::category_list_box_selection_changed
                >::type(
                    m_current_category_index,
                    *p_list_box,
                    TETENGO2_CPP11_BIND(&font_color_dialog::update, this, tetengo2::cpp11::placeholders_1())
                )
            );

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

        void update(const boost::optional<int_size_type>& previous_category_index)
        {

        }


    };


}

#endif
