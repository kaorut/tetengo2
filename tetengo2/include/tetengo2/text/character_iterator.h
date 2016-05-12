/*! \file
    \brief The definition of tetengo2::text::character_iterator.

    Copyright (C) 2007-2016 kaoru

    $Id$
*/

#if !defined(TETENGO2_TEXT_CHARACTERITERATOR_H)
#define TETENGO2_TEXT_CHARACTERITERATOR_H

#include <iterator>

#include <boost/iterator/iterator_facade.hpp>


namespace tetengo2 { namespace text
{
    /*!
        \brief The class template for a character iterator.

        \tparam String A string type.
    */
    template <typename String>
    class character_iterator :
        public boost::iterator_facade<character_iterator<String>, String, std::forward_iterator_tag>
    {
    public:
        // types

        //! The string type.
        using string_type = String;


        // constructors and destructor

        /*!
            \brief Creates a character iterator.

            \param string A string.
        */
        explicit character_iterator(const string_type& string)
        :
        m_p_string(&string),
        m_current_character(),
        m_next_offset(0)
        {}


        // functions

        /*!
            \brief Dereferences the iterator.

            \return The dereferenced value.
        */
        const string_type& dereference()
        const
        {
            return m_current_character;
        }

        /*!
            \brief Checks whether the iterator is equal to another iterator.

            \param another Another iterator.

            \retval true  When the iterator is equal to another iterator.
            \retval false Otherwise.
        */
        bool equal(const character_iterator& another)
        const
        {
            return
                m_p_string == another.m_p_string &&
                m_current_character == another.m_current_character &&
                m_next_offset == another.m_next_offset;
        }

        /*!
            \brief Increments the iterator.
        */
        void increment()
        {

        }


    private:
        // types

        using size_type = typename string_type::size_type;

        using difference_type = typename std::iterator_traits<character_iterator>::difference_type;


        // variables

        const string_type* m_p_string;

        string_type m_current_character;

        size_type m_next_offset;


    };


    /*!
        \brief Creates a character  iterator.

        \tparam String A string type.

        \param string A string.

        \return A character iterator.
    */
    template <typename String>
    character_iterator<String> make_character_iterator(const String& string)
    {
        return character_iterator<String>{ string };
    }


}}


#endif
