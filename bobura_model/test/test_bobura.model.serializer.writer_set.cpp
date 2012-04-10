/*! \file
    \brief Test of class bobura::model::serializer::writer_set.

    Copyright (C) 2007-2012 kaoru

    $Id$
*/

//#include <memory>
//#include <vector>

//#include <boost/mpl/at.hpp>
#include <boost/test/unit_test.hpp>

#include "test_bobura.model.type_list.h"


namespace
{
    // types

    typedef
        boost::mpl::at<
            test_bobura::model::serialization_type_list, test_bobura::model::type::serialization::writer
        >::type
        writer_type;

    typedef
        boost::mpl::at<
            test_bobura::model::serialization_type_list, test_bobura::model::type::serialization::writer_set
        >::type
        writer_set_type;


}


BOOST_AUTO_TEST_SUITE(test_bobura)
BOOST_AUTO_TEST_SUITE(model)
BOOST_AUTO_TEST_SUITE(serializer)
BOOST_AUTO_TEST_SUITE(writer_set)
    // test cases

    BOOST_AUTO_TEST_CASE(create_writers)
    {
        BOOST_TEST_PASSPOINT();

        const std::vector<std::unique_ptr<writer_type>> p_writers = writer_set_type::create_writers();

        BOOST_CHECK(!p_writers.empty());
        BOOST_CHECK(p_writers[0]);
    }


BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()
