/*! \file
    \brief Test of class bobura::model::serializer::writer_set.

    Copyright (C) 2007-2012 kaoru

    $Id$
*/

//#include <memory>
//#include <sstream>
//#include <string>
//#include <utility>

//#include <boost/mpl/at.hpp>
#include <boost/test/unit_test.hpp>

#include <tetengo2.text.h>
#include <tetengo2.unique.h>

#include "test_bobura.model.type_list.h"


namespace
{
    // types

    typedef
        boost::mpl::at<
            test_bobura::model::serialization_type_list,
            test_bobura::model::type::serialization::writer_set
        >::type
        writer_set_type;


}


BOOST_AUTO_TEST_SUITE(test_bobura)
BOOST_AUTO_TEST_SUITE(model)
BOOST_AUTO_TEST_SUITE(serializer)
BOOST_AUTO_TEST_SUITE(writer_set)
    // test cases

    BOOST_AUTO_TEST_CASE(make_writers)
    {
        BOOST_TEST_PASSPOINT();

    }


BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()
