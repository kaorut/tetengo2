/*! \file
    \brief The definition of bobura::load_save::new_file.

    Copyright (C) 2007-2013 kaoru

    $Id$
*/

#if !defined(BOBURA_LOADSAVE_NEWFILE_H)
#define BOBURA_LOADSAVE_NEWFILE_H

#include <tetengo2.unique.h>


namespace bobura { namespace load_save
{
    /*!
        \brief The class template for a new-file load_save.

        \tparam Model           A model type.
        \tparam AbstractWindow  An abstract window type.
        \tparam ConfirmFileSave A file save confirmation type.
    */
    template <typename Model, typename AbstractWindow, typename ConfirmFileSave>
    class new_file
    {
    public:
        // types

        //! The model type.
        typedef Model model_type;

        //! The abstract window type.
        typedef AbstractWindow abstract_window_type;

        //! The file save confirmation type.
        typedef ConfirmFileSave confirm_file_save_type;


        // constructors and destructor

        /*!
            \brief Creates a new-file load_save.

            \param confirm_file_save A file save confirmation.
        */
        explicit new_file(const confirm_file_save_type& confirm_file_save)
        :
        m_confirm_file_save(confirm_file_save)
        {}


        // functions

        /*!
            \brief Executes the load_save.

            \param model  A model.
            \param parent A parent window.
        */
        void operator()(model_type& model, abstract_window_type& parent)
        const
        {
            if (!m_confirm_file_save(parent))
                return;

            model.reset_timetable(tetengo2::make_unique<timetable_type>());
        }


    private:
        // types

        typedef typename model_type::timetable_type timetable_type;


        // variables

        const confirm_file_save_type& m_confirm_file_save;


    };


}}


#endif
