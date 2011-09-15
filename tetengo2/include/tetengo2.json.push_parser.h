/*! \file
    \brief The definition of tetengo2::json::push_parser.

    Copyright (C) 2007-2011 kaoru

    $Id$
*/

#if !defined(TETENGO2_JSON_PUSHPARSER_H)
#define TETENGO2_JSON_PUSHPARSER_H

#include <utility>

#include <boost/noncopyable.hpp>


namespace tetengo2 { namespace json
{
    /*!
        \brief The class template for a push parser.

        \tparam ForwardIterator A forward iterator type.
        \tparam Grammar         A grammar type.
    */
    template <typename ForwardIterator, typename Grammar>
    class push_parser : private boost::noncopyable
    {
    public:
        // types

        //! The iterator type.
        typedef ForwardIterator iterator;

        //! The grammar type.
        typedef Grammar grammar_type;


        // constructors and destructor

        /*!
            \brief Creates a push parser.

            \tparam G A grammar type.

            \param first   A first iterator to a parsed range.
            \param last    A last iterator to a parsed range.
            \param grammar A grammer.
        */
        template <typename G>
        push_parser(const iterator first, const iterator last, G&& grammar)
        :
        m_first(first),
        m_last(last),
        m_grammer(std::forward<G>(grammar))
        {}


        // functions
        
        /*!
            \brief Parses the range.
        */
        void parse()
        const
        {

        }


    private:
        // variables

        const iterator m_first;

        const iterator m_last;

        grammar_type m_grammar;

    
    };


}}


#endif
