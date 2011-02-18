/*! \file
    \brief The definition of bobura::about_dialog.

    Copyright (C) 2007-2011 kaoru

    $Id$
*/

#if !defined(BOBURA_ABOUTDIALOG_H)
#define BOBURA_ABOUTDIALOG_H

#include <sstream>
//#include <utility>

#include <boost/format.hpp>
#include <boost/mpl/at.hpp>

#include <tetengo2.cpp0x_keyword.h>
#include <tetengo2.gui.measure.h>
#include <tetengo2.text.h>

#include "bobura.message.type_list.h"


namespace bobura
{
    /*!
        \brief The class template for the about dialog.

        \tparam Dialog                     A dialog type.
        \tparam MessageCatalog             A message catalog type.
        \tparam Settings                   A settings type.
        \tparam Label                      A label type.
        \tparam Image                      An image type.
        \tparam Button                     A button type.
        \tparam PictureReader              A picture reader type.
        \tparam TransparentBackground      A transparent background type.
        \tparam AboutDialogMessageTypeList A message type.
    */
    template <
        typename Dialog,
        typename MessageCatalog,
        typename Settings,
        typename Label,
        typename Image,
        typename Button,
        typename PictureReader,
        typename TransparentBackground,
        typename AboutDialogMessageTypeList
    >
    class about_dialog : public Dialog
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

        //! The settings type.
        typedef Settings settings_type;

        //! The label type.
        typedef Label label_type;

        //! The image type.
        typedef Image image_type;

        //! The button type.
        typedef Button button_type;

        //! The color type.
        typedef typename label_type::color_type color_type;

        //! The picture reader type.
        typedef PictureReader picture_reader_type;

        //! The transparent background type.
        typedef TransparentBackground transparent_background_type;

        //! The message type list type.
        typedef
            AboutDialogMessageTypeList about_dialog_message_type_list_type;


        // constructors and destructor

        /*!
            \brief Creates an about dialog.

            \param parent          A parent window.
            \param message_catalog A message catalog.
            \param settings        Settings.
        */
        about_dialog(
            abstract_window_type&       parent,
            const message_catalog_type& message_catalog,
            const settings_type&        settings
        )
        :
        base_type(parent),
        m_message_catalog(message_catalog),
        m_settings(settings),
        m_p_application_image(),
        m_p_title_label(),
        m_p_copyright_label(),
        m_p_link_label(),
        m_p_ok_button()
        {
            initialize_dialog(parent);
        }

        /*!
            \brief Destroys the about dialog.
        */
        virtual ~about_dialog()
        TETENGO2_CPP0X_NOEXCEPT
        {}


    private:
        // variables

        const message_catalog_type& m_message_catalog;

        const settings_type& m_settings;

        typename tetengo2::cpp0x::unique_ptr<image_type>::type
        m_p_application_image;

        typename tetengo2::cpp0x::unique_ptr<label_type>::type
        m_p_title_label;

        typename tetengo2::cpp0x::unique_ptr<label_type>::type
        m_p_copyright_label;

        typename tetengo2::cpp0x::unique_ptr<label_type>::type
        m_p_link_label;

        typename tetengo2::cpp0x::unique_ptr<button_type>::type
        m_p_ok_button;


        // functions

        void initialize_dialog(const abstract_window_type& parent)
        {
            set_text(m_message_catalog.get(TETENGO2_TEXT("About")));

            this->set_client_dimension(
                typename about_dialog::dimension_type(36, 10)
            );

            typedef
                tetengo2::gui::position<typename about_dialog::position_type>
                pos_type;
            this->set_position(
                typename about_dialog::position_type(
                    pos_type::left(parent.position()) + 6,
                    pos_type::top(parent.position()) + 6
                )
            );

            m_p_application_image = create_application_image();
            m_p_title_label = create_title_label();
            m_p_copyright_label = create_copyright_label();
            m_p_link_label = create_link_label();
            m_p_ok_button = create_ok_button();

            locate_controls();
        }

