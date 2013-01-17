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

    typedef
        boost::mpl::at<test_bobura::model::type_list, test_bobura::model::type::abstract_window>::type
        abstract_window_type;

    typedef
        boost::mpl::at<test_bobura::model::type_list, test_bobura::model::type::message_catalog>::type
        message_catalog_type;

    struct oudia_diagram_dialog
    {
        typedef
            boost::mpl::at<test_bobura::model::type_list, test_bobura::model::type::abstract_window>::type
            abstract_window_type;

        typedef
            boost::mpl::at<test_bobura::model::type_list, test_bobura::model::type::message_catalog>::type
            message_catalog_type;

        oudia_diagram_dialog(abstract_window_type&, const message_catalog_type&)
        {}

        void do_modal()
        {}

    };

    typedef bobura::model::serializer::select_oudia_diagram<oudia_diagram_dialog> select_oudia_diagram_type;


}


BOOST_AUTO_TEST_SUITE(test_bobura)
BOOST_AUTO_TEST_SUITE(model)
BOOST_AUTO_TEST_SUITE(serializer)
BOOST_AUTO_TEST_SUITE(select_oudia_diagram)
    // test cases

    BOOST_AUTO_TEST_CASE(construction)
    {
        BOOST_TEST_PASSPOINT();

        abstract_window_type parent;
        const message_catalog_type message_catalog;
        const select_oudia_diagram_type select_oudia_diagram(parent, message_catalog);
    }

    BOOST_AUTO_TEST_CASE(operator_paren)
    {
        BOOST_TEST_PASSPOINT();

        abstract_window_type parent;
        const message_catalog_type message_catalog;
        const select_oudia_diagram_type select_oudia_diagram(parent, message_catalog);

        std::vector<string_type> diagram_names;
        const std::vector<string_type>::const_iterator selected =
            select_oudia_diagram(diagram_names.begin(), diagram_names.end());

        BOOST_CHECK(selected == diagram_names.end());
    }


BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()
