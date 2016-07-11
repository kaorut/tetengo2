/*! \file
    \brief The definition of tetengo2::detail::config.

    Copyright (C) 2007-2016 kaoru

    $Id$
*/

#include <boost/predef.h>

#if BOOST_OS_WINDOWS
#   include <tetengo2/detail/windows/config.h>
#elif BOOST_OS_UNIX
#   include <tetengo2/detail/unixos/config.h>
#else
#   error No stub implementation.
#endif


namespace tetengo2 { namespace detail
{
    /*!
        \brief The class for a detail implementation of a config.
    */
#if BOOST_OS_WINDOWS
    using config = windows::config;
#elif BOOST_OS_UNIX
    using config = unixos::config;
#else
#   error No stub implementation.
#endif


}}