        typename tetengo2::cpp0x::unique_ptr<image_type>::type
        create_application_image()
        {
            picture_reader_type picture_reader(
                m_settings.image_directory_path() /
                typename picture_reader_type::path_type::string_type(
                    TETENGO2_TEXT("kuma.png")
                )
            );
            typename tetengo2::cpp0x::unique_ptr<image_type>::type p_image(
                new image_type(*this, picture_reader)
            );

            return std::move(p_image);
        }

        typename tetengo2::cpp0x::unique_ptr<label_type>::type
        create_title_label()
        {
            typedef typename base_type::string_type::value_type char_type;
            std::basic_ostringstream<char_type> title;
            title <<
                boost::basic_format<char_type>(TETENGO2_TEXT("%s  %s %s")) %
                    m_message_catalog.get(TETENGO2_TEXT("Bobura")) %
                    m_message_catalog.get(TETENGO2_TEXT("version")) %
                    typename base_type::string_type(TETENGO2_TEXT("0.0.0"));

            typename tetengo2::cpp0x::unique_ptr<label_type>::type p_label(
                new label_type(*this)
            );

            p_label->set_text(title.str());
            p_label->set_text_color(color_type(255, 0, 0));
            typename tetengo2::cpp0x::unique_ptr<background_type>::type
            p_background(new transparent_background_type());
            p_label->set_background(std::move(p_background));

            return std::move(p_label);
        }

        typename tetengo2::cpp0x::unique_ptr<label_type>::type
        create_copyright_label()
        {
            typename tetengo2::cpp0x::unique_ptr<label_type>::type p_label(
                new label_type(*this)
            );

            p_label->set_text(
                typename base_type::string_type(
                    TETENGO2_TEXT("Copyright (C) 2007-2011 kaoru")
                )
            );
            typename tetengo2::cpp0x::unique_ptr<background_type>::type
            p_background(new transparent_background_type());
            p_label->set_background(std::move(p_background));

            return std::move(p_label);
        }

        typename tetengo2::cpp0x::unique_ptr<label_type>::type
        create_link_label()
        {
            typename tetengo2::cpp0x::unique_ptr<label_type>::type p_label(
                new label_type(*this)
            );

            p_label->set_text(
                typename base_type::string_type(
                    TETENGO2_TEXT("http://www.tetengo.org/")
                )
            );
            typename tetengo2::cpp0x::unique_ptr<background_type>::type
            p_background(new transparent_background_type());
            p_label->set_background(std::move(p_background));

            return std::move(p_label);
        }

        typename tetengo2::cpp0x::unique_ptr<button_type>::type
        create_ok_button()
        {
            typename tetengo2::cpp0x::unique_ptr<button_type>::type p_button(
                new button_type(*this, button_type::style_default)
            );

            p_button->set_text(m_message_catalog.get(TETENGO2_TEXT("OK")));
            p_button->mouse_observer_set().clicked().connect(
                typename boost::mpl::at<
                    about_dialog_message_type_list_type,
                    message::about_dialog::type::ok_button_mouse
                >::type(*this)
            );

            return std::move(p_button);
        }

        void locate_controls()
        {
            typedef typename about_dialog::dimension_type dimension_type;
            typedef typename about_dialog::position_type position_type;

            //m_p_application_image->fit_to_content();
            m_p_application_image->set_dimension(dimension_type(10, 10));
            m_p_application_image->set_position(position_type(0, 0));

            m_p_title_label->fit_to_content();
            m_p_title_label->set_position(position_type(2, 1));

            m_p_copyright_label->fit_to_content();
            m_p_copyright_label->set_position(position_type(2, 3));

            m_p_link_label->fit_to_content();
            m_p_link_label->set_position(position_type(2, 5));

            m_p_ok_button->set_dimension(dimension_type(8, 2));
            m_p_ok_button->set_position(position_type(26, 7));
        }


    };


}

#endif
