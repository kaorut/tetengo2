/*! \file
    \brief The definition of tetengo2::message::messages.

    Copyright (C) 2007-2017 kaoru

    $Id$
*/

#if !defined(TETENGO2_MESSAGE_MESSAGES_H)
#define TETENGO2_MESSAGE_MESSAGES_H

#include <algorithm>
#include <functional>
#include <ios>
#include <istream>
#include <iterator>
#include <locale>
#include <memory>
#include <stdexcept>
#include <string>
#include <unordered_map>
#include <utility>
#include <vector>

#include <boost/algorithm/string.hpp>
#include <boost/core/ignore_unused.hpp>
#include <boost/core/noncopyable.hpp>
#include <boost/filesystem.hpp>
#include <boost/filesystem/fstream.hpp>
#include <boost/optional.hpp>
#include <boost/spirit/include/support_multi_pass.hpp>
#include <boost/throw_exception.hpp>

#include <tetengo2/iterator/observable_forward_iterator.h>
#include <tetengo2/message/message_catalog_parser.h>
#include <tetengo2/stdalt.h>
#include <tetengo2/text.h>
#include <tetengo2/text/grammar/json.h>


namespace tetengo2 { namespace message
{
    /*!
        \brief The class template for a messages facet.

        It is a customized locale facet for a messages facet.

        \tparam ForwardIterator   A forward iterator type.
        \tparam String            A string type.
        \tparam Size              A size type.
        \tparam Encoder           An encoder type.
        \tparam LocaleNameEncoder An encoder type for locale names.
    */
    template <
        typename ForwardIterator,
        typename String,
        typename Size,
        typename Encoder,
        typename LocaleNameEncoder
    >
    class messages : public std::messages<typename String::value_type>, private boost::noncopyable
    {
    public:
        // types

        //! The iterator type.
        using iterator = ForwardIterator;

        //! The string type.
        using string_type = String;

        //! The size type.
        using size_type = Size;

        //! The encoder type.
        using encoder_type = Encoder;

        //! The message catalog parser type.
        using message_catalog_parser_type = message_catalog_parser<iterator, string_type, size_type, encoder_type>;

        //! The encoder type for locale names.
        using locale_name_encoder_type = LocaleNameEncoder;

        //! The base type.
        using base_type = std::messages<typename string_type::value_type>;

        //! The catalog type.
        using catalog = typename base_type::catalog;


        // static functions

        /*!
            \brief Removes namespaces.

            \param key A key.

            \return The key in which the namespace part is removed.
        */
        static string_type remove_namespace(const string_type& key)
        {
            if (key.length() <= 1)
                return key;

            auto start = key.length() - 2;
            for(;;)
            {
                const auto offset = key.rfind(TETENGO2_TEXT(':'), start);
                if (offset == string_type::npos)
                    return key;
                if (offset == 0 || key[offset - 1] != typename string_type::value_type{ TETENGO2_TEXT('\\') })
                {
                    string_type ns_removed = key.substr(offset + 1);
                    boost::replace_all(
                        ns_removed, string_type{ TETENGO2_TEXT("\\:") }, string_type{ TETENGO2_TEXT(":") }
                    );
                    return ns_removed;
                }
                if (offset == 1)
                    return key;

                start = offset - 2;
            }
        }


        // constructors and destructor

        /*!
            \brief Creates a messages facet.

            \param path   A path where message catalogs are stored.
            \param locale A locale for the messages facet.

            \throw std::ios_base::failure When the path does not exist or is not a directory.
        */
        messages(const boost::filesystem::path& path, const std::locale& locale)
        :
        m_open(false),
        m_message_catalog(load_message_catalog(path, locale))
        {}

        /*!
            \brief Destroys the messages facet.
        */
        virtual ~messages()
        = default;


    private:
        // types

        using catalog_file_mappings_type = std::unordered_map<string_type, string_type>;

        using message_catalog_type = std::unordered_map<string_type, string_type>;

        using directory_iterator_type = boost::filesystem::directory_iterator;

        using directory_entry_type = boost::filesystem::directory_entry;

        struct matches_locale_type
        {
            const std::locale& m_locale;

            matches_locale_type(const std::locale& locale)
            :
            m_locale(locale)
            {}

