/*! \file
    \brief Test of namespace bobura::model.

    Copyright (C) 2007-2008 kaoru

    $Id$
*/

#include "precompiled.test.h"

//#include <boost/test/unit_test.hpp>

#include "init_bobura.model.h"
#include "init_bobura.model.station_info.h"
#include "init_bobura.model.timetable_info.h"
#include "init_bobura.model.train_info.h"
#include "test_bobura.model.station.h"
#include "test_bobura.model.timetable.h"
#include "test_bobura.model.train.h"


namespace test_bobura { namespace model
{
    // functions

    boost::unit_test::test_suite* suite()
    {
        boost::unit_test::test_suite* const p_suite =
            BOOST_TEST_SUITE("test_bobura::model");

        p_suite->add(station_info::suite());
        p_suite->add(timetable_info::suite());
        p_suite->add(train_info::suite());

        p_suite->add(station::suite());
        p_suite->add(timetable::suite());
        p_suite->add(train::suite());

        return p_suite;
    }


}}
