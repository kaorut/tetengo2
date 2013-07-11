/*! \file
    \brief The definition of bobura::main_window.

    Copyright (C) 2007-2013 kaoru

    $Id$
*/

#if !defined(BOBURA_MAINWINDOW_H)
#define BOBURA_MAINWINDOW_H

//#include <memory>

#include <boost/optional.hpp>

#include <tetengo2.stdalt.h>


namespace bobura
{
    /*!
        \brief The class template for the main window.

        \tparam Window            A window type.
        \tparam MessageCatalog    A message catalog type.
        \tparam DiagramPictureBox A diagram picture box type.
        \tparam PropertyBar       A property bar type.
        \tparam Settings          A settings type.
        \tparam ConfirmFileSave   A file save confirmation type.
    */
    template <
        typename Window,
        typename MessageCatalog,
        typename DiagramPictureBox,
        typename PropertyBar,
        typename Settings,
        typename ConfirmFileSave
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

        //! The diagram picture box type.
        typedef DiagramPictureBox diagram_picture_box_type;

        //! The property bar type.
        typedef PropertyBar property_bar_type;
        
        //! The settings type.
        typedef Settings settings_type;

        //! The file save confirmation type.
        typedef ConfirmFileSave confirm_file_save_type;


        // constructors and destructor

        /*!
            \brief Creates a main window.

            \param message_catalog   A message catalog.
            \param settings          Settings.
            \param confirm_file_save A file save confirmation.
        */
        main_window(
            const message_catalog_type&   message_catalog,
            settings_type&                settings,
            const confirm_file_save_type& confirm_file_save
        );

        /*!
            \brief Destroys the main window.
        */
        virtual ~main_window()
        TETENGO2_STDALT_NOEXCEPT;


        // functions

        /*!
            \brief Sets a title.

            \param document_name A document name.
            \param changed       A changed status.
        */
        void set_title(const boost::optional<string_type>& document_name, const bool changed);

        /*!
            \brief Returns the diagram picture box.

            \return The diagram picture box.
        */
        const diagram_picture_box_type& diagram_picture_box()
        const;

        /*!
            \brief Returns the diagram picture box.

            \return The diagram picture box.
        */
        diagram_picture_box_type& diagram_picture_box();

        /*!
            \brief Returns the property bar.

            \return The property bar.
        */
        const property_bar_type& property_bar()
        const;

        /*!
            \brief Returns the property bar.

            \return The property bar.
        */
        property_bar_type& property_bar();


    private:
        // types

        class impl;


        // variables

        const std::unique_ptr<impl> m_p_impl;


    };


}

#endif
