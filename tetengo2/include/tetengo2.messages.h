/*! \file
    \brief The definition of tetengo2::messages.

    Copyright (C) 2007-2009 kaoru

    $Id$
*/

#if !defined(TETENGO2_MESSAGES_H)
#define TETENGO2_MESSAGES_H

#include <algorithm>
#include <functional>
#include <fstream>
#include <ios>
#include <iterator>
#include <locale>
#include <stdexcept>
//#include <string>
#include <utility>
#include <vector>

#include <boost/bind.hpp>
//#include <boost/concept_check.hpp>
//#include <boost/filesystem.hpp>
#include <boost/noncopyable.hpp>
#include <boost/optional.hpp>
#include <boost/tokenizer.hpp>
#include <boost/unordered_map.hpp>
#include <boost/algorithm/string.hpp>

#include "concept_tetengo2.Path.h"
#include "concept_tetengo2.String.h"


namespace tetengo2
{
    /*!
        \brief The class template for messages.

        It is a customized locale facet for messages.

        \tparam String A string type. It must conform to
                       concept_tetengo2::String<String>.
        \tparam Path   A path type. It must conform to
                       concept_tetengo2::Path<Path>.
        \tparam Encode An encoding unary functor type. The types
                       Encode<String, std::wstring> and
                       Encode<std::wstring, String> must conform to
                       boost::UnaryFunction<Encode, String, std::wstring> and
                       boost::UnaryFunction<Encode, std::wstring, String>.
    */
    template <
        typename String,
        typename Path,
        template <typename Target, typename Source> class Encode
    >
    class messages :
        public std::messages<typename String::value_type>,
        private boost::noncopyable
    {
    private:
        // concept checks

        BOOST_CONCEPT_ASSERT((concept_tetengo2::String<String>));
        BOOST_CONCEPT_ASSERT((concept_tetengo2::Path<Path>));
        struct concept_check_Encode
        {
            typedef Encode<String, std::string> encode_from_stdstring_type;
            BOOST_CONCEPT_ASSERT((
                boost::UnaryFunction<
                    encode_from_stdstring_type, String, std::string
                >
            ));
            typedef Encode<std::string, String> encode_to_stdstring_type;
            BOOST_CONCEPT_ASSERT((
                boost::UnaryFunction<
                    encode_from_stdstring_type, std::string, String
                >
            ));
        };


    public:
        // types

        //! The path type.
        typedef Path path_type;

        //! The unary functor type for encoding from the std::string.
        typedef Encode<string_type, std::string> encode_from_stdstring_type;

        //! The unary functor type for encoding to the std::string.
        typedef Encode<std::string, string_type> encode_to_stdstring_type;


        // constructors and destructor

        /*!
            \brief Creates messages.

            \param path   A path where message catalogs are stored.
            \param locale A locale for the messages.

            \throw std::ios_base::failure When the path does not exist or is
                                          not a directory.
        */
        messages(const path_type& path, const std::locale& locale)
        :
        m_open(false),
        m_message_catalog(load_message_catalog(path, locale))
        {}

        virtual ~messages()
        throw ()
        {}


    protected:
        // functions
        
        /*!
            \brief Opens a message catalog.

            \param catalog_name Not used.
            \param locale       Not used.

            \return The catalog ID. When failed, the value is less than 0.

            \throw std::runtime_error A message catalog is already open.
        */
        virtual catalog do_open(
            const std::string& catalog_name,
            const std::locale& locale
        )
        const
        {
            if (m_open)
            {
                throw std::runtime_error(
                    "A message catalog is already open."
                );
            }

            if (!m_message_catalog) return -1;

            m_open = true;
            return 1;
        }
        
        /*!
            \brief Returns the localized message.

            \param catalog_id      A catalog ID. It must be 0.
            \param set             Not used.
            \param message         Not used.
            \param default_message A default message. Also, used as a key.

            \return The localized message.

            \throw std::runtime_error The message catalog is not open.
        */
        virtual string_type do_get(
            const catalog      catalog_id,
            const int          set,
            const int          message,
            const string_type& default_message
        )
        const
        {
            if (catalog_id < 0)
                return default_message;
            
            if (!m_open)
                throw std::runtime_error("The message catalog is not open.");

            const typename message_catalog_type::const_iterator found =
                m_message_catalog->find(default_message);

            return found != m_message_catalog->end() ?
                found->second : default_message;
        }

        /*!
            \brief Closes the message catalog.

            \param catalog_id A catalog ID. It must be 0.

            \throw std::runtime_error The message catalog is not open or the
                                      catalog ID is invalid.
        */
        virtual void do_close(const catalog catalog_id)
        const
        {
            if (!m_open || catalog_id < 0)
            {
                throw std::runtime_error(
                    "The message catalog is not open or the catalog ID is"
                    "invalid."
                );
            }

            m_open = false;
        }


    private:
        // types

        typedef
            boost::unordered_map<string_type, string_type>
            message_catalog_type;

        typedef
            boost::filesystem::basic_directory_iterator<path_type>
            directory_iterator_type;

        typedef
            boost::filesystem::basic_directory_entry<path_type>
            directory_entry_type;

        struct matches_locale_type :
            public std::unary_function<path_type, bool>
        {
            const std::locale& m_locale;

            matches_locale_type(const std::locale& locale)
            : m_locale(locale) {}

            bool operator()(const path_type& path)
            const
            {
                std::locale catalog_locale;
                try
                {
                    const std::string locale_name =
                        encode_to_stdstring_type()(path.stem());
                    catalog_locale = std::locale(locale_name.c_str());
                }
                catch (const std::runtime_error&)
                {
                    return false;
                }

                return catalog_locale == m_locale;
            }

        };

        typedef
            boost::escaped_list_separator<typename string_type::value_type>
            separator_type;

        typedef
            boost::tokenizer<
                separator_type,
                typename string_type::const_iterator,
                string_type
            >
            tokenizer_type;


        // static functions

        static const boost::optional<message_catalog_type>
        load_message_catalog(
            const path_type&   path,
            const std::locale& locale
        )
        {
            const boost::optional<path_type> catalog_file =
                select_catalog_file(path, locale);
            if (!catalog_file)
                return boost::optional<message_catalog_type>();

            message_catalog_type message_catalog;
            read_message_catalog(*catalog_file, message_catalog);
            
            return boost::optional<message_catalog_type>(message_catalog);
        }

        static const boost::optional<path_type> select_catalog_file(
            const path_type&   path,
            const std::locale& locale
        )
        {
            if (!boost::filesystem::exists(path))
                throw std::ios_base::failure("Path does not exist.");
            if (!boost::filesystem::is_directory(path))
                throw std::ios_base::failure("Path is not a directory.");

            std::vector<path_type> catalog_files;
            std::transform(
                directory_iterator_type(path),
                directory_iterator_type(),
                std::back_inserter(catalog_files),
                boost::bind(&directory_entry_type::path, _1)
            );
            std::sort(
                catalog_files.begin(),
                catalog_files.end(),
                std::greater<path_type>()
            );

            const std::vector<path_type>::const_iterator found =
                std::find_if(
                    catalog_files.begin(),
                    catalog_files.end(),
                    matches_locale_type(locale)
                );
            if (found != catalog_files.end())
                return *found;

            return boost::optional<path_type>();
        }

        static void read_message_catalog(
            const path_type&      catalog_file,
            message_catalog_type& message_catalog
        )
        {
            std::ifstream stream(catalog_file.external_file_string().c_str());
            while (stream.good())
            {
                std::string line;
                std::getline(stream, line);
                boost::trim(line);
                const string_type encoded_line =
                    encode_from_stdstring_type()(line);

                if (is_comment(encoded_line)) continue;

                const std::pair<string_type, string_type> parsed =
                    parse_line(encoded_line);
                if (!parsed.first.empty())
                    message_catalog.insert(parsed);
            }
        }

        static bool is_comment(const string_type& line)
        {
            return line.empty() || line[0] == L'#';
        }

        static const std::pair<string_type, string_type> parse_line(
            const string_type& line
        )
        {
            const tokenizer_type tokenizer(
                line, separator_type(L"\\", L"=", L"\"'")
            );
            std::vector<string_type> tokens;
            std::copy(
                tokenizer.begin(), tokenizer.end(), std::back_inserter(tokens)
            );

            if (tokens.size() < 2)
                return std::make_pair(L"", L"");

            return std::make_pair(tokens[0], tokens[1]);
        }


        // variables

        mutable bool m_open;

        const boost::optional<message_catalog_type> m_message_catalog;
        


    };


}

#endif
