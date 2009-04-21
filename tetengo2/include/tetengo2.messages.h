/*! \file
    \brief The definition of tetengo2::messages.

    Copyright (C) 2007-2009 kaoru

    $Id$
*/

#if !defined(TETENGO2_MESSAGES_H)
#define TETENGO2_MESSAGES_H

#include <ios>
#include <locale>
#include <stdexcept>
#include <string>

#include <boost/filesystem.hpp>


namespace tetengo2
{
    /*!
        \brief The class template for messages.

        It is a customized locale facet for messages.

        \tparam String A string type.
        \tparam Path   A path type.
    */
    template <typename String, typename Path>
    class messages : public std::messages<typename String::value_type>
    {
    public:
        // types

        //! The path type.
        typedef Path path_type;


        // constructors and destructor

        /*!
            \brief Creates messages.

            \param path A path where message catalogs are stored.

            \throw std::ios_base::failure When the path does not exist.
        */
        messages(const path_type& path)
        :
        m_open(false)
        {
            if (!boost::filesystem::exists(path))
            {
                throw std::ios_base::failure("The path does not exist.");
            }
        }

        virtual ~messages()
        throw ()
        {}


    protected:
        // functions
        
        /*!
            \brief Opens a message catalog.

            \param catalog_name Not used.
            \param locale       Not used.

            \return The catalog ID. When failed, the value is less than 0.

            \throw std::runtime_error A message catalog is already open.
        */
        virtual catalog do_open(
            const std::string& catalog_name,
            const std::locale& locale
        )
        const
        {
            if (m_open)
            {
                throw std::runtime_error(
                    "A message catalog is already open."
                );
            }

            m_open = true;

            return fixed_catalog_id();
        }
        
        /*!
            \brief Returns the localized message.

            \param catalog_id      A catalog ID. It must be 0.
            \param set             Not used.
            \param message         Not used.
            \param default_message A default message. Also, used as a key.

            \return The localized message.

            \throw std::runtime_error The message catalog is not open or the
                                      catalog ID is invalid.
        */
        virtual string_type do_get(
            const catalog      catalog_id,
            const int          set,
            const int          message,
            const string_type& default_message
        )
        const
        {
            if (!m_open || catalog_id != fixed_catalog_id())
            {
                throw std::runtime_error(
                    "The message catalog is not open or the catalog ID is"
                    "invalid."
                );
            }

            return default_message;
        }

        /*!
            \brief Closes the message catalog.

            \param catalog_id A catalog ID. It must be 0.
        */
        virtual void do_close(const catalog catalog_id)
        const
        {
            if (!m_open || catalog_id != fixed_catalog_id())
            {
                throw std::runtime_error(
                    "The message catalog is not open or the catalog ID is"
                    "invalid."
                );
            }

            m_open = false;
        }


    private:
        // static functions

        static catalog fixed_catalog_id()
        {
            return 0;
        }


        // variables

        mutable bool m_open;



    };


}

#endif
