/*! \file
    \brief The definition of tetengo2::message_catalog.

    Copyright (C) 2007-2010 kaoru

    $Id$
*/

#if !defined(TETENGO2_MESSAGECATALOG_H)
#define TETENGO2_MESSAGECATALOG_H

#include <cstddef>
//#include <locale>

//#include <boost/concept_check.hpp>
#include <boost/noncopyable.hpp>

#include "concept_tetengo2.Messages.h"


namespace tetengo2
{
    /*!
        \brief The class template for a message catalog.

        \tparam Messages A messages facet type. It must conform to
                         concept_tetengo2::Messages<Messages>.
    */
    template <typename Messages>
    class message_catalog : private boost::noncopyable
    {
    private:
        // concept checks

        BOOST_CONCEPT_ASSERT((concept_tetengo2::Messages<Messages>));


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
        explicit message_catalog()
        :
        m_p_messages(get_messages(std::locale())),
        m_catalog_id(open_messages(m_p_messages, std::locale()))
        {}

        /*!
            \brief Destroys a message catalog.
        */
        ~message_catalog()
        throw ()
        {
            if (m_p_messages != NULL && m_catalog_id >= 0)
                m_p_messages->close(m_catalog_id);
        }


        // functions

        /*!
            \brief Returns the localized text.

            \param default_text A default text. It is also used as a key of
                                the message catalog.

            \return The localized text.
        */
        string_type get(const string_type default_text)
        const
        {
            if (m_p_messages == NULL || m_catalog_id < 0)
                return default_text;

            return m_p_messages->get(m_catalog_id, 0, 0, default_text);
        }


    private:
        // types

        typedef typename messages_type::catalog catalog_id_type;


        // static functions

        static const messages_type* get_messages(const std::locale& locale)
        {
            return std::has_facet<messages_type>(locale) ?
                &std::use_facet<messages_type>(locale) : NULL;
        }

        static catalog_id_type open_messages(
            const messages_type* const p_messages,
            const std::locale&         locale
        )
        {
            return p_messages != NULL ? p_messages->open("", locale) : -1;
        }


        // variables

        const messages_type* const m_p_messages;

        const catalog_id_type m_catalog_id;


    };


}

#endif
