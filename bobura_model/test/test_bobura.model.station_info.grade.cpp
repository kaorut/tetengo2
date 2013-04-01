/*! \file
    \brief Test of class bobura::model::station_info::grade.

    Copyright (C) 2007-2013 kaoru

    $Id$
*/

//#include <boost/mpl/at.hpp>
#include <boost/test/unit_test.hpp>

#include <tetengo2.text.h>

#include "test_bobura.model.type_list.h"


namespace
{
    // types

    typedef boost::mpl::at<test_bobura::model::type_list, test_bobura::model::type::string>::type string_type;

    typedef
        boost::mpl::at<test_bobura::model::model_type_list, test_bobura::model::type::model::grade_type_set>::type
        grade_type_set_type;

    typedef grade_type_set_type::grade_type grade_type;

    typedef grade_type_set_type::local_type local_type;

    typedef grade_type_set_type::principal_type principal_type;

    typedef grade_type_set_type::local_terminal_type local_terminal_type;

    typedef grade_type_set_type::principal_terminal_type principal_terminal_type;

    class concrete_grade : public grade_type
    {
    public:
        concrete_grade()
        :
        grade_type(),
        m_name(TETENGO2_TEXT("hoge"))
        {}

        virtual ~concrete_grade()
        TETENGO2_CPP11_NOEXCEPT
        {}

    private:
        string_type m_name;

        virtual const string_type& name_impl()
        const override
        {
            return m_name;
        }

    };


}


BOOST_AUTO_TEST_SUITE(test_bobura)
BOOST_AUTO_TEST_SUITE(model)
BOOST_AUTO_TEST_SUITE(station_info)
BOOST_AUTO_TEST_SUITE(grade)
    // test cases

    BOOST_AUTO_TEST_CASE(construction)
    {
        BOOST_TEST_PASSPOINT();

        const concrete_grade grade;
    }

    BOOST_AUTO_TEST_CASE(name)
    {
        BOOST_TEST_PASSPOINT();

        const concrete_grade grade;

        BOOST_CHECK(grade.name() == string_type(TETENGO2_TEXT("hoge")));
    }


BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE(local)
    // test cases

    BOOST_AUTO_TEST_CASE(instance)
    {
        BOOST_TEST_PASSPOINT();

        local_type::instance();
    }

    BOOST_AUTO_TEST_CASE(name)
    {
        BOOST_TEST_PASSPOINT();

        BOOST_CHECK(local_type::instance().name() == string_type(TETENGO2_TEXT("local")));
    }


BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE(principal)
    // test cases

    BOOST_AUTO_TEST_CASE(instance)
    {
        BOOST_TEST_PASSPOINT();

        principal_type::instance();
    }

    BOOST_AUTO_TEST_CASE(name)
    {
        BOOST_TEST_PASSPOINT();

        BOOST_CHECK(principal_type::instance().name() == string_type(TETENGO2_TEXT("principal")));
    }


BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE(local_terminal)
    // test cases

    BOOST_AUTO_TEST_CASE(instance)
    {
        BOOST_TEST_PASSPOINT();

        local_terminal_type::instance();
    }

    BOOST_AUTO_TEST_CASE(name)
    {
        BOOST_TEST_PASSPOINT();

        BOOST_CHECK(local_terminal_type::instance().name() == string_type(TETENGO2_TEXT("local terminal")));
    }


BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE(principal_terminal)
    // test cases

    BOOST_AUTO_TEST_CASE(instance)
    {
        BOOST_TEST_PASSPOINT();

        principal_terminal_type::instance();
    }

    BOOST_AUTO_TEST_CASE(name)
    {
        BOOST_TEST_PASSPOINT();

        BOOST_CHECK(principal_terminal_type::instance().name() == string_type(TETENGO2_TEXT("principal terminal")));
    }


BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()
