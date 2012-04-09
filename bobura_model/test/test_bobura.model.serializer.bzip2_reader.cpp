/*! \file
    \brief Test of class bobura::model::serializer::bzip2_reader.

    Copyright (C) 2007-2012 kaoru

    $Id$
*/

//#include <memory>
#include <stdexcept>
#include <string>
#include <utility>

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
            test_bobura::model::serialization_type_list,
            test_bobura::model::type::serialization::reader
        >::type
        reader_type;

    typedef
        boost::mpl::at<
            test_bobura::model::type_list, test_bobura::model::type::string
        >::type
        string_type;

    typedef
        boost::mpl::at<
            test_bobura::model::model_type_list,
            test_bobura::model::type::model::timetable
        >::type
        timetable_type;

    typedef
        boost::mpl::at<
            test_bobura::model::serialization_type_list,
            test_bobura::model::type::serialization::bzip2_reader
        >::type
        bzip2_reader_type;

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
            return true;
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
BOOST_AUTO_TEST_SUITE(bzip2_reader)
    // test cases

    BOOST_AUTO_TEST_CASE(construction)
    {
        BOOST_TEST_PASSPOINT();

        std::unique_ptr<reader_type> p_reader =
            tetengo2::make_unique<concrete_reader>();
        const bzip2_reader_type bzip2_reader(std::move(p_reader));
    }

    BOOST_AUTO_TEST_CASE(selects)
    {
        BOOST_TEST_PASSPOINT();

        {
            std::unique_ptr<reader_type> p_reader =
                tetengo2::make_unique<concrete_reader>();
            bzip2_reader_type bzip2_reader(std::move(p_reader));

            const std::string input("BZ");
            BOOST_CHECK(bzip2_reader.selects(input.begin(), input.end()));
        }
        {
            std::unique_ptr<reader_type> p_reader =
                tetengo2::make_unique<concrete_reader>();
            bzip2_reader_type bzip2_reader(std::move(p_reader));

            const std::string input("AZ");
            BOOST_CHECK(!bzip2_reader.selects(input.begin(), input.end()));
        }
    }

    BOOST_AUTO_TEST_CASE(read)
    {
        BOOST_TEST_PASSPOINT();

        BOOST_WARN_MESSAGE(false, "Not implemented yet.");
    }


BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()
