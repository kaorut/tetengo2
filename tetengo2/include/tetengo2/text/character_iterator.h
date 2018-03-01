/*! \file
    \brief The definition of tetengo2::text::character_iterator.

    Copyright (C) 2007-2018 kaoru

    $Id$
*/

#if !defined(TETENGO2_TEXT_CHARACTERITERATOR_H)
#define TETENGO2_TEXT_CHARACTERITERATOR_H

#include <iterator>
#include <memory>

#include <boost/iterator/iterator_facade.hpp>

#include <tetengo2/text/encoding/polymorphic.h>


namespace tetengo2 { namespace text {
    /*!
        \brief The class template for a character iterator.

        Traverses the string codepoint by codepoint.

        \tparam String A string type.
    */
    template <typename String>
    class character_iterator
    : public boost::iterator_facade<character_iterator<String>, const String, std::forward_iterator_tag>
    {
    public:
        // types

        //! The string type.
        using string_type = String;

        //! THe encoding type.
        using encoding_type = encoding::polymorphic<string_type>;


        // constructors and destructor

        /*!
            \brief Creates a character iterator.

            The iterator created by this constructor is used for a terminator.
        */
        character_iterator();

        /*!
            \brief Creates a character iterator.

            \param string   A string.
            \param encoding An encoding of string.
        */
        character_iterator(const string_type& string, encoding_type encoding);

        /*!
            \brief Copies a character iterator.

            \param another Another character iterator.
        */
        character_iterator(const character_iterator& another);

        /*!
            \brief Moves a character iterator.

            \param another Another character iterator.
        */
        character_iterator(character_iterator&& another);

        /*!
            \brief Destroys the character iterator.
        */
        ~character_iterator();


        // functions

        /*!
            \brief Dereferences the iterator.

            \return The dereferenced value.
        */
        const string_type& dereference() const;

        /*!
            \brief Checks whether the iterator is equal to another iterator.

            \param another Another iterator.

            \retval true  When the iterator is equal to another iterator.
            \retval false Otherwise.
        */
        bool equal(const character_iterator& another) const;

        /*!
            \brief Increments the iterator.
        */
        void increment();


    private:
        // types

        class impl;


        // variables

        std::shared_ptr<impl> m_p_impl;
    };


    /*!
        \brief Creates a character iterator.

        The iterator created by this function is used for a terminator.

        \tparam String      A string type.
        \tparam Utf8Encoder An encoder type converting from the encoding of String to UTF-8.

        \return A character iterator.
    */
    template <typename String>
    character_iterator<String> make_character_iterator();

    /*!
        \brief Creates a character iterator.

        \tparam String A string type.

        \param string   A string.
        \param encoding An encoding of string.

        \return A character iterator.
    */
    template <typename String>
    character_iterator<String> make_character_iterator(const String& string, encoding::polymorphic<String> encoding);


}}


#endif
