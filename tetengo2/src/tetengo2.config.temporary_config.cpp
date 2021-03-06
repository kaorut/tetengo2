/*! \file
    \brief The definition of tetengo2::config::temporary_config.

    Copyright (C) 2007-2019 kaoru

    $Id$
*/

#include <memory>
#include <unordered_map>
#include <utility>

#include <boost/core/noncopyable.hpp>
#include <boost/type_traits.hpp>

#include <tetengo2/config/temporary_config.h>
#include <tetengo2/stdalt.h>


namespace tetengo2::config {
    class temporary_config::impl : private boost::noncopyable
    {
    public:
        // types

        using string_type = temporary_config::string_type;

        using uint_type = temporary_config::uint_type;

        using base_type = temporary_config::base_type;

        using value_type = temporary_config::value_type;


        // constructors and destructor

        impl() : m_values{} {}


        // functions

        tetengo2::stdalt::optional<value_type> get_impl(const string_type& key) const
        {
            const auto found = m_values.find(key);
            if (found == m_values.end())
                return TETENGO2_STDALT_NULLOPT;

            return tetengo2::stdalt::make_optional(value_type{ found->second });
        }

        void set_impl(const string_type& key, value_type value)
        {
            m_values[key] = std::move(value);
        }

        void clear_impl()
        {
            m_values.clear();
        }


    private:
        // types

        using key_value_type = std::unordered_map<string_type, value_type>;


        // variables

        key_value_type m_values;
    };


    temporary_config::temporary_config() : m_p_impl{ std::make_unique<impl>() } {}

    temporary_config::~temporary_config() = default;

    tetengo2::stdalt::optional<temporary_config::value_type> temporary_config::get_impl(const string_type& key) const
    {
        return m_p_impl->get_impl(key);
    }

    void temporary_config::set_impl(const string_type& key, value_type value)
    {
        m_p_impl->set_impl(key, std::move(value));
    }

    void temporary_config::clear_impl()
    {
        m_p_impl->clear_impl();
    }
}
