/*! \file
    \brief The definition of bobura::command::load_from_file.

    Copyright (C) 2007-2013 kaoru

    $Id$
*/

#if !defined(BOBURA_COMMAND_LOADFROMFILE_H)
#define BOBURA_COMMAND_LOADFROMFILE_H

//#include <memory>

//#include <boost/mpl/at.hpp>
//#include <boost/optional.hpp>

#include <tetengo2.stdalt.h>

#include "bobura.command.command_base.h"


namespace bobura { namespace command
{
    /*!
        \brief The class for a load-from-file command.
    */
    class load_from_file : public command_base
    {
    public:
        // types

        //! The base type.
        typedef command_base base_type;

        //! The file loading type.
        typedef boost::mpl::at<load_save_type_list, type::load_save::load_from_file>::type load_from_file_type;

        //! The path type.
        typedef load_from_file_type::path_type path_type;

        //! The parameter type.
        class parameter_type : public base_type::parameter_base_type
        {
        public:
            explicit parameter_type(path_type path);

            virtual ~parameter_type()
            TETENGO2_STDALT_NOEXCEPT;

            const path_type& path()
            const;

        private:
            path_type m_path;

        };


        // constructors and destructor

        /*!
            \brief Creates a load-from-file command.

            \param load_from_file A file loading.
            \param given_path     A given path.
        */
        explicit load_from_file(const load_from_file_type& load_from_file);

        /*!
            \brief Destroys the load-from-file command.
        */
        virtual ~load_from_file()
        TETENGO2_STDALT_NOEXCEPT;


    private:
        // types

        class impl;


        // variables

        const std::unique_ptr<impl> m_p_impl;


        // virtual functions

        virtual bool enabled_impl(const model_type& model)
        const override;

        virtual void execute_impl(model_type& model, abstract_window_type& parent)
        const;

        virtual void execute_impl(
            model_type&                model,
            abstract_window_type&      parent,
            const parameter_base_type& parameter
        )
        const;


    };


}}


#endif
