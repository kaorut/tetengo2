/*! \file
    \brief Test of class bobura::timetable_model.

    Copyright (C) 2007-2012 kaoru

    $Id$
*/

//#include <memory>
//#include <stdexcept>
//#include <utility>

//#include <boost/mpl/at.hpp>
#include <boost/test/unit_test.hpp>

#include <tetengo2.text.h>
#include <tetengo2.unique.h>

#include "bobura.type_list.h"


namespace
{
    // types

    typedef boost::mpl::at<bobura::model_type_list, bobura::type::model::model>::type model_type;

    typedef boost::mpl::at<bobura::common_type_list, bobura::type::string>::type string_type;

    typedef model_type::timetable_type timetable_type;


}


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
            const model_type model;

            const timetable_type& timetable = model.timetable();

            BOOST_CHECK(timetable.title().empty());
        }
    }

    BOOST_AUTO_TEST_CASE(has_path)
    {
        BOOST_TEST_PASSPOINT();

        {
            const model_type model;

            BOOST_CHECK(!model.has_path());
        }
        {
            model_type model;
            std::unique_ptr<timetable_type> p_timetable = tetengo2::make_unique<timetable_type>();
            model.reset_timetable(std::move(p_timetable), model_type::path_type(string_type(TETENGO2_TEXT("hoge"))));

            BOOST_CHECK(model.has_path());
        }
    }

    BOOST_AUTO_TEST_CASE(path)
    {
        BOOST_TEST_PASSPOINT();

        {
            const model_type model;

            BOOST_CHECK_THROW(model.path(), std::logic_error);
        }
        {
            model_type model;
            std::unique_ptr<timetable_type> p_timetable = tetengo2::make_unique<timetable_type>();
            model.reset_timetable(std::move(p_timetable), model_type::path_type(string_type(TETENGO2_TEXT("hoge"))));

            BOOST_CHECK(model.path() == model_type::path_type(string_type(TETENGO2_TEXT("hoge"))));
        }
    }

    BOOST_AUTO_TEST_CASE(set_path)
    {
        BOOST_TEST_PASSPOINT();

        model_type model;
        model.set_path(model_type::path_type(string_type(TETENGO2_TEXT("hoge"))));

        BOOST_CHECK(model.path() == model_type::path_type(string_type(TETENGO2_TEXT("hoge"))));
    }

    BOOST_AUTO_TEST_CASE(reset_timetable)
    {
        BOOST_TEST_PASSPOINT();

        {
            model_type model;

            model.reset_timetable(tetengo2::make_unique<timetable_type>());
        }
        {
            model_type model;

            model.reset_timetable(
                tetengo2::make_unique<timetable_type>(), model_type::path_type(string_type(TETENGO2_TEXT("hoge")))
            );
        }
        {
            model_type model;

            BOOST_CHECK_THROW(
                model.reset_timetable(
                    std::unique_ptr<timetable_type>(), model_type::path_type(string_type(TETENGO2_TEXT("hoge")))
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
