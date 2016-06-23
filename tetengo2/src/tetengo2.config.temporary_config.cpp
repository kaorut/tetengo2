/*! \file
    \brief The definition of tetengo2::config::temporary_config.

    Copyright (C) 2007-2016 kaoru

    $Id$
*/

#include <unordered_map>
#include <utility>

#include <boost/core/noncopyable.hpp>
#include <boost/optional.hpp>

#include <tetengo2/config/temporary_config.h>
#include <tetengo2/stdalt.h>


namespace tetengo2 { namespace config
{
    class temporary_config::impl : private boost::noncopyable
    {
    public:
        // types

        using string_type = temporary_config::string_type;

        using uint_type = temporary_config::uint_type;

        using base_type = temporary_config::base_type;

        using value_type = temporary_config::value_type;


        // constructors and destructor

        impl()
        :
        m_values()
        {}


        // functions

        boost::optional<value_type> get_impl(const string_type& key)
        const
        {
            const typename key_value_type::const_iterator found = m_values.find(key);
            return found != m_values.end() ? boost::make_optional<value_type>(found->second) : boost::none;
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


    temporary_config::temporary_config()
    :
    m_p_impl(tetengo2::stdalt::make_unique<impl>())
    {}

    temporary_config::~temporary_config()
    = default;

    boost::optional<temporary_config::value_type> temporary_config::get_impl(const string_type& key)
    const
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


}}
