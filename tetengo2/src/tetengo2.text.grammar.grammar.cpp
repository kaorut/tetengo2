/*! \file
    \brief The definition of tetengo2::text::grammar::grammar.

    Copyright (C) 2007-2018 kaoru

    $Id$
*/

#include <iterator>
#include <string>

#include <boost/core/noncopyable.hpp>
#include <boost/spirit/include/support_multi_pass.hpp>

#include <tetengo2/iterator/observable_forward_iterator.h>
#include <tetengo2/stdalt.h>
#include <tetengo2/text/grammar/grammar.h>


namespace tetengo2::text::grammar {
    template <typename String>
    structure_attribute<String>::structure_attribute(
        string_type           name,
        const value_type_type value_type,
        const string_type&    attribute)
    : m_name{ std::move(name) }, m_value_type{ value_type }, m_attribute{ attribute }
    {}

    template <typename String>
    const typename structure_attribute<String>::string_type& structure_attribute<String>::name() const
    {
        return m_name;
    }

    template <typename String>
    typename structure_attribute<String>::value_type_type structure_attribute<String>::value_type() const
    {
        return m_value_type;
    }

    template <typename String>
    const typename structure_attribute<String>::string_type& structure_attribute<String>::attribute() const
    {
        return m_attribute;
    }


    template <typename ForwardIterator>
    class grammar<ForwardIterator>::impl : boost::noncopyable
    {
    public:
        // types

        using iterator = typename grammar::iterator;

        using string_type = typename grammar::string_type;

        using signal_result_combiner_type = typename grammar::signal_result_combiner_type;

        using structure_signal_type = typename grammar::structure_signal_type;

        using value_signal_type = typename grammar::value_signal_type;

        using rule_type = typename grammar::rule_type;


        // constructors and destructor

        impl() : m_on_structure_begin{}, m_on_structure_end{}, m_on_value{} {}


        // functions

        const structure_signal_type& on_structure_begin() const
        {
            return m_on_structure_begin;
        }

        structure_signal_type& on_structure_begin()
        {
            return m_on_structure_begin;
        }

        const structure_signal_type& on_structure_end() const
        {
            return m_on_structure_end;
        }

        structure_signal_type& on_structure_end()
        {
            return m_on_structure_end;
        }

        const value_signal_type& on_value() const
        {
            return m_on_value;
        }

        value_signal_type& on_value()
        {
            return m_on_value;
        }


    private:
        // variables

        structure_signal_type m_on_structure_begin;

        structure_signal_type m_on_structure_end;

        value_signal_type m_on_value;
    };


    template <typename ForwardIterator>
    grammar<ForwardIterator>::~grammar() = default;

    template <typename ForwardIterator>
    grammar<ForwardIterator>::grammar(rule_type& root_rule)
    : grammar::base_type{ root_rule }, m_p_impl{ stdalt::make_unique<impl>() }
    {}

    template <typename ForwardIterator>
    const typename grammar<ForwardIterator>::structure_signal_type& grammar<ForwardIterator>::on_structure_begin() const
    {
        return m_p_impl->on_structure_begin();
    }

    template <typename ForwardIterator>
    typename grammar<ForwardIterator>::structure_signal_type& grammar<ForwardIterator>::on_structure_begin()
    {
        return m_p_impl->on_structure_begin();
    }

    template <typename ForwardIterator>
    const typename grammar<ForwardIterator>::structure_signal_type& grammar<ForwardIterator>::on_structure_end() const
    {
        return m_p_impl->on_structure_end();
    }

    template <typename ForwardIterator>
    typename grammar<ForwardIterator>::structure_signal_type& grammar<ForwardIterator>::on_structure_end()
    {
        return m_p_impl->on_structure_end();
    }

    template <typename ForwardIterator>
    const typename grammar<ForwardIterator>::value_signal_type& grammar<ForwardIterator>::on_value() const
    {
        return m_p_impl->on_value();
    }

    template <typename ForwardIterator>
    typename grammar<ForwardIterator>::value_signal_type& grammar<ForwardIterator>::on_value()
    {
        return m_p_impl->on_value();
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

    template class structure_attribute<std::string>;

    template class grammar<application::input_stream_iterator_type>;

    template class grammar<test::input_stream_iterator_type>;
}
