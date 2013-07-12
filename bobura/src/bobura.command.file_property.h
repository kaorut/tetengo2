/*! \file
    \brief The definition of bobura::command::file_property.

    Copyright (C) 2007-2013 kaoru

    $Id$
*/

#if !defined(BOBURA_COMMAND_FILEPROPERTY_H)
#define BOBURA_COMMAND_FILEPROPERTY_H

//#include <memory>

//#include <boost/mpl/at.hpp>

#include <tetengo2.stdalt.h>

#include "bobura.command.command_base.h"


namespace bobura { namespace command
{
    /*!
        \brief The class for a file property command.
    */
    class file_property : public command_base
    {
    public:
        // types

        //! The base type.
        typedef command_base base_type;

        //! The file property dialog type.
        typedef boost::mpl::at<dialog_type_list, type::dialog::file_property_dialog>::type file_property_dialog_type;

        //! The dialog base type.
        typedef file_property_dialog_type::base_type dialog_base_type;

        //! The string type.
        typedef file_property_dialog_type::string_type string_type;

        //! The message catalog type.
        typedef file_property_dialog_type::message_catalog_type message_catalog_type;


        // constructors and destructor

        /*!
            \brief Creates a file property command.

            \param message_catalog A message catalog.
        */
        explicit file_property(const message_catalog_type& message_catalog);

        /*!
            \brief Destroys the file property command.
        */
        ~file_property()
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
