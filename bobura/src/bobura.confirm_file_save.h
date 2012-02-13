/*! \file
    \brief The definition of bobura::confirm_file_save.

    Copyright (C) 2007-2012 kaoru

    $Id$
*/

#if !defined(BOBURA_CONFIRMFILESAVE_H)
#define BOBURA_CONFIRMFILESAVE_H

#include <memory>

#include <tetengo2.text.h>
#include <tetengo2.unique.h>


namespace bobura
{
    /*!
        \brief The class template for the file save confirmation.

        \tparam Model          A model type.
        \tparam Window         A window type.
        \tparam MessageBox     A message box type.
        \tparam MessageCatalog A message catalog type.
    */
    template <
        typename Model,
        typename Window,
        typename MessageBox,
        typename MessageCatalog
    >
    class confirm_file_save
    {
    public:
        // types

        //! The model type.
        typedef Model model_type;

        //! The window type.
        typedef Window window_type;
        
        //! The string type.
        typedef typename window_type::string_type string_type;

        //! The message box type.
        typedef MessageBox message_box_type;

        //! The message catalog type.
        typedef MessageCatalog message_catalog_type;


        // constructors and destructor

        /*!
            \brief Creates a file save confirmation.

            \param model           A model.
            \param message_catalog A message catalog.
        */
        confirm_file_save(
            const model_type&           model,
            const message_catalog_type& message_catalog
        )
        :
        m_model(model),
        m_message_catalog(message_catalog)
        {}


        // functions

        /*!
            \brief Confirms file save, and if necessary, save the model.

            \param window A window.

            \retval true  When the model is saved or there is no need to save
                          it.
            \retval false Otherwise.
        */
        bool operator()(window_type& window)
        const
        {
            if (!m_model.changed())
                return false;

            const typename message_box_type::button_id_type selected_button =
                create_message_box(window)->do_modal();
            if (selected_button == message_box_type::button_cancel)
                return true;

            return false;
        }


    private:
        // variables

        const model_type& m_model;

        const message_catalog_type& m_message_catalog;


        // functions

        std::unique_ptr<message_box_type> create_message_box(
            window_type& window
        )
        const
        {
            return tetengo2::make_unique<message_box_type>(
                window,
                m_message_catalog.get(TETENGO2_TEXT("App:Bobura")),
                m_message_catalog.get(
                    TETENGO2_TEXT(
                        "Message:File:The file has been changed. Do you want to save the changes?"
                    )
                ),
                string_type(),
                message_box_type::button_style_type::yes_no(
                    true,
                    m_message_catalog.get(
                        TETENGO2_TEXT("Message:File:&Save")
                    ),
                    m_message_catalog.get(
                        TETENGO2_TEXT("Message:File:&Don't save")
                    )
                ),
                message_box_type::icon_style_warning
            );
        }


    };


}

#endif
