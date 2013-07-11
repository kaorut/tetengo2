/*! \file
    \brief The definition of bobura::command::new_file.

    Copyright (C) 2007-2013 kaoru

    $Id$
*/

#if !defined(BOBURA_COMMAND_NEWFILE_H)
#define BOBURA_COMMAND_NEWFILE_H

//#include <memory>

//#include <boost/mpl/at.hpp>

#include <tetengo2.stdalt.h>

#include "bobura.command.command_base.h"


namespace bobura { namespace command
{
    /*!
        \brief The class for a new-file command.
    */
    class new_file : public command_base
    {
    public:
        // types

        //! The base type.
        typedef command_base base_type;

        //! The file initialization type.
        typedef boost::mpl::at<load_save_type_list, type::load_save::new_file>::type new_file_type;


        // constructors and destructor

        /*!
            \brief Creates a new-file command.

            \param new_file A file initialization type.
        */
        explicit new_file(const new_file_type& new_file);

        /*!
            \brief Destroys the new-file command.
        */
        ~new_file()
        TETENGO2_CPP11_NOEXCEPT;


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
