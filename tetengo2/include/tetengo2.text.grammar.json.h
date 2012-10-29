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
        struct value_type_type { enum enum_t //!< Scoped enum.
        {
            string,  //!< A string.
            number,  //!< A number.
            boolean, //!< A boolean.
            null,    //!< A null.
        };};

        //! The attribute type.
        typedef
            std::tuple<string_type, typename value_type_type::enum_t, const string_type&> structure_attribute_type;

        //! The structure signal type.
        typedef
            boost::signals2::signal<void (const std::string&, const std::vector<structure_attribute_type>&)>
            structure_signal_type;

        //! The value signal type.
        typedef
            boost::signals2::signal<void (typename value_type_type::enum_t, const string_type&)> value_signal_type;

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

        struct call_handler_type
        {
            typedef void (json::* handler_type)(const string_type& attribute);

            json& m_self;
            handler_type const m_handler;

            call_handler_type(json& self, const handler_type handler)
            :
            m_self(self),
            m_handler(handler)
            {}

            void operator()(const string_type& attribute, const boost::spirit::qi::unused_type&, const bool)
            const
            {
                (m_self.*m_handler)(attribute);
            }

        };


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

        void object_begun(const string_type&)
        {
            m_on_structure_begin(string_type(TETENGO2_TEXT("object")), std::vector<structure_attribute_type>());
        }

        void object_ended(const string_type&)
        {
            m_on_structure_end(string_type(TETENGO2_TEXT("object")), std::vector<structure_attribute_type>());
        }

        void member_begun(const string_type& attribute)
        {
            m_on_structure_begin(
                string_type(TETENGO2_TEXT("member")),
                std::vector<structure_attribute_type>(
                    1, structure_attribute_type(string_type(TETENGO2_TEXT("name")), value_type_type::string, attribute)
                )
            );
        }

        void member_ended(const string_type&)
        {
            m_on_structure_end(string_type(TETENGO2_TEXT("member")), std::vector<structure_attribute_type>());
        }

        void array_begun(const string_type&)
        {
            m_on_structure_begin(string_type(TETENGO2_TEXT("array")), std::vector<structure_attribute_type>());
        }

        void array_ended(const string_type&)
        {
            m_on_structure_end(string_type(TETENGO2_TEXT("array")), std::vector<structure_attribute_type>());
        }

        void string_passed(const string_type& attribute)
        {
            m_on_value(value_type_type::string, attribute);
        }

        void number_passed(const string_type& attribute)
        {
            m_on_value(value_type_type::number, attribute);
        }

        void boolean_passed(const string_type& attribute)
        {
            m_on_value(value_type_type::boolean, attribute);
        }

        void null_passed(const string_type& attribute)
        {
            m_on_value(value_type_type::null, attribute);
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
                m_false[call_handler_type(*this, &json::boolean_passed)] |
                m_null[call_handler_type(*this, &json::null_passed)] |
                m_true[call_handler_type(*this, &json::boolean_passed)] |
                m_object |
                m_array |
                m_number[call_handler_type(*this, &json::number_passed)] |
                m_string[call_handler_type(*this, &json::string_passed)];
            m_value.name("value");
            m_false = qi::string(string_type(TETENGO2_TEXT("false")));
            m_null = qi::string(string_type(TETENGO2_TEXT("null")));
            m_true = qi::string(string_type(TETENGO2_TEXT("true")));

            // 2.2. Objects
            m_object =
                m_begin_object[call_handler_type(*this, &json::object_begun)] >>
                -(m_member >> *(m_value_separator >> m_member)) >>
                m_end_object[call_handler_type(*this, &json::object_ended)];
            m_object.name("object");
            m_member =
                m_string[call_handler_type(*this, &json::member_begun)] >>
                m_name_separator >>
                m_value[call_handler_type(*this, &json::member_ended)];
            m_member.name("member");

            // 2.3. Arrays
            m_array =
                m_begin_array[call_handler_type(*this, &json::array_begun)] >>
                -(m_value >> *(m_value_separator >> m_value)) >>
                m_end_array[call_handler_type(*this, &json::array_ended)];
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
