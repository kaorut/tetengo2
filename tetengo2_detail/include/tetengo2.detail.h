/*! \file
    \brief The facade of tetengo2::detail.

    Copyright (C) 2007-2017 kaoru

    $Id$
*/

#if !defined(TETENGO2_DETAIL_H)
#define TETENGO2_DETAIL_H

#include <boost/predef.h>

#if BOOST_OS_WINDOWS
#   include <tetengo2/detail/windows/alert.h>
#elif BOOST_OS_UNIX
#else
#   error No stub implementation.
#endif
#include <tetengo2/detail/config.h>


namespace tetengo2 { namespace detail
{
    /*!
        \brief The class for a detail implementations.
    */
#if BOOST_OS_WINDOWS
    using alert = windows::alert;
#elif BOOST_OS_UNIX
#else
#   error No detail implementation.
#endif


}}

#endif
