/*! \file
    \brief The definition of tetengo2::text::grammar::grammar.

    Copyright (C) 2007-2017 kaoru

    $Id$
*/

#include <iterator>
#include <string>

#include <boost/core/noncopyable.hpp>
#include <boost/spirit/include/support_multi_pass.hpp>

#include <tetengo2/iterator/observable_forward_iterator.h>
#include <tetengo2/stdalt.h>
#include <tetengo2/text/grammar/grammar.h>


namespace tetengo2 { namespace text { namespace grammar
{
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

        impl(rule_type& root_rule)
        :
        m_root_rule(root_rule)
        {}


        // functions

        const rule_type& root_rule()
        const
        {
            return m_root_rule;
        }

        rule_type& root_rule()
        {
            return m_root_rule;
        }


    private:
        // variables

        rule_type& m_root_rule;


    };


    template <typename ForwardIterator>
    grammar<ForwardIterator>::~grammar()
    = default;

    template <typename ForwardIterator>
    grammar<ForwardIterator>::grammar()
    :
    grammar::base_type(m_root_rule),
    m_root_rule(),
    m_p_impl(tetengo2::stdalt::make_unique<impl>(m_root_rule))
    {}

    template <typename ForwardIterator>
    const typename grammar<ForwardIterator>::rule_type& grammar<ForwardIterator>::root_rule()
    const
    {
        return m_p_impl->root_rule();
    }

    template <typename ForwardIterator>
    typename grammar<ForwardIterator>::rule_type& grammar<ForwardIterator>::root_rule()
    {
        return m_p_impl->root_rule();
    }


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

    template class grammar<application::input_stream_iterator_type>;

    template class grammar<test::input_stream_iterator_type>;


}}}
