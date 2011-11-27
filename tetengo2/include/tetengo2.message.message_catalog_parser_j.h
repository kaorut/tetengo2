/*! \file
    \brief The definition of tetengo2::message::message_catalog_parser_j.

    Copyright (C) 2007-2011 kaoru

    $Id$
*/

#if !defined(TETENGO2_MESSAGE_MESSAGECATALOGPARSERJ_H)
#define TETENGO2_MESSAGE_MESSAGECATALOGPARSERJ_H

#include <locale>
//#include <memory>
#include <stdexcept>
#include <string>
//#include <utility>

#include <boost/noncopyable.hpp>
#include <boost/throw_exception.hpp>

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
    class message_catalog_parser_j : private boost::noncopyable
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
        explicit message_catalog_parser_j(
            std::unique_ptr<pull_parser_type> p_pull_parser
        )
        :
        m_p_pull_parser(std::move(p_pull_parser)),
        m_p_preread_entry()
        {
            m_input_stream.imbue(std::locale::classic());
        }


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
            \brief Returns the next entry.

            \return The next entry.

            \throw std::runtime_error No next entry exists.
        */
        entry_type next()
        {
            if (!has_next())
                BOOST_THROW_EXCEPTION(std::runtime_error("No next entry."));

            const std::unique_ptr<entry_type> p_entry(
                std::move(m_p_preread_entry)
            );
            m_p_preread_entry.reset();
            return *p_entry;
        }


    private:
        // static functions

        static const encoder_type& encoder()
        {
            static const encoder_type singleton;
            return singleton;
        }


        // variables

        std::unique_ptr<pull_parser_type>& m_p_pull_parser;

        mutable std::unique_ptr<entry_type> m_p_preread_entry;


        // functions

        bool preread()
        const
        {
            if (m_p_preread_entry) return true;

            //while (m_input_stream.good())
            //{
            //    std::unique_ptr<entry_type> p_entry = parse(get_line());
            //    if (p_entry)
            //    {
            //        m_p_preread_entry = std::move(p_entry);
            //        return true;
            //    }
            //}

            return false;
        }


    };


}}


#endif
