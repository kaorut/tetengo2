/*! \file
    \brief The definition of bobura::command::save_to_file.

    Copyright (C) 2007-2014 kaoru

    $Id$
*/

#if !defined(BOBURA_COMMAND_SAVETOFILE_H)
#define BOBURA_COMMAND_SAVETOFILE_H

//#include <memory>

//#include <boost/mpl/at.hpp>

#include <tetengo2.stdalt.h>

#include "bobura.command.command_base.h"


namespace bobura { namespace command
{
    /*!
        \brief The class for a save-to-file command.
    */
    class save_to_file : public command_base
    {
    public:
        // types

        //! The base type.
        typedef command_base base_type;

        //! The file saving type.
        typedef boost::mpl::at<load_save_type_list, type::load_save::save_to_file>::type save_to_file_type;


        // constructors and destructor

        /*!
            \brief Creates a save-to-file command.

            \param save_to_file A file saving.
        */
        explicit save_to_file(const save_to_file_type& save_to_file);

        /*!
            \brief Destroys the save-to-file command.
        */
        virtual ~save_to_file()
        TETENGO2_STDALT_NOEXCEPT;


    private:
        // types

        class impl;


        // variables

        const std::unique_ptr<impl> m_p_impl;


        // virtual functions

        virtual void execute_impl(model_type& model, abstract_window_type& parent)
        const override;


    };


}}


#endif
