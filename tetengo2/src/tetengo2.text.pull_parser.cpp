/*! \file
    \brief The definition of tetengo2::text::pull_parser.

    Copyright (C) 2007-2018 kaoru

    $Id$
*/

#include <cassert>
#include <iterator>
#include <memory>
#include <stdexcept>
#include <string>
#include <utility>

#include <boost/core/ignore_unused.hpp>
#include <boost/core/noncopyable.hpp>
#include <boost/shared_ptr.hpp>
#include <boost/spirit/include/support_multi_pass.hpp>
#include <boost/throw_exception.hpp>
#include <boost/variant.hpp>

#include <tetengo2/concurrent/channel.h>
#include <tetengo2/concurrent/consumer.h>
#include <tetengo2/concurrent/producer.h>
#include <tetengo2/iterator/observable_forward_iterator.h>
#include <tetengo2/text/pull_parser.h>
#include <tetengo2/text/push_parser.h>


namespace tetengo2::text {
    template <structure_kind Kind, typename String, typename AttributeMap>
    structure_kind structure<Kind, String, AttributeMap>::kind()
    {
        return Kind;
    }

    template <structure_kind Kind, typename String, typename AttributeMap>
    structure<Kind, String, AttributeMap>::structure(string_type name, attribute_map_type attribute_map)
    : m_name{ std::move(name) }, m_attribute_map{ std::move(attribute_map) }
    {}

    template <structure_kind Kind, typename String, typename AttributeMap>
    const typename structure<Kind, String, AttributeMap>::string_type&
    structure<Kind, String, AttributeMap>::name() const
    {
        return m_name;
    }

    template <structure_kind Kind, typename String, typename AttributeMap>
    const typename structure<Kind, String, AttributeMap>::attribute_map_type&
    structure<Kind, String, AttributeMap>::attribute_map() const
    {
        return m_attribute_map;
    }


    template <typename ForwardIterator>
    class pull_parser<ForwardIterator>::impl : private boost::noncopyable
    {
    public:
        // types

        using iterator = typename pull_parser<ForwardIterator>::iterator;

        using string_type = typename pull_parser<ForwardIterator>::string_type;

        using size_type = typename pull_parser<ForwardIterator>::size_type;

        using push_parser_type = typename pull_parser<ForwardIterator>::push_parser_type;

        using value_type = typename pull_parser<ForwardIterator>::value_type;

        using attribute_map_type = typename pull_parser<ForwardIterator>::attribute_map_type;

        using structure_begin_type = typename pull_parser<ForwardIterator>::structure_begin_type;

        using structure_end_type = typename pull_parser<ForwardIterator>::structure_end_type;

        using element_type = typename pull_parser<ForwardIterator>::element_type;


        // constructors and destructor

        impl(std::unique_ptr<push_parser_type> p_push_parser, const size_type channel_capacity)
        : m_p_push_parser{ std::move(p_push_parser) }, m_channel{ channel_capacity },
#if !defined(DOCUMENTATION) // Doxygen warning suppression
          m_producer{ [this](channel_type& channel) { generate(channel, *this->m_p_push_parser); }, m_channel },
#endif
          m_consumer{ m_channel }
        {}


        // functions

        bool has_next() const
        {
            return !m_consumer.closed();
        }

        const element_type& peek() const
        {
            if (!has_next())
                BOOST_THROW_EXCEPTION((std::logic_error{ "The parser has no more element." }));

            return m_consumer.peek();
        }

        void next()
        {
            if (!has_next())
                BOOST_THROW_EXCEPTION((std::logic_error{ "The parser has no more element." }));

            m_consumer.take();
        }

        void skip_next()
        {
            const auto element = peek();

            if (element.which() == 1 || element.which() == 2)
            {
                next();
                return;
            }
            assert(element.which() == 0);
            const auto& structure_begin_name = boost::get<structure_begin_type>(element).name();

            next();

            while (has_next())
            {
                const auto& next_element = peek();
                if (next_element.which() == 1)
                {
                    const auto& structure_end_name = boost::get<structure_end_type>(next_element).name();
                    if (structure_end_name == structure_begin_name)
                    {
                        next();
                        return;
                    }
                }

                skip_next();
            }
        }


    private:
        // types

        using channel_type = concurrent::channel<element_type>;

        using producer_type = concurrent::producer<element_type>;

        using consumer_type = concurrent::consumer<element_type>;


        // static functions

        static void generate(channel_type& channel, push_parser_type& push_parser)
        {
            push_parser.on_structure_begin().connect(
                [&channel](const string_type& name, const attribute_map_type& attribute_map) {
                    return on_structure_begin(name, attribute_map, channel);
                });
            push_parser.on_structure_end().connect(
                [&channel](const string_type& name, const attribute_map_type& attribute_map) {
                    boost::ignore_unused(attribute_map);

                    return on_structure_end(name, channel);
                });
            push_parser.on_value().connect([&channel](const value_type& value) { return on_value(value, channel); });

            push_parser.parse();
        }

        static bool
        on_structure_begin(const string_type& name, const attribute_map_type& attribute_map, channel_type& channel)
        {
            if (channel.close_requested())
                return false;

            channel.insert(element_type{ structure_begin_type{ name, attribute_map } });
            return true;
        }

        static bool on_structure_end(const string_type& name, channel_type& channel)
        {
            if (channel.close_requested())
                return false;

            channel.insert(element_type{ structure_end_type{ name, attribute_map_type{} } });
            return true;
        }

        static bool on_value(const value_type& value, channel_type& channel)
        {
            if (channel.close_requested())
                return false;

            channel.insert(element_type{ value });
            return true;
        }


        // variables

        const std::unique_ptr<push_parser_type> m_p_push_parser;

        channel_type m_channel;

        producer_type m_producer;

        consumer_type m_consumer;
    };

    template <typename ForwardIterator>
    pull_parser<ForwardIterator>::pull_parser(
        std::unique_ptr<push_parser_type> p_push_parser,
        const size_type                   channel_capacity)
    : m_p_impl{ stdalt::make_unique<impl>(std::move(p_push_parser), channel_capacity) }
    {}

    template <typename ForwardIterator>
    pull_parser<ForwardIterator>::~pull_parser() = default;

    template <typename ForwardIterator>
    bool pull_parser<ForwardIterator>::has_next() const
    {
        return m_p_impl->has_next();
    }

    template <typename ForwardIterator>
    const typename pull_parser<ForwardIterator>::element_type& pull_parser<ForwardIterator>::peek() const
    {
        return m_p_impl->peek();
    }

    template <typename ForwardIterator>
    void pull_parser<ForwardIterator>::next()
    {
        m_p_impl->next();
    }

    template <typename ForwardIterator>
    void pull_parser<ForwardIterator>::skip_next()
    {
        m_p_impl->skip_next();
    }


    namespace {
        using string_type = std::string;

        namespace application {
            using input_stream_iterator_type = iterator::observable_forward_iterator<
                boost::spirit::multi_pass<std::istreambuf_iterator<string_type::value_type>>>;
        }

        namespace test {
            using input_stream_iterator_type = string_type::const_iterator;
        }

        using attribute_map_type = push_parser<application::input_stream_iterator_type>::attribute_map_type;
    }

    template class structure<structure_kind::begin, string_type, attribute_map_type>;

    template class structure<structure_kind::end, string_type, attribute_map_type>;

    template class pull_parser<application::input_stream_iterator_type>;

    template class pull_parser<test::input_stream_iterator_type>;
}
