/*! \file
    \brief The definition of tetengo2::text::grammar::json.

    Copyright (C) 2007-2019 kaoru

    $Id$
*/

#include <iterator>
#include <memory>
#include <string>
#include <vector>

#include <boost/core/noncopyable.hpp>
#include <boost/proto/operators.hpp>
#include <boost/spirit/include/qi.hpp>
#include <boost/spirit/include/support.hpp>
#include <boost/spirit/include/support_multi_pass.hpp>

#include <tetengo2/iterator/observable_forward_iterator.h>
#include <tetengo2/text.h>

#include <tetengo2/text/grammar/grammar.h>
#include <tetengo2/text/grammar/json.h>

namespace boost::spirit {
    struct unused_type;
}


namespace tetengo2::text::grammar {
    template <typename ForwardIterator>
    class json<ForwardIterator>::impl : private boost::noncopyable
    {
    public:
        // types

        using iterator = typename json<ForwardIterator>::iterator;

        using base_type = typename json<ForwardIterator>::base_type;

        using rule_type = typename json<ForwardIterator>::rule_type;


        // constructors and destructor

        impl(rule_type& json_text, json& base)
        : m_json_text{ json_text }, m_begin_array{}, m_begin_object{}, m_end_array{}, m_end_object{},
          m_name_separator{}, m_value_separator{}, m_ws{}, m_value{}, m_false{}, m_null{}, m_true{}, m_object{},
          m_member{}, m_array{}, m_number{}, m_decimal_point{}, m_digit1to9{}, m_e{}, m_exp{}, m_frac{}, m_int{},
          m_minus{}, m_plus{}, m_zero{}, m_string{}, m_char{}, m_escape{}, m_quotation_mark{}, m_unescaped{}
        {
            define_rules(base);
        }


        // functions

        const rule_type& json_text() const
        {
            return m_json_text;
        }

        const rule_type& value() const
        {
            return m_value;
        }

        const rule_type& object() const
        {
            return m_object;
        }

        const rule_type& member() const
        {
            return m_member;
        }

        const rule_type& array() const
        {
            return m_array;
        }

        const rule_type& number() const
        {
            return m_number;
        }

        const rule_type& string() const
        {
            return m_string;
        }


    private:
        // types

        using char_type = typename iterator::value_type;

        using string_type = typename base_type::string_type;

        using structure_attribute_type = structure_attribute<string_type>;

        using value_type_type = typename structure_attribute_type::value_type_type;

        using char_rule_type = boost::spirit::qi::rule<iterator, char_type()>;

        struct call_handler_type
        {
            using handler_type = bool (impl::*)(const string_type& attribute, json& base);

            impl& m_self;

            json& m_base;

            const handler_type m_handler;

            call_handler_type(impl& self, json& base, const handler_type handler)
            : m_self{ self }, m_base{ base }, m_handler{ handler }
            {}

            void operator()(const string_type& attribute, const boost::spirit::qi::unused_type&, bool& pass) const
            {
                pass = (m_self.*m_handler)(attribute, m_base);
            }
        };


        // variables

        rule_type& m_json_text;

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

        bool object_begun(const string_type&, json& base)
        {
            return base.on_structure_begin()(
                string_type{ TETENGO2_TEXT("object") }, std::vector<structure_attribute_type>{});
        }

        bool object_ended(const string_type&, json& base)
        {
            return base.on_structure_end()(
                string_type{ TETENGO2_TEXT("object") }, std::vector<structure_attribute_type>{});
        }

        bool member_begun(const string_type& attribute, json& base)
        {
            return base.on_structure_begin()(
                string_type{ TETENGO2_TEXT("member") },
                std::vector<structure_attribute_type>{ 1,
                                                       structure_attribute_type{ string_type{ TETENGO2_TEXT("name") },
                                                                                 value_type_type::string,
                                                                                 attribute } });
        }

