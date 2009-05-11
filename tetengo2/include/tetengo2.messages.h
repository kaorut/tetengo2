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
#include <vector>

#include <boost/bind.hpp>
//#include <boost/concept_check.hpp>
//#include <boost/filesystem.hpp>
#include <boost/noncopyable.hpp>
#include <boost/optional.hpp>
#include <boost/unordered_map.hpp>

#include "concept_tetengo2.MessageCatalogParser.h"
#include "concept_tetengo2.Path.h"


namespace tetengo2
{
    /*!
        \brief The class template for a messages facet.

        It is a customized locale facet for a messages facet.

        \tparam Path                 A path type. It must conform to
                                     concept_tetengo2::Path<Path>.
        \tparam MessageCatalogParser A message catalog parser type. It must
                                     conform to
                                     concept_tetengo2::MessageCatalogParser<MessageCatalogParser>.
        \tparam Encode               An encoding unary functor type. The 
                                     Encode<std::wstring, typename Path::string_type>
                                     must conform to
                                     boost::UnaryFunction<Encode, std::string, typename Path::string_type>.
    */
    template <
        typename Path,
        typename MessageCatalogParser,
        template <typename Target, typename Source> class Encode
    >
    class messages :
        public std::messages<
            typename MessageCatalogParser::string_type::value_type
        >,
        private boost::noncopyable
    {
    private:
        // concept checks

        BOOST_CONCEPT_ASSERT((concept_tetengo2::Path<Path>));
        BOOST_CONCEPT_ASSERT((
            concept_tetengo2::MessageCatalogParser<MessageCatalogParser>
        ));
        struct concept_check_Encode
        {
            typedef
                Encode<std::string, typename Path::string_type>
                encode_to_std_string_type;
            BOOST_CONCEPT_ASSERT((
                boost::UnaryFunction<
                    encode_to_std_string_type,
                    std::string,
                    typename Path::string_type
                >
            ));
        };


    public:
        // types

        //! The path type.
        typedef Path path_type;

        //! The message catalog parser type.
        typedef MessageCatalogParser message_catalog_parser_type;

        //! The unary functor type for encoding to std::string.
        typedef
            Encode<std::string, typename Path::string_type>
            encode_to_std_string_type;


        // constructors and destructor

        /*!
            \brief Creates a messages facet.

            \param path   A path where message catalogs are stored.
            \param locale A locale for the messages facet.

            \throw std::ios_base::failure When the path does not exist or is
                                          not a directory.
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

            \param catalog_id      A catalog ID.
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

            \param catalog_id A catalog ID.

            \throw std::runtime_error The message catalog is not open.
        */
        virtual void do_close(const catalog catalog_id)
        const
        {
            if (catalog_id < 0) return;

            if (!m_open)
                throw std::runtime_error("The message catalog is not open.");

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
                        encode_to_std_string_type()(path.stem());
                    catalog_locale = std::locale(locale_name.c_str());
                }
                catch (const std::runtime_error&)
                {
                    return false;
                }

                return catalog_locale == m_locale;
            }

        };


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
            std::ifstream input_stream(
                catalog_file.external_file_string().c_str()
            );

            message_catalog_parser_type parser(input_stream);
            while (parser.has_next())
                message_catalog.insert(parser.next());
        }


        // variables

        mutable bool m_open;

        const boost::optional<message_catalog_type> m_message_catalog;
        


    };


}

#endif
