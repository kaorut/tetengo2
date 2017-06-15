/*! \file
    \brief The definition of tetengo2::text::grammar::grammar.

    Copyright (C) 2007-2017 kaoru

    $Id$
*/

#include <iterator>
#include <string>
#include <utility>

#include <boost/core/noncopyable.hpp>
#include <boost/spirit/include/support_multi_pass.hpp>

#include <tetengo2/iterator/observable_forward_iterator.h>
#include <tetengo2/stdalt.h>
#include <tetengo2/text/grammar/grammar.h>


namespace tetengo2 { namespace text { namespace grammar
{
    template <typename String>
    structure_attribute<String>::structure_attribute(string_type name, const value_type_type value_type, const string_type& attribute)
    :
    m_name(std::move(name)),
    m_value_type(value_type),
    m_attribute(attribute)
    {}

    template <typename String>
    const typename structure_attribute<String>::string_type& structure_attribute<String>::name()
    const
    {
        return m_name;
    }

    template <typename String>
    typename structure_attribute<String>::value_type_type structure_attribute<String>::value_type()
    const
    {
        return m_value_type;
    }

    template <typename String>
    const typename structure_attribute<String>::string_type& structure_attribute<String>::attribute()
    const
    {
        return m_attribute;
    }


    template <typename ForwardIterator>
    class grammar<ForwardIterator>::impl : boost::noncopyable
    {
    public:
        // types

        using iterator = typename grammar::iterator;

        using char_type = typename grammar::char_type;

        using string_type = typename grammar::string_type;

        using rule_type = typename grammar::rule_type;


        // constructors and destructor

        impl()
        {}


        // functions


    private:
        // variables


    };


    template <typename ForwardIterator>
    grammar<ForwardIterator>::~grammar()
    = default;

    template <typename ForwardIterator>
    grammar<ForwardIterator>::grammar(rule_type& root_rule)
    :
    grammar::base_type(root_rule),
    m_p_impl(tetengo2::stdalt::make_unique<impl>())
    {}


    namespace
    {
        namespace application
        {
            using input_stream_iterator_type =
                tetengo2::iterator::observable_forward_iterator<boost::spirit::multi_pass<std::istreambuf_iterator<char>>>;

        }

        namespace test
        {
            using input_stream_iterator_type = std::string::const_iterator;

        }

    }

    template class structure_attribute<std::string>;

    template class grammar<application::input_stream_iterator_type>;

    template class grammar<test::input_stream_iterator_type>;


}}}
