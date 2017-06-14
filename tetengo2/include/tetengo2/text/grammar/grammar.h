/*! \file
    \brief The definition of tetengo2::text::grammar::grammar.

    Copyright (C) 2007-2017 kaoru

    $Id$
*/

#if !defined(TETENGO2_TEXT_GRAMMAR_GRAMMAR_H)
#define TETENGO2_TEXT_GRAMMAR_GRAMMAR_H

#include <memory>
#include <string>

#include <boost/spirit/include/qi.hpp>


namespace tetengo2 { namespace text { namespace grammar
{
    /*!
        \brief The class template for a grammar.

        \tparam ForwardIterator A forward iterator type.
    */
    template <typename ForwardIterator>
    class grammar :
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

        //! The rule type.
        using rule_type = boost::spirit::qi::rule<iterator, string_type ()>;


        // constructors and destructor

        /*!
            \brief Destroys the grammar.
        */
        virtual ~grammar();


    protected:
        // constructors

        /*!
            \brief Creates a grammar.
        */
        grammar();


        // functions

        /*!
            \brief Returns the root rule.

            \return The root rule.
        */
        const rule_type& root_rule()
        const;

        /*!
            \brief Returns the root rule.

            \return The root rule.
        */
        rule_type& root_rule();


    private:
        // typess

        class impl;


        // variables

        rule_type m_root_rule;

        const std::unique_ptr<impl> m_p_impl;


    };


}}}


#endif
