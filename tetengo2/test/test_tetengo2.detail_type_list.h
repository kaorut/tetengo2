/*! \file
    \brief The definition of test_tetengo2::detail_type_list.

    Copyright (C) 2007-2014 kaoru

    $Id$
*/

#if !defined(TESTTETENGO2_DETAILTYPELIST_H)
#define TESTTETENGO2_DETAILTYPELIST_H

#include <boost/mpl/pair.hpp>
#include <boost/predef.h>

#include <tetengo2.h>
#if BOOST_COMP_MSVC
#   include <tetengo2/detail/windows/encoding.h>
#else
#   include <tetengo2/detail/unixos/encoding.h>
#endif


namespace test_tetengo2
{
    /**** Detail Implementation *********************************************/

    namespace type { namespace detail
    {
        struct encoding;        //!< The encoding type.
    }}

#if !defined(DOCUMENTATION)
    namespace detail { namespace detail
    {
#if BOOST_COMP_MSVC
        using encoding_details_type = tetengo2::detail::windows::encoding;
#else
        using encoding_details_type = tetengo2::detail::unixos::encoding;
#endif
    }}
#endif

    //! The detail type list.
    using detail_type_list =
        tetengo2::meta::assoc_list<boost::mpl::pair<type::detail::encoding, detail::detail::encoding_details_type>,
        tetengo2::meta::assoc_list_end
        >;


}


#endif
