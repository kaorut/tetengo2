/*! \file
    \brief The definition of bobura::file_property_dialog.

    Copyright (C) 2007-2012 kaoru

    $Id$
*/

#if !defined(BOBURA_FILEPROPERTYDIALOG_H)
#define BOBURA_FILEPROPERTYDIALOG_H

//#include <memory>
#include <sstream>
//#include <utility>

#include <boost/format.hpp>
#include <boost/mpl/at.hpp>

#include <tetengo2.gui.measure.h>
#include <tetengo2.text.h>
#include <tetengo2.unique.h>

#include "bobura.message.type_list.h"


namespace bobura
{
    /*!
        \brief The class template for the file property dialog.

        \tparam Dialog                            A dialog type.
        \tparam MessageCatalog                    A message catalog type.
        \tparam Label                             A label type.
        \tparam TextBox                           A text box type.
        \tparam Button                            A button type.
        \tparam TransparentBackground             A transparent background
                                                  type.
        \tparam FilePropertyDialogMessageTypeList A message type.
    */
    template <
        typename Dialog,
        typename MessageCatalog,
        typename Label,
        typename TextBox,
        typename Button,
        typename TransparentBackground,
        typename FilePropertyDialogMessageTypeList
    >
    class file_property_dialog : public Dialog
    {
    public:
        // types

        //! The base type.
        typedef Dialog base_type;

        //! The abstract window type.
        typedef typename base_type::base_type abstract_window_type;

        //! The background type.
        typedef typename base_type::background_type background_type;

        //! The message catalog type.
        typedef MessageCatalog message_catalog_type;

        //! The label type.
        typedef Label label_type;

        //! The text box type.
        typedef TextBox text_box_type;

        //! The button type.
        typedef Button button_type;

        //! The transparent background type.
        typedef TransparentBackground transparent_background_type;

        //! The message type list type.
        typedef
            FilePropertyDialogMessageTypeList
            file_property_dialog_message_type_list_type;


        // constructors and destructor

        /*!
            \brief Creates a file property dialog.

            \param parent          A parent window.
            \param message_catalog A message catalog.
        */
        file_property_dialog(
            abstract_window_type&       parent,
            const message_catalog_type& message_catalog
        )
        :
        base_type(parent),
        m_message_catalog(message_catalog),
        m_p_line_name_label(),
        m_p_line_name_text_box(),
        m_p_file_name_label(),
        m_p_file_name_text_box(),
        m_p_ok_button(),
        m_p_cancel_button()
        {
            initialize_dialog(parent);
        }

        /*!
            \brief Destroys the file property dialog.
        */
        virtual ~file_property_dialog()
        TETENGO2_CPP11_NOEXCEPT
        {}


    private:
        // types

        typedef typename file_property_dialog::dimension_type dimension_type;

        typedef
            typename tetengo2::gui::dimension<dimension_type>::width_type
            width_type;

        typedef
            typename tetengo2::gui::dimension<dimension_type>::height_type
            height_type;

        typedef typename file_property_dialog::position_type position_type;

        typedef
            typename tetengo2::gui::position<position_type>::left_type
            left_type;

        typedef
            typename tetengo2::gui::position<position_type>::top_type
            top_type;


        // variables

        const message_catalog_type& m_message_catalog;

        std::unique_ptr<label_type> m_p_line_name_label;

        std::unique_ptr<text_box_type> m_p_line_name_text_box;

        std::unique_ptr<label_type> m_p_file_name_label;

        std::unique_ptr<text_box_type> m_p_file_name_text_box;

        std::unique_ptr<button_type> m_p_ok_button;

        std::unique_ptr<button_type> m_p_cancel_button;


        // functions

        void initialize_dialog(const abstract_window_type& parent)
        {
            set_text(
                m_message_catalog.get(
                    TETENGO2_TEXT("Dialog:FileProperty:File Property")
                )
            );

            this->set_client_dimension(
                dimension_type(width_type(36), height_type(13))
            );

            m_p_line_name_label = create_line_name_label();
            m_p_line_name_text_box = create_line_name_text_box();
            m_p_file_name_label = create_file_name_label();
            m_p_file_name_text_box = create_file_name_text_box();
            m_p_ok_button = create_ok_button();
            m_p_cancel_button = create_cancel_button();

            locate_controls();
        }

