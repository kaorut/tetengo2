/*! \file
    \brief The definition of tetengo2::message::messages.

    Copyright (C) 2007-2017 kaoru

    $Id$
*/

#if !defined(TETENGO2_MESSAGE_MESSAGES_H)
#define TETENGO2_MESSAGE_MESSAGES_H

#include <ios>
#include <locale>
#include <memory>
#include <string>

#include <boost/core/noncopyable.hpp>
#include <boost/filesystem.hpp>

#include <tetengo2/text.h>
#include <tetengo2/type_list.h>


namespace tetengo2 { namespace message
{
    /*!
        \brief The class for a messages facet.

        It is a customized locale facet for a messages facet.
    */
    class messages : public std::messages<type_list::string_type::value_type>, private boost::noncopyable
    {
    public:
        // types

        //! The string type.
        using string_type = type_list::string_type;

        //! The catalog type.
        using catalog = std::messages<string_type::value_type>::catalog;


        // static functions

        /*!
            \brief Removes namespaces.

            \param key A key.

            \return The key in which the namespace part is removed.
        */
        static string_type remove_namespace(const string_type& key);


        // constructors and destructor

        /*!
            \brief Creates a messages facet.

            \param path   A path where message catalogs are stored.
            \param locale A locale for the messages facet.

            \throw std::ios_base::failure When the path does not exist or is not a directory.
        */
        messages(const boost::filesystem::path& path, const std::locale& locale);

        /*!
            \brief Destroys the messages facet.
        */
        virtual ~messages();


    private:
        // types

        class impl;


        // variables

        const std::unique_ptr<impl> m_p_impl;


        // virtual functions

        virtual catalog do_open(const std::string& catalog_name, const std::locale& locale)
        const override;

        virtual string_type do_get(catalog catalog_id, int set, int message, const string_type& default_message)
        const override;

        virtual void do_close(catalog catalog_id)
        const override;


    };


}}


#endif
