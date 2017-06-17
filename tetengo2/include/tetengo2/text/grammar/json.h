/*! \file
    \brief The definition of tetengo2::text::grammar::json.

    Copyright (C) 2007-2017 kaoru

    $Id$
*/

#if !defined(TETENGO2_TEXT_GRAMMAR_JSON_H)
#define TETENGO2_TEXT_GRAMMAR_JSON_H

#include <memory>

#include <tetengo2/text/grammar/grammar.h>


namespace tetengo2 { namespace text { namespace grammar
{
    /*!
        \brief The class template for a grammar of JSON.

        The grammar of JSON is based on RFC4627.
        http://www.ietf.org/rfc/rfc4627.txt

        \tparam ForwardIterator A forward iterator type.
    */
    template <typename ForwardIterator>
    class json : public grammar<ForwardIterator>
    {
    public:
        // types

        //! The iterator type.
        using iterator = ForwardIterator;

        //! The base type.
        using base_type = grammar<iterator>;

        //! The rule type.
        using rule_type = typename base_type::rule_type;


        // constructors and destructor

        /*!
            \brief Creates a grammar of JSON.
        */
        json();

        /*!
            \brief Destroys the grammar of JSON.
        */
        virtual ~json();


        // functions
        
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
