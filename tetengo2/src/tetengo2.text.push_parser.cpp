/*! \file
    \brief The definition of tetengo2::text::push_parser.

    Copyright (C) 2007-2017 kaoru

    $Id$
*/

#include <cassert>
#include <cmath>
#include <iterator>
#include <memory>
#include <stdexcept>
#include <string>
#include <utility>
#include <vector>

#include <boost/algorithm/string.hpp>
#include <boost/core/ignore_unused.hpp>
#include <boost/core/noncopyable.hpp>
#include <boost/lexical_cast.hpp>
#include <boost/spirit/include/qi.hpp>
#include <boost/spirit/include/support_multi_pass.hpp>
#include <boost/throw_exception.hpp>
#include <boost/variant.hpp>

#include <tetengo2/iterator/observable_forward_iterator.h>
#include <tetengo2/stdalt.h>
#include <tetengo2/text.h>
#include <tetengo2/text/push_parser.h>


namespace tetengo2 { namespace text
{
    template <typename ForwardIterator>
    class push_parser<ForwardIterator>::impl : private boost::noncopyable
    {
    public:
        // types

        using iterator = typename push_parser<ForwardIterator>::iterator;

        using grammar_type = typename push_parser<ForwardIterator>::grammar_type;

        using integer_type = typename push_parser<ForwardIterator>::integer_type;

        using float_type = typename push_parser<ForwardIterator>::float_type;

        using string_type = typename push_parser<ForwardIterator>::string_type;

        using value_type = typename push_parser<ForwardIterator>::value_type;

        using attribute_map_type = typename push_parser<ForwardIterator>::attribute_map_type;

        using signal_result_combiner_type = typename push_parser<ForwardIterator>::signal_result_combiner_type;

        using structure_signal_type = typename push_parser<ForwardIterator>::structure_signal_type;

        using value_signal_type = typename push_parser<ForwardIterator>::value_signal_type;


        // constructors and destructor

        impl(const iterator first, const iterator last, std::unique_ptr<grammar_type> p_grammar)
        :
        m_first(first),
        m_last(last),
        m_p_grammar(std::move(p_grammar)),
        m_on_structure_begin(),
        m_on_structure_end(),
        m_on_value()
        {
            if (!m_p_grammar)
                BOOST_THROW_EXCEPTION((std::invalid_argument{ "The grammar is nullptr." }));

            m_p_grammar->on_structure_begin().connect(
                [this](
                    const string_type&                           structure_name,
                    const std::vector<structure_attribute_type>& structure_attributes
                )
                {
                    return this->observe_structure_begin(structure_name, structure_attributes);
                }
            );
            m_p_grammar->on_structure_end().connect(
                [this](
                    const string_type&                           structure_name,
                    const std::vector<structure_attribute_type>& structure_attributes
                )
                {
                    boost::ignore_unused(structure_attributes);

                    return this->observe_structure_end(structure_name);
                }
            );
            m_p_grammar->on_value().connect(
                [this](const value_type_type value_type, const string_type& value)
                {
                    return this->observe_value(value_type, value);
                }
            );
        }


        // functions
        
        const structure_signal_type& on_structure_begin()
        const
        {
            return m_on_structure_begin;
        }

        structure_signal_type& on_structure_begin()
        {
            return m_on_structure_begin;
        }

        const structure_signal_type& on_structure_end()
        const
        {
            return m_on_structure_end;
        }

        structure_signal_type& on_structure_end()
        {
            return m_on_structure_end;
        }

        const value_signal_type& on_value()
        const
        {
            return m_on_value;
        }

        value_signal_type& on_value()
        {
            return m_on_value;
        }

        bool parse()
        const
        {
            auto first = m_first;
            const auto result = boost::spirit::qi::parse(first, m_last, *m_p_grammar);
            return result && first == m_last;
        }


    private:
        // types

        using structure_attribute_type = grammar::structure_attribute<string_type>;

        using value_type_type = typename structure_attribute_type::value_type_type;


        // static functions

        static attribute_map_type to_attribute_map(const std::vector<structure_attribute_type>& structure_attributes)
        {
            attribute_map_type attribute_map{};

            for (const auto& sa: structure_attributes)
                attribute_map.insert(to_attribute(sa));

            return attribute_map;
        }

        static typename attribute_map_type::value_type to_attribute(
            const structure_attribute_type& structure_attribute
        )
        {
            return
                {
                    structure_attribute.name(),
                    to_value(structure_attribute.value_type(), structure_attribute.attribute())
                };
        }

        static value_type to_value(const value_type_type value_type, const string_type& string_value)
        {
            switch (value_type)
            {
            case value_type_type::string:
                return to_string(string_value);
            case value_type_type::number:
                return to_number(string_value);
            case value_type_type::boolean:
                return to_boolean(string_value);
            case value_type_type::null:
                return to_null(string_value);
            default:
                assert(false);
                BOOST_THROW_EXCEPTION((std::logic_error{ "Must not come here." }));
            }
        }

