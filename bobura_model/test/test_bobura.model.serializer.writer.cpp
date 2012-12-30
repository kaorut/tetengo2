/*! \file
    \brief Test of class bobura::model::serializer::writer.

    Copyright (C) 2007-2013 kaoru

    $Id$
*/

//#include <sstream>

//#include <boost/mpl/at.hpp>
#include <boost/test/unit_test.hpp>

#include <tetengo2.text.h>

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

    class concrete_writer : public writer_type
    {
    public:
        concrete_writer()
        :
        writer_type()
        {}

        virtual ~concrete_writer()
        {}


    private:
        virtual path_type extension_impl()
        const
        {
            return path_type(TETENGO2_TEXT("hoge"));
        }

        virtual void write_impl(const timetable_type& timetable, output_stream_type& output_stream)
        {}


    };

}


BOOST_AUTO_TEST_SUITE(test_bobura)
BOOST_AUTO_TEST_SUITE(model)
BOOST_AUTO_TEST_SUITE(serializer)
BOOST_AUTO_TEST_SUITE(writer)
    // test cases

    BOOST_AUTO_TEST_CASE(construction)
    {
        BOOST_TEST_PASSPOINT();

        const concrete_writer writer;
    }

    BOOST_AUTO_TEST_CASE(extension)
    {
        BOOST_TEST_PASSPOINT();

        const concrete_writer writer;

        BOOST_CHECK(writer.extension() == path_type(TETENGO2_TEXT("hoge")));
    }

    BOOST_AUTO_TEST_CASE(selects)
    {
        BOOST_TEST_PASSPOINT();

        const concrete_writer writer;

        BOOST_CHECK(writer.selects(path_type(TETENGO2_TEXT("hoge"))));
        BOOST_CHECK(!writer.selects(path_type(TETENGO2_TEXT("fuga"))));
        BOOST_CHECK(!writer.selects(path_type()));
    }

    BOOST_AUTO_TEST_CASE(write)
    {
        BOOST_TEST_PASSPOINT();

        concrete_writer writer;
        const timetable_type timetable;
        std::ostringstream stream;
        writer.write(timetable, stream);
    }


BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()
