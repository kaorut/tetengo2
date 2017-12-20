/*! \file
    \brief The definition of tetengo2::message::message_catalog_parser.

    Copyright (C) 2007-2017 kaoru

    $Id$
*/

#if !defined(TETENGO2_MESSAGE_MESSAGECATALOGPARSER_H)
#define TETENGO2_MESSAGE_MESSAGECATALOGPARSER_H

#include <memory>
#include <string>
#include <utility>

#include <boost/core/noncopyable.hpp>

#include <tetengo2/text/encoding/polymorphic.h>
#include <tetengo2/text/pull_parser.h>
#include <tetengo2/type_list.h>


namespace tetengo2 { namespace message
{
    /*!
        \brief The class template for a message catalog parser.

        \tparam ForwardIterator A forward iterator type.
    */
    template <typename ForwardIterator>
    class message_catalog_parser : private boost::noncopyable
    {
    public:
        // types

        //! The iterator type.
        using iterator = ForwardIterator;

        //! THe input string type.
        using input_string_type = std::basic_string<typename iterator::value_type>;

        //! The input encoding type.
        using input_encoding_type = text::encoding::polymorphic<input_string_type>;

        //! The pull parser type.
        using pull_parser_type = text::pull_parser<iterator>;

        //! The string type.
        using string_type = type_list::string_type;

        //! The entry type.
        using entry_type = std::pair<string_type, string_type>;


        // constructors and destructor

        /*!
            \brief Creates a message catalog parser.

            \param p_pull_parser  A unique pointer to a pull parser.
            \param input_encoding An input encoding.
        */
        message_catalog_parser(std::unique_ptr<pull_parser_type> p_pull_parser, input_encoding_type input_encoding);

        /*!
            \brief Destroys the message catalog parser.
        */
        ~message_catalog_parser();


        // functions

        /*!
            \brief Checks whether a next entry exists.

            \retval true  A next entry exists.
            \retval false Otherwise.
        */
        bool has_next()
        const;

        /*!
            \brief Peeks the next entry.

            \return The next entry.

            \throw std::logic_error No next entry exists.
        */
        const entry_type& peek()
        const;

        /*!
            \brief Removes the next entry.

            \throw std::logic_error No next entry exists.
        */
        void next();


    private:
        // types
        
        class impl;


        // variables

        const std::unique_ptr<impl> m_p_impl;


    };


}}


#endif
