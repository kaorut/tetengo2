/*! \file
    \brief The definition of tetengo2::json::grammar.

    Copyright (C) 2007-2011 kaoru

    $Id$
*/

#if !defined(TETENGO2_JSON_GRAMMAR_H)
#define TETENGO2_JSON_GRAMMAR_H

#include <cassert>
#include <string>

#include <boost/spirit/include/qi.hpp>
#include <boost/utility.hpp>

#include "tetengo2.cpp0x.h"
#include "tetengo2.text.h"


namespace tetengo2 { namespace json
{
    /*!
        \brief The class template for a grammar.

        The grammar of JSON is based on RFC4627.
        http://www.ietf.org/rfc/rfc4627.txt

        \tparam ForwardIterator A forward iterator type.
    */
    template <typename ForwardIterator>
    class grammar :
        public boost::spirit::qi::grammar<
            ForwardIterator,
            std::basic_string<typename ForwardIterator::value_type> ()
        >
    {
    public:
        // types

        //! The iterator type.
        typedef ForwardIterator iterator;

        //! The character type.
        typedef typename iterator::value_type char_type;

        //! The string type.
        typedef std::basic_string<char_type> string_type;

        //! The rule type.
        typedef boost::spirit::qi::rule<iterator, string_type ()> rule_type;


        // constructors and destructor

        /*!
            \brief Creates a grammar.
        */
        grammar()
        :
        grammar::base_type(m_json, "json")
        {
            namespace qi = boost::spirit::qi;

            m_json = qi::string("dummy");

            m_string =
                m_quotation_mark >> *m_char >> m_quotation_mark;
            m_char =
                m_unescaped |
                (
                    m_escape >> (
                        qi::char_(char_type(TETENGO2_TEXT('"'))) |
                        qi::char_(char_type(TETENGO2_TEXT('\\'))) |
                        qi::char_(char_type(TETENGO2_TEXT('/'))) |
                        qi::char_(char_type(TETENGO2_TEXT('b'))) |
                        qi::char_(char_type(TETENGO2_TEXT('f'))) |
                        qi::char_(char_type(TETENGO2_TEXT('n'))) |
                        qi::char_(char_type(TETENGO2_TEXT('r'))) |
                        qi::char_(char_type(TETENGO2_TEXT('t'))) |
                        (
                            qi::char_(char_type(TETENGO2_TEXT('n'))) >>
                            qi::repeat(4)[qi::xdigit]
                        )
                    )
                );
            m_escape =
                char_type(TETENGO2_TEXT('\\'));
            m_quotation_mark =
                char_type(TETENGO2_TEXT('"'));
            m_unescaped =
                qi::char_ -
                qi::char_(char_type(0x00), char_type(0x19)) -
                m_quotation_mark -
                m_escape;
        }


        // functions

        const rule_type& string()
        const
        {
            return m_string;
        }


    private:
        // types

        typedef
            boost::spirit::qi::rule<iterator, char_type ()> char_rule_type;


        // variables

        rule_type m_json;

        rule_type m_string;

        rule_type m_char;

        rule_type m_escape;

        char_rule_type m_quotation_mark;

        char_rule_type m_unescaped;


    };


}}


#endif
