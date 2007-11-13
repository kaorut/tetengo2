/*! \file
    \brief The definition of a macro TETENGO2_NOTHROW.

    Copyright (C) 2007 kaoru

    $Id$
*/

#if !defined(TETENGO2_NOTHROW)

#if defined(NDEBUG)
#   define TETENGO2_NOTHROW
#else
#   define TETENGO2_NOTHROW throw ()
#endif

#endif