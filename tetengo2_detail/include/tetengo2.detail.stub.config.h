/*! \file
    \brief The definition of tetengo2::detail::stub::config.

    Copyright (C) 2007-2013 kaoru

    $Id$
*/

#if !defined(TETENGO2_DETAIL_STUB_CONFIG_H)
#define TETENGO2_DETAIL_STUB_CONFIG_H

#include <boost/noncopyable.hpp>
#include <boost/optional.hpp>
#include <boost/variant.hpp>


namespace tetengo2 { namespace detail { namespace stub
{
    /*!
        \brief The class for a detail implementation of a config.
    */
    class config : private boost::noncopyable
    {
    public:
        // static functions

        template <typename String, typename UInt>
        static boost::optional<boost::variant<String, UInt>> get(const String& group_name, const String& key)
        {
            return boost::none;
        }

        template <typename String, typename UInt>
        static void set(const String& group_name, const String& key, boost::variant<String, UInt> value)
        {

        }


    };


}}}


#endif
