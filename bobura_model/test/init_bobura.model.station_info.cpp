/*! \file
    \brief Test of namespace bobura::model::station_info.

    Copyright (C) 2007-2008 kaoru

    $Id$
*/

#include "precompiled.h"

#include "init_bobura.model.station_info.h"
#include "test_bobura.model.station_info.grade.h"


namespace test_bobura { namespace model { namespace station_info
{
    // functions

    boost::unit_test::test_suite* suite()
    {
        boost::unit_test::test_suite* const p_suite =
            BOOST_TEST_SUITE("test_bobura::model::station_info");

        p_suite->add(grade::suite());

        return p_suite;
    }


}}}
