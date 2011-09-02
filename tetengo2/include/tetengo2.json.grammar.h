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
        grammar::base_type(m_json_text, "json")
        {
            namespace qi = boost::spirit::qi;

            // 2. JSON Grammar
            m_json_text =
                qi::string("dummy");
            m_begin_array =
                m_ws >> qi::char_(char_type(TETENGO2_TEXT('['))) >> m_ws;
            m_begin_object =
                m_ws >> qi::char_(char_type(TETENGO2_TEXT('{'))) >> m_ws;
            m_end_array =
                m_ws >> qi::char_(char_type(TETENGO2_TEXT(']'))) >> m_ws;
            m_end_object =
                m_ws >> qi::char_(char_type(TETENGO2_TEXT('}'))) >> m_ws;
            m_name_separator =
                m_ws >> qi::char_(char_type(TETENGO2_TEXT(':'))) >> m_ws;
            m_value_separator =
                m_ws >> qi::char_(char_type(TETENGO2_TEXT(','))) >> m_ws;
            m_ws =
                *(
                    qi::char_(char_type(TETENGO2_TEXT(' '))) |
                    qi::char_(char_type(TETENGO2_TEXT('\t'))) |
                    qi::char_(char_type(TETENGO2_TEXT('\n'))) |
                    qi::char_(char_type(TETENGO2_TEXT('\r')))
                );

            // 2.1. Values
            m_value =
                m_false |
                m_null |
                m_true |
                m_object |
                m_array |
                m_number |
                m_string;
            m_false =
                qi::string(string_type(TETENGO2_TEXT("false")));
            m_null =
                qi::string(string_type(TETENGO2_TEXT("null")));
            m_true =
                qi::string(string_type(TETENGO2_TEXT("true")));

            // 2.2. Objects


            // 2.3. Arrays
            m_array =
                m_begin_array >>
                -(m_value >> *(m_value_separator >> m_value)) >>
                m_end_array;

            // 2.4. Numbers
            m_number =
                -m_minus >> m_int >> -m_frac >> -m_exp;
            m_decimal_point =
                qi::char_(char_type(TETENGO2_TEXT('.')));
            m_digit1to9 =
                qi::char_(
                    char_type(TETENGO2_TEXT('1')),
                    char_type(TETENGO2_TEXT('9'))
                );
            m_e =
                qi::char_(char_type(TETENGO2_TEXT('e'))) |
                qi::char_(char_type(TETENGO2_TEXT('E')));
            m_exp =
                m_e >> (m_minus | m_plus) >> +qi::digit;
            m_frac =
                m_decimal_point >> +qi::digit;
            m_int =
                m_zero | (m_digit1to9 >> *qi::digit);
            m_minus =
                qi::char_(char_type(TETENGO2_TEXT('-')));
            m_plus =
                qi::char_(char_type(TETENGO2_TEXT('+')));
            m_zero =
                qi::char_(char_type(TETENGO2_TEXT('0')));

            // 2.5. Strings
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
                            qi::char_(char_type(TETENGO2_TEXT('u'))) >>
                            qi::repeat(4)[qi::xdigit]
                        )
                    )
                );
            m_escape =
                qi::char_(char_type(TETENGO2_TEXT('\\')));
            m_quotation_mark =
                qi::char_(char_type(TETENGO2_TEXT('"')));
            m_unescaped =
                qi::char_ -
                qi::char_(char_type(0x00), char_type(0x19)) -
                m_quotation_mark -
                m_escape;
        }


        // functions

        /*!
            \brief Returns the parser for a value.

            \return The parser for a value.
        */
        const rule_type& value()
        const
        {
            return m_value;
        }

        /*!
            \brief Returns the parser for an array.

            \return The parser for an array.
        */
        const rule_type& array()
        const
        {
            return m_array;
        }

        /*!
            \brief Returns the parser for a number.

            \return The parser for a number.
        */
        const rule_type& number()
        const
        {
            return m_number;
        }

        /*!
            \brief Returns the parser for a string.

            \return The parser for a string.
        */
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

        rule_type m_json_text;

        rule_type m_begin_array;

        rule_type m_begin_object;

        rule_type m_end_array;

        rule_type m_end_object;

        rule_type m_name_separator;

        rule_type m_value_separator;

        rule_type m_ws;

        rule_type m_value;

        rule_type m_false;

        rule_type m_null;

        rule_type m_true;

        rule_type m_object;

        rule_type m_array;

        rule_type m_number;

        char_rule_type m_decimal_point;

        char_rule_type m_digit1to9;

        char_rule_type m_e;

        rule_type m_exp;

        rule_type m_frac;

        rule_type m_int;

        char_rule_type m_minus;

        char_rule_type m_plus;

        char_rule_type m_zero;

        rule_type m_string;

        rule_type m_char;

        rule_type m_escape;

        char_rule_type m_quotation_mark;

        char_rule_type m_unescaped;


    };


}}


#endif
