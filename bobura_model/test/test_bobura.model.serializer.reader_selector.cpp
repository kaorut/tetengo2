/*! \file
    \brief Test of class bobura::model::serializer::reader_selector.

    Copyright (C) 2007-2012 kaoru

    $Id$
*/

//#include <iterator>
//#include <memory>
//#include <stdexcept>
//#include <sstream>
//#include <utility>
//#include <vector>

//#include <boost/mpl/at.hpp>
//#include <boost/spirit/include/support_multi_pass.hpp>
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
            test_bobura::model::type::serialization::reader_selector
        >::type
        reader_selector_type;

    class concrete_reader : public reader_type
    {
    public:
        concrete_reader(string_type&& title)
        :
        reader_type(),
        m_title(std::forward<string_type>(title))
        {}

        virtual ~concrete_reader()
        TETENGO2_CPP11_NOEXCEPT
        {}


    private:
        const string_type m_title;

        virtual bool selects_impl(const iterator first, const iterator last)
        {
            return string_type(first, last) == m_title;
        }

        virtual std::unique_ptr<timetable_type> read_impl(
            const iterator first,
            const iterator last
        )
        {
            std::unique_ptr<timetable_type> p_timetable =
                tetengo2::make_unique<timetable_type>();

            p_timetable->set_title(m_title);

            return std::move(p_timetable);
        }


    };


    // functions

    std::vector<std::unique_ptr<reader_type>> create_concrete_readers()
    {
        std::vector<std::unique_ptr<reader_type>> readers;

        readers.push_back(
            tetengo2::make_unique<concrete_reader>(
                string_type(TETENGO2_TEXT("hoge"))
            )
        );
        readers.push_back(
            tetengo2::make_unique<concrete_reader>(
                string_type(TETENGO2_TEXT("fuga"))
            )
        );

        return std::move(readers);
    }


}


BOOST_AUTO_TEST_SUITE(test_bobura)
BOOST_AUTO_TEST_SUITE(model)
BOOST_AUTO_TEST_SUITE(serializer)
BOOST_AUTO_TEST_SUITE(reader_selector)
    // test cases

    BOOST_AUTO_TEST_CASE(construction)
    {
        BOOST_TEST_PASSPOINT();

        {
            std::vector<std::unique_ptr<reader_type>> concrete_readers =
                create_concrete_readers();
            const reader_selector_type reader_selector(
                std::move(concrete_readers)
            );
        }
        {
            std::vector<std::unique_ptr<reader_type>> concrete_readers;
            BOOST_CHECK_THROW(
                reader_selector_type(std::move(concrete_readers)),
                std::invalid_argument
            );
        }
    }

    BOOST_AUTO_TEST_CASE(selects)
    {
        BOOST_TEST_PASSPOINT();

        std::vector<std::unique_ptr<reader_type>> concrete_readers =
            create_concrete_readers();
        reader_selector_type reader_selector(
            std::move(concrete_readers)
        );

        std::istringstream input_stream("hoge");
        BOOST_CHECK_THROW(
            reader_selector.selects(
                boost::spirit::make_default_multi_pass(
                    std::istreambuf_iterator<char>(input_stream)
                ),
                boost::spirit::make_default_multi_pass(
                    std::istreambuf_iterator<char>()
                )
            ),
            std::logic_error
        );
    }

    BOOST_AUTO_TEST_CASE(read)
    {
        BOOST_TEST_PASSPOINT();

        {
            std::vector<std::unique_ptr<reader_type>> concrete_readers =
                create_concrete_readers();
            reader_selector_type reader_selector(
                std::move(concrete_readers)
            );

            std::istringstream input_stream("hoge");
            const std::unique_ptr<timetable_type> p_timetable =
                reader_selector.read(
                    boost::spirit::make_default_multi_pass(
                        std::istreambuf_iterator<char>(input_stream)
                    ),
                    boost::spirit::make_default_multi_pass(
                        std::istreambuf_iterator<char>()
                    )
                );

            BOOST_CHECK(
                p_timetable->title() == string_type(TETENGO2_TEXT("hoge"))
            );
        }
        {
            std::vector<std::unique_ptr<reader_type>> concrete_readers =
                create_concrete_readers();
            reader_selector_type reader_selector(
                std::move(concrete_readers)
            );

            std::istringstream input_stream("fuga");
            const std::unique_ptr<timetable_type> p_timetable =
                reader_selector.read(
                    boost::spirit::make_default_multi_pass(
                        std::istreambuf_iterator<char>(input_stream)
                    ),
                    boost::spirit::make_default_multi_pass(
                        std::istreambuf_iterator<char>()
                    )
                );

            BOOST_CHECK(
                p_timetable->title() == string_type(TETENGO2_TEXT("fuga"))
            );
        }
        {
            std::vector<std::unique_ptr<reader_type>> concrete_readers =
                create_concrete_readers();
            reader_selector_type reader_selector(
                std::move(concrete_readers)
            );

            std::istringstream input_stream("piyo");
            const std::unique_ptr<timetable_type> p_timetable =
                reader_selector.read(
                    boost::spirit::make_default_multi_pass(
                        std::istreambuf_iterator<char>(input_stream)
                    ),
                    boost::spirit::make_default_multi_pass(
                        std::istreambuf_iterator<char>()
                    )
                );

            BOOST_CHECK(
                p_timetable->title() == string_type(TETENGO2_TEXT("hoge"))
            );
        }
    }


BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()
