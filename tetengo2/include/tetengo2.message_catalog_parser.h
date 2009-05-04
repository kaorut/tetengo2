/*! \file
    \brief The definition of tetengo2::message_catalog_parser.

    Copyright (C) 2007-2009 kaoru

    $Id$
*/

#if !defined(TETENGO2_MESSAGECATALOGPARSER_H)
#define TETENGO2_MESSAGECATALOGPARSER_H

#include <algorithm>
#include <stdexcept>
#include <string>
#include <utility>

//#include <boost/concept_check.hpp>
#include <boost/optional.hpp>
#include <boost/noncopyable.hpp>
#include <boost/scope_exit.hpp>
#include <boost/tokenizer.hpp>

#include "concept_tetengo2.String.h"


namespace tetengo2
{
    /*!
        \brief The class template for message_catalog_parser.

        It is a customized locale facet for message_catalog_parser.

        \tparam String A string type. It must conform to
                       concept_tetengo2::String<String>.
        \tparam Encode An encoding unary functor type. The types
                       Encode<String, std::string> must conform to
                       boost::UnaryFunction<Encode, String, std::string>.
    */
    template <
        typename String,
        template <typename Target, typename Source> class Encode
    >
    class message_catalog_parser : private boost::noncopyable
    {
    private:
        // concept checks

        BOOST_CONCEPT_ASSERT((concept_tetengo2::String<String>));
        struct concept_check_Encode
        {
            typedef Encode<String, std::string> encode_from_stdstring_type;
            BOOST_CONCEPT_ASSERT((
                boost::UnaryFunction<
                    encode_from_stdstring_type, String, std::string
                >
            ));
        };


    public:
        // types

        //! The input string_type.
        typedef std::string input_string_type;

        //! The string type.
        typedef String string_type;

        //! The unary functor type for encoding from the input string.
        typedef Encode<string_type, input_string_type> encode_type;

        //! The entry type.
        typedef std::pair<string_type, string_type> entry_type;


        // constructors and destructor

        /*!
            \brief Creates a message catalog parser.

            \tparam InputIterator An input iterator type.

            \param first An iterator to a first element.
            \param last  An iterator to the next to a last element.
        */
        template <typename InputIterator>
        message_catalog_parser(InputIterator first, InputIterator last)
        :
        m_line_tokenizer(first, last, separator_type("\\", "\r\n", "\"'")),
        m_line_token_iterator(m_line_tokenizer.begin()),
        m_preread_entry()
        {}

        /*!
            \brief Destroys a message catalog parser.
        */
        virtual ~message_catalog_parser()
        throw ()
        {}


        // functions

        /*!
            \brief Checks whether a next entry exists.

            \retval true  A next entry exists.
            \retval false Otherwise.
        */
        bool has_next()
        const
        {
            return preread();
        }

        /*!
            \brief Returns the next entry.

            \return The next entry.

            \throw std::runtime_error No next entry exists.
        */
        const entry_type next()
        {
            if (!has_next())
                throw std::runtime_error("No next entry.");

            BOOST_SCOPE_EXIT((&m_preread_entry))
            {
                m_preread_entry = boost::optional<entry_type>();
            } BOOST_SCOPE_EXIT_END
            return *m_preread_entry;
        }


    private:
        // types

        typedef
            boost::escaped_list_separator<
                typename input_string_type::value_type
            >
            separator_type;

        typedef
            boost::tokenizer<
                separator_type,
                typename input_string_type::const_iterator,
                input_string_type
            >
            tokenizer_type;


        // variables

        const tokenizer_type m_line_tokenizer;

        mutable typename tokenizer_type::iterator m_line_token_iterator;

        mutable boost::optional<entry_type> m_preread_entry;


        // functions

        bool preread()
        const
        {
            if (m_preread_entry) return true;

            while (m_line_token_iterator != m_line_tokenizer.end())
            {
                input_string_type line = *m_line_token_iterator;
                ++m_line_token_iterator;
                remove_comment(line);

                const entry_type entry = parse(line);
                if (!entry.first.empty())
                {
                    m_preread_entry = entry;
                    return true;
                }
            }

            return false;
        }

        void remove_comment(input_string_type& line)
        const
        {
            const typename input_string_type::size_type position =
                line.find('#');
            if (position != input_string_type::npos)
                line.substr(position);
        }

        const entry_type parse(const input_string_type& line)
        const
        {
            const tokenizer_type key_value_tokenizer(
                line, separator_type("\\", "=", "\"'")
            );
            std::vector<input_string_type> tokens;
            tokens.reserve(2);
            std::copy(
                key_value_tokenizer.begin(),
                key_value_tokenizer.end(),
                std::back_inserter(tokens)
            );

            if (tokens.size() < 2)
                return std::make_pair(L"", L"");

            return entry_type(
                encode_type()(tokens[0]), encode_type()(tokens[1])
            );
        }


    };


}

#endif
