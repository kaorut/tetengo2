/*! \file
    \brief The definition of tetengo2::text::push_parser.

    Copyright (C) 2007-2019 kaoru

    $Id$
*/

#if !defined(TETENGO2_JSON_PUSHPARSER_H)
#define TETENGO2_JSON_PUSHPARSER_H

#include <algorithm>
#include <memory>
#include <string>
#include <unordered_map>

#include <boost/core/noncopyable.hpp>
#include <boost/signals2.hpp>

#include <tetengo2/stdalt.h>
#include <tetengo2/text/grammar/grammar.h>
#include <tetengo2/type_list.h>


namespace tetengo2::text {
    /*!
        \brief The class template for a push parser.

        \tparam ForwardIterator A forward iterator type.
    */
    template <typename ForwardIterator>
    class push_parser : private boost::noncopyable
    {
    public:
        // types

        //! The iterator type.
        using iterator = ForwardIterator;

        //! The grammar type.
        using grammar_type = grammar::grammar<iterator>;

        //! The integer type.
        using integer_type = type_list::integer_type;

        //! The floating point number type.
        using float_type = type_list::float_type;

        //! The string type.
        using string_type = std::basic_string<typename iterator::value_type>;

        //! The value type.
        using value_type = tetengo2::stdalt::variant<bool, void*, integer_type, float_type, string_type>;

        //! The attribute map type.
        using attribute_map_type = std::unordered_map<string_type, value_type>;

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
            boost::signals2::signal<bool(const string_type&, const attribute_map_type&), signal_result_combiner_type>;

        //! The value signal type.
        using value_signal_type = boost::signals2::signal<bool(const value_type&), signal_result_combiner_type>;


        // constructors and destructor

        /*!
            \brief Creates a push parser.

            \param first     A first iterator to a parsed range.
            \param last      A last iterator to a parsed range.
            \param p_grammar A unique pointer to a grammer.
        */
        push_parser(iterator first, iterator last, std::unique_ptr<grammar_type> p_grammar);

        /*!
            \brief Destroys the push parser.
        */
        ~push_parser();


        // functions

        /*!
            \brief Returns the structure begin signal.

            \return The structure begin signal.
        */
        const structure_signal_type& on_structure_begin() const;

        /*!
            \brief Returns the structure begin signal.

            \return The structure begin signal.
        */
        structure_signal_type& on_structure_begin();

        /*!
            \brief Returns the structure end signal.

            \return The structure end signal.
        */
        const structure_signal_type& on_structure_end() const;

        /*!
            \brief Returns the structure end signal.

            \return The structure end signal.
        */
        structure_signal_type& on_structure_end();

        /*!
            \brief Returns the value signal.

            \return The value signal.
        */
        const value_signal_type& on_value() const;

        /*!
            \brief Returns the value signal.

            \return The value signal.
        */
        value_signal_type& on_value();

        /*!
            \brief Parses the range.

            \retval true  When the parsing is finished successfully.
            \retval false Otherwise.
        */
        bool parse() const;


    private:
        // types

        class impl;


        // variables

        const std::unique_ptr<impl> m_p_impl;
    };
}


#endif
