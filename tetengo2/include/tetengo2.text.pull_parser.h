/*! \file
    \brief The definition of tetengo2::text::pull_parser.

    Copyright (C) 2007-2013 kaoru

    $Id$
*/

#if !defined(TETENGO2_JSON_PULLPARSER_H)
#define TETENGO2_JSON_PULLPARSER_H

//#include <cassert>
//#include <memory>
//#include <stdexcept>
//#include <utility>

//#include <boost/noncopyable.hpp>
//#include <boost/throw_exception.hpp>
//#include <boost/variant.hpp>

#include "tetengo2.concurrent.channel.h"
#include "tetengo2.concurrent.consumer.h"
#include "tetengo2.concurrent.producer.h"
#include "tetengo2.utility.h"


namespace tetengo2 { namespace text
{
    /*!
        \brief The class template for a pull parser.

        \tparam PushParser A push parser type.
        \tparam Size       A size type.
    */
    template <typename PushParser, typename Size>
    class pull_parser : private boost::noncopyable
    {
    public:
        // types

        //! The push parser type.
        typedef PushParser push_parser_type;

        //! The string type.
        typedef typename push_parser_type::string_type string_type;

        //! The value type.
        typedef typename push_parser_type::value_type value_type;

        //! The attribute map type.
        typedef
            typename push_parser_type::attribute_map_type attribute_map_type;

        //! The size type.
        typedef Size size_type;

        //! The structure kind type.
        enum class structure_kind_type
        {
            begin, //!< The structure kind begin.
            end,   //!< The structure kind end.
        };

        //! The structure type.
        template <structure_kind_type Kind>
        class structure
        {
        public:
            // static functions

            /*!
                \brief Returns the kind.

                \return The kind.
            */
            static structure_kind_type kind()
            {
                return Kind;
            }


            // constructors

            /*!
                \brief Creates a structure type.

                \param name          A name.
                \param attribute_map A attribute map.
            */
            structure(string_type name, attribute_map_type attribute_map)
            :
            m_name(std::move(name)),
            m_attribute_map(std::move(attribute_map))
            {}


            // functions

            /*!
                \brief Returns the name.

                \return The name.
            */
            const string_type& name()
            const
            {
                return m_name;
            }

            /*!
                \brief Returns the attribute map.

                \return The attribute map.
            */
            const attribute_map_type& attribute_map()
            const
            {
                return m_attribute_map;
            }


        private:
            // variables

            string_type m_name;

            attribute_map_type m_attribute_map;


        };

        //! The beginning structure type.
        typedef structure<structure_kind_type::begin> structure_begin_type;

        //! The ending structure type.
        typedef structure<structure_kind_type::end> structure_end_type;

        //! The element type.
        typedef boost::variant<structure_begin_type, structure_end_type, value_type> element_type;


        // constructors and destructor

        /*!
            \brief Creates a pull parser.

            \param p_push_parser    A unique pointer to a push parser.
            \param channel_capacity A channel capacity. It must be greater than 0.

            \throw std::invalid_argument When channel_capacity is equal to 0.
        */
        pull_parser(std::unique_ptr<push_parser_type> p_push_parser, const size_type channel_capacity)
        :
        m_p_push_parser(std::move(p_push_parser)),
        m_channel(channel_capacity),
#if !defined(DOCUMENTATION) // Doxygen warning suppression
        m_producer([this](channel_type& channel) { generate(channel, *this->m_p_push_parser); }, m_channel),
#endif
        m_consumer(m_channel)
        {}


        // functions

        /*!
            \brief Returns whether the parser has a next element.

            \retval true  When the parser has a next element.
            \retval false Otherwise.
        */
        bool has_next()
        const
        {
            return !m_consumer.closed();
        }

        /*!
            \brief Peeks the next element.

            It just peeks the next element, doesn't extract the one.

            \return A next element.

            \throw std::logic_error When the parser has no more element.
        */
        const element_type& peek()
        const
        {
            if (!has_next())
                BOOST_THROW_EXCEPTION(std::logic_error("The parser has no more element."));

            return m_consumer.peek();
        }

        /*!
            \brief Removes the next element.

            \throw std::logic_error When the parser has no more element.
        */
        void next()
        {
            if (!has_next())
                BOOST_THROW_EXCEPTION(std::logic_error("The parser has no more element."));

            m_consumer.take();
        }

        /*!
            \brief Removes the next element and its children.

            \throw std::logic_error When the parser has no more element.
        */
        void skip_next()
        {
            const auto element = peek();

            if (element.which() == 1 || element.which() == 2)
            {
                next();
                return;
            }
            assert(element.which() == 0);
            const auto& structure_begin_name = boost::get<structure_begin_type>(element).name();

            next();

            while (has_next())
            {
                const auto& next_element = peek();
                if (next_element.which() == 1)
                {
                    const auto& structure_end_name = boost::get<structure_end_type>(next_element).name();
                    if (structure_end_name == structure_begin_name)
                    {
                        next();
                        return;
                    }
                }

                skip_next();
            }
        }


    private:
        // types

        typedef concurrent::channel<element_type, size_type> channel_type;

        typedef concurrent::producer<channel_type> producer_type;

        typedef concurrent::consumer<channel_type> consumer_type;


        // static functions

        static void generate(channel_type& channel, push_parser_type& push_parser)
        {
            push_parser.on_structure_begin().connect(
                [&channel](
                    const string_type&        name,
                    const attribute_map_type& attribute_map
                )
                {
                    on_structure_begin(name, attribute_map, channel);
                }
            );
            push_parser.on_structure_end().connect(
                [&channel](
                    const string_type&        name,
                    const attribute_map_type& attribute_map
                )
                {
                    suppress_unused_variable_warning(attribute_map);

                    on_structure_end(name, channel);
                }
            );
            push_parser.on_value().connect(
                [&channel](const value_type& value)
                {
                    on_value(value, channel);
                }
            );

            push_parser.parse();
        }

        static void on_structure_begin(
            const string_type&        name,
            const attribute_map_type& attribute_map,
            channel_type&             channel
        )
        {
            channel.insert(element_type(structure_begin_type(name, attribute_map)));
        }

        static void on_structure_end(const string_type& name, channel_type& channel)
        {
            channel.insert(element_type(structure_end_type(name, attribute_map_type())));
        }

        static void on_value(const value_type& value, channel_type& channel)
        {
            channel.insert(element_type(value));
        }


        // variables

        const std::unique_ptr<push_parser_type> m_p_push_parser;

        channel_type m_channel;

        producer_type m_producer;

        consumer_type m_consumer;

        
    };


}}


#endif
