/*! \file
    \brief Test of class bobura::timetable_model.

    Copyright (C) 2007-2012 kaoru

    $Id$
*/

//#include <memory>
//#include <stdexcept>

//#include <boost/filesystem.hpp>
#include <boost/test/unit_test.hpp>

#include <tetengo2.unique.h>

#include "test_bobura.types.h"


BOOST_AUTO_TEST_SUITE(test_bobura)
BOOST_AUTO_TEST_SUITE(timetable_model)
    // test cases

    BOOST_AUTO_TEST_CASE(construction)
    {
        BOOST_TEST_PASSPOINT();

        const model_type model;
    }

    BOOST_AUTO_TEST_CASE(timetable)
    {
        BOOST_TEST_PASSPOINT();

        {
            const model_type model;

            const timetable_type& timetable = model.timetable();

            BOOST_CHECK(timetable.title().empty());
        }
        {
            model_type model;

            timetable_type& timetable = model.timetable();

            BOOST_CHECK(timetable.title().empty());
        }
    }

    BOOST_AUTO_TEST_CASE(path)
    {
        BOOST_TEST_PASSPOINT();

        const model_type model;

        const model_type::path_type& path = model.path();

        BOOST_CHECK(path.empty());
    }

    BOOST_AUTO_TEST_CASE(reset_timetable)
    {
        BOOST_TEST_PASSPOINT();

        {
            model_type model;

            model.reset_timetable(
                tetengo2::make_unique<timetable_type>(),
                boost::filesystem::path(L"hoge")
            );
        }
        {
            model_type model;

            BOOST_CHECK_THROW(
                model.reset_timetable(
                    std::unique_ptr<timetable_type>(),
                    boost::filesystem::path(L"hoge")
                ),
                std::invalid_argument
            );
        }
    }

    BOOST_AUTO_TEST_CASE(changed)
    {
        BOOST_TEST_PASSPOINT();

        const model_type model;

        BOOST_CHECK(!model.changed());
    }

    BOOST_AUTO_TEST_CASE(set_changed)
    {
        BOOST_TEST_PASSPOINT();

        {
            model_type model;

            model.set_changed(false);

            BOOST_CHECK(!model.changed());
        }
        {
            model_type model;

            model.set_changed(true);

            BOOST_CHECK(model.changed());
        }
    }

    BOOST_AUTO_TEST_CASE(observer_set)
    {
        BOOST_TEST_PASSPOINT();

        {
            const model_type model;

            model.observer_set();
        }
        {
            model_type model;

            model.observer_set();
        }
    }


BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()
