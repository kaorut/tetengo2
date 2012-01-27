/*! \file
    \brief The definition of bobura::command::file_property.

    Copyright (C) 2007-2012 kaoru

    $Id$
*/

#if !defined(BOBURA_COMMAND_FILEPROPERTY_H)
#define BOBURA_COMMAND_FILEPROPERTY_H

#include <tetengo2.cpp11.h>


namespace bobura { namespace command
{
    /*!
        \brief The class template for a file property command.

        \tparam FilePropertyDialog A file property dialog type.
    */
    template <typename FilePropertyDialog>
    class file_property
    {
    public:
        // types

        //! The file property dialog type.
        typedef FilePropertyDialog file_property_dialog_type;

        //! The abstract window type.
        typedef
            typename file_property_dialog_type::abstract_window_type
            abstract_window_type;

        //! The message catalog type.
        typedef
            typename file_property_dialog_type::message_catalog_type
            message_catalog_type;


        // constructors and destructor

        /*!
            \brief Creates a file property command.

            \param parent          A parent window.
            \param message_catalog A message catalog.
        */
        file_property(
            abstract_window_type&       parent,
            const message_catalog_type& message_catalog
        )
        :
        m_parent(parent),
        m_message_catalog(message_catalog)
        {}


        // functions

        /*!
            \brief Executes the command.
        */
        void operator()()
        {
            file_property_dialog_type(
                m_parent, m_message_catalog
            ).do_modal();
        }


    private:
        // variables

        typename tetengo2::cpp11::reference_wrapper<
            abstract_window_type
        >::type m_parent;

        typename tetengo2::cpp11::reference_wrapper<
            const message_catalog_type
        >::type m_message_catalog;


    };


}}


#endif