        bool member_ended(const string_type&, json& base)
        {
            return base.on_structure_end()(
                string_type{ TETENGO2_TEXT("member") }, std::vector<structure_attribute_type>{});
        }

        bool array_begun(const string_type&, json& base)
        {
            return base.on_structure_begin()(
                string_type{ TETENGO2_TEXT("array") }, std::vector<structure_attribute_type>{});
        }

        bool array_ended(const string_type&, json& base)
        {
            return base.on_structure_end()(
                string_type{ TETENGO2_TEXT("array") }, std::vector<structure_attribute_type>{});
        }

        bool string_passed(const string_type& attribute, json& base)
        {
            return base.on_value()(value_type_type::string, attribute);
        }

        bool number_passed(const string_type& attribute, json& base)
        {
            return base.on_value()(value_type_type::number, attribute);
        }

        bool boolean_passed(const string_type& attribute, json& base)
        {
            return base.on_value()(value_type_type::boolean, attribute);
        }

        bool null_passed(const string_type& attribute, json& base)
        {
            return base.on_value()(value_type_type::null, attribute);
        }

        void define_rules(json& base)
        {
            namespace qi = boost::spirit::qi;

            // 2. JSON Grammar
            m_json_text = m_object | m_array;
            m_json_text.name("JSON-text");
            m_begin_array = m_ws >> qi::char_(char_type{ TETENGO2_TEXT('[') }) >> m_ws;
            m_begin_object = m_ws >> qi::char_(char_type{ TETENGO2_TEXT('{') }) >> m_ws;
            m_end_array = m_ws >> qi::char_(char_type{ TETENGO2_TEXT(']') }) >> m_ws;
            m_end_object = m_ws >> qi::char_(char_type{ TETENGO2_TEXT('}') }) >> m_ws;
            m_name_separator = m_ws >> qi::char_(char_type{ TETENGO2_TEXT(':') }) >> m_ws;
            m_value_separator = m_ws >> qi::char_(char_type{ TETENGO2_TEXT(',') }) >> m_ws;
            m_ws =
                *(qi::char_(char_type{ TETENGO2_TEXT(' ') }) | qi::char_(char_type{ TETENGO2_TEXT('\t') }) |
                  qi::char_(char_type{ TETENGO2_TEXT('\n') }) | qi::char_(char_type{ TETENGO2_TEXT('\r') }));

            // 2.1. Values
            m_value = m_false[call_handler_type{ *this, base, &impl::boolean_passed }] |
                      m_null[call_handler_type{ *this, base, &impl::null_passed }] |
                      m_true[call_handler_type{ *this, base, &impl::boolean_passed }] | m_object | m_array |
                      m_number[call_handler_type{ *this, base, &impl::number_passed }] |
                      m_string[call_handler_type{ *this, base, &impl::string_passed }];
            m_value.name("value");
            m_false = qi::string(string_type{ TETENGO2_TEXT("false") });
            m_null = qi::string(string_type{ TETENGO2_TEXT("null") });
            m_true = qi::string(string_type{ TETENGO2_TEXT("true") });

            // 2.2. Objects
            m_object = m_begin_object[call_handler_type{ *this, base, &impl::object_begun }] >>
                       -(m_member >> *(m_value_separator >> m_member)) >>
                       m_end_object[call_handler_type{ *this, base, &impl::object_ended }];
            m_object.name("object");
            m_member = m_string[call_handler_type{ *this, base, &impl::member_begun }] >> m_name_separator >>
                       m_value[call_handler_type{ *this, base, &impl::member_ended }];
            m_member.name("member");

            // 2.3. Arrays
            m_array = m_begin_array[call_handler_type{ *this, base, &impl::array_begun }] >>
                      -(m_value >> *(m_value_separator >> m_value)) >>
                      m_end_array[call_handler_type{ *this, base, &impl::array_ended }];
            m_array.name("array");

            // 2.4. Numbers
            m_number = -m_minus >> m_int >> -m_frac >> -m_exp;
            m_number.name("number");
            m_decimal_point = qi::char_(char_type{ TETENGO2_TEXT('.') });
            m_digit1to9 = qi::char_(char_type{ TETENGO2_TEXT('1') }, char_type{ TETENGO2_TEXT('9') });
            m_e = qi::char_(char_type{ TETENGO2_TEXT('e') }) | qi::char_(char_type{ TETENGO2_TEXT('E') });
            m_exp = m_e >> (m_minus | m_plus) >> +qi::digit;
            m_frac = m_decimal_point >> +qi::digit;
            m_int = m_zero | (m_digit1to9 >> *qi::digit);
            m_minus = qi::char_(char_type{ TETENGO2_TEXT('-') });
            m_plus = qi::char_(char_type{ TETENGO2_TEXT('+') });
            m_zero = qi::char_(char_type{ TETENGO2_TEXT('0') });

            // 2.5. Strings
            m_string = m_quotation_mark >> *m_char >> m_quotation_mark;
            m_string.name("string");
            m_char =
                m_unescaped |
                (m_escape >> (qi::char_(char_type{ TETENGO2_TEXT('"') }) | qi::char_(char_type{ TETENGO2_TEXT('\\') }) |
                              qi::char_(char_type{ TETENGO2_TEXT('/') }) | qi::char_(char_type{ TETENGO2_TEXT('b') }) |
                              qi::char_(char_type{ TETENGO2_TEXT('f') }) | qi::char_(char_type{ TETENGO2_TEXT('n') }) |
                              qi::char_(char_type{ TETENGO2_TEXT('r') }) | qi::char_(char_type{ TETENGO2_TEXT('t') }) |
                              (qi::char_(char_type{ TETENGO2_TEXT('u') }) >> qi::repeat(4)[qi::xdigit])));
            m_escape = qi::char_(char_type{ TETENGO2_TEXT('\\') });
            m_quotation_mark = qi::char_(char_type{ TETENGO2_TEXT('"') });
            m_unescaped = qi::char_ - qi::char_(char_type{ 0x00 }, char_type{ 0x19 }) - m_quotation_mark - m_escape;
        }
    };


