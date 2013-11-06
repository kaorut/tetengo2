/*! \file
    \brief The definition of tetengo2::message::messages.

    Copyright (C) 2007-2013 kaoru

    $Id$
*/

#if !defined(TETENGO2_MESSAGE_MESSAGES_H)
#define TETENGO2_MESSAGE_MESSAGES_H

#include <algorithm>
#include <functional>
#include <ios>
#include <istream>
//#include <iterator>
#include <locale>
//#include <memory>
#include <stdexcept>
#include <string>
#include <unordered_map>
//#include <utility>
#include <vector>

#include <boost/algorithm/string.hpp>
#include <boost/filesystem.hpp>
#include <boost/filesystem/fstream.hpp>
#include <boost/noncopyable.hpp>
#include <boost/optional.hpp>
#include <boost/spirit/include/support_multi_pass.hpp>
#include <boost/throw_exception.hpp>

#include "tetengo2.stdalt.h"
#include "tetengo2.text.h"
#include "tetengo2.utility.h"


namespace tetengo2 { namespace message
{
    /*!
        \brief The class template for a messages facet.

        It is a customized locale facet for a messages facet.

        \tparam Path                 A path type.
        \tparam MessageCatalogParser A message catalog parser type.
        \tparam LocaleNameEncoder    An encoder type for locale names.
    */
    template <typename Path, typename MessageCatalogParser, typename LocaleNameEncoder>
    class messages :
        public std::messages<typename MessageCatalogParser::string_type::value_type>,
        private boost::noncopyable
    {
    public:
        // types

        //! The base type.
        typedef std::messages<typename MessageCatalogParser::string_type::value_type> base_type;

        //! The catalog type.
        typedef typename base_type::catalog catalog;

        //! The string type.
        typedef typename base_type::string_type string_type;

        //! The path type.
        typedef Path path_type;

        //! The message catalog parser type.
        typedef MessageCatalogParser message_catalog_parser_type;

        //! The encoder type for locale names.
        typedef LocaleNameEncoder locale_name_encoder_type;


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
                if (offset == 0 || key[offset - 1] != typename string_type::value_type(TETENGO2_TEXT('\\')))
                {
                    string_type ns_removed = key.substr(offset + 1);
                    boost::algorithm::replace_all(
                        ns_removed, string_type(TETENGO2_TEXT("\\:")), string_type(TETENGO2_TEXT(":"))
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
        messages(const path_type& path, const std::locale& locale)
        :
        m_open(false),
        m_message_catalog(load_message_catalog(path, locale))
        {}

        /*!
            \brief Destroys the messages facet.
        */
        virtual ~messages()
        TETENGO2_STDALT_NOEXCEPT
        {}


    private:
        // types

        typedef std::unordered_map<string_type, string_type> catalog_file_mappings_type;

        typedef std::unordered_map<string_type, string_type> message_catalog_type;

        typedef boost::filesystem::directory_iterator directory_iterator_type;

        typedef boost::filesystem::directory_entry directory_entry_type;

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
                    return std::locale(locale_name.c_str()) == m_locale;
                }
                catch (const std::runtime_error&)
                {
                    return false;
                }
            }

        };

        typedef typename message_catalog_parser_type::pull_parser_type pull_parser_type;

        typedef typename pull_parser_type::push_parser_type push_parser_type;

        typedef typename push_parser_type::grammar_type grammar_type;


        // static functions

        static const locale_name_encoder_type& locale_name_encoder()
        {
            static const locale_name_encoder_type singleton;
            return singleton;
        }

        static const typename path_type::string_type& catalog_file_mappings_filename()
        {
            static const typename path_type::string_type singleton(TETENGO2_TEXT("_catalogs.json"));
            return singleton;
        }

        static boost::optional<message_catalog_type>
        load_message_catalog(const path_type& path, const std::locale& locale)
        {
            const auto catalog_file = select_catalog_file(path, locale);
            if (!catalog_file)
                return boost::none;

            message_catalog_type message_catalog;
            read_message_catalog(*catalog_file, message_catalog);

            return boost::make_optional(std::move(message_catalog));
        }

