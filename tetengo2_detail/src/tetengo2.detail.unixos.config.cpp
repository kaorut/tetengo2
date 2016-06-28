/*! \file
    \brief The definition of tetengo2::detail::unixos::config.

    Copyright (C) 2007-2016 kaoru

    $Id$
*/

#include <utility>

#include <tetengo2/detail/unixos/config.h>
#include <tetengo2/stdalt.h>

namespace tetengo2 { namespace detail { namespace unixos
{
    class config::impl : private boost::noncopyable
    {
    public:
        // types

        using string_type = config::string_type;

        using uint_type = config::uint_type;

        using value_type = config::value_type;


        // constructors and destructor

        impl()
        {}


        // functions

        // virtual functions

        virtual boost::optional<value_type> get_impl(const string_type& /*group_name*/, const string_type& /*key*/)
        const
        {
            // TODO Implement it.
            return boost::none;
        }

        virtual void set_impl(const string_type& /*group_name*/, const string_type& /*key*/, value_type /*value*/)
        const
        {
            // TODO Implement it.
        }

        virtual void clear_impl(const string_type& /*group_name*/)
        const
        {
            // TODO Implement it.
        }


    };


    const config& config::instance()
    {
        static const config singleton{};
        return singleton;
    }

    config::~config()
    = default;

    config::config()
    :
    m_p_impl(tetengo2::stdalt::make_unique<impl>())
    {}


    // virtual functions

    boost::optional<config::value_type> config::get_impl(const string_type& group_name, const string_type& key)
    const
    {
        return m_p_impl->get_impl(group_name, key);
    }

    void config::set_impl(const string_type& group_name, const string_type& key, value_type value)
    const
    {
        m_p_impl->set_impl(group_name, key, std::move(value));
    }

    void config::clear_impl(const string_type& group_name)
    const
    {
        m_p_impl->clear_impl(group_name);
    }


}}}
