/*! \file
    \brief The definition of tetengo2::message_catalog_parser.

    Copyright (C) 2007-2011 kaoru

    $Id$
*/

#if !defined(TETENGO2_MESSAGECATALOGPARSER_H)
#define TETENGO2_MESSAGECATALOGPARSER_H

#include <cassert>
#include <cstddef>
#include <ios>
#include <iterator>
#include <locale>
#include <stdexcept>
#include <string>
#include <utility>
#include <vector>

#include <boost/algorithm/string.hpp>
#include <boost/fusion/include/all.hpp>
#include <boost/noncopyable.hpp>
#include <boost/optional.hpp>
#include <boost/spirit/include/qi.hpp>
#include <boost/spirit/include/support_multi_pass.hpp>
#include <boost/throw_exception.hpp>
#include <boost/variant.hpp>

#include "tetengo2.cpp0x.h"
#include "tetengo2.text.h"
#include "tetengo2.unique.h"


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

        typedef
            std::vector<
                boost::fusion::vector3<
                    input_char_type,
                    boost::optional<input_char_type>,
                    std::vector<input_char_type>
                >
            >
            parsed_content_latter_type;

        typedef
            boost::fusion::vector2<
                std::vector<input_char_type>, parsed_content_latter_type
            >
            parsed_content_type;


        // static functions

        static const encoder_type& encoder()
        {
            static const encoder_type singleton;
            return singleton;
        }

        template <typename ForwardIterator>
        static boost::optional<input_string_type> parse_escaped(
            ForwardIterator&      first,
            const ForwardIterator last,
            const input_char_type splitter
        )
        {
            using boost::spirit::qi::char_;

            static const input_char_type escape = TETENGO2_TEXT('\\');

            parsed_content_type parsed;
            const bool result =
                boost::spirit::qi::parse(
                    first,
                    last,
                    (
                        *(char_ - escape - splitter) >>
                        *(
                            char_(escape) >>
                            -char_(splitter) >>
                            *(char_ - escape - splitter)
                        )
                    )[make_content_holder(parsed)] >>
                    -char_(splitter)
                );

            return boost::make_optional(result, to_string(parsed));
        }
        
        template <typename ForwardIterator>
        static boost::optional<input_string_type> parse_escaped(
            const ForwardIterator& first,
            const ForwardIterator  last,
            const input_char_type  splitter
        )
        {
            ForwardIterator mutable_first = first;
            return parse_escaped(mutable_first, last, splitter);
        }

        template <typename ForwardIterator>
        static boost::optional<
            std::pair<input_string_type, input_string_type>
        >
        parse_escaped_or_quoted_key_value(
            const ForwardIterator first,
            const ForwardIterator last,
            const input_char_type splitter
        )
        {
            using boost::spirit::qi::char_;
            using boost::spirit::qi::lit;

            static const input_char_type escape = TETENGO2_TEXT('\\');
            static const input_char_type s_quot = TETENGO2_TEXT('\'');
            static const input_char_type d_quot = TETENGO2_TEXT('"');

            parsed_content_type parsed_key;
            boost::variant<
                parsed_content_type, std::vector<input_char_type>
            > parsed_value;
            const bool result =
                boost::spirit::qi::parse(
                    first,
                    last,
                    (
                        (
                            lit(s_quot) >>
                            *(char_ - escape - s_quot) >>
                            *(
                                char_(escape) >>
                                -char_(s_quot) >>
                                *(char_ - escape - s_quot)
                            ) >>
                            lit(s_quot)
                        ) |
                        (
                            lit(d_quot) >>
                            *(char_ - escape - d_quot) >>
                            *(
                                char_(escape) >>
                                -char_(d_quot) >>
                                *(char_ - escape - d_quot)
                            ) >>
                            lit(d_quot)
                        ) |
                        (
                            *(char_ - escape - splitter) >>
                            *(
                                char_(escape) >>
                                -char_(splitter) >>
                                *(char_ - escape - splitter)
                            )
                        )
                    )[make_content_holder(parsed_key)] >>
                    lit(splitter) >>
                    (
                        (
                            lit(s_quot) >>
                            *(char_ - escape - s_quot) >>
                            *(
                                char_(escape) >>
                                -char_(s_quot) >>
                                *(char_ - escape - s_quot)
                            ) >>
                            -lit(s_quot)
                        ) |
                        (
                            lit(d_quot) >>
                            *(char_ - escape - d_quot) >>
                            *(
                                char_(escape) >>
                                -char_(d_quot) >>
                                *(char_ - escape - d_quot)
                            ) >>
                            -lit(d_quot)
                        ) |
                        (*char_)
                    )[make_content_holder(parsed_value)]
            );

            if (!result)
            {
                return boost::none;
            }

            input_string_type value;
            if (
                const parsed_content_type* const p_value0 =
                    boost::get<parsed_content_type>(&parsed_value)
            )
            {
                value = to_string(*p_value0);
            }
            else
            {
                const std::vector<input_char_type>* const p_value1 =
                    boost::get<std::vector<input_char_type>>(&parsed_value);
                assert(p_value1);
                value.assign(p_value1->begin(), p_value1->end());
            }
            return boost::make_optional(
                std::make_pair(to_string(parsed_key), value)
            );
        }
        
        template <typename T>
        static content_holder<T> make_content_holder(T& content)
        {
            return content_holder<T>(content);
        }

        static input_string_type to_string(const parsed_content_type& parsed)
        {
            const std::vector<input_char_type>& element0 =
                boost::fusion::at_c<0>(parsed);
            input_string_type string(element0.begin(), element0.end());

            const parsed_content_latter_type& element1 =
                boost::fusion::at_c<1>(parsed);
            for (std::size_t i = 0; i < element1.size(); ++i)
            {
                const typename parsed_content_latter_type::value_type&
                element1i = element1[i];

                string.push_back(boost::fusion::at_c<0>(element1i));

                if (boost::fusion::at_c<1>(element1i))
                    string.push_back(*boost::fusion::at_c<1>(element1i));

                const std::vector<input_char_type> element1i2 =
                    boost::fusion::at_c<2>(element1i);
                string.append(element1i2.begin(), element1i2.end());
            }

            return string;
        }

        static void replace_special_characters(input_string_type& line)
        {
            boost::replace_all(
                line,
                input_string_type(TETENGO2_TEXT("\\#")),
                input_string_type(TETENGO2_TEXT("#"))
            );
            boost::replace_all(
                line,
                input_string_type(TETENGO2_TEXT("\\=")),
                input_string_type(TETENGO2_TEXT("="))
            );
            boost::replace_all(
                line,
                input_string_type(TETENGO2_TEXT("\\'")),
                input_string_type(TETENGO2_TEXT("'"))
            );
            boost::replace_all(
                line,
                input_string_type(TETENGO2_TEXT("\\\"")),
                input_string_type(TETENGO2_TEXT("\""))
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


        // variables

        mutable input_stream_type& m_input_stream;

        mutable typename cpp0x::unique_ptr<entry_type>::type
        m_p_preread_entry;


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
            input_string_type line;

            typedef
                boost::spirit::multi_pass<
                    std::istreambuf_iterator<input_char_type>
                >
                input_stream_iterator_type;
            input_stream_iterator_type first =
                boost::spirit::make_default_multi_pass(
                    std::istreambuf_iterator<input_char_type>(m_input_stream)
                );
            const input_stream_iterator_type last =
                boost::spirit::make_default_multi_pass(
                    std::istreambuf_iterator<input_char_type>()
                );
            for(;;)
            {
                if (first == last)
                {
                    m_input_stream.setstate(std::ios_base::eofbit);
                    break;
                }

                const boost::optional<input_string_type> parsed =
                    parse_escaped(first, last, TETENGO2_TEXT('\n'));
                assert(parsed);

                if (!parsed->empty())
                {
                    line = *parsed;
                    break;
                }
            }

            boost::replace_all(
                line,
                input_string_type(TETENGO2_TEXT("\\\n")),
                input_string_type()
            );
            remove_comment(line);

            return line;
        }

        void remove_comment(input_string_type& line)
        const
        {
            const boost::optional<input_string_type> parsed =
                parse_escaped(line.begin(), line.end(), TETENGO2_TEXT('#'));
            if (parsed)
                line = *parsed;
        }

        typename cpp0x::unique_ptr<entry_type>::type parse(
            const input_string_type& line
        )
        const
        {
            boost::optional<
                std::pair<input_string_type, input_string_type>
            > parsed =
                parse_escaped_or_quoted_key_value(
                    line.begin(), line.end(), TETENGO2_TEXT('=')
                );
            if (!parsed)
                return typename cpp0x::unique_ptr<entry_type>::type();

            replace_special_characters(parsed->first);
            replace_special_characters(parsed->second);

            return make_unique<entry_type>(
                encoder().decode(parsed->first),
                encoder().decode(parsed->second)
            );
        }


    };


}

#endif
