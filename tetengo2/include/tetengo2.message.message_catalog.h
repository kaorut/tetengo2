/*! \file
    \brief The definition of tetengo2::message::message_catalog.

    Copyright (C) 2007-2012 kaoru

    $Id$
*/

#if !defined(TETENGO2_MESSAGE_MESSAGECATALOG_H)
#define TETENGO2_MESSAGE_MESSAGECATALOG_H

#include <cstddef>
#include <locale>
#include <type_traits>
#include <utility>

#include <boost/noncopyable.hpp>


namespace tetengo2 { namespace message
{
    /*!
        \brief The class template for a message catalog.

        \tparam Messages A messages facet type.
    */
    template <typename Messages>
    class message_catalog : private boost::noncopyable
    {
    public:
        // types

        //! The messages type.
        typedef Messages messages_type;

        //! The string type.
        typedef typename messages_type::string_type string_type;


        // constructors and destructor

        /*!
            \brief Creates a message catalog.
        */
        message_catalog()
        :
        m_p_messages(get_messages(std::locale())),
        m_catalog_id(open_messages(m_p_messages, std::locale()))
        {}

        /*!
            \brief Destroys a message catalog.
        */
        ~message_catalog()
        {
            if (m_p_messages && m_catalog_id >= 0)
                m_p_messages->close(m_catalog_id);
        }


        // functions

        /*!
            \brief Returns the localized text.

            When no corresponding value to the key is found, it returns the key in which the namespace part is removed.
            Namespaces and the other are separated by colons (':').

            \param key A key.

            \return The localized text.
        */
        string_type get(string_type key)
        const
        {
            if (!m_p_messages || m_catalog_id < 0)
                return messages_type::remove_namespace(key);

            return m_p_messages->get(m_catalog_id, 0, 0, std::move(key));
        }

        /*!
            \brief Returns the localized text.

            When no corresponding value to the key is found, it returns the key in which the namespace part is removed.
            Namespaces and the other are separated by colons (':').

            \param p_key A pointer to a key.

            \return The localized text.
        */
        string_type get(const typename string_type::value_type* const p_key)
        const
        {
            return get(string_type(p_key));
        }


    private:
        // types

        typedef typename messages_type::catalog catalog_id_type;


        // static functions

        static const messages_type* get_messages(const std::locale& locale)
        {
            return std::has_facet<messages_type>(locale) ? &std::use_facet<messages_type>(locale) : NULL;
        }

        static catalog_id_type open_messages(const messages_type* const p_messages, const std::locale& locale)
        {
            return p_messages ? p_messages->open("", locale) : -1;
        }


        // variables

        const messages_type* const m_p_messages;

        const catalog_id_type m_catalog_id;


    };


}}


#endif
