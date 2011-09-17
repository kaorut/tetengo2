/*! \file
    \brief The definition of tetengo2::json::push_parser.

    Copyright (C) 2007-2011 kaoru

    $Id$
*/

#if !defined(TETENGO2_JSON_PUSHPARSER_H)
#define TETENGO2_JSON_PUSHPARSER_H

#include <memory>
#include <string>

#include <boost/noncopyable.hpp>
#include <boost/signals2.hpp>
#include <boost/variant.hpp>


namespace tetengo2 { namespace json
{
    /*!
        \brief The class template for a push parser.

        \tparam ForwardIterator A forward iterator type.
        \tparam Grammar         A grammar type.
        \tparam Integer         An integer type.
        \tparam Float           A floating point number type.
    */
    template <
        typename ForwardIterator,
        typename Grammar,
        typename Integer,
        typename Float
    >
    class push_parser : private boost::noncopyable
    {
    public:
        // types

        //! The iterator type.
        typedef ForwardIterator iterator;

        //! The grammar type.
        typedef Grammar grammar_type;

        //! The integer type.
        typedef Integer integer_type;

        //! The floating point number type.
        typedef Float float_type;

        //! The structure type.
        enum structure_type
        {
            structure_object_begin, //!< An object begin.
            structure_object_end,   //!< An object end.
            structure_member_begin, //!< A member begin.
            structure_member_end,   //!< A member end.
            structure_array_begin,  //!< An array begin.
            structure_array_end,    //!< An array end.
            structure_value,        //!< A value.
        };

        //! The string type.
        typedef std::basic_string<typename iterator::value_type> string_type;

        //! The value type.
        typedef
            boost::variant<bool, void*, integer_type, float_type, string_type>
            value_type;

        //! The signal type.
        typedef
            boost::signals2::signal<void (structure_type, const value_type&)>
            signal_type;


        // constructors and destructor

        /*!
            \brief Creates a push parser.

            \param first     A first iterator to a parsed range.
            \param last      A last iterator to a parsed range.
            \param p_grammar A unique pointer to a grammer.
        */
        push_parser(
            const iterator                first,
            const iterator                last,
            std::unique_ptr<grammar_type> p_grammar
        )
        :
        m_first(first),
        m_last(last),
        m_p_grammar(std::move(p_grammar))
        {}


        // functions
        
        /*!
            \brief Returns the signal.
            
            \return The signal.
        */
        const signal_type& structure_passed()
        const
        {
            return m_signal;
        }

        /*!
            \brief Returns the signal.
            
            \return The signal.
        */
        signal_type& structure_passed()
        {
            return m_signal;
        }

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

        const std::unique_ptr<grammar_type> m_p_grammar;

        signal_type m_signal;

    
    };


}}


#endif
