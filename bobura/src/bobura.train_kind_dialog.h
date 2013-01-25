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
        typename Button,
        typename PictureBox,
        typename Font,
        typename Color,
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

        //! The button type.
        typedef Button button_type;

        //! The picture box type.
        typedef PictureBox picture_box_type;

        //! The font type.
        typedef Font font_type;

        //! The color type.
        typedef Color color_type;

        //! The train kind type.
        typedef std::pair<const font_type&, const color_type&> font_color_type;

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
            set_text(m_message_catalog.get(TETENGO2_TEXT("Dialog:FontAndColor:Fonts And Colors")));

            m_p_ok_button = create_ok_button();
            m_p_cancel_button = create_cancel_button();

            locate_controls();
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
            this->set_client_dimension(dimension_type(width_type(46), height_type(22)));

            const left_type category_label_left(2);

            m_p_ok_button->set_dimension(dimension_type(width_type(8), height_type(2)));
            m_p_ok_button->set_position(position_type(left_type(27), top_type(19)));

            m_p_cancel_button->set_dimension(dimension_type(width_type(8), height_type(2)));
            m_p_cancel_button->set_position(position_type(left_type(36), top_type(19)));
        }


    };


}

#endif
