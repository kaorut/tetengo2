/*! \file
    \brief The facade of tetengo2::detail.

    Copyright (C) 2007-2017 kaoru

    $Id$
*/

#if !defined(TETENGO2_DETAIL_H)
#define TETENGO2_DETAIL_H

#include <boost/predef.h>

#include <tetengo2/detail/base/alert.h>
#include <tetengo2/detail/base/config.h>
#if BOOST_OS_WINDOWS
#   include <tetengo2/detail/windows/alert.h>
#   include <tetengo2/detail/windows/config.h>
#elif BOOST_OS_UNIX
#   include <tetengo2/detail/unixos/config.h>
#else
#   error No stub implementation.
#endif


namespace tetengo2 { namespace detail
{
    /*!
        \brief The class for a detail implementations.
    */
#if BOOST_OS_WINDOWS
    using alert = windows::alert;
    using config = windows::config;
#elif BOOST_OS_UNIX
    using config = unixos::config;
#else
#   error No detail implementation.
#endif


}}

#endif
