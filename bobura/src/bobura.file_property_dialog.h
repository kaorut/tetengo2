/*! \file
    \brief The definition of bobura::file_property_dialog.

    Copyright (C) 2007-2013 kaoru

    $Id$
*/

#if !defined(BOBURA_FILEPROPERTYDIALOG_H)
#define BOBURA_FILEPROPERTYDIALOG_H

//#include <memory>

#include <tetengo2.stdalt.h>


namespace bobura
{
    /*!
        \brief The class template for the file property dialog.

        \tparam Dialog         A dialog type.
        \tparam MessageCatalog A message catalog type.
    */
    template <typename Dialog, typename MessageCatalog>
    class file_property_dialog : public Dialog
    {
    public:
        // types

        //! The base type.
        typedef Dialog base_type;

        //! The abstract window type.
        typedef typename base_type::base_type abstract_window_type;

        //! The string type.
        typedef typename base_type::string_type string_type;

        //! The message catalog type.
        typedef MessageCatalog message_catalog_type;


        // constructors and destructor

        /*!
            \brief Creates a file property dialog.

            \param parent          A parent window.
            \param message_catalog A message catalog.
        */
        file_property_dialog(abstract_window_type& parent, const message_catalog_type& message_catalog);

        /*!
            \brief Destroys the file property dialog.
        */
        virtual ~file_property_dialog()
        TETENGO2_STDALT_NOEXCEPT;


        // functions

        /*!
            \brief Returns the company name.

            \return The company name.
        */
        const string_type& company_name()
        const;

        /*!
            \brief Sets a company name.

            \param company_name A company name.
        */
        void set_company_name(string_type company_name);

        /*!
            \brief Returns the line name.

            \return The line name.
        */
        const string_type& line_name()
        const;

        /*!
            \brief Sets a line name.

            \param line_name A line name.
        */
        void set_line_name(string_type line_name);

        /*!
            \brief Returns the note.

            \return The note.
        */
        const string_type& note()
        const;

        /*!
            \brief Sets a note.

            \param note A note.
        */
        void set_note(string_type note);

        /*!
            \brief Returns the file name.

            \return The file name.
        */
        const string_type& file_name()
        const;

        /*!
            \brief Sets a file name.

            \param file_name A file name.
        */
        void set_file_name(string_type file_name);


    private:
        // types

        class impl;


        // variables

        const std::unique_ptr<impl> m_p_impl;


        // virtual functions

        virtual void set_result_impl()
        override;


    };


}

#endif
