/*! \file
    \brief The definition of tetengo2::message::message_catalog_parser.

    Copyright (C) 2007-2012 kaoru

    $Id$
*/

#if !defined(TETENGO2_MESSAGE_MESSAGECATALOGPARSER_H)
#define TETENGO2_MESSAGE_MESSAGECATALOGPARSER_H

#include <cassert>
#include <cstddef>
//#include <memory>
#include <stdexcept>
//#include <utility>

#include <boost/noncopyable.hpp>
#include <boost/optional.hpp>
#include <boost/throw_exception.hpp>
#include <boost/variant.hpp>

#include "tetengo2.text.h"
#include "tetengo2.unique.h"


namespace tetengo2 { namespace message
{
    /*!
        \brief The class template for a message catalog parser.

        \tparam PullParser A pull parser type.
        \tparam String     A string type.
        \tparam Encoder    An encoder type.
    */
    template <typename PullParser, typename String, typename Encoder>
    class message_catalog_parser : private boost::noncopyable
    {
    public:
        // types

        //! The pull parser type.
        typedef PullParser pull_parser_type;

        //! The input string type.
        typedef typename pull_parser_type::string_type input_string_type;

        //! The string type.
        typedef String string_type;

        //! The encoder type.
        typedef Encoder encoder_type;

        //! The entry type.
        typedef std::pair<string_type, string_type> entry_type;


        // constructors and destructor

        /*!
            \brief Creates a message catalog parser.

            \param p_pull_parser A unique pointer to a pull parser.
        */
        explicit message_catalog_parser(std::unique_ptr<pull_parser_type> p_pull_parser)
        :
        m_p_pull_parser(std::move(p_pull_parser)),
        m_p_preread_entry(),
        m_preamble_read_succeeded()
        {}


        // functions

        /*!
            \brief Checks whether a next entry exists.

            \retval true  A next entry exists.
            \retval false Otherwise.
        */
        bool has_next()
        const
        {
            return preread();
        }

        /*!
            \brief Peeks the next entry.

            \return The next entry.

            \throw std::logic_error No next entry exists.
        */
        const entry_type& peek()
        const
        {
            if (!has_next())
                BOOST_THROW_EXCEPTION(std::logic_error("No next entry."));

            return *m_p_preread_entry;
        }

        /*!
            \brief Removes the next entry.

            \throw std::logic_error No next entry exists.
        */
        void next()
        {
            if (!has_next())
                BOOST_THROW_EXCEPTION(std::logic_error("No next entry."));

            m_p_preread_entry.reset();
        }


    private:
        // types

        typedef typename pull_parser_type::attribute_map_type attribute_map_type;

        typedef typename pull_parser_type::element_type element_type;

        typedef typename pull_parser_type::structure_begin_type structure_begin_type;

        typedef typename pull_parser_type::structure_end_type structure_end_type;

        typedef typename pull_parser_type::value_type value_type;


        // static functions

        static const encoder_type& encoder()
        {
            static const encoder_type singleton;
            return singleton;
        }


        // variables

        std::unique_ptr<pull_parser_type> m_p_pull_parser;

        mutable std::unique_ptr<entry_type> m_p_preread_entry;

        mutable boost::optional<bool> m_preamble_read_succeeded;


        // functions

        bool preread()
        const
        {
            if (m_p_preread_entry) return true;

            if (!m_preamble_read_succeeded)
                skip_preamble();
            assert(m_preamble_read_succeeded);
            if (!*m_preamble_read_succeeded)
                return false;

            m_p_preread_entry = next_entry();
            if (!m_p_preread_entry)
                return false;

            return true;
        }

        void skip_preamble()
        const
        {
            if (!next_is<structure_begin_type>(input_string_type(TETENGO2_TEXT("object"))))
            {
                m_preamble_read_succeeded = boost::make_optional(false);
                return;
            }
            m_p_pull_parser->next();

            if (
                next_is<structure_begin_type>(
                    input_string_type(TETENGO2_TEXT("member")), input_string_type(TETENGO2_TEXT("header"))
                )
            )
            {
                m_p_pull_parser->skip_next();
            }

            if (
                !next_is<structure_begin_type>(
                    input_string_type(TETENGO2_TEXT("member")), input_string_type(TETENGO2_TEXT("body"))
                )
            )
            {
                m_preamble_read_succeeded = boost::make_optional(false);
                return;
            }
            m_p_pull_parser->next();

            if (!next_is<structure_begin_type>(input_string_type(TETENGO2_TEXT("object"))))
            {
                m_preamble_read_succeeded = boost::make_optional(false);
                return;
            }
            m_p_pull_parser->next();

            m_preamble_read_succeeded = boost::make_optional(true);
            return;
        }

        std::unique_ptr<entry_type> next_entry()
        const
        {
            input_string_type key;
            input_string_type value;

            {
                if (!m_p_pull_parser->has_next())
                    return std::unique_ptr<entry_type>();
                const element_type& element = m_p_pull_parser->peek();
                if (element.which() != 0)
                    return std::unique_ptr<entry_type>();

                const structure_begin_type& structure = boost::get<structure_begin_type>(element);
                key = get_attribute(structure);
                if (key.empty())
                    return std::unique_ptr<entry_type>();

                m_p_pull_parser->next();
            }
            {
                if (!m_p_pull_parser->has_next())
                    return std::unique_ptr<entry_type>();
                const element_type& element = m_p_pull_parser->peek();
                if (element.which() != 2)
                    return std::unique_ptr<entry_type>();

                const value_type& parsed_value = boost::get<value_type>(element);
                if (parsed_value.which() != 4)
                    return std::unique_ptr<entry_type>();

                value = boost::get<input_string_type>(parsed_value);

                m_p_pull_parser->next();
            }
            {
                if (!m_p_pull_parser->has_next())
                    return std::unique_ptr<entry_type>();
                const element_type& element = m_p_pull_parser->peek();
                if (element.which() != 1)
                    return std::unique_ptr<entry_type>();

                m_p_pull_parser->next();
            }

            return make_unique<entry_type>(
                encoder().decode(key), encoder().decode(value)
            );
        }

        template <typename Structure>
        bool next_is(const input_string_type& name, const input_string_type& attribute = input_string_type())
        const
        {
            if (!m_p_pull_parser->has_next())
                return false;

            const element_type& element = m_p_pull_parser->peek();
            if (!is_structure(element, static_cast<const Structure*>(NULL)))
                return false;

            const Structure structure = boost::get<Structure>(element);
            if (structure.name() != name)
                return false;
            if (!attribute.empty())
            {
                if (get_attribute(structure) != attribute)
                    return false;
            }

            return true;
        }

        bool is_structure(const element_type& element, const structure_begin_type* const)
        const
        {
            return element.which() == 0;
        }

        bool is_structure(const element_type& element, const structure_end_type* const)
        const
        {
            return element.which() == 1;
        }

        input_string_type get_attribute(const structure_begin_type& structure)
        const
        {
            const typename attribute_map_type::const_iterator found =
                structure.attribute_map().find(input_string_type(TETENGO2_TEXT("name")));
            if (found == structure.attribute_map().end())
                return input_string_type();
            if (found->second.which() != 4)
                return input_string_type();
            
            return boost::get<input_string_type>(found->second);
        }


    };


}}


#endif
