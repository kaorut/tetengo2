/*! \file
    \brief Test of class bobura::model::serializer::bzip2_writer.

    Copyright (C) 2007-2013 kaoru

    $Id$
*/

//#include <memory>
//#include <sstream>
//#include <string>
//#include <utility>

//#include <boost/mpl/at.hpp>
#include <boost/test/unit_test.hpp>

#include <tetengo2.cpp11.h>
#include <tetengo2.text.h>
#include <tetengo2.unique.h>
#include <tetengo2.utility.h>

#include "test_bobura.model.type_list.h"


namespace
{
    // types

    typedef
        boost::mpl::at<test_bobura::model::model_type_list, test_bobura::model::type::model::timetable>::type
        timetable_type;

    typedef
        boost::mpl::at<
            test_bobura::model::serialization_type_list, test_bobura::model::type::serialization::writer
        >::type
        writer_type;

    typedef writer_type::path_type path_type;

    typedef
        boost::mpl::at<
            test_bobura::model::serialization_type_list, test_bobura::model::type::serialization::bzip2_writer
        >::type
        bzip2_writer_type;

    class concrete_writer : public writer_type
    {
    public:
        concrete_writer()
        :
        writer_type()
        {}

        virtual ~concrete_writer()
        TETENGO2_CPP11_NOEXCEPT
        {}


    private:
        virtual path_type extension_impl()
        const
        {
            return path_type(TETENGO2_TEXT("hoge.ext"));
        }

        virtual void write_impl(const timetable_type& timetable, output_stream_type& output_stream)
        {
            tetengo2::suppress_unused_variable_warning(timetable, output_stream);
        }


    };


}

BOOST_AUTO_TEST_SUITE(test_bobura)
BOOST_AUTO_TEST_SUITE(model)
BOOST_AUTO_TEST_SUITE(serializer)
BOOST_AUTO_TEST_SUITE(bzip2_writer)
    // test cases

    BOOST_AUTO_TEST_CASE(construction)
    {
        BOOST_TEST_PASSPOINT();

        std::unique_ptr<writer_type> p_writer = tetengo2::make_unique<concrete_writer>();
        const bzip2_writer_type bzip2_writer(std::move(p_writer));
    }

    BOOST_AUTO_TEST_CASE(extension)
    {
        BOOST_TEST_PASSPOINT();

        std::unique_ptr<writer_type> p_writer = tetengo2::make_unique<concrete_writer>();
        const bzip2_writer_type bzip2_writer(std::move(p_writer));

        BOOST_CHECK(bzip2_writer.extension() == path_type(TETENGO2_TEXT("hoge.ext_bz2")));
    }

    BOOST_AUTO_TEST_CASE(selects)
    {
        BOOST_TEST_PASSPOINT();

        std::unique_ptr<writer_type> p_writer = tetengo2::make_unique<concrete_writer>();
        const bzip2_writer_type bzip2_writer(std::move(p_writer));

        BOOST_CHECK(bzip2_writer.selects(path_type(TETENGO2_TEXT("hoge.ext_bz2"))));
        BOOST_CHECK(!bzip2_writer.selects(path_type(TETENGO2_TEXT("hoge.ext"))));
        BOOST_CHECK(!bzip2_writer.selects(path_type()));
    }

    BOOST_AUTO_TEST_CASE(write)
    {
        BOOST_TEST_PASSPOINT();

        std::unique_ptr<writer_type> p_writer = tetengo2::make_unique<concrete_writer>();
        bzip2_writer_type bzip2_writer(std::move(p_writer));
        const timetable_type timetable;
        std::ostringstream stream;
        bzip2_writer.write(timetable, stream);

        const std::string result = stream.str();
        BOOST_CHECK(result.substr(0, 2) == "BZ");
    }


BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()
