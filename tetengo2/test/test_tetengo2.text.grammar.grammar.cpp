/*! \file
    \brief Test of class tetengo2::text::grammar::grammar.

    Copyright (C) 2007-2017 kaoru

    $Id$
*/

#include <string>

#include <boost/test/unit_test.hpp>

#include <tetengo2/text/grammar/grammar.h>


namespace
{
    // types

    using structure_attribute_type = tetengo2::text::grammar::structure_attribute<std::string>;

    using value_type_type = structure_attribute_type::value_type_type;

    using grammar_type = tetengo2::text::grammar::grammar<std::string::const_iterator>;

    class concrete_grammar : public grammar_type
    {
    public:
        using rule_type = grammar_type::rule_type;

        concrete_grammar()
        :
        grammar_type(m_rule),
        m_rule{}
        {}

    private:
        rule_type m_rule;

    };


}


BOOST_AUTO_TEST_SUITE(test_tetengo2)
BOOST_AUTO_TEST_SUITE(text)
BOOST_AUTO_TEST_SUITE(grammar)
BOOST_AUTO_TEST_SUITE(structure_attribute)
    // test cases

    BOOST_AUTO_TEST_CASE(construction)
    {
        BOOST_TEST_PASSPOINT();

        const std::string attribute{ "fuga" };
        const structure_attribute_type structure_attribute{ "hoge", value_type_type::number, attribute };
    }

    BOOST_AUTO_TEST_CASE(name)
    {
        BOOST_TEST_PASSPOINT();

        const std::string attribute{ "fuga" };
        const structure_attribute_type structure_attribute{ "hoge", value_type_type::number, attribute };

        BOOST_CHECK(structure_attribute.name() == "hoge");
    }

    BOOST_AUTO_TEST_CASE(value_type)
    {
        BOOST_TEST_PASSPOINT();

        BOOST_TEST_PASSPOINT();

        const std::string attribute{ "fuga" };
        const structure_attribute_type structure_attribute{ "hoge", value_type_type::number, attribute };

        BOOST_CHECK(structure_attribute.value_type() == value_type_type::number);
    }

    BOOST_AUTO_TEST_CASE(attribute)
    {
        BOOST_TEST_PASSPOINT();

        BOOST_TEST_PASSPOINT();

        const std::string attribute{ "fuga" };
        const structure_attribute_type structure_attribute{
            "hoge", structure_attribute_type::value_type_type::number, attribute
        };

        BOOST_CHECK(structure_attribute.attribute() == "fuga");
    }

    
BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE(grammar)
    // test cases

    BOOST_AUTO_TEST_CASE(construction)
    {
        BOOST_TEST_PASSPOINT();

        const concrete_grammar grammar;
    }

    BOOST_AUTO_TEST_CASE(on_structure_begin)
    {
        BOOST_TEST_PASSPOINT();

        {
            const concrete_grammar grammar;

            grammar.on_structure_begin();
        }
        {
            concrete_grammar grammar;

            grammar.on_structure_begin();
        }
    }

    BOOST_AUTO_TEST_CASE(on_structure_end)
    {
        BOOST_TEST_PASSPOINT();

        {
            const concrete_grammar grammar;

            grammar.on_structure_end();
        }
        {
            concrete_grammar grammar;

            grammar.on_structure_end();
        }
    }

    BOOST_AUTO_TEST_CASE(on_value)
    {
        BOOST_TEST_PASSPOINT();

        {
            const concrete_grammar grammar;

            grammar.on_value();
        }
        {
            concrete_grammar grammar;

            grammar.on_value();
        }
    }

    
BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()
