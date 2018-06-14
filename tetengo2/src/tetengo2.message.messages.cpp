/*! \file
    \brief The definition of tetengo2::message::messages.

    Copyright (C) 2007-2018 kaoru

    $Id$
*/

#include <algorithm>
#include <fstream>
#include <functional>
#include <ios>
#include <iterator>
#include <locale>
#include <memory>
#include <stdexcept>
#include <string>
#include <type_traits>
#include <unordered_map>
#include <utility>
#include <vector>

#include <boost/algorithm/string.hpp>
#include <boost/core/noncopyable.hpp>
#include <boost/iterator/iterator_facade.hpp>
#include <boost/predef.h>
#include <boost/spirit/include/support_multi_pass.hpp>
#include <boost/throw_exception.hpp>

#include <tetengo2/detail/base/impl_set.h>
#include <tetengo2/detail/base/messages.h>
#include <tetengo2/iterator/observable_forward_iterator.h>
#include <tetengo2/message/message_catalog_parser.h>
#include <tetengo2/message/messages.h>
#include <tetengo2/stdalt.h>
#include <tetengo2/text.h>
#include <tetengo2/text/encoder.h>
#include <tetengo2/text/encoding/locale.h>
#include <tetengo2/text/encoding/polymorphic.h>
#include <tetengo2/text/encoding/utf8.h>
#include <tetengo2/text/grammar/json.h>
#include <tetengo2/text/push_parser.h>


namespace tetengo2::message {
    class messages::impl : private boost::noncopyable
    {
    public:
        // types

        using string_type = messages::string_type;

        using catalog = messages::catalog;


        // static functions

        static string_type remove_namespace(const string_type& key)
        {
            if (key.length() <= 1)
                return key;

            auto start = key.length() - 2;
            for (;;)
            {
                const auto offset = key.rfind(TETENGO2_TEXT(':'), start);
                if (offset == string_type::npos)
                    return key;
                if (offset == 0 || key[offset - 1] != string_type::value_type{ TETENGO2_TEXT('\\') })
                {
                    string_type ns_removed = key.substr(offset + 1);
                    boost::replace_all(
                        ns_removed, string_type{ TETENGO2_TEXT("\\:") }, string_type{ TETENGO2_TEXT(":") });
                    return ns_removed;
                }
                if (offset == 1)
                    return key;

                start = offset - 2;
            }
        }


        // constructors and destructor

        impl(const tetengo2::stdalt::filesystem::path& path, const std::locale& locale)
        : m_open{ false }, m_message_catalog{ load_message_catalog(path, locale) }
        {}


        // functions

        catalog do_open(
            TETENGO2_STDALT_MAYBE_UNUSED const std::string& catalog_name,
            TETENGO2_STDALT_MAYBE_UNUSED const std::locale& locale) const
        {
            if (m_open)
                BOOST_THROW_EXCEPTION((std::runtime_error{ "A message catalog is already open." }));

            if (!m_message_catalog)
                return -1;

            m_open = true;
            return 1;
        }

        string_type do_get(
            const catalog                          catalog_id,
            TETENGO2_STDALT_MAYBE_UNUSED const int set,
            TETENGO2_STDALT_MAYBE_UNUSED const int message,
            TETENGO2_STDALT_MAYBE_UNUSED const string_type& default_message) const
        {
            if (catalog_id < 0)
                return remove_namespace(default_message);

            if (!m_open)
                BOOST_THROW_EXCEPTION((std::runtime_error{ "The message catalog is not open." }));

            const auto found = m_message_catalog->find(default_message);

            return found != m_message_catalog->end() ? found->second : remove_namespace(default_message);
        }

        void do_close(const catalog catalog_id) const
        {
            if (catalog_id < 0)
                return;

            if (!m_open)
                BOOST_THROW_EXCEPTION((std::runtime_error{ "The message catalog is not open." }));

            m_open = false;
        }


    private:
        // types

        using iterator =
            iterator::observable_forward_iterator<boost::spirit::multi_pass<std::istreambuf_iterator<char>>>;

        using message_catalog_parser_type = message_catalog_parser<iterator>;

        using locale_name_encoder_type =
            text::encoder<text::encoding::locale<string_type>, text::encoding::locale<std::string>>;

        using catalog_file_mappings_type = std::unordered_map<string_type, string_type>;

        using message_catalog_type = std::unordered_map<string_type, string_type>;

        using directory_iterator_type = tetengo2::stdalt::filesystem::directory_iterator;

        using directory_entry_type = tetengo2::stdalt::filesystem::directory_entry;

        struct matches_locale_type
        {
            const std::locale& m_locale;

            matches_locale_type(const std::locale& locale) : m_locale{ locale } {}

            bool operator()(const catalog_file_mappings_type::value_type& mapping) const
            {
                const auto key_prefix =
                    detail::detail_impl_set().messages_().locale_name_prefix() + string_type{ TETENGO2_TEXT(":") };
                if (!boost::starts_with(mapping.first, key_prefix))
                    return false;

                const auto locale_name = locale_name_encoder().encode(mapping.first.substr(key_prefix.length()));
                try
                {
                    return std::locale{ locale_name.c_str() } == m_locale;
                }
                catch (const std::runtime_error&)
                {
                    return false;
                }
            }
        };

        using pull_parser_type = message_catalog_parser_type::pull_parser_type;

