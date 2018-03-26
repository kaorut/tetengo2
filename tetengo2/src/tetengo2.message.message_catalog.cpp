/*! \file
    \brief The definition of tetengo2::message::message_catalog.

    Copyright (C) 2007-2018 kaoru

    $Id$
*/

#include <locale>
#include <memory>

#include <boost/core/noncopyable.hpp>

#include <tetengo2/message/message_catalog.h>
#include <tetengo2/stdalt.h>


namespace tetengo2::message {
    class message_catalog::impl : private boost::noncopyable
    {
    public:
        // types

        using string_type = message_catalog::string_type;

        using messages_type = message_catalog::messages_type;


        // constructors and destructor

        impl() : m_p_messages{ get_messages(std::locale{}) }, m_catalog_id{ open_messages(m_p_messages, std::locale{}) }
        {}

        ~impl() noexcept
        {
            try
            {
                if (m_p_messages && m_catalog_id >= 0)
                    m_p_messages->close(m_catalog_id);
            }
            catch (...)
            {
            }
        }


        // functions

        string_type get(const string_type& key) const
        {
            if (!m_p_messages || m_catalog_id < 0)
                return messages_type::remove_namespace(key);

            return m_p_messages->get(m_catalog_id, 0, 0, key);
        }

        string_type get(const string_type::value_type* p_key) const
        {
            return get(string_type{ p_key });
        }


    private:
        // types

        using catalog_id_type = messages_type::catalog;


        // static functions

        static const messages_type* get_messages(const std::locale& locale)
        {
            return std::has_facet<messages_type>(locale) ? &std::use_facet<messages_type>(locale) : nullptr;
        }

        static catalog_id_type open_messages(const messages_type* const p_messages, const std::locale& locale)
        {
            return p_messages ? p_messages->open("", locale) : -1;
        }


        // variables

        const messages_type* const m_p_messages;

        const catalog_id_type m_catalog_id;
    };


    message_catalog::message_catalog() : m_p_impl{ stdalt::make_unique<impl>() } {}

    message_catalog::~message_catalog() = default;

    message_catalog::string_type message_catalog::get(const string_type& key) const
    {
        return m_p_impl->get(key);
    }

    message_catalog::string_type message_catalog::get(const string_type::value_type* p_key) const
    {
        return m_p_impl->get(p_key);
    }
}
