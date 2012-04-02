/*! \file
    \brief Test of class bobura::model::serializer::writer_selector.

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

    typedef writer_type::path_string_type path_string_type;

    typedef
        boost::mpl::at<
            test_bobura::model::serialization_type_list,
            test_bobura::model::type::serialization::writer_selector
        >::type
        writer_set_type;

    class concrete_writer : public writer_type
    {
    public:
        typedef 
            std::basic_string<output_stream_type::char_type>
            output_string_type;

        concrete_writer(path_string_type&& extention)
        :
        writer_type(),
        m_extention(std::forward<path_string_type>(extention))
        {}

        virtual ~concrete_writer()
        TETENGO2_CPP11_NOEXCEPT
        {}


    private:
        const path_string_type m_extention;

        virtual path_string_type extention_impl()
        const
        {
            return m_extention;
        }

        virtual void write_impl(
            const timetable_type& timetable,
            output_stream_type&   output_stream
        )
        {
            const output_string_type output(
                m_extention.begin(), m_extention.end()
            );
            output_stream << output;
        }


    };


    // functions

    std::vector<std::unique_ptr<writer_type>> create_concrete_writers()
    {
        std::vector<std::unique_ptr<writer_type>> writers;

        writers.push_back(
            tetengo2::make_unique<concrete_writer>(
                path_string_type(TETENGO2_TEXT("hoge"))
            )
        );
        writers.push_back(
            tetengo2::make_unique<concrete_writer>(
                path_string_type(TETENGO2_TEXT("fuga"))
            )
        );
        writers.push_back(
            tetengo2::make_unique<concrete_writer>(path_string_type())
        );

        return std::move(writers);
    }


}


BOOST_AUTO_TEST_SUITE(test_bobura)
BOOST_AUTO_TEST_SUITE(model)
BOOST_AUTO_TEST_SUITE(serializer)
BOOST_AUTO_TEST_SUITE(writer_selector)
    // test cases

    BOOST_AUTO_TEST_CASE(construction)
    {
        BOOST_TEST_PASSPOINT();

        {
            std::vector<std::unique_ptr<writer_type>> concrete_writers =
                create_concrete_writers();
            const writer_set_type writer_selector(
                std::move(concrete_writers), path_string_type()
            );
        }
        {
            BOOST_CHECK_THROW(
                writer_set_type(
                    std::vector<std::unique_ptr<writer_type>>(),
                    path_string_type()
                ),
                std::invalid_argument
            );
        }
    }

    BOOST_AUTO_TEST_CASE(extention)
    {
        BOOST_TEST_PASSPOINT();

        std::vector<std::unique_ptr<writer_type>> concrete_writers =
            create_concrete_writers();
        const writer_set_type writer_selector(
            std::move(concrete_writers), path_string_type()
        );

        BOOST_CHECK_THROW(writer_selector.extention(), std::logic_error);
    }

    BOOST_AUTO_TEST_CASE(selects)
    {
        BOOST_TEST_PASSPOINT();

        std::vector<std::unique_ptr<writer_type>> concrete_writers =
            create_concrete_writers();
        const writer_set_type writer_selector(
            std::move(concrete_writers), path_string_type()
        );

        BOOST_CHECK_THROW(
            writer_selector.selects(path_string_type(TETENGO2_TEXT("hoge"))),
            std::logic_error
        );
        BOOST_CHECK_THROW(
            writer_selector.selects(path_string_type(TETENGO2_TEXT("foo"))),
            std::logic_error
        );
        BOOST_CHECK_THROW(
            writer_selector.selects(path_string_type()), std::logic_error
        );
    }

    BOOST_AUTO_TEST_CASE(write)
    {
        BOOST_TEST_PASSPOINT();

        {
            std::vector<std::unique_ptr<writer_type>> concrete_writers =
                create_concrete_writers();
            writer_set_type writer_selector(
                std::move(concrete_writers),
                path_string_type(TETENGO2_TEXT("hoge"))
            );
            const timetable_type timetable;
            std::ostringstream stream;
            writer_selector.write(timetable, stream);

            BOOST_CHECK(stream.str() == std::string("hoge"));
        }
        {
            std::vector<std::unique_ptr<writer_type>> concrete_writers =
                create_concrete_writers();
            writer_set_type writer_selector(
                std::move(concrete_writers),
                path_string_type(TETENGO2_TEXT("fuga"))
            );
            const timetable_type timetable;
            std::ostringstream stream;
            writer_selector.write(timetable, stream);

            BOOST_CHECK(stream.str() == std::string("fuga"));
        }
        {
            std::vector<std::unique_ptr<writer_type>> concrete_writers =
                create_concrete_writers();
            writer_set_type writer_selector(
                std::move(concrete_writers), path_string_type()
            );
            const timetable_type timetable;
            std::ostringstream stream;
            writer_selector.write(timetable, stream);

            BOOST_CHECK(stream.str().empty());
        }
        {
            std::vector<std::unique_ptr<writer_type>> concrete_writers =
                create_concrete_writers();
            writer_set_type writer_selector(
                std::move(concrete_writers),
                path_string_type(TETENGO2_TEXT("foo"))
            );
            const timetable_type timetable;
            std::ostringstream stream;
            writer_selector.write(timetable, stream);

            BOOST_CHECK(stream.str() == std::string("hoge"));
        }
    }


BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()