        std::unique_ptr<label_type> create_line_name_label()
        {
            std::unique_ptr<label_type> p_label(
                tetengo2::make_unique<label_type>(*this)
            );

            p_label->set_text(
                m_message_catalog.get(
                    TETENGO2_TEXT("Dialog:FileProperty:&Line Name:")
                )
            );
            std::unique_ptr<background_type> p_background(
                tetengo2::make_unique<transparent_background_type>()
            );
            p_label->set_background(std::move(p_background));

            return std::move(p_label);
        }

        std::unique_ptr<text_box_type> create_line_name_text_box()
        {
            std::unique_ptr<text_box_type> p_text_box(
                tetengo2::make_unique<text_box_type>(*this)
            );

            return std::move(p_text_box);
        }

        std::unique_ptr<label_type> create_file_name_label()
        {
            std::unique_ptr<label_type> p_label(
                tetengo2::make_unique<label_type>(*this)
            );

            p_label->set_text(
                m_message_catalog.get(
                    TETENGO2_TEXT("Dialog:FileProperty:&File Name:")
                )
            );
            std::unique_ptr<background_type> p_background(
                tetengo2::make_unique<transparent_background_type>()
            );
            p_label->set_background(std::move(p_background));

            return std::move(p_label);
        }

        std::unique_ptr<text_box_type> create_file_name_text_box()
        {
            std::unique_ptr<text_box_type> p_text_box(
                tetengo2::make_unique<text_box_type>(*this)
            );

            return std::move(p_text_box);
        }

        std::unique_ptr<button_type> create_ok_button()
        {
            std::unique_ptr<button_type> p_button(
                tetengo2::make_unique<button_type>(
                    *this, button_type::style_default
                )
            );

            p_button->set_text(
                m_message_catalog.get(TETENGO2_TEXT("Common:OK"))
            );
            p_button->mouse_observer_set().clicked().connect(
                typename boost::mpl::at<
                    file_property_dialog_message_type_list_type,
                    message::file_property_dialog::type::ok_button_mouse
                >::type(*this)
            );

            return std::move(p_button);
        }

        std::unique_ptr<button_type> create_cancel_button()
        {
            std::unique_ptr<button_type> p_button(
                tetengo2::make_unique<button_type>(
                    *this, button_type::style_cancel
                )
            );

            p_button->set_text(
                m_message_catalog.get(TETENGO2_TEXT("Common:Cancel"))
            );
            //p_button->mouse_observer_set().clicked().connect(
            //    typename boost::mpl::at<
            //        file_property_dialog_message_type_list_type,
            //        message::file_property_dialog::type::ok_button_mouse
            //    >::type(*this)
            //);

            return std::move(p_button);
        }

        void locate_controls()
        {
            const left_type label_left(2);

            m_p_line_name_label->fit_to_content();
            m_p_line_name_label->set_position(
                position_type(label_left, top_type(1))
            );

            m_p_line_name_text_box->set_dimension(
                dimension_type(width_type(32), height_type(2))
            );
            m_p_line_name_text_box->set_position(
                position_type(
                    label_left,
                    m_p_line_name_label->position().second +
                        m_p_line_name_label->dimension().second
                )
            );

            m_p_file_name_label->fit_to_content();
            m_p_file_name_label->set_position(
                position_type(label_left, top_type(5))
            );

            m_p_file_name_text_box->set_dimension(
                dimension_type(width_type(32), height_type(2))
            );
            m_p_file_name_text_box->set_position(
                position_type(
                    label_left,
                    m_p_file_name_label->position().second +
                        m_p_file_name_label->dimension().second
                )
            );

            m_p_ok_button->set_dimension(
                dimension_type(width_type(8), height_type(2))
            );
            m_p_ok_button->set_position(
                position_type(left_type(17), top_type(10))
            );

            m_p_cancel_button->set_dimension(
                dimension_type(width_type(8), height_type(2))
            );
            m_p_cancel_button->set_position(
                position_type(left_type(26), top_type(10))
            );
        }


    };


}

#endif
