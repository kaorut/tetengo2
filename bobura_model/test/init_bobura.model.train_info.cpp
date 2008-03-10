/*! \file
    \brief Test of namespace bobura::model::train_info.

    Copyright (C) 2007-2008 kaoru

    $Id$
*/

#include "precompiled.test.h"

//#include <boost/test/unit_test.hpp>

#include "init_bobura.model.train_info.h"
#include "test_bobura.model.train_info.stop.h"
#include "test_bobura.model.train_info.time.h"
#include "test_bobura.model.train_info.time_span.h"


namespace test_bobura { namespace model { namespace train_info
{
    // functions

    boost::unit_test::test_suite* suite()
    {
        boost::unit_test::test_suite* const p_suite =
            BOOST_TEST_SUITE("test_bobura::model::train_info");

        p_suite->add(stop::suite());
        p_suite->add(time::suite());
        p_suite->add(time_span::suite());

        return p_suite;
    }


}}}
