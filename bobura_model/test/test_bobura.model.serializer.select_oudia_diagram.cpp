/*! \file
    \brief Test of class bobura::model::serializer::select_oudia_diagram.

    Copyright (C) 2007-2013 kaoru

    $Id$
*/

//#include <vector>

//#include <boost/mpl/at.hpp>
#include <boost/test/unit_test.hpp>

#include "test_bobura.model.type_list.h"

#include "bobura.model.serializer.select_oudia_diagram.h"


namespace
{
    // types

    typedef boost::mpl::at<test_bobura::model::type_list, test_bobura::model::type::string>::type string_type;

    typedef bobura::model::serializer::select_oudia_diagram<string_type> select_oudia_diagram_type;


}


BOOST_AUTO_TEST_SUITE(test_bobura)
BOOST_AUTO_TEST_SUITE(model)
BOOST_AUTO_TEST_SUITE(serializer)
BOOST_AUTO_TEST_SUITE(select_oudia_diagram)
    // test cases

    BOOST_AUTO_TEST_CASE(construction)
    {
        BOOST_TEST_PASSPOINT();

        const select_oudia_diagram_type select_oudia_diagram_type;
    }

    BOOST_AUTO_TEST_CASE(operator_paren)
    {
        BOOST_TEST_PASSPOINT();

        const select_oudia_diagram_type select_oudia_diagram;

        std::vector<string_type> diagram_names;
        const std::vector<string_type>::const_iterator selected =
            select_oudia_diagram(diagram_names.begin(), diagram_names.end());

        BOOST_CHECK(selected == diagram_names.end());
    }


BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()
