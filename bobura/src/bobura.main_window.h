/*! \file
    \brief The definition of bobura::main_window.

    Copyright (C) 2007-2012 kaoru

    $Id$
*/

#if !defined(BOBURA_MAINWINDOW_H)
#define BOBURA_MAINWINDOW_H

#include <cassert>
//#include <cstddef>
//#include <memory>
//#include <utility>

#include <boost/mpl/at.hpp>
#include <boost/optional.hpp>

#include <tetengo2.cpp11.h>
#include <tetengo2.gui.measure.h>
#include <tetengo2.text.h>
#include <tetengo2.unique.h>

#include "bobura.message.type_list.h"


namespace bobura
{
    /*!
        \brief The class template for the main window.

        \tparam Window                    A window type.
        \tparam MessageCatalog            A message catalog type.
        \tparam PictureBox                A picture box type.
        \tparam Settings                  A settings type.
        \tparam ConfirmFileSave           A file save confirmation type.
        \tparam MessageLoopBreak          A message loop break type.
        \tparam MainWindowMessageTypeList A main window message type list type.
    */
    template <
        typename Window,
        typename MessageCatalog,
        typename PictureBox,
        typename Settings,
        typename ConfirmFileSave,
        typename MessageLoopBreak,
        typename MainWindowMessageTypeList
    >
    class main_window : public Window
    {
    public:
        // types

        //! The base type.
        typedef Window base_type;

        //! The string type.
        typedef typename base_type::string_type string_type;

        //! The message catalog type.
        typedef MessageCatalog message_catalog_type;

        //! The picture box type.
        typedef PictureBox picture_box_type;

        //! The settings type.
        typedef Settings settings_type;

        //! The file save confirmation type.
        typedef ConfirmFileSave confirm_file_save_type;

        //! The message loop break type.
        typedef MessageLoopBreak message_loop_break_type;

        //! The main window message type list type.
        typedef MainWindowMessageTypeList main_window_message_type_list_type;


        // constructors and destructor

        /*!
            \brief Creates a main window.

            \param message_catalog   A message catalog.
            \param settings          Settings.
            \param confirm_file_save A file save confirmation.
        */
        main_window(
            const message_catalog_type&   message_catalog,
            const settings_type&          settings,
            const confirm_file_save_type& confirm_file_save
        )
        :
        base_type(),
        m_message_catalog(message_catalog),
        m_p_diagram_picture_box(),
        m_settings(settings),
        m_confirm_file_save(confirm_file_save)
        {
            initialize_window();
        }

        /*!
            \brief Destroys the main window.
        */
        virtual ~main_window()
        {}


        // functions

        /*!
            \brief Sets a title.

            \param document_name A document name.
            \param changed       A changed status.
        */
        void set_title(const boost::optional<string_type>& document_name, const bool changed)
        {
            string_type title =
                document_name ? *document_name : m_message_catalog.get(TETENGO2_TEXT("Common:Untitled"));
            if (changed)
                title += string_type(TETENGO2_TEXT(" *"));
            title += string_type(TETENGO2_TEXT(" - "));
            title += m_message_catalog.get(TETENGO2_TEXT("App:Bobura"));

            set_text(title);
        }

        /*!
            \brief Returns the diagram picture box.

            \return The diagram picture box.
        */
        const picture_box_type& diagram_picture_box()
        const
        {
            assert(m_p_diagram_picture_box);
            return *m_p_diagram_picture_box;
        }

        /*!
            \brief Returns the diagram picture box.

            \return The diagram picture box.
        */
        picture_box_type& diagram_picture_box()
        {
            assert(m_p_diagram_picture_box);
            return *m_p_diagram_picture_box;
        }


    private:
        // types

        typedef typename main_window::position_type position_type;

        typedef typename tetengo2::gui::position<position_type>::left_type left_type;

        typedef typename tetengo2::gui::position<position_type>::top_type top_type;

        struct paint_background
        {
            bool operator()(typename base_type::canvas_type& canvas)
            const
            {
                return true;
            }

        };


        // variables

        const message_catalog_type& m_message_catalog;

        std::unique_ptr<picture_box_type> m_p_diagram_picture_box;

        const settings_type& m_settings;

        const confirm_file_save_type& m_confirm_file_save;


        // functions

        void initialize_window()
        {
            m_p_diagram_picture_box = create_diagram_picture_box();

            set_message_observers();

            set_title(boost::none, false);
        }

        std::unique_ptr<picture_box_type> create_diagram_picture_box()
        {
            std::unique_ptr<picture_box_type> p_picture_box =
                tetengo2::make_unique<picture_box_type>(*this, picture_box_type::scroll_bar_style_both);

            return std::move(p_picture_box);
        }

        void set_message_observers()
        {
            this->paint_observer_set().paint_background().connect(paint_background());
            this->window_observer_set().resized().connect(
                typename boost::mpl::at<
                    main_window_message_type_list_type, message::main_window::type::window_resized
                >::type(*this, *m_p_diagram_picture_box)
            );
            this->window_observer_set().closing().connect(
                typename boost::mpl::at<
                    main_window_message_type_list_type, message::main_window::type::window_closing
                >::type(*this, m_confirm_file_save)
            );
            this->window_observer_set().destroyed().connect(TETENGO2_CPP11_BIND(message_loop_break_type(), 0));
        }


    };


}

#endif
