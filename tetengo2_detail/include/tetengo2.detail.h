/*! \file
    \brief The facade of tetengo2::detail.

    Copyright (C) 2007-2017 kaoru

    $Id$
*/

#if !defined(TETENGO2_DETAIL_H)
#define TETENGO2_DETAIL_H

#include <boost/predef.h>

#include <tetengo2/detail/base/impl_set.h>
#include <tetengo2/detail/stub/impl_set.h>
#if BOOST_OS_WINDOWS
#   include <tetengo2/detail/windows/impl_set.h>
#elif BOOST_OS_LINUX
#   include <tetengo2/detail/unixos/impl_set.h>
#endif


namespace tetengo2 { namespace detail
{
    /*!
        \brief The class for a detail implementation set.
    */
#if BOOST_OS_WINDOWS
    using impl_set = windows::impl_set;
#elif BOOST_OS_LINUX
    using impl_set = unixos::impl_set;
#endif


}}


#endif
