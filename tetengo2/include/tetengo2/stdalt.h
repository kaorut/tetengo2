/*! \file
    \brief The definition of the standard C++ alternatives for tetengo2.

    Copyright (C) 2007-2018 kaoru

    $Id$
*/

#if !defined(TETENGO2_STDALT_H)
#define TETENGO2_STDALT_H

#include <boost/predef.h>


#if BOOST_COMP_GNUC && BOOST_COMP_GNUC < BOOST_VERSION_NUMBER(7, 0, 0)
#define TETENGO2_STDALT_MAYBE_UNUSED __attribute__((unused))
#else
/*!
    \brief The alternate to [[maybe_unused]].
*/
#define TETENGO2_STDALT_MAYBE_UNUSED [[maybe_unused]]
#endif


#endif