        static string_type to_string(const string_type& string_value)
        {
            assert(string_value.length() >= 2);
            string_type string{ std::next(string_value.begin()), std::prev(string_value.end()) };

            boost::replace_all(string, string_type{ TETENGO2_TEXT("\\\"") }, string_type{ TETENGO2_TEXT("\"") });
            boost::replace_all(string, string_type{ TETENGO2_TEXT("\\\\") }, string_type{ TETENGO2_TEXT("\\") });
            boost::replace_all(string, string_type{ TETENGO2_TEXT("\\/") }, string_type{ TETENGO2_TEXT("/") });
            boost::replace_all(string, string_type{ TETENGO2_TEXT("\\b") }, string_type{ TETENGO2_TEXT("\b") });
            boost::replace_all(string, string_type{ TETENGO2_TEXT("\\f") }, string_type{ TETENGO2_TEXT("\f") });
            boost::replace_all(string, string_type{ TETENGO2_TEXT("\\n") }, string_type{ TETENGO2_TEXT("\n") });
            boost::replace_all(string, string_type{ TETENGO2_TEXT("\\r") }, string_type{ TETENGO2_TEXT("\r") });
            boost::replace_all(string, string_type{ TETENGO2_TEXT("\\t") }, string_type{ TETENGO2_TEXT("\t") });

            return string;
        }

        static value_type to_number(const string_type& string_value)
        {
            const auto exp_index = string_value.find_first_of("eE");
            if (exp_index != string_type::npos)
                return to_number_exp(string_value, exp_index);

            const auto fp_index = string_value.find('.');
            if (fp_index != string_type::npos)
                return to_number_impl<float_type>(string_value);

            return to_number_impl<integer_type>(string_value);
        }

        template <typename T>
        static boost::variant<T> to_number_impl(const string_type& string_value)
        {
            try
            {
                return boost::lexical_cast<T>(string_value);
            }
            catch (const boost::bad_lexical_cast&)
            {
                return boost::variant<T>(0);
            }
        }

        static boost::variant<float_type> to_number_exp(
            const string_type&                    string_value,
            const typename string_type::size_type exp_index
        )
        {
            try
            {
                const auto fraction = boost::lexical_cast<float_type>(string_value.substr(0, exp_index));
                const auto exp = boost::lexical_cast<float_type>(string_value.substr(exp_index + 1));
                return fraction * std::pow(10.0, exp);
            }
            catch (const boost::bad_lexical_cast&)
            {
                return{ 0 };
            }
        }

        static bool to_boolean(const string_type& string_value)
        {
            assert(
                string_value == string_type{ TETENGO2_TEXT("true") } ||
                string_value == string_type{ TETENGO2_TEXT("false") }
            );

            return string_value == string_type{ TETENGO2_TEXT("true") };
        }

        static void* to_null(const string_type& string_value)
        {
            boost::ignore_unused(string_value);

            assert(string_value == string_type{ TETENGO2_TEXT("null") });

            return nullptr;
        }


        // variables

        const iterator m_first;

        const iterator m_last;

        const std::unique_ptr<grammar_type> m_p_grammar;

        structure_signal_type m_on_structure_begin;

        structure_signal_type m_on_structure_end;

        value_signal_type m_on_value;


        // functions

        bool observe_structure_begin(
            const string_type&                           structure_name,
            const std::vector<structure_attribute_type>& structure_attributes
        )
        {
            return m_on_structure_begin(structure_name, to_attribute_map(structure_attributes));
        }

        bool observe_structure_end(const string_type& structure_name)
        {
            return m_on_structure_end(structure_name, attribute_map_type{});
        }

        bool observe_value(const value_type_type value_type, const string_type& value)
        {
            return m_on_value(to_value(value_type, value));
        }


    };


    template <typename ForwardIterator>
    push_parser<ForwardIterator>::push_parser(
        const iterator                first,
        const iterator                last,
        std::unique_ptr<grammar_type> p_grammar
    )
    :
    m_p_impl(stdalt::make_unique<impl>(first, last, std::move(p_grammar)))
    {}

    template <typename ForwardIterator>
    push_parser<ForwardIterator>::~push_parser()
    = default;

    template <typename ForwardIterator>
    const typename push_parser<ForwardIterator>::structure_signal_type&
    push_parser<ForwardIterator>::on_structure_begin()
    const
    {
        return m_p_impl->on_structure_begin();
    }

    template <typename ForwardIterator>
    typename push_parser<ForwardIterator>::structure_signal_type& push_parser<ForwardIterator>::on_structure_begin()
    {
        return m_p_impl->on_structure_begin();
    }

    template <typename ForwardIterator>
    const typename push_parser<ForwardIterator>::structure_signal_type&
    push_parser<ForwardIterator>::on_structure_end()
    const
    {
        return m_p_impl->on_structure_end();
    }

    template <typename ForwardIterator>
    typename push_parser<ForwardIterator>::structure_signal_type& push_parser<ForwardIterator>::on_structure_end()
    {
        return m_p_impl->on_structure_end();
    }

    template <typename ForwardIterator>
    const typename push_parser<ForwardIterator>::value_signal_type& push_parser<ForwardIterator>::on_value()
    const
    {
        return m_p_impl->on_value();
    }

    template <typename ForwardIterator>
    typename push_parser<ForwardIterator>::value_signal_type& push_parser<ForwardIterator>::on_value()
    {
        return m_p_impl->on_value();
    }

    template <typename ForwardIterator>
    bool push_parser<ForwardIterator>::parse()
    const
    {
        return m_p_impl->parse();
    }


    namespace
    {
        namespace application
        {
            using input_stream_iterator_type =
                iterator::observable_forward_iterator<boost::spirit::multi_pass<std::istreambuf_iterator<char>>>;

        }

        namespace test
        {
            using input_stream_iterator_type = std::string::const_iterator;

        }

    }

    template class push_parser<application::input_stream_iterator_type>;

    template class push_parser<test::input_stream_iterator_type>;


}}
