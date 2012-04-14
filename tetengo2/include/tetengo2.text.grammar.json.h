/*! \file
    \brief The definition of tetengo2::text::grammar::json.

    Copyright (C) 2007-2012 kaoru

    $Id$
*/

#if !defined(TETENGO2_TEXT_GRAMMAR_JSON_H)
#define TETENGO2_TEXT_GRAMMAR_JSON_H

#include <string>
#include <tuple>
#include <vector>

#include <boost/signals2.hpp>
#include <boost/spirit/include/qi.hpp>

#include "tetengo2.cpp11.h"
#include "tetengo2.text.h"


namespace tetengo2 { namespace text { namespace grammar
{
    /*!
        \brief The class template for a grammar of JSON.

        The grammar of JSON is based on RFC4627.
        http://www.ietf.org/rfc/rfc4627.txt

        \tparam ForwardIterator A forward iterator type.
    */
    template <typename ForwardIterator>
    class json :
        public boost::spirit::qi::grammar<ForwardIterator, std::basic_string<typename ForwardIterator::value_type> ()>
    {
    public:
        // types

        //! The iterator type.
        typedef ForwardIterator iterator;

        //! The character type.
        typedef typename iterator::value_type char_type;

        //! The string type.
        typedef std::basic_string<char_type> string_type;

        //! The value type type.
        enum value_type_type
        {
            value_type_string,  //!< A string.
            value_type_number,  //!< A number.
            value_type_boolean, //!< A boolean.
            value_type_null,    //!< A null.
        };

        //! The attribute type.
        typedef std::tuple<string_type, value_type_type, const string_type&> structure_attribute_type;

        //! The structure signal type.
        typedef
            boost::signals2::signal<void (const std::string&, const std::vector<structure_attribute_type>&)>
            structure_signal_type;

        //! The value signal type.
        typedef boost::signals2::signal<void (value_type_type, const string_type&)> value_signal_type;

        //! The rule type.
        typedef boost::spirit::qi::rule<iterator, string_type ()> rule_type;


        // constructors and destructor

        /*!
            \brief Creates a grammar of JSON.
        */
        json()
        :
        json::base_type(m_json_text, "json"),
        m_on_structure_begin(),
        m_on_structure_end(),
        m_on_value(),
        m_json_text(),
        m_begin_array(),
        m_begin_object(),
        m_end_array(),
        m_end_object(),
        m_name_separator(),
        m_value_separator(),
        m_ws(),
        m_value(),
        m_false(),
        m_null(),
        m_true(),
        m_object(),
        m_member(),
        m_array(),
        m_number(),
        m_decimal_point(),
        m_digit1to9(),
        m_e(),
        m_exp(),
        m_frac(),
        m_int(),
        m_minus(),
        m_plus(),
        m_zero(),
        m_string(),
        m_char(),
        m_escape(),
        m_quotation_mark(),
        m_unescaped()
        {
            define_rules();
        }


        // functions
        
        /*!
            \brief Returns the structure begin signal.

            The signal is called when the parser parses the beginning tokens of an object, a member and an array
            structure.

            \return The structure signal.
        */
        const structure_signal_type& on_structure_begin()
        const
        {
            return m_on_structure_begin;
        }

        /*!
            \brief Returns the structure begin signal.

            The signal is called when the parser parses the beginning tokens of an object, a member and an array
            structure.

            \return The structure signal.
        */
        structure_signal_type& on_structure_begin()
        {
            return m_on_structure_begin;
        }

        /*!
            \brief Returns the structure end signal.

            The signal is called when the parser parses the ending tokens of an object, a member and an array
            structure.

            \return The structure signal.
        */
        const structure_signal_type& on_structure_end()
        const
        {
            return m_on_structure_end;
        }

        /*!
            \brief Returns the structure end signal.

            The signal is called when the parser parses the ending tokens of an object, a member and an array
            structure.

            \return The structure signal.
        */
        structure_signal_type& on_structure_end()
        {
            return m_on_structure_end;
        }

        /*!
            \brief Returns the value signal.

            The signal is called when the parser parses a value.

            \return The value signal.
        */
        const value_signal_type& on_value()
        const
        {
            return m_on_value;
        }

        /*!
            \brief Returns the value signal.

            The signal is called when the parser parses a value.

            \return The value signal.
        */
        value_signal_type& on_value()
        {
            return m_on_value;
        }

        /*!
            \brief Returns the parser for a JSON text.

            \return The parser for a JSON text.
        */
        const rule_type& json_text()
        const
        {
            return m_json_text;
        }

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
            \brief Returns the parser for an object.

            \return The parser for an object.
        */
        const rule_type& object()
        const
        {
            return m_object;
        }

        /*!
            \brief Returns the parser for a member.

            \return The parser for a member.
        */
        const rule_type& member()
        const
        {
            return m_member;
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

        typedef boost::spirit::qi::rule<iterator, char_type ()> char_rule_type;


        // variables

        structure_signal_type m_on_structure_begin;

        structure_signal_type m_on_structure_end;

        value_signal_type m_on_value;

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

        rule_type m_member;

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


        // functions

        void object_begun(const boost::spirit::qi::unused_type&)
        {
            m_on_structure_begin(string_type(TETENGO2_TEXT("object")), std::vector<structure_attribute_type>());
        }

        void object_ended(const boost::spirit::qi::unused_type&)
        {
            m_on_structure_end(string_type(TETENGO2_TEXT("object")), std::vector<structure_attribute_type>());
        }

        void member_begun(const string_type& attribute)
        {
            m_on_structure_begin(
                string_type(TETENGO2_TEXT("member")),
                std::vector<structure_attribute_type>(
                    1, structure_attribute_type(string_type(TETENGO2_TEXT("name")), value_type_string, attribute)
                )
            );
        }

        void member_ended(const boost::spirit::qi::unused_type&)
        {
            m_on_structure_end(string_type(TETENGO2_TEXT("member")), std::vector<structure_attribute_type>());
        }

        void array_begun(const boost::spirit::qi::unused_type&)
        {
            m_on_structure_begin(string_type(TETENGO2_TEXT("array")), std::vector<structure_attribute_type>());
        }

        void array_ended(const boost::spirit::qi::unused_type&)
        {
            m_on_structure_end(string_type(TETENGO2_TEXT("array")), std::vector<structure_attribute_type>());
        }

        void string_passed(const string_type& attribute)
        {
            m_on_value(value_type_string, attribute);
        }

        void number_passed(const string_type& attribute)
        {
            m_on_value(value_type_number, attribute);
        }

        void boolean_passed(const string_type& attribute)
        {
            m_on_value(value_type_boolean, attribute);
        }

        void null_passed(const string_type& attribute)
        {
            m_on_value(value_type_null, attribute);
        }

        void define_rules()
        {
            namespace qi = boost::spirit::qi;

            // 2. JSON Grammar
            m_json_text = m_object | m_array;
            m_json_text.name("JSON-text");
            m_begin_array = m_ws >> qi::char_(char_type(TETENGO2_TEXT('['))) >> m_ws;
            m_begin_object = m_ws >> qi::char_(char_type(TETENGO2_TEXT('{'))) >> m_ws;
            m_end_array = m_ws >> qi::char_(char_type(TETENGO2_TEXT(']'))) >> m_ws;
            m_end_object = m_ws >> qi::char_(char_type(TETENGO2_TEXT('}'))) >> m_ws;
            m_name_separator = m_ws >> qi::char_(char_type(TETENGO2_TEXT(':'))) >> m_ws;
            m_value_separator = m_ws >> qi::char_(char_type(TETENGO2_TEXT(','))) >> m_ws;
            m_ws =
                *(
                    qi::char_(char_type(TETENGO2_TEXT(' '))) |
                    qi::char_(char_type(TETENGO2_TEXT('\t'))) |
                    qi::char_(char_type(TETENGO2_TEXT('\n'))) |
                    qi::char_(char_type(TETENGO2_TEXT('\r')))
                );

            // 2.1. Values
            m_value =
                m_false[TETENGO2_CPP11_BIND(&json::boolean_passed, this, cpp11::placeholders_1())] |
                m_null[TETENGO2_CPP11_BIND(&json::null_passed, this, cpp11::placeholders_1())] |
                m_true[TETENGO2_CPP11_BIND(&json::boolean_passed, this, cpp11::placeholders_1())] |
                m_object |
                m_array |
                m_number[TETENGO2_CPP11_BIND(&json::number_passed, this, cpp11::placeholders_1())] |
                m_string[TETENGO2_CPP11_BIND(&json::string_passed, this, cpp11::placeholders_1())];
            m_value.name("value");
            m_false = qi::string(string_type(TETENGO2_TEXT("false")));
            m_null = qi::string(string_type(TETENGO2_TEXT("null")));
            m_true = qi::string(string_type(TETENGO2_TEXT("true")));

            // 2.2. Objects
            m_object =
                m_begin_object[TETENGO2_CPP11_BIND(&json::object_begun, this, cpp11::placeholders_1())] >>
                -(m_member >> *(m_value_separator >> m_member)) >>
                m_end_object[TETENGO2_CPP11_BIND(&json::object_ended, this, cpp11::placeholders_1())];
            m_object.name("object");
            m_member =
                m_string[TETENGO2_CPP11_BIND(&json::member_begun, this, cpp11::placeholders_1())] >>
                m_name_separator >>
                m_value[TETENGO2_CPP11_BIND(&json::member_ended, this, cpp11::placeholders_1())];
            m_member.name("member");

            // 2.3. Arrays
            m_array =
                m_begin_array[TETENGO2_CPP11_BIND(&json::array_begun, this, cpp11::placeholders_1())] >>
                -(m_value >> *(m_value_separator >> m_value)) >>
                m_end_array[TETENGO2_CPP11_BIND(&json::array_ended, this, cpp11::placeholders_1())];
            m_array.name("array");

            // 2.4. Numbers
            m_number = -m_minus >> m_int >> -m_frac >> -m_exp;
            m_number.name("number");
            m_decimal_point = qi::char_(char_type(TETENGO2_TEXT('.')));
            m_digit1to9 = qi::char_(char_type(TETENGO2_TEXT('1')), char_type(TETENGO2_TEXT('9')));
            m_e = qi::char_(char_type(TETENGO2_TEXT('e'))) | qi::char_(char_type(TETENGO2_TEXT('E')));
            m_exp = m_e >> (m_minus | m_plus) >> +qi::digit;
            m_frac = m_decimal_point >> +qi::digit;
            m_int = m_zero | (m_digit1to9 >> *qi::digit);
            m_minus = qi::char_(char_type(TETENGO2_TEXT('-')));
            m_plus = qi::char_(char_type(TETENGO2_TEXT('+')));
            m_zero = qi::char_(char_type(TETENGO2_TEXT('0')));

            // 2.5. Strings
            m_string = m_quotation_mark >> *m_char >> m_quotation_mark;
            m_string.name("string");
            m_char =
                m_unescaped |
                (
                    m_escape >>
                    (
                        qi::char_(char_type(TETENGO2_TEXT('"'))) |
                        qi::char_(char_type(TETENGO2_TEXT('\\'))) |
                        qi::char_(char_type(TETENGO2_TEXT('/'))) |
                        qi::char_(char_type(TETENGO2_TEXT('b'))) |
                        qi::char_(char_type(TETENGO2_TEXT('f'))) |
                        qi::char_(char_type(TETENGO2_TEXT('n'))) |
                        qi::char_(char_type(TETENGO2_TEXT('r'))) |
                        qi::char_(char_type(TETENGO2_TEXT('t'))) |
                        (qi::char_(char_type(TETENGO2_TEXT('u'))) >> qi::repeat(4)[qi::xdigit])
                    )
                );
            m_escape = qi::char_(char_type(TETENGO2_TEXT('\\')));
            m_quotation_mark = qi::char_(char_type(TETENGO2_TEXT('"')));
            m_unescaped = qi::char_ - qi::char_(char_type(0x00), char_type(0x19)) - m_quotation_mark - m_escape;
        }


    };


}}}


#endif
