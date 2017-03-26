/*! \file
    \brief The definition of tetengo2::config::config_base.

    Copyright (C) 2007-2017 kaoru

    $Id$
*/

#include <utility>

#include <boost/core/noncopyable.hpp>
#include <boost/optional.hpp>

#include <tetengo2/config/config_base.h>
#include <tetengo2/stdalt.h>


namespace tetengo2 { namespace config
{
    class config_base::impl : private boost::noncopyable
    {
    public:
        // types

        using string_type = config_base::string_type;

        using uint_type = config_base::uint_type;

        using value_type = config_base::value_type;


        // functions
        
        boost::optional<value_type> get(const string_type& key, const config_base& base)
        const
        {
            return base.get_impl(key);
        }

        void set(const string_type& key, value_type value, config_base& base)
        {
            base.set_impl(key, std::move(value));
        }

        void clear(config_base& base)
        {
            base.clear_impl();
        }


    };


    config_base::config_base()
    :
    m_p_impl(tetengo2::stdalt::make_unique<impl>())
    {}

    config_base::~config_base()
    = default;

    boost::optional<config_base::value_type> config_base::get(const string_type& key)
    const
    {
        return m_p_impl->get(key, *this);
    }

    void config_base::set(const string_type& key, value_type value)
    {
        m_p_impl->set(key, std::move(value), *this);
    }

    void config_base::clear()
    {
        m_p_impl->clear(*this);
    }


}}
