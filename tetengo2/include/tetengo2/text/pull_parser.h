/*! \file
    \brief The definition of tetengo2::text::pull_parser.

    Copyright (C) 2007-2018 kaoru

    $Id$
*/

#if !defined(TETENGO2_JSON_PULLPARSER_H)
#define TETENGO2_JSON_PULLPARSER_H

#include <memory>
#include <string>

#include <boost/core/noncopyable.hpp>
#include <boost/variant.hpp>

#include <tetengo2/text/push_parser.h>
#include <tetengo2/type_list.h>


namespace tetengo2 { namespace text {
    /*!
        \brief The pull parser structure kind type.
    */
    enum class structure_kind
    {
        begin, //!< The structure kind begin.
        end, //!< The structure kind end.
    };


    /*!
        \brief The pull parser structure type.

        \tparam Kind         A kind.
        \tparam String       A string type.
        \tparam AttributeMap An attribute map type.
    */
    template <structure_kind Kind, typename String, typename AttributeMap>
    class structure
    {
    public:
        // types

        //! The string type.
        using string_type = String;

        //! The attribute map type.
        using attribute_map_type = AttributeMap;


        // static functions

        /*!
            \brief Returns the kind.

            \return The kind.
        */
        static structure_kind kind();


        // constructors

        /*!
            \brief Creates a structure.

            \param name          A name.
            \param attribute_map A attribute map.
        */
        structure(string_type name, attribute_map_type attribute_map);


        // functions

        /*!
            \brief Returns the name.

            \return The name.
        */
        const string_type& name() const;

        /*!
            \brief Returns the attribute map.

            \return The attribute map.
        */
        const attribute_map_type& attribute_map() const;


    private:
        // variables

        string_type m_name;

        attribute_map_type m_attribute_map;
    };


    /*!
        \brief The class template for a pull parser.

        \tparam ForwardIterator A forward iterator type.
    */
    template <typename ForwardIterator>
    class pull_parser : private boost::noncopyable
    {
    public:
        // types

        //! The iterator type.
        using iterator = ForwardIterator;

        //! The string type.
        using string_type = std::basic_string<typename iterator::value_type>;

        //! The size type.
        using size_type = type_list::size_type;

        //! The push parser type.
        using push_parser_type = push_parser<iterator>;

        //! The value type.
        using value_type = typename push_parser_type::value_type;

        //! The attribute map type.
        using attribute_map_type = typename push_parser_type::attribute_map_type;

        //! The beginning structure type.
        using structure_begin_type = structure<structure_kind::begin, string_type, attribute_map_type>;

        //! The ending structure type.
        using structure_end_type = structure<structure_kind::end, string_type, attribute_map_type>;

        //! The element type.
        using element_type = boost::variant<structure_begin_type, structure_end_type, value_type>;


        // constructors and destructor

        /*!
            \brief Creates a pull parser.

            \param p_push_parser    A unique pointer to a push parser.
            \param channel_capacity A channel capacity. It must be greater than 0.

            \throw std::invalid_argument When channel_capacity is equal to 0.
        */
        pull_parser(std::unique_ptr<push_parser_type> p_push_parser, size_type channel_capacity);

        /*!
            \brief Destroys the pull parser.
        */
        ~pull_parser();


        // functions

        /*!
            \brief Returns whether the parser has a next element.

            \retval true  When the parser has a next element.
            \retval false Otherwise.
        */
        bool has_next() const;

        /*!
            \brief Peeks the next element.

            It just peeks the next element, doesn't extract the one.

            \return A next element.

            \throw std::logic_error When the parser has no more element.
        */
        const element_type& peek() const;

        /*!
            \brief Removes the next element.

            \throw std::logic_error When the parser has no more element.
        */
        void next();

        /*!
            \brief Removes the next element and its children.

            \throw std::logic_error When the parser has no more element.
        */
        void skip_next();


    private:
        // types

        class impl;


        // variables

        const std::unique_ptr<impl> m_p_impl;
    };


}}


#endif
