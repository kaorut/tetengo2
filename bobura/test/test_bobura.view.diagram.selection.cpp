/*! \file
    \brief Test of class bobura::view::diagram::selection.

    Copyright (C) 2007-2013 kaoru

    $Id$
*/

//#include <boost/mpl/at.hpp>
#include <boost/test/unit_test.hpp>

#include <tetengo2.text.h>

 #include "bobura.type_list.h"
 
#include "bobura.view.diagram.selection.h"


namespace
{
    // types

    typedef boost::mpl::at<bobura::common_type_list, bobura::type::string>::type string_type;

    typedef boost::mpl::at<bobura::model_type_list, bobura::type::model::model>::type model_type;

    typedef model_type::timetable_type::train_type train_type;

    typedef bobura::view::diagram::selection<train_type> selection_type;


}


BOOST_AUTO_TEST_SUITE(test_bobura)
BOOST_AUTO_TEST_SUITE(view)
BOOST_AUTO_TEST_SUITE(diagram)
BOOST_AUTO_TEST_SUITE(selection)
    // test cases

    BOOST_AUTO_TEST_CASE(construction)
    {
        BOOST_TEST_PASSPOINT();

        const selection_type selection;
    }

    BOOST_AUTO_TEST_CASE(selected_train)
    {
        BOOST_TEST_PASSPOINT();

        const selection_type selection;

        const train_type train(
            string_type(TETENGO2_TEXT("number")),
            0,
            string_type(TETENGO2_TEXT("name")),
            string_type(TETENGO2_TEXT("name_number")),
            string_type(TETENGO2_TEXT("note"))
        );

        BOOST_CHECK(!selection.selected(train));
    }

    BOOST_AUTO_TEST_CASE(select_train)
    {
        BOOST_TEST_PASSPOINT();

        selection_type selection;

        const train_type train(
            string_type(TETENGO2_TEXT("number")),
            0,
            string_type(TETENGO2_TEXT("name")),
            string_type(TETENGO2_TEXT("name_number")),
            string_type(TETENGO2_TEXT("note"))
        );
        
        selection.select(train);
        
        BOOST_CHECK(selection.selected(train));
    }

    BOOST_AUTO_TEST_CASE(unselect_all)
    {
        BOOST_TEST_PASSPOINT();

        selection_type selection;

        const train_type train(
            string_type(TETENGO2_TEXT("number")),
            0,
            string_type(TETENGO2_TEXT("name")),
            string_type(TETENGO2_TEXT("name_number")),
            string_type(TETENGO2_TEXT("note"))
        );
        selection.select(train);

        selection.unselect_all();

        BOOST_CHECK(!selection.selected(train));
    }


BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()
