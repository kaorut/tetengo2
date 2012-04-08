/*! \file
    \brief Test of class bobura::model::serializer::reader.

    Copyright (C) 2007-2012 kaoru

    $Id$
*/

//#include <memory>

//#include <boost/mpl/at.hpp>
#include <boost/test/unit_test.hpp>

#include <tetengo2.cpp11.h>
#include <tetengo2.text.h>
#include <tetengo2.unique.h>

#include "test_bobura.model.type_list.h"


namespace
{
    // types

    typedef
        boost::mpl::at<
            test_bobura::model::model_type_list,
            test_bobura::model::type::model::timetable
        >::type
        timetable_type;

    typedef
        boost::mpl::at<
            test_bobura::model::type_list, test_bobura::model::type::string
        >::type
        string_type;

    typedef
        boost::mpl::at<
            test_bobura::model::serialization_type_list,
            test_bobura::model::type::serialization::reader
        >::type
        reader_type;

    class concrete_reader : public reader_type
    {
    public:
        concrete_reader()
        :
        reader_type()
        {}

        virtual ~concrete_reader()
        TETENGO2_CPP11_NOEXCEPT
        {}


    private:
        virtual bool selects_impl(const iterator first, const iterator last)
        {
            return
                string_type(first, last) ==
                string_type(TETENGO2_TEXT("hoge"));
        }

        virtual std::unique_ptr<timetable_type> read_impl(
            const iterator first,
            const iterator last
        )
        {
            return tetengo2::make_unique<timetable_type>();
        }


    };

}


BOOST_AUTO_TEST_SUITE(test_bobura)
BOOST_AUTO_TEST_SUITE(model)
BOOST_AUTO_TEST_SUITE(serializer)
BOOST_AUTO_TEST_SUITE(reader)
    // test cases

    BOOST_AUTO_TEST_CASE(construction)
    {
        BOOST_TEST_PASSPOINT();

        const concrete_reader reader;
    }

    BOOST_AUTO_TEST_CASE(selects)
    {
        BOOST_TEST_PASSPOINT();

        concrete_reader reader;

        {
            const string_type input(TETENGO2_TEXT("hoge"));
            BOOST_CHECK(reader.selects(input.begin(), input.end()));
        }
        {
            const string_type input(TETENGO2_TEXT("fuga"));
            BOOST_CHECK(!reader.selects(input.begin(), input.end()));
        }
    }

    BOOST_AUTO_TEST_CASE(read)
    {
        BOOST_TEST_PASSPOINT();

        concrete_reader reader;
        const string_type input(TETENGO2_TEXT("hoge"));
        const std::unique_ptr<timetable_type> p_timetable =
            reader.read(input.begin(), input.end());

        BOOST_CHECK(p_timetable);
    }


BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()
