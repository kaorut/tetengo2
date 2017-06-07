/*! \file
    \brief The definition of tetengo2::text::character_iterator.

    Copyright (C) 2007-2017 kaoru

    $Id$
*/

#if !defined(TETENGO2_TEXT_CHARACTERITERATOR_H)
#define TETENGO2_TEXT_CHARACTERITERATOR_H

#include <cassert>
#include <iterator>
#include <stdexcept>
#include <utility>

#include <boost/iterator/iterator_facade.hpp>
#include <boost/throw_exception.hpp>


namespace tetengo2 { namespace text
{
    /*!
        \brief The class template for a character iterator.

        Traverses the string codepoint by codepoint.

        \tparam String      A string type.
        \tparam Utf8Encoder An encoder type converting from the encoding of String to UTF-8.
    */
    template <typename String, typename Utf8Encoder>
    class character_iterator :
        public boost::iterator_facade<character_iterator<String, Utf8Encoder>, const String, std::forward_iterator_tag>
    {
    public:
        // types

        //! The string type.
        using string_type = String;

        //! The UTF-8 encoder type.
        using utf8_encoder_type = Utf8Encoder;


        // constructors and destructor

        /*!
            \brief Creates a character iterator.

            The iterator created by this constructor is used for a terminator.
        */
        character_iterator()
        :
        m_p_string(nullptr),
        m_utf8_encoder(utf8_encoder_type::internal_encoding_type{}, utf8_encoder_type::external_encoding_type{}),
        m_utf8_string(utf8_string_type{}),
        m_next_offset(0),
        m_current_character(string_type{})
        {}

        /*!
            \brief Creates a character iterator.

            \param string       A string.
            \param utf8_encoder An encoder converting from the encoding of string to UTF-8.
        */
        character_iterator(const string_type& string, utf8_encoder_type utf8_encoder)
        :
        m_p_string(&string),
        m_utf8_encoder(std::move(utf8_encoder)),
        m_utf8_string(m_utf8_encoder.encode(*m_p_string)),
        m_next_offset(0),
        m_current_character(extract_current_character(m_utf8_string, m_next_offset, m_utf8_encoder))
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
            if (m_current_character.empty() && another.m_current_character.empty())
                return true;

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
            if (!m_p_string)
                BOOST_THROW_EXCEPTION(std::logic_error("The iterator has reached the terminal."));
            if (m_next_offset >= m_utf8_string.length())
            {
                m_p_string = nullptr;
                m_utf8_string.clear();
                m_next_offset = 0;
                m_current_character.clear();
                return;
            }

            m_current_character = extract_current_character(m_utf8_string, m_next_offset, m_utf8_encoder);
        }


    private:
        // types

        using utf8_string_type = typename utf8_encoder_type::external_string_type;

        using size_type = typename string_type::size_type;

        using difference_type = typename std::iterator_traits<character_iterator>::difference_type;


        // static functions

        static string_type extract_current_character(
            const utf8_string_type&  utf8_string,
            size_type&               next_offset,
            const utf8_encoder_type& utf8_encoder
        )
        {
            const unsigned char head = static_cast<unsigned char>(utf8_string[next_offset]);
            if (head == 0x00)
                return string_type{};

            size_type byte_length = 0;
            if      ((head & 0x80) == 0x00)
            {
                byte_length = 1;
            }
            else if ((head & 0xE0) == 0xC0)
            {
                byte_length = 2;
            }
            else if ((head & 0xF0) == 0xE0)
            {
                byte_length = 3;
            }
            else
            {
                assert((head & 0xF8) == 0xF0);
                byte_length = 4;
            }

            utf8_string_type utf8_character{};
            for (size_type i = 0; i < byte_length; ++i)
            {
                assert(i == 0 || (static_cast<unsigned char>(utf8_string[next_offset + i]) & 0xC0) == 0x80);
                utf8_character.push_back(utf8_string[next_offset + i]);
            }

            next_offset += byte_length;
            return utf8_encoder.decode(utf8_character);
        }


        // variables

        const string_type* m_p_string;

        utf8_encoder_type m_utf8_encoder;

        utf8_string_type m_utf8_string;

        size_type m_next_offset;

        string_type m_current_character;


    };


    /*!
        \brief Creates a character iterator.

        The iterator created by this function is used for a terminator.

        \tparam String      A string type.
        \tparam Utf8Encoder An encoder type converting from the encoding of String to UTF-8.

        \return A character iterator.
    */
    template <typename String, typename Utf8Encoder>
    character_iterator<String, Utf8Encoder> make_character_iterator()
    {
        return character_iterator<String, Utf8Encoder>{};
    }

    /*!
        \brief Creates a character iterator.

        \tparam String      A string type.
        \tparam Utf8Encoder An encoder type converting from the encoding of String to UTF-8.

        \param string       A string.
        \param utf8_encoder An encoder converting from the encoding of string to UTF-8.

        \return A character iterator.
    */
    template <typename String, typename Utf8Encoder>
    character_iterator<String, Utf8Encoder> make_character_iterator(const String& string, Utf8Encoder utf8_encoder)
    {
        return character_iterator<String, Utf8Encoder>{ string, std::move(utf8_encoder) };
    }


}}


#endif
