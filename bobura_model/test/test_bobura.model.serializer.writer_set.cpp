/*! \file
    \brief Test of class bobura::model::serializer::writer_set.

    Copyright (C) 2007-2012 kaoru

    $Id$
*/

#include <memory>
//#include <sstream>
#include <utility>
#include <vector>

//#include <boost/mpl/at.hpp>
#include <boost/test/unit_test.hpp>

#include <tetengo2.cpp11.h>
#include <tetengo2.text.h>

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
            test_bobura::model::serialization_type_list,
            test_bobura::model::type::serialization::writer
        >::type
        writer_type;

    typedef
        boost::mpl::at<
            test_bobura::model::serialization_type_list,
            test_bobura::model::type::serialization::writer_set
        >::type
        writer_set_type;

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
        virtual path_string_type extention_impl()
        const
        {
            return path_string_type();
        }

        virtual void write_impl(
            const timetable_type& timetable,
            output_stream_type&   output_stream
        )
        {}


    };


    // functions

    std::vector<std::unique_ptr<writer_type>> create_concrete_writers()
    {
        std::vector<std::unique_ptr<writer_type>> writers;

        writers.push_back(tetengo2::make_unique<concrete_writer>());
        writers.push_back(tetengo2::make_unique<concrete_writer>());
        writers.push_back(tetengo2::make_unique<concrete_writer>());

        return std::move(writers);
    }


}


BOOST_AUTO_TEST_SUITE(test_bobura)
BOOST_AUTO_TEST_SUITE(model)
BOOST_AUTO_TEST_SUITE(serializer)
BOOST_AUTO_TEST_SUITE(writer_set)
    // test cases

    BOOST_AUTO_TEST_CASE(construction)
    {
        BOOST_TEST_PASSPOINT();

        std::vector<std::unique_ptr<writer_type>> concrete_writers =
            create_concrete_writers();
        const writer_set_type writer_set(std::move(concrete_writers));
    }

    BOOST_AUTO_TEST_CASE(extention)
    {
        BOOST_TEST_PASSPOINT();

        BOOST_WARN_MESSAGE(false, "Not implemented yet.");
    }

    BOOST_AUTO_TEST_CASE(adopts)
    {
        BOOST_TEST_PASSPOINT();

        BOOST_WARN_MESSAGE(false, "Not implemented yet.");
    }

    BOOST_AUTO_TEST_CASE(write)
    {
        BOOST_TEST_PASSPOINT();

        //concrete_writer writer_set;
        //const timetable_type timetable;
        //std::ostringstream stream;
        //writer_set.write(timetable, stream);
    }


BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()
