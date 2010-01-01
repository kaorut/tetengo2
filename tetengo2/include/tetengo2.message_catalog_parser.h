/*! \file
    \brief The definition of tetengo2::message_catalog_parser.

    Copyright (C) 2007-2010 kaoru

    $Id$
*/

#if !defined(TETENGO2_MESSAGECATALOGPARSER_H)
#define TETENGO2_MESSAGECATALOGPARSER_H

#include <algorithm>
#include <cstddef>
#include <iterator>
#include <memory>
#include <stdexcept>
//#include <string>
#include <utility>
#include <vector>

//#include <boost/concept_check.hpp>
#include <boost/noncopyable.hpp>
#include <boost/tokenizer.hpp>
#include <boost/algorithm/string.hpp>

#include "concept_tetengo2.String.h"


namespace tetengo2
{
    /*!
        \brief The class template for a message catalog parser.

        \tparam InputStream An input stream type. It must conform to
                            concept_tetengo2::InputStream<InputStream>.
        \tparam String      A string type. It must conform to
                            concept_tetengo2::String<String>.
        \tparam Encode      An encoding unary functor type. The types
                            Encode<String, std::string> must conform to
                            boost::UnaryFunction<Encode, String, std::string>.
    */
    template <
        typename InputStream,
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

        //! The input stream type.
        typedef InputStream input_stream_type;

        //! The input string_type.
        typedef
            std::basic_string<typename input_stream_type::char_type>
            input_string_type;

        //! The string type.
        typedef String string_type;

        //! The unary functor type for encoding from the input string.
        typedef Encode<string_type, input_string_type> encode_type;

        //! The entry type.
        typedef std::pair<string_type, string_type> entry_type;


        // constructors and destructor

        /*!
            \brief Creates a message catalog parser.

            \param input_stream An input stream.
        */
        explicit message_catalog_parser(input_stream_type& input_stream)
        :
        m_input_stream(input_stream),
        m_p_preread_entry()
        {}

        /*!
            \brief Destroys a message catalog parser.
        */
        ~message_catalog_parser()
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

            const std::auto_ptr<entry_type> p_entry = m_p_preread_entry;
            m_p_preread_entry.reset();
            return *p_entry;
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

        mutable input_stream_type& m_input_stream;

        mutable std::auto_ptr<entry_type> m_p_preread_entry;


        // functions

        bool preread()
        const
        {
            if (m_p_preread_entry.get() != NULL) return true;

            while (m_input_stream.good())
            {
                std::auto_ptr<entry_type> p_entry = parse(get_line());
                if (p_entry.get() != NULL)
                {
                    m_p_preread_entry = p_entry;
                    return true;
                }
            }

            return false;
        }

        const input_string_type get_line()
        const
        {
            input_string_type line;
            for (;;)
            {
                input_string_type got_line;
                std::getline(m_input_stream, got_line);
                if (got_line.empty()) break;
                if (got_line[got_line.length() - 1] != '\\')
                {
                    line.append(got_line);
                    break;
                }

                line.append(got_line.begin(), got_line.end() - 1);
            }

            remove_comment(line);
            replace_special_characters(line);

            return line;
        }

        void remove_comment(input_string_type& line)
        const
        {
            typename input_string_type::size_type position = 0;
            for (;;)
            {
                position = line.find('#', position);
                if (position == input_string_type::npos) break;

                if (position == 0 || line[position - 1] != '\\')
                {
                    line = line.substr(0, position);
                    break;
                }

                ++position;
            }

            boost::replace_all(line, "\\#", "#");
        }

        void replace_special_characters(input_string_type& line)
        const
        {
            boost::replace_all(line, "\\t", "\t");
            boost::replace_all(line, "\\n", "\n");
        }

        std::auto_ptr<entry_type> parse(const input_string_type& line)
        const
        {
            const tokenizer_type tokenizer(
                line, separator_type("\\", "=", "\"'")
            );
            std::vector<input_string_type> tokens;
            tokens.reserve(2);
            std::copy(
                tokenizer.begin(), tokenizer.end(), std::back_inserter(tokens)
            );

            if (tokens.size() < 2)
                return std::auto_ptr<entry_type>();

            return std::auto_ptr<entry_type>(
                new entry_type(
                    encode_type()(tokens[0]), encode_type()(tokens[1])
                )
            );
        }


    };


}

#endif
