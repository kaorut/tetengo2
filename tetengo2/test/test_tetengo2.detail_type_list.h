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
#   include <tetengo2/detail/windows/config.h>
#   include <tetengo2/detail/windows/encoding.h>
#else
#   include <tetengo2/detail/unixos/config.h>
#   include <tetengo2/detail/unixos/encoding.h>
#endif


namespace test_tetengo2
{
    namespace type { namespace detail
    {
        struct config;   //!< The configuration type.
        struct encoding; //!< The encoding type.
    }}

#if !defined(DOCUMENTATION)
    namespace detail { namespace detail
    {
        namespace test
        {
#if BOOST_COMP_MSVC
            using config_details_type = tetengo2::detail::windows::config;

            using encoding_details_type = tetengo2::detail::windows::encoding;
#else
            using config_details_type = tetengo2::detail::unixos::config;

            using encoding_details_type = tetengo2::detail::unixos::encoding;
#endif

        }

    }}
#endif

    /*!
        \brief The detail type list for the testing.
    */
    using detail_type_list_for_test =
        tetengo2::meta::assoc_list<boost::mpl::pair<type::detail::config, detail::detail::test::config_details_type>,
        tetengo2::meta::assoc_list<
            boost::mpl::pair<type::detail::encoding, detail::detail::test::encoding_details_type>,
        tetengo2::meta::assoc_list_end
        >>;


}


#endif
