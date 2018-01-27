/*! \file
    \brief The definition of tetengo2::text::character_iterator.

    Copyright (C) 2007-2018 kaoru

    $Id$
*/

#include <cassert>
#include <iterator>
#include <memory>
#include <stdexcept>
#include <string>

#include <boost/throw_exception.hpp>

#include <tetengo2/text/character_iterator.h>
#include <tetengo2/text/encoder.h>
#include <tetengo2/text/encoding/polymorphic.h>
#include <tetengo2/text/encoding/utf8.h>


namespace tetengo2 { namespace text
{
    template <typename String>
    class character_iterator<String>::impl
    {
    public:
        // types

        using string_type = typename character_iterator<String>::string_type;

        using encoding_type = typename character_iterator<String>::encoding_type;


        // constructors and destructor

        impl()
        :
        m_p_string(nullptr),
        m_utf8_encoder(encoding_type{}, encoding::utf8{}),
        m_utf8_string(utf8_string_type{}),
        m_next_offset(0),
        m_current_character(string_type{})
        {}

        impl(const string_type& string, encoding_type encoding)
        :
        m_p_string(&string),
        m_utf8_encoder(encoding, encoding::utf8{}),
        m_utf8_string(m_utf8_encoder.encode(*m_p_string)),
        m_next_offset(0),
        m_current_character(extract_current_character(m_utf8_string, m_next_offset, m_utf8_encoder))
        {}


        // functions

        const string_type& dereference()
        const
        {
            return m_current_character;
        }

        bool equal(const character_iterator& another)
        const
        {
            if (m_current_character.empty() && another.m_p_impl->m_current_character.empty())
                return true;

            return
                m_p_string == another.m_p_impl->m_p_string &&
                m_current_character == another.m_p_impl->m_current_character &&
                m_next_offset == another.m_p_impl->m_next_offset;
        }

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

        using utf8_encoder_type = encoder<encoding_type, encoding::utf8>;

        using utf8_string_type = typename utf8_encoder_type::external_string_type;

        using size_type = typename string_type::size_type;

        using difference_type = typename std::iterator_traits<character_iterator<string_type>>::difference_type;


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


    template <typename String>
    character_iterator<String>::character_iterator()
    :
    m_p_impl(std::make_shared<impl>())
    {}

    template <typename String>
    character_iterator<String>::character_iterator(const string_type& string, encoding_type encoding)
    :
    m_p_impl(std::make_shared<impl>(string, std::move(encoding)))
    {}

    template <typename String>
    character_iterator<String>::character_iterator(const character_iterator& another)
    :
    m_p_impl(std::make_shared<impl>(*another.m_p_impl))
    {}

    template <typename String>
    character_iterator<String>::character_iterator(character_iterator&& another)
    :
    m_p_impl(std::make_shared<impl>(std::move(*another.m_p_impl)))
    {}

    template <typename String>
    character_iterator<String>::~character_iterator()
    = default;

    template <typename String>
    const typename character_iterator<String>::string_type& character_iterator<String>::dereference()
    const
    {
        return m_p_impl->dereference();
    }

    template <typename String>
    bool character_iterator<String>::equal(const character_iterator& another)
    const
    {
        return m_p_impl->equal(another);
    }

    template <typename String>
    void character_iterator<String>::increment()
    {
        m_p_impl->increment();
    }


    template <typename String>
    character_iterator<String> make_character_iterator()
    {
        return character_iterator<String>{};
    }

    template <typename String>
    character_iterator<String> make_character_iterator(const String& string, encoding::polymorphic<String> encoding)
    {
        return character_iterator<String>{ string, std::move(encoding) };
    }


    template class character_iterator<std::string>;

    template class character_iterator<std::wstring>;

    template character_iterator<std::string> make_character_iterator();

    template character_iterator<std::wstring> make_character_iterator();

    template character_iterator<std::string> make_character_iterator(
        const std::string&                 string,
        encoding::polymorphic<std::string> encoding
    );

    template character_iterator<std::wstring> make_character_iterator(
        const std::wstring&                 string,
        encoding::polymorphic<std::wstring> encoding
    );


}}
