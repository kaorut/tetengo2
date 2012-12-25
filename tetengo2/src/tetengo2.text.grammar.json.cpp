/*! \file
    \brief The definition of tetengo2::text::grammar::json.

    Copyright (C) 2007-2012 kaoru

    $Id$
*/

#include "tetengo2.text.grammar.json.h"


namespace tetengo2 { namespace text { namespace grammar
{
    template <typename ForwardIterator>
    json<ForwardIterator>::structure_attribute_type::structure_attribute_type(
        string_type                            name,
        const typename value_type_type::enum_t value_type,
        const string_type&                     attribute
    )
    :
    m_name(std::move(name)),
    m_value_type(value_type),
    m_attribute(attribute)
    {}

    template <typename ForwardIterator>
    const typename json<ForwardIterator>::string_type& json<ForwardIterator>::structure_attribute_type::name()
    const
    {
        return m_name;
    }

    template <typename ForwardIterator>
    typename json<ForwardIterator>::value_type_type::enum_t
    json<ForwardIterator>::structure_attribute_type::value_type()
    const
    {
        return m_value_type;
    }

    template <typename ForwardIterator>
    const typename json<ForwardIterator>::string_type& json<ForwardIterator>::structure_attribute_type::attribute()
    const
    {
        return m_attribute;
    }


    typedef boost::spirit::multi_pass<std::istreambuf_iterator<char>> input_stream_iterator_type;
    template class json<input_stream_iterator_type>::structure_attribute_type;

    template class json<std::string::const_iterator>::structure_attribute_type;


}}}
