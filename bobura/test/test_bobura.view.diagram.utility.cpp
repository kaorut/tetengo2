/*! \file
    \brief Test of class bobura::view::diagram::utility.

    Copyright (C) 2007-2013 kaoru

    $Id$
*/

#include <boost/test/unit_test.hpp>

#include <tetengo2.detail.stub.unit.h>
#include <tetengo2.gui.unit.em.h>

#include "bobura.model.train_info.time.h"
#include "bobura.model.train_info.time_span.h"

#include "bobura.view.diagram.utility.h"


namespace
{
    typedef tetengo2::gui::unit::em<int, tetengo2::detail::stub::unit> left_type;

    typedef bobura::model::train_info::time_span<int> time_span_type;

    typedef bobura::model::train_info::time<int, time_span_type> time_type;

}

BOOST_AUTO_TEST_SUITE(test_bobura)
BOOST_AUTO_TEST_SUITE(view)
BOOST_AUTO_TEST_SUITE(diagram)
    // test cases

    BOOST_AUTO_TEST_CASE(time_to_left)
    {
        BOOST_TEST_PASSPOINT();

        const left_type result =
            bobura::view::diagram::time_to_left(
                time_type(1),
                time_span_type(2),
                0,
                left_type(3),
                left_type(4),
                left_type(5)
            );

        BOOST_CHECK_EQUAL(result.value(), 2396);
    }


BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()