        using push_parser_type = pull_parser_type::push_parser_type;

        using grammar_type = text::grammar::json<push_parser_type::iterator>;


        // static functions

        static const locale_name_encoder_type& locale_name_encoder()
        {
            static const locale_name_encoder_type singleton{};
            return singleton;
        }

        static const tetengo2::stdalt::filesystem::path::string_type& catalog_file_mappings_filename()
        {
            static const tetengo2::stdalt::filesystem::path::string_type singleton{ TETENGO2_TEXT("_catalogs.json") };
            return singleton;
        }

        static tetengo2::stdalt::optional<message_catalog_type>
        load_message_catalog(const tetengo2::stdalt::filesystem::path& path, const std::locale& locale)
        {
            const auto catalog_file = select_catalog_file(path, locale);
            if (!catalog_file)
                return TETENGO2_STDALT_NULLOPT;

            message_catalog_type message_catalog{};
            read_message_catalog(*catalog_file, message_catalog);

            return tetengo2::stdalt::make_optional(std::move(message_catalog));
        }

        static const tetengo2::stdalt::optional<tetengo2::stdalt::filesystem::path>
        select_catalog_file(const tetengo2::stdalt::filesystem::path& path, const std::locale& locale)
        {
            if (!tetengo2::stdalt::filesystem::exists(path))
                BOOST_THROW_EXCEPTION((std::ios_base::failure{ "Path does not exist." }));
            if (!tetengo2::stdalt::filesystem::is_directory(path))
                BOOST_THROW_EXCEPTION((std::ios_base::failure{ "Path is not a directory." }));

            std::vector<tetengo2::stdalt::filesystem::path> catalog_files{};
            std::transform(
                directory_iterator_type{ path },
                directory_iterator_type{},
                std::back_inserter(catalog_files),
                [](const directory_entry_type& entry) { return entry.path(); });
            std::sort(catalog_files.begin(), catalog_files.end(), std::greater<tetengo2::stdalt::filesystem::path>{});

            const auto catalog_file_mappings = read_catalog_file_mappings(path);

            const auto found =
                std::find_if(catalog_file_mappings.begin(), catalog_file_mappings.end(), matches_locale_type(locale));
            if (found != catalog_file_mappings.end())
                return path / found->second;

            return TETENGO2_STDALT_NULLOPT;
        }

        static catalog_file_mappings_type
        read_catalog_file_mappings(const tetengo2::stdalt::filesystem::path& message_catalog_directory)
        {
            catalog_file_mappings_type mappings{};

            std::ifstream input_stream{ tetengo2::stdalt::filesystem::path{ message_catalog_directory /
                                                                            catalog_file_mappings_filename() } };
            if (!input_stream.is_open())
                BOOST_THROW_EXCEPTION((std::ios_base::failure{ "Can't open the message catalog file mappings." }));

            message_catalog_parser_type parser{ create_pull_parser(input_stream),
                                                text::encoding::make_polymorphic<text::encoding::utf8>() };
            while (parser.has_next())
            {
                mappings.insert(parser.peek());
                parser.next();
            }

            return mappings;
        }

        static void read_message_catalog(
            const tetengo2::stdalt::filesystem::path& catalog_file,
            message_catalog_type&                     message_catalog)
        {
            std::ifstream input_stream{ catalog_file };
            if (!input_stream.is_open())
                BOOST_THROW_EXCEPTION((std::ios_base::failure{ "Can't open a message catalog." }));

            message_catalog_parser_type parser{ create_pull_parser(input_stream),
                                                text::encoding::make_polymorphic<text::encoding::utf8>() };
            while (parser.has_next())
            {
                message_catalog.insert(parser.peek());
                parser.next();
            }
        }

        static std::unique_ptr<pull_parser_type> create_pull_parser(std::istream& input_stream)
        {
            auto p_grammar = std::make_unique<grammar_type>();

            const auto first = tetengo2::iterator::make_observable_forward_iterator(
                boost::spirit::make_default_multi_pass(std::istreambuf_iterator<char>{ input_stream }));
            const auto last = tetengo2::iterator::make_observable_forward_iterator(
                boost::spirit::make_default_multi_pass(std::istreambuf_iterator<char>{}));
            auto p_push_parser = std::make_unique<push_parser_type>(first, last, std::move(p_grammar));

            return std::make_unique<pull_parser_type>(std::move(p_push_parser), 5);
        }


        // variables

        mutable bool m_open;

        const tetengo2::stdalt::optional<message_catalog_type> m_message_catalog;
    };


    messages::string_type messages::remove_namespace(const string_type& key)
    {
        return impl::remove_namespace(key);
    }

    messages::messages(const tetengo2::stdalt::filesystem::path& path, const std::locale& locale)
    : m_p_impl{ std::make_unique<impl>(path, locale) }
    {}

    messages::~messages() = default;

    messages::catalog messages::do_open(const std::string& catalog_name, const std::locale& locale) const
    {
        return m_p_impl->do_open(catalog_name, locale);
    }

    messages::string_type
    messages::do_get(const catalog catalog_id, const int set, const int message, const string_type& default_message)
        const
    {
        return m_p_impl->do_get(catalog_id, set, message, default_message);
    }

    void messages::do_close(catalog catalog_id) const
    {
        return m_p_impl->do_close(catalog_id);
    }
}
