/*! \file
    \brief The definition of tetengo2::message::message_catalog_parser.

    Copyright (C) 2007-2018 kaoru

    $Id$
*/

#include <cassert>
#include <iterator>
#include <memory>
#include <stdexcept>
#include <string>
#include <utility>

#include <boost/core/noncopyable.hpp>
#include <boost/optional.hpp>
#include <boost/spirit/include/support_multi_pass.hpp>
#include <boost/throw_exception.hpp>
#include <boost/variant.hpp>

#include <tetengo2/iterator/observable_forward_iterator.h>
#include <tetengo2/message/message_catalog_parser.h>
#include <tetengo2/stdalt.h>
#include <tetengo2/text.h>
#include <tetengo2/text/encoder.h>
#include <tetengo2/type_list.h>


namespace tetengo2 { namespace message {
    template <typename ForwardIterator>
    class message_catalog_parser<ForwardIterator>::impl : private boost::noncopyable
    {
    public:
        // types

        using iterator = typename message_catalog_parser<ForwardIterator>::iterator;

        using input_string_type = typename message_catalog_parser<ForwardIterator>::input_string_type;

        using input_encoding_type = typename message_catalog_parser<ForwardIterator>::input_encoding_type;

        using pull_parser_type = typename message_catalog_parser<ForwardIterator>::pull_parser_type;

        using string_type = typename message_catalog_parser<ForwardIterator>::string_type;

        using entry_type = typename message_catalog_parser<ForwardIterator>::entry_type;


        // constructors and destructor

        impl(std::unique_ptr<pull_parser_type> p_pull_parser, input_encoding_type input_encoding)
        : m_p_pull_parser(std::move(p_pull_parser)), m_input_encoder(make_input_encoder(std::move(input_encoding))),
          m_p_preread_entry(), m_preamble_read_succeeded()
        {}


        // functions

        bool has_next() const
        {
            return preread();
        }

        const entry_type& peek() const
        {
            if (!has_next())
                BOOST_THROW_EXCEPTION((std::logic_error{ "No next entry." }));

            return *m_p_preread_entry;
        }

        void next()
        {
            if (!has_next())
                BOOST_THROW_EXCEPTION((std::logic_error{ "No next entry." }));

            m_p_preread_entry.reset();
        }


    private:
        // types

        using input_encoder_type = text::encoder<type_list::internal_encoding_type, input_encoding_type>;

        using element_type = typename pull_parser_type::element_type;

        using structure_begin_type = typename pull_parser_type::structure_begin_type;

        using structure_end_type = typename pull_parser_type::structure_end_type;

        using value_type = typename pull_parser_type::value_type;


        // static functions

        static input_encoder_type make_input_encoder(input_encoding_type input_encoding)
        {
            return input_encoder_type{ type_list::internal_encoding_type{}, std::move(input_encoding) };
        }


        // variables

        std::unique_ptr<pull_parser_type> m_p_pull_parser;

        input_encoder_type m_input_encoder;

        mutable std::unique_ptr<entry_type> m_p_preread_entry;

        mutable boost::optional<bool> m_preamble_read_succeeded;


        // functions

        bool preread() const
        {
            if (m_p_preread_entry)
                return true;

            if (!m_preamble_read_succeeded)
                skip_preamble();
            assert(m_preamble_read_succeeded);
            if (!*m_preamble_read_succeeded)
                return false;

            m_p_preread_entry = next_entry();
            if (!m_p_preread_entry)
                return false;

            return true;
        }

