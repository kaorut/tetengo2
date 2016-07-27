/*! \file
    \brief Test of class tetengo2::iterator::observable_forward_iteratorpolymorphic_forward_iterator.

    Copyright (C) 2007-2016 kaoru

    $Id$
*/

#include <boost/test/unit_test.hpp>

#include <tetengo2/iterator/polymorphic_forward_iterator.h>


namespace
{
    // types

    class concrete_iterator : public tetengo2::iterator::polymorphic_forward_iterator<int>
    {

    };


}


BOOST_AUTO_TEST_SUITE(test_tetengo2)
BOOST_AUTO_TEST_SUITE(iterator)
BOOST_AUTO_TEST_SUITE(polymorphic_forward_iterator)
    // test cases

    BOOST_AUTO_TEST_CASE(construction)
    {
        BOOST_TEST_PASSPOINT();

        const concrete_iterator iter{};
    }


BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()