    template <typename ForwardIterator>
    json<ForwardIterator>::json()
    : base_type{ m_json_text }, m_json_text{}, m_p_impl{ std::make_unique<impl>(m_json_text, *this) }
    {}

    template <typename ForwardIterator>
    json<ForwardIterator>::~json() = default;

    template <typename ForwardIterator>
    const typename json<ForwardIterator>::rule_type& json<ForwardIterator>::json_text() const
    {
        return m_p_impl->json_text();
    }

    template <typename ForwardIterator>
    const typename json<ForwardIterator>::rule_type& json<ForwardIterator>::value() const
    {
        return m_p_impl->value();
    }

    template <typename ForwardIterator>
    const typename json<ForwardIterator>::rule_type& json<ForwardIterator>::object() const
    {
        return m_p_impl->object();
    }

    template <typename ForwardIterator>
    const typename json<ForwardIterator>::rule_type& json<ForwardIterator>::member() const
    {
        return m_p_impl->member();
    }

    template <typename ForwardIterator>
    const typename json<ForwardIterator>::rule_type& json<ForwardIterator>::array() const
    {
        return m_p_impl->array();
    }

    template <typename ForwardIterator>
    const typename json<ForwardIterator>::rule_type& json<ForwardIterator>::number() const
    {
        return m_p_impl->number();
    }

    template <typename ForwardIterator>
    const typename json<ForwardIterator>::rule_type& json<ForwardIterator>::string() const
    {
        return m_p_impl->string();
    }


    namespace {
        namespace application {
            using input_stream_iterator_type =
                iterator::observable_forward_iterator<boost::spirit::multi_pass<std::istreambuf_iterator<char>>>;
        }

        namespace test {
            using input_stream_iterator_type = std::string::const_iterator;
        }
    }

    template class json<application::input_stream_iterator_type>;

    template class json<test::input_stream_iterator_type>;
}