        void skip_preamble() const
        {
            if (!next_is<structure_begin_type>(input_string_type{ TETENGO2_TEXT("object") }))
            {
                m_preamble_read_succeeded = boost::make_optional(false);
                return;
            }
            m_p_pull_parser->next();

            if (next_is<structure_begin_type>(
                    input_string_type{ TETENGO2_TEXT("member") }, input_string_type{ TETENGO2_TEXT("header") }))
            {
                m_p_pull_parser->skip_next();
            }

            if (!next_is<structure_begin_type>(
                    input_string_type{ TETENGO2_TEXT("member") }, input_string_type{ TETENGO2_TEXT("body") }))
            {
                m_preamble_read_succeeded = boost::make_optional(false);
                return;
            }
            m_p_pull_parser->next();

            if (!next_is<structure_begin_type>(input_string_type{ TETENGO2_TEXT("object") }))
            {
                m_preamble_read_succeeded = boost::make_optional(false);
                return;
            }
            m_p_pull_parser->next();

            m_preamble_read_succeeded = boost::make_optional(true);
            return;
        }

        std::unique_ptr<entry_type> next_entry() const
        {
            input_string_type key{};
            input_string_type value{};

            {
                if (!m_p_pull_parser->has_next())
                    return {};
                const auto& element = m_p_pull_parser->peek();
                if (element.which() != 0)
                    return {};

                const auto& structure = boost::get<structure_begin_type>(element);
                key = get_attribute(structure);
                if (key.empty())
                    return {};

                m_p_pull_parser->next();
            }
            {
                if (!m_p_pull_parser->has_next())
                    return {};
                const auto& element = m_p_pull_parser->peek();
                if (element.which() != 2)
                    return {};

                const auto& parsed_value = boost::get<value_type>(element);
                if (parsed_value.which() != 4)
                    return {};

                value = boost::get<input_string_type>(parsed_value);

                m_p_pull_parser->next();
            }
            {
                if (!m_p_pull_parser->has_next())
                    return {};
                const auto& element = m_p_pull_parser->peek();
                if (element.which() != 1)
                    return {};

                m_p_pull_parser->next();
            }

            return stdalt::make_unique<entry_type>(m_input_encoder.decode(key), m_input_encoder.decode(value));
        }

        template <typename Structure>
        bool next_is(const input_string_type& name, const input_string_type& attribute = input_string_type{}) const
        {
            if (!m_p_pull_parser->has_next())
                return false;

            const auto& element = m_p_pull_parser->peek();
            if (!is_structure(element, static_cast<const Structure*>(nullptr)))
                return false;

            const auto structure = boost::get<Structure>(element);
            if (structure.name() != name)
                return false;
            if (!attribute.empty())
            {
                if (get_attribute(structure) != attribute)
                    return false;
            }

            return true;
        }

        bool is_structure(const element_type& element, const structure_begin_type* const) const
        {
            return element.which() == 0;
        }

        bool is_structure(const element_type& element, const structure_end_type* const) const
        {
            return element.which() == 1;
        }

        input_string_type get_attribute(const structure_begin_type& structure) const
        {
            const auto found = structure.attribute_map().find(input_string_type{ TETENGO2_TEXT("name") });
            if (found == structure.attribute_map().end())
                return {};
            if (found->second.which() != 4)
                return {};

            return boost::get<input_string_type>(found->second);
        }
    };


    template <typename ForwardIterator>
    message_catalog_parser<ForwardIterator>::message_catalog_parser(
        std::unique_ptr<pull_parser_type> p_pull_parser,
        input_encoding_type               input_encoding)
    : m_p_impl(stdalt::make_unique<impl>(std::move(p_pull_parser), std::move(input_encoding)))
    {}

    template <typename ForwardIterator>
    message_catalog_parser<ForwardIterator>::~message_catalog_parser() = default;

    template <typename ForwardIterator>
    bool message_catalog_parser<ForwardIterator>::has_next() const
    {
        return m_p_impl->has_next();
    }

    template <typename ForwardIterator>
    const typename message_catalog_parser<ForwardIterator>::entry_type&
    message_catalog_parser<ForwardIterator>::peek() const
    {
        return m_p_impl->peek();
    }

    template <typename ForwardIterator>
    void message_catalog_parser<ForwardIterator>::next()
    {
        m_p_impl->next();
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

    template class message_catalog_parser<application::input_stream_iterator_type>;

    template class message_catalog_parser<test::input_stream_iterator_type>;


}}
