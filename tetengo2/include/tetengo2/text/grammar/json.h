/*! \file
    \brief The definition of tetengo2::text::grammar::json.

    Copyright (C) 2007-2015 kaoru

    $Id$
*/

#if !defined(TETENGO2_TEXT_GRAMMAR_JSON_H)
#define TETENGO2_TEXT_GRAMMAR_JSON_H

#include <algorithm>
#include <memory>
#include <string>
#include <vector>

#include <boost/signals2.hpp>
#include <boost/spirit/include/qi.hpp>

#include <tetengo2/stdalt.h>


namespace tetengo2 { namespace text { namespace grammar
{
    /*!
        \brief The class template for a grammar of JSON.

        The grammar of JSON is based on RFC4627.
        http://www.ietf.org/rfc/rfc4627.txt

        \tparam ForwardIterator A forward iterator type.
    */
    template <typename ForwardIterator>
    class json :
        public boost::spirit::qi::grammar<ForwardIterator, std::basic_string<typename ForwardIterator::value_type> ()>
    {
    public:
        // types

        //! The iterator type.
        using iterator = ForwardIterator;

        //! The character type.
        using char_type = typename iterator::value_type;

        //! The string type.
        using string_type = std::basic_string<char_type>;

        //! The value type type.
        enum class value_type_type
        {
            string,  //!< A string.
            number,  //!< A number.
            boolean, //!< A boolean.
            null,    //!< A null.
        };

        //! The structure attribute type.
        class structure_attribute_type
        {
        public:
            /*!
                \brief Creates a structure attribute.

                \param name       A name.
                \param value_type A value type.
                \param attribute  An attribute.
            */
            structure_attribute_type(string_type name, const value_type_type value_type, const string_type& attribute);

            /*!
                \brief Returns the name.

                \return The name.
            */
            const string_type& name()
            const;

            /*!
                \brief Returns the value type.

                \return The value type.
            */
            value_type_type value_type()
            const;

            /*!
                \brief Returns the attribute.

                \return The attribute.
            */
            const string_type& attribute()
            const;

        private:
            string_type m_name;

            value_type_type m_value_type;

            const string_type& m_attribute;

        };

        //! The signal result combiner type.
        struct signal_result_combiner_type
        {
            //! The result type.
            using result_type = bool;

            /*!
                \brief Combines the results.

                \param first The first position of result.
                \param last  The last position of result.

                \return The combined result.
            */
            template <typename InputIterator>
            bool operator()(InputIterator first, InputIterator last)
            {
                return std::all_of(first, last, [](bool b) { return b; });
            }

        };

        //! The structure signal type.
        using structure_signal_type =
            boost::signals2::signal<
                bool (const std::string&, const std::vector<structure_attribute_type>&), signal_result_combiner_type
            >;

        //! The value signal type.
        using value_signal_type =
            boost::signals2::signal<bool (value_type_type, const string_type&), signal_result_combiner_type>;

        //! The rule type.
        using rule_type = boost::spirit::qi::rule<iterator, string_type ()>;


        // constructors and destructor

        /*!
            \brief Creates a grammar of JSON.
        */
        json();

        /*!
            \brief Destroys the grammar of JSON.
        */
        ~json()
        TETENGO2_STDALT_NOEXCEPT;


        // functions
        
        /*!
            \brief Returns the structure begin signal.

            The signal is called when the parser parses the beginning tokens of an object, a member and an array
            structure.

            \return The structure signal.
        */
        const structure_signal_type& on_structure_begin()
        const;

        /*!
            \brief Returns the structure begin signal.

            The signal is called when the parser parses the beginning tokens of an object, a member and an array
            structure.

            \return The structure signal.
        */
        structure_signal_type& on_structure_begin();

        /*!
            \brief Returns the structure end signal.

            The signal is called when the parser parses the ending tokens of an object, a member and an array
            structure.

            \return The structure signal.
        */
        const structure_signal_type& on_structure_end()
        const;

        /*!
            \brief Returns the structure end signal.

            The signal is called when the parser parses the ending tokens of an object, a member and an array
            structure.

            \return The structure signal.
        */
        structure_signal_type& on_structure_end();

        /*!
            \brief Returns the value signal.

            The signal is called when the parser parses a value.

            \return The value signal.
        */
        const value_signal_type& on_value()
        const;

        /*!
            \brief Returns the value signal.

            The signal is called when the parser parses a value.

            \return The value signal.
        */
        value_signal_type& on_value();

        /*!
            \brief Returns the parser for a JSON text.

            \return The parser for a JSON text.
        */
        const rule_type& json_text()
        const;

        /*!
            \brief Returns the parser for a value.

            \return The parser for a value.
        */
        const rule_type& value()
        const;

        /*!
            \brief Returns the parser for an object.

            \return The parser for an object.
        */
        const rule_type& object()
        const;

        /*!
            \brief Returns the parser for a member.

            \return The parser for a member.
        */
        const rule_type& member()
        const;

        /*!
            \brief Returns the parser for an array.

            \return The parser for an array.
        */
        const rule_type& array()
        const;

        /*!
            \brief Returns the parser for a number.

            \return The parser for a number.
        */
        const rule_type& number()
        const;

        /*!
            \brief Returns the parser for a string.

            \return The parser for a string.
        */
        const rule_type& string()
        const;


    private:
        // types

        class impl;


        // variables

        rule_type m_json_text;

        const std::unique_ptr<impl> m_p_impl;


    };


}}}


#endif
