/*! \file
    \brief The definition of tetengo2::message::message_catalog.

    Copyright (C) 2007-2018 kaoru

    $Id$
*/

#if !defined(TETENGO2_MESSAGE_MESSAGECATALOG_H)
#define TETENGO2_MESSAGE_MESSAGECATALOG_H

#include <memory>

#include <boost/core/noncopyable.hpp>

#include <tetengo2/message/messages.h>
#include <tetengo2/type_list.h>


namespace tetengo2 { namespace message
{
    /*!
        \brief The class for a message catalog.
    */
    class message_catalog : private boost::noncopyable
    {
    public:
        // types

        //! The string type.
        using string_type = type_list::string_type;

        //! The messages type.
        using messages_type = messages;


        // constructors and destructor

        /*!
            \brief Creates a message catalog.
        */
        message_catalog();

        /*!
            \brief Destroys the message catalog.
        */
        ~message_catalog();


        // functions

        /*!
            \brief Returns the localized text.

            When no corresponding value to the key is found, it returns the key in which the namespace part is removed.
            Namespaces and the other are separated by colons (':').

            \param key A key.

            \return The localized text.
        */
        string_type get(const string_type& key)
        const;

        /*!
            \brief Returns the localized text.

            When no corresponding value to the key is found, it returns the key in which the namespace part is removed.
            Namespaces and the other are separated by colons (':').

            \param p_key A pointer to a key.

            \return The localized text.
        */
        string_type get(const string_type::value_type* p_key)
        const;


    private:
        // types

        class impl;


        // variables

        const std::unique_ptr<impl> m_p_impl;


    };


}}


#endif
