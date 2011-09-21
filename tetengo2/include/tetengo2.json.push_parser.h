/*! \file
    \brief The definition of tetengo2::json::push_parser.

    Copyright (C) 2007-2011 kaoru

    $Id$
*/

#if !defined(TETENGO2_JSON_PUSHPARSER_H)
#define TETENGO2_JSON_PUSHPARSER_H

#include <cmath>
#include <memory>
#include <stdexcept>
#include <string>

#include <boost/lexical_cast.hpp>
#include <boost/noncopyable.hpp>
#include <boost/optional.hpp>
#include <boost/signals2.hpp>
#include <boost/spirit/include/qi.hpp>
#include <boost/utility.hpp>
#include <boost/variant.hpp>

#include "tetengo2.cpp11.h"
#include "tetengo2.text.h"


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
            boost::signals2::signal<
                void (structure_type, const boost::optional<value_type>&)
            >
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
        {
            if (!m_p_grammar)
                throw std::invalid_argument("The grammar is NULL.");

            m_p_grammar->structure_passed().connect(
                TETENGO2_CPP11_BIND(
                    &push_parser::observe_structure,
                    this,
                    cpp11::placeholders_1()
                )
            );
            m_p_grammar->value_passed().connect(
                TETENGO2_CPP11_BIND(
                    &push_parser::observe_value,
                    this,
                    cpp11::placeholders_1(),
                    cpp11::placeholders_2()
                )
            );
        }


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

            \retval true  When the parsing is finished successfully.
            \retval false Otherwise.
        */
        bool parse()
        const
        {
            iterator first = m_first;
            const bool result =
                boost::spirit::qi::parse(first, m_last, *m_p_grammar);
            return result && first == m_last;
        }


    private:
        // static functions

        structure_type to_structure(
            typename grammar_type::structure_type_type grammar_structure_type
        )
        {
            switch(grammar_structure_type)
            {
            case grammar_type::structure_type_object_begin:
                return structure_object_begin;
            case grammar_type::structure_type_object_end:
                return structure_object_end;
            case grammar_type::structure_type_member_begin:
                return structure_member_begin;
            case grammar_type::structure_type_member_end:
                return structure_member_end;
            case grammar_type::structure_type_array_begin:
                return structure_array_begin;
            case grammar_type::structure_type_array_end:
                return structure_array_end;
            default:
                assert(false);
                throw std::logic_error("Must not come here.");
            }
        }

        value_type to_value(
            const typename grammar_type::value_type_type value_type,
            const string_type&                           string_value
        )
        {
            switch (value_type)
            {
            case grammar_type::value_type_string:
                return to_string(string_value);
            case grammar_type::value_type_number:
                return to_number(string_value);
            case grammar_type::value_type_boolean:
                return to_boolean(string_value);
            case grammar_type::value_type_null:
                return to_null(string_value);
            default:
                assert(false);
                throw std::logic_error("Must not come here.");
            }
        }

        string_type to_string(const string_type& string_value)
        {
            assert(string_value.length() >= 2);

            return string_type(
                boost::next(string_value.begin()),
                boost::prior(string_value.end())
            );
        }

        value_type to_number(const string_type& string_value)
        {
            const typename string_type::size_type exp_index =
                string_value.find_first_of("eE");
            if (exp_index != string_type::npos)
                return to_number_exp(string_value, exp_index);

            const typename string_type::size_type fp_index =
                string_value.find('.');
            if (fp_index != string_type::npos)
                return to_number_impl<float_type>(string_value);

            return to_number_impl<integer_type>(string_value);
        }

        template <typename T>
        boost::variant<T> to_number_impl(const string_type& string_value)
        {
            try
            {
                return boost::lexical_cast<T>(string_value);
            }
            catch (const boost::bad_lexical_cast&)
            {
                return boost::variant<T>(0);
            }
        }

        boost::variant<float_type> to_number_exp(
            const string_type&                    string_value,
            const typename string_type::size_type exp_index
        )
        {
            try
            {
                const float_type fraction =
                    boost::lexical_cast<float_type>(
                        string_value.substr(0, exp_index)
                    );
                const float_type exp =
                    boost::lexical_cast<float_type>(
                        string_value.substr(exp_index + 1)
                    );
                return fraction * std::pow(10.0, exp);
            }
            catch (const boost::bad_lexical_cast&)
            {
                return boost::variant<float_type>(0);
            }
        }

        bool to_boolean(const string_type& string_value)
        {
            assert(
                string_value == string_type(TETENGO2_TEXT("true")) ||
                string_value == string_type(TETENGO2_TEXT("false"))
            );

            return string_value == string_type(TETENGO2_TEXT("true"));
        }

        void* to_null(const string_type& string_value)
        {
            assert(string_value == string_type(TETENGO2_TEXT("null")));

            return NULL;
        }


        // variables

        const iterator m_first;

        const iterator m_last;

        const std::unique_ptr<grammar_type> m_p_grammar;

        signal_type m_signal;


        // functions

        void observe_structure(
            const typename grammar_type::structure_type_type structure_type
        )
        {
            m_signal(to_structure(structure_type), boost::none);
        }

        void observe_value(
            const typename grammar_type::value_type_type value_type,
            const string_type&                           value
        )
        {
            m_signal(
                structure_value,
                boost::make_optional(to_value(value_type, value))
            );
        }


    };


}}


#endif
