/*! \file
    \brief The definition of tetengo2::message_catalog_parser.

    Copyright (C) 2007-2011 kaoru

    $Id$
*/

#if !defined(TETENGO2_MESSAGECATALOGPARSER_H)
#define TETENGO2_MESSAGECATALOGPARSER_H

#include <algorithm>
#include <iterator>
#include <locale>
#include <stdexcept>
#include <string>
#include <utility>
#include <vector>

#include <boost/algorithm/string.hpp>
#include <boost/iterator/indirect_iterator.hpp>
#include <boost/noncopyable.hpp>
#include <boost/spirit/include/qi.hpp>
#include <boost/throw_exception.hpp>
#include <boost/tokenizer.hpp>

#include "tetengo2.cpp0x.h"
#include "tetengo2.text.h"


namespace tetengo2
{
    /*!
        \brief The class template for a message catalog parser.

        \tparam InputStream An input stream type.
        \tparam String      A string type.
        \tparam Encoder     An encoder type.
    */
    template <typename InputStream, typename String, typename Encoder>
    class message_catalog_parser : private boost::noncopyable
    {
    public:
        // types

        //! The input stream type.
        typedef InputStream input_stream_type;

        //! The input string type.
        typedef
            std::basic_string<typename input_stream_type::char_type>
            input_string_type;

        //! The string type.
        typedef String string_type;

        //! The encoder type.
        typedef Encoder encoder_type;

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
        {
            m_input_stream.imbue(std::locale::classic());
        }


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
        entry_type next()
        {
            if (!has_next())
                BOOST_THROW_EXCEPTION(std::runtime_error("No next entry."));

            const typename cpp0x::unique_ptr<entry_type>::type p_entry(
                std::move(m_p_preread_entry)
            );
            m_p_preread_entry.reset();
            return *p_entry;
        }


    private:
        // types

        typedef typename input_stream_type::char_type input_char_type;

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


        // static functions

        static const encoder_type& encoder()
        {
            static const encoder_type singleton;
            return singleton;
        }


        // variables

        mutable input_stream_type& m_input_stream;

        mutable typename cpp0x::unique_ptr<entry_type>::type
        m_p_preread_entry;

        template <typename T>
        struct content_holder
        {
            content_holder(T& content)
            :
            m_content(content)
            {}

            void operator()(
                const T& content,
                boost::spirit::qi::unused_type,
                boost::spirit::qi::unused_type
            )
            const
            {
                m_content = content;
            }


        private:
            T& m_content;

        
        };


        // functions

        bool preread()
        const
        {
            if (m_p_preread_entry) return true;

            while (m_input_stream.good())
            {
                typename cpp0x::unique_ptr<entry_type>::type p_entry =
                    parse(get_line());
                if (p_entry)
                {
                    m_p_preread_entry = std::move(p_entry);
                    return true;
                }
            }

            return false;
        }

        input_string_type get_line()
        const
        {
            namespace qi = boost::spirit::qi;

            input_string_type line;
            for (;;)
            {
                input_string_type got_line;
                std::getline(m_input_stream, got_line);
                if (got_line.empty()) break;

                std::vector<input_char_type> parsed;
                if (
                    !qi::parse(
                        got_line.begin(),
                        got_line.end(),
                        (*(qi::char_ - (qi::lit('\\') >> qi::eoi)))[
                            content_holder<std::vector<input_char_type>>(
                                parsed
                            )
                        ]
                    ) ||
                    parsed.size() == got_line.length()
                )
                {
                    line.append(got_line);
                    break;
                }

                line.append(parsed.begin(), parsed.end());
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

                if (
                    position == 0 ||
                    line[position - 1] !=
                        static_cast<typename input_stream_type::char_type>(
                            TETENGO2_TEXT('\\')
                        )
                )
                {
                    line = line.substr(0, position);
                    break;
                }

                ++position;
            }
        }

        void replace_special_characters(input_string_type& line)
        const
        {
            boost::replace_all(
                line,
                input_string_type(TETENGO2_TEXT("\\#")),
                input_string_type(TETENGO2_TEXT("#"))
            );
            boost::replace_all(
                line,
                input_string_type(TETENGO2_TEXT("\\t")),
                input_string_type(TETENGO2_TEXT("\t"))
            );
            boost::replace_all(
                line,
                input_string_type(TETENGO2_TEXT("\\n")),
                input_string_type(TETENGO2_TEXT("\n"))
            );
        }

        typename cpp0x::unique_ptr<entry_type>::type parse(
            const input_string_type& line
        )
        const
        {
            const tokenizer_type tokenizer(
                line,
                separator_type(
                    input_string_type(TETENGO2_TEXT("\\")),
                    input_string_type(TETENGO2_TEXT("=")),
                    input_string_type(TETENGO2_TEXT("\"'"))
                )
            );
            std::vector<input_string_type> tokens;
            tokens.reserve(2);
            std::copy(
                tokenizer.begin(), tokenizer.end(), std::back_inserter(tokens)
            );

            if (tokens.size() < 2)
                return typename cpp0x::unique_ptr<entry_type>::type();

            return typename cpp0x::unique_ptr<entry_type>::type(
                new entry_type(
                    encoder().decode(tokens[0]), encoder().decode(tokens[1])
                )
            );
        }


    };


}

#endif