        static const boost::optional<path_type> select_catalog_file(const path_type& path, const std::locale& locale)
        {
            if (!boost::filesystem::exists(path))
                BOOST_THROW_EXCEPTION(std::ios_base::failure("Path does not exist."));
            if (!boost::filesystem::is_directory(path))
                BOOST_THROW_EXCEPTION(std::ios_base::failure("Path is not a directory."));

            std::vector<path_type> catalog_files;
            std::transform(
                directory_iterator_type(path),
                directory_iterator_type(),
                std::back_inserter(catalog_files),
                [](const directory_entry_type& entry) { return entry.path(); }
            );
            std::sort(catalog_files.begin(), catalog_files.end(), std::greater<path_type>());

            const auto catalog_file_mappings = read_catalog_file_mappings(path);

            const auto found =
                std::find_if(catalog_file_mappings.begin(), catalog_file_mappings.end(), matches_locale_type(locale));
            if (found != catalog_file_mappings.end())
                return path / found->second;

            return boost::none;
        }

        static catalog_file_mappings_type read_catalog_file_mappings(const path_type& message_catalog_directory)
        {
            catalog_file_mappings_type mappings;

            boost::filesystem::ifstream input_stream(
                path_type(message_catalog_directory / catalog_file_mappings_filename())
            );
            if (!input_stream.is_open())
                BOOST_THROW_EXCEPTION(std::ios_base::failure("Can't open the message catalog file mappings."));

            message_catalog_parser_type parser(create_pull_parser(input_stream));
            while (parser.has_next())
            {
                mappings.insert(parser.peek());
                parser.next();
            }

            return mappings;
        }

        static void read_message_catalog(const path_type& catalog_file, message_catalog_type& message_catalog)
        {
            boost::filesystem::ifstream input_stream(catalog_file);
            if (!input_stream.is_open())
                BOOST_THROW_EXCEPTION(std::ios_base::failure("Can't open a message catalog."));

            message_catalog_parser_type parser(create_pull_parser(input_stream));
            while (parser.has_next())
            {
                message_catalog.insert(parser.peek());
                parser.next();
            }
        }

        static std::unique_ptr<pull_parser_type> create_pull_parser(std::istream& input_stream)
        {
            auto p_grammar = stdalt::make_unique<grammar_type>();
            
            auto p_push_parser =
                stdalt::make_unique<push_parser_type>(
                    boost::spirit::make_default_multi_pass(std::istreambuf_iterator<char>(input_stream)),
                    boost::spirit::make_default_multi_pass(std::istreambuf_iterator<char>()),
                    std::move(p_grammar)
                );

            return stdalt::make_unique<pull_parser_type>(std::move(p_push_parser), 5);
        }


        // variables

        mutable bool m_open;

        const boost::optional<message_catalog_type> m_message_catalog;


        // virtual functions

        virtual catalog do_open(const std::string& catalog_name, const std::locale& locale)
        const override
        {
            suppress_unused_variable_warning(catalog_name, locale);

            if (m_open)
                BOOST_THROW_EXCEPTION(std::runtime_error("A message catalog is already open."));

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
            suppress_unused_variable_warning(set, message);

            if (catalog_id < 0)
                return remove_namespace(default_message);

            if (!m_open)
                BOOST_THROW_EXCEPTION(std::runtime_error("The message catalog is not open."));

            const auto found = m_message_catalog->find(default_message);

            return found != m_message_catalog->end() ? found->second : remove_namespace(default_message);
        }

        virtual void do_close(const catalog catalog_id)
        const override
        {
            if (catalog_id < 0) return;

            if (!m_open)
                BOOST_THROW_EXCEPTION(std::runtime_error("The message catalog is not open."));

            m_open = false;
        }


    };


}}


#endif
