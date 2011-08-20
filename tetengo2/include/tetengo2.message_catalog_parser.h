/*! \file
    \brief The definition of tetengo2::message_catalog_parser.

    Copyright (C) 2007-2011 kaoru

    $Id$
*/

#if !defined(TETENGO2_MESSAGECATALOGPARSER_H)
#define TETENGO2_MESSAGECATALOGPARSER_H

#include <cassert>
#include <cstddef>
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
#include <boost/throw_exception.hpp>
#include <boost/variant.hpp>

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
            boost::fusion::vector2<
                std::vector<input_char_type>,
                std::vector<
                    boost::fusion::vector3<
                        input_char_type,
                        boost::optional<input_char_type>,
                        std::vector<input_char_type>
                    >
                >
            >
            remove_comment_parsed_content_type;

        typedef
            boost::fusion::vector2<
                std::vector<input_char_type>,
                std::vector<
                    boost::fusion::vector3<
                        input_char_type,
                        boost::optional<input_char_type>,
                        std::vector<input_char_type>
                    >
                >
            >
            parse_parsed_content_type;


        // static functions

        static const encoder_type& encoder()
        {
            static const encoder_type singleton;
            return singleton;
        }

        template <typename T>
        static content_holder<T> make_content_holder(T& content)
        {
            return content_holder<T>(content);
        }

        static input_string_type to_string(
            const remove_comment_parsed_content_type& parsed
        )
        {
            const std::vector<input_char_type>& element0 =
                boost::fusion::at_c<0>(parsed);
            input_string_type string(element0.begin(), element0.end());

            typedef
                boost::fusion::vector3<
                    input_char_type,
                    boost::optional<input_char_type>,
                    std::vector<input_char_type>
                >
                element1i_type;
            const std::vector<element1i_type>& element1 =
                boost::fusion::at_c<1>(parsed);
            for (std::size_t i = 0; i < element1.size(); ++i)
            {
                const element1i_type& element1i = element1[i];

                string.push_back(boost::fusion::at_c<0>(element1i));

                if (boost::fusion::at_c<1>(element1i))
                    string.push_back(*boost::fusion::at_c<1>(element1i));

                const std::vector<input_char_type> element1i2 =
                    boost::fusion::at_c<2>(element1i);
                string.append(element1i2.begin(), element1i2.end());
            }

            return string;
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
            using boost::spirit::qi::char_;
            using boost::spirit::qi::lit;
            using boost::spirit::qi::eoi;

            input_string_type line;
            for (;;)
            {
                input_string_type got_line;
                std::getline(m_input_stream, got_line);
                if (got_line.empty()) break;

                typename input_string_type::iterator got_line_begin =
                    got_line.begin();
                std::vector<input_char_type> parsed;
                const bool result =
                    boost::spirit::qi::parse(
                        got_line_begin,
                        got_line.end(),
                        (
                            *(
                                char_ -
                                (
                                    lit(
                                        input_char_type(TETENGO2_TEXT('\\'))
                                    ) >> eoi
                                )
                            )
                        )[make_content_holder(parsed)]
                    );
                assert(result);

                line.append(parsed.begin(), parsed.end());
                if (got_line_begin == got_line.end()) break;
            }

            remove_comment(line);

            return line;
        }

        void remove_comment(input_string_type& line)
        const
        {
            using boost::spirit::qi::char_;

            remove_comment_parsed_content_type parsed;
            const bool result =
                boost::spirit::qi::parse(
                    line.begin(),
                    line.end(),
                    (
                        *(
                            char_ -
                            input_char_type(TETENGO2_TEXT('\\')) -
                            input_char_type(TETENGO2_TEXT('#'))
                        ) >>
                        *(
                            char_(input_char_type(TETENGO2_TEXT('\\'))) >>
                            -char_(input_char_type(TETENGO2_TEXT('#'))) >>
                            *(
                                char_ -
                                input_char_type(TETENGO2_TEXT('\\')) -
                                input_char_type(TETENGO2_TEXT('#'))
                            )
                        )
                    )[make_content_holder(parsed)]
                );

            if (result)
                line = to_string(parsed);
        }

        typename cpp0x::unique_ptr<entry_type>::type parse(
            const input_string_type& line
        )
        const
        {
            using boost::spirit::qi::char_;
            using boost::spirit::qi::lit;
                
            parse_parsed_content_type parsed_key;
            boost::variant<
                parse_parsed_content_type, std::vector<input_char_type>
            > parsed_value;
            const bool result =
                boost::spirit::qi::parse(
                    line.begin(),
                    line.end(),
                    (
                        (
                            lit(input_char_type(TETENGO2_TEXT('\''))) >>
                            *(
                                char_ -
                                input_char_type(TETENGO2_TEXT('\\')) -
                                input_char_type(TETENGO2_TEXT('\''))
                            ) >>
                            *(
                                char_(input_char_type(TETENGO2_TEXT('\\'))) >>
                                -char_(
                                    input_char_type(TETENGO2_TEXT('\''))
                                ) >>
                                *(
                                    char_ -
                                    input_char_type(TETENGO2_TEXT('\\')) -
                                    input_char_type(TETENGO2_TEXT('\''))
                                )
                            ) >>
                            lit(input_char_type(TETENGO2_TEXT('\'')))
                        ) |
                        (
                            lit(input_char_type(TETENGO2_TEXT('"'))) >>
                            *(
                                char_ -
                                input_char_type(TETENGO2_TEXT('\\')) -
                                input_char_type(TETENGO2_TEXT('"'))
                            ) >>
                            *(
                                char_(input_char_type(TETENGO2_TEXT('\\'))) >>
                                -char_(input_char_type(TETENGO2_TEXT('"'))) >>
                                *(
                                    char_ -
                                    input_char_type(TETENGO2_TEXT('\\')) -
                                    input_char_type(TETENGO2_TEXT('"'))
                                )
                            ) >>
                            lit(input_char_type(TETENGO2_TEXT('"')))
                        ) |
                        (
                            *(
                                char_ -
                                input_char_type(TETENGO2_TEXT('\\')) -
                                input_char_type(TETENGO2_TEXT('='))
                            ) >>
                            *(
                                char_(input_char_type(TETENGO2_TEXT('\\'))) >>
                                -char_(input_char_type(TETENGO2_TEXT('='))) >>
                                *(
                                    char_ -
                                    input_char_type(TETENGO2_TEXT('\\')) -
                                    input_char_type(TETENGO2_TEXT('='))
                                )
                            )
                        )
                    )[make_content_holder(parsed_key)] >>
                    lit(input_char_type(TETENGO2_TEXT('='))) >>
                    (
                        (
                            lit(input_char_type(TETENGO2_TEXT('\''))) >>
                            *(
                                char_ -
                                input_char_type(TETENGO2_TEXT('\\')) -
                                input_char_type(TETENGO2_TEXT('\''))
                            ) >>
                            *(
                                char_(input_char_type(TETENGO2_TEXT('\\'))) >>
                                -char_(
                                    input_char_type(TETENGO2_TEXT('\''))
                                ) >>
                                *(
                                    char_ -
                                    input_char_type(TETENGO2_TEXT('\\')) -
                                    input_char_type(TETENGO2_TEXT('\''))
                                )
                            ) >>
                            -lit(input_char_type(TETENGO2_TEXT('\'')))
                        ) |
                        (
                            lit(input_char_type(TETENGO2_TEXT('"'))) >>
                            *(
                                char_ -
                                input_char_type(TETENGO2_TEXT('\\')) -
                                input_char_type(TETENGO2_TEXT('"'))
                            ) >>
                            *(
                                char_(input_char_type(TETENGO2_TEXT('\\'))) >>
                                -char_(input_char_type(TETENGO2_TEXT('"'))) >>
                                *(
                                    char_ -
                                    input_char_type(TETENGO2_TEXT('\\')) -
                                    input_char_type(TETENGO2_TEXT('"'))
                                )
                            ) >>
                            -lit(input_char_type(TETENGO2_TEXT('"')))
                        ) |
                        (*char_)
                    )[make_content_holder(parsed_value)]
            );
            if (!result)
                return typename cpp0x::unique_ptr<entry_type>::type();

            input_string_type key = to_string(parsed_key);
            input_string_type value;
            if (
                const parse_parsed_content_type* const p_value0 =
                    boost::get<parse_parsed_content_type>(&parsed_value)
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
            replace_special_characters(key);
            replace_special_characters(value);

            return typename cpp0x::unique_ptr<entry_type>::type(
                new entry_type(encoder().decode(key), encoder().decode(value))
            );
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


    };


}

#endif
