/*! \file
    \brief The definition of bobura::command::save_to_file.

    Copyright (C) 2007-2012 kaoru

    $Id$
*/

#if !defined(BOBURA_COMMAND_SAVETOFILE_H)
#define BOBURA_COMMAND_SAVETOFILE_H

#include <utility>

#include <boost/optional.hpp>

#include <tetengo2.text.h>


namespace bobura { namespace command
{
    /*!
        \brief The class template for a save-to-file command.

        \tparam Model          A model type.
        \tparam AbstractWindow An abstract window type.
        \tparam SaveToFile     A file saving type.
    */
    template <typename Model, typename AbstractWindow, typename SaveToFile>
    class save_to_file
    {
    public:
        // types

        //! The model type.
        typedef Model model_type;

        //! The abstract window type.
        typedef AbstractWindow abstract_window_type;

        //! The file saving type.
        typedef SaveToFile save_to_file_type;


        // constructors and destructor

        /*!
            \brief Creates a save-to-file command.

            \param save_to_file A file saving.
        */
        save_to_file(const save_to_file_type& save_to_file)
        :
        m_save_to_file(save_to_file)
        {}


        // functions

        /*!
            \brief Executes the command.

            \param model  A model.
            \param parent A parent window.
        */
        void operator()(model_type& model, abstract_window_type& parent)
        const
        {
            m_save_to_file(model, parent);
        }


    private:
        // variables

        const save_to_file_type& m_save_to_file;


    };


}}


#endif