            bool operator()(const typename catalog_file_mappings_type::value_type& mapping)
            const
            {
                const auto locale_name = locale_name_encoder().encode(mapping.first);
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

        using pull_parser_type = typename message_catalog_parser_type::pull_parser_type;

        using push_parser_type = typename pull_parser_type::push_parser_type;

        using grammar_type = text::grammar::json<typename push_parser_type::iterator>;


        // static functions

        static const locale_name_encoder_type& locale_name_encoder()
        {
            static const locale_name_encoder_type singleton{};
            return singleton;
        }

        static const typename boost::filesystem::path::string_type& catalog_file_mappings_filename()
        {
            static const typename boost::filesystem::path::string_type singleton{ TETENGO2_TEXT("_catalogs.json") };
            return singleton;
        }

        static boost::optional<message_catalog_type>
        load_message_catalog(const boost::filesystem::path& path, const std::locale& locale)
        {
            const auto catalog_file = select_catalog_file(path, locale);
            if (!catalog_file)
                return boost::none;

            message_catalog_type message_catalog{};
            read_message_catalog(*catalog_file, message_catalog);

            return boost::make_optional(std::move(message_catalog));
        }

        static const boost::optional<boost::filesystem::path> select_catalog_file(
            const boost::filesystem::path& path,
            const std::locale&             locale
        )
        {
            if (!boost::filesystem::exists(path))
                BOOST_THROW_EXCEPTION((std::ios_base::failure{ "Path does not exist." }));
            if (!boost::filesystem::is_directory(path))
                BOOST_THROW_EXCEPTION((std::ios_base::failure{ "Path is not a directory." }));

            std::vector<boost::filesystem::path> catalog_files{};
            std::transform(
                directory_iterator_type{ path },
                directory_iterator_type{},
                std::back_inserter(catalog_files),
                [](const directory_entry_type& entry) { return entry.path(); }
            );
            std::sort(catalog_files.begin(), catalog_files.end(), std::greater<boost::filesystem::path>{});

            const auto catalog_file_mappings = read_catalog_file_mappings(path);

            const auto found =
                std::find_if(catalog_file_mappings.begin(), catalog_file_mappings.end(), matches_locale_type(locale));
            if (found != catalog_file_mappings.end())
                return path / found->second;

            return boost::none;
        }

        static catalog_file_mappings_type read_catalog_file_mappings(
            const boost::filesystem::path& message_catalog_directory
        )
        {
            catalog_file_mappings_type mappings{};

            boost::filesystem::ifstream input_stream{
                boost::filesystem::path{ message_catalog_directory / catalog_file_mappings_filename() }
            };
            if (!input_stream.is_open())
                BOOST_THROW_EXCEPTION((std::ios_base::failure{ "Can't open the message catalog file mappings." }));

            message_catalog_parser_type parser{ create_pull_parser(input_stream) };
            while (parser.has_next())
            {
                mappings.insert(parser.peek());
                parser.next();
            }

            return mappings;
        }

        static void read_message_catalog(
            const boost::filesystem::path& catalog_file,
            message_catalog_type&          message_catalog
        )
        {
            boost::filesystem::ifstream input_stream{ catalog_file };
            if (!input_stream.is_open())
                BOOST_THROW_EXCEPTION((std::ios_base::failure{ "Can't open a message catalog." }));

            message_catalog_parser_type parser{ create_pull_parser(input_stream) };
            while (parser.has_next())
            {
                message_catalog.insert(parser.peek());
                parser.next();
            }
        }

        static std::unique_ptr<pull_parser_type> create_pull_parser(std::istream& input_stream)
        {
            auto p_grammar = stdalt::make_unique<grammar_type>();
            
            const auto first =
                iterator::make_observable_forward_iterator(
                    boost::spirit::make_default_multi_pass(std::istreambuf_iterator<char>{ input_stream })
                );
            const auto last =
                iterator::make_observable_forward_iterator(
                    boost::spirit::make_default_multi_pass(std::istreambuf_iterator<char>{})
                );
            auto p_push_parser = stdalt::make_unique<push_parser_type>(first, last, std::move(p_grammar));

            return stdalt::make_unique<pull_parser_type>(std::move(p_push_parser), 5);
        }


        // variables

        mutable bool m_open;

        const boost::optional<message_catalog_type> m_message_catalog;


        // virtual functions

        virtual catalog do_open(const std::string& catalog_name, const std::locale& locale)
        const override
        {
            boost::ignore_unused(catalog_name, locale);

            if (m_open)
                BOOST_THROW_EXCEPTION((std::runtime_error{ "A message catalog is already open." }));

            if (!m_message_catalog) return -1;

            m_open = true;
            return 1;
        }

        virtual string_type do_get(
            const catalog      catalog_id,
            const int          set,
            const int          message,
            const string_type& default_message
        )
        const override
        {
            boost::ignore_unused(set, message);

            if (catalog_id < 0)
                return remove_namespace(default_message);

            if (!m_open)
                BOOST_THROW_EXCEPTION((std::runtime_error{ "The message catalog is not open." }));

            const auto found = m_message_catalog->find(default_message);

            return found != m_message_catalog->end() ? found->second : remove_namespace(default_message);
        }

        virtual void do_close(const catalog catalog_id)
        const override
        {
            if (catalog_id < 0) return;

            if (!m_open)
                BOOST_THROW_EXCEPTION((std::runtime_error{ "The message catalog is not open." }));

            m_open = false;
        }


    };


}}


#endif
