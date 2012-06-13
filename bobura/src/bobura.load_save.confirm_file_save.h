/*! \file
    \brief The definition of bobura::load_save::confirm_file_save.

    Copyright (C) 2007-2012 kaoru

    $Id$
*/

#if !defined(BOBURA_LOADSAVE_CONFIRMFILESAVE_H)
#define BOBURA_LOADSAVE_CONFIRMFILESAVE_H

//#include <memory>

#include <tetengo2.text.h>
#include <tetengo2.unique.h>


namespace bobura { namespace load_save
{
    /*!
        \brief The class template for the file save confirmation.

        \tparam Model          A model type.
        \tparam AbstractWindow An abstract window type.
        \tparam MessageBox     A message box type.
        \tparam SaveToFile     A file saving type.
        \tparam MessageCatalog A message catalog type.
    */
    template <
        typename Model,
        typename AbstractWindow,
        typename MessageBox,
        typename SaveToFile,
        typename MessageCatalog
    >
    class confirm_file_save
    {
    public:
        // types

        //! The model type.
        typedef Model model_type;

        //! The abstract window type.
        typedef AbstractWindow abstract_window_type;
        
        //! The string type.
        typedef typename abstract_window_type::string_type string_type;

        //! The message box type.
        typedef MessageBox message_box_type;

        //! The file saving type.
        typedef SaveToFile save_to_file_type;

        //! The message catalog type.
        typedef MessageCatalog message_catalog_type;


        // constructors and destructor

        /*!
            \brief Creates a file save confirmation.

            \param model           A model.
            \param save_to_file    A file saving.
            \param message_catalog A message catalog.
        */
        confirm_file_save(
            model_type&                 model,
            const save_to_file_type&    save_to_file,
            const message_catalog_type& message_catalog
        )
        :
        m_model(model),
        m_save_to_file(save_to_file),
        m_message_catalog(message_catalog)
        {}


        // functions

        /*!
            \brief Confirms file save, and if necessary, save the model.

            \param parent A parent window.

            \retval true  When the model is saved or there is no need to save it.
            \retval false Otherwise.
        */
        bool operator()(abstract_window_type& parent)
        const
        {
            if (!m_model.changed())
                return true;

            const typename message_box_type::button_id_type selected_button = create_message_box(parent)->do_modal();
            if (selected_button == message_box_type::button_cancel)
                return false;
            if (selected_button == message_box_type::button_yes)
            {
                if (!m_save_to_file(m_model, parent))
                    return false;
            }

            return true;
        }


    private:
        // variables

        model_type& m_model;

        const save_to_file_type& m_save_to_file;

        const message_catalog_type& m_message_catalog;


        // functions

        std::unique_ptr<message_box_type> create_message_box(abstract_window_type& parent)
        const
        {
            const string_type file_path =
                m_model.has_path() ?
                m_model.path().template string<string_type>() :
                m_message_catalog.get(TETENGO2_TEXT("Common:Untitled"));

            return
                tetengo2::make_unique<message_box_type>(
                    parent,
                    m_message_catalog.get(TETENGO2_TEXT("App:Bobura")),
                    m_message_catalog.get(
                        TETENGO2_TEXT("Message:File:The file has been changed. Do you want to save the changes?")
                    ),
                    file_path,
                    message_box_type::button_style_type::yes_no(
                        true,
                        m_message_catalog.get(TETENGO2_TEXT("Message:File:&Save")),
                        m_message_catalog.get(TETENGO2_TEXT("Message:File:&Don't save"))
                    ),
                    message_box_type::icon_style_warning
                );
        }


    };


}}


#endif
