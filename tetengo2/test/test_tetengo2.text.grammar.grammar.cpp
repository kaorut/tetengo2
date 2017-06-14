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
BOOST_AUTO_TEST_SUITE(grammar)
    // test cases

    BOOST_AUTO_TEST_CASE(construction)
    {
        BOOST_TEST_PASSPOINT();

        const concrete_grammar grammar;
    }

    
BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()
