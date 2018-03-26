/*! \file
    \brief The definition of tetengo2::config::config_base.

    Copyright (C) 2007-2018 kaoru

    $Id$
*/

#if !defined(TETENGO2_CONFIG_CONFIGBASE_H)
#define TETENGO2_CONFIG_CONFIGBASE_H

#include <memory>

#include <boost/core/noncopyable.hpp>
#include <boost/optional.hpp>
#include <boost/variant.hpp>

#include <tetengo2/type_list.h>


namespace tetengo2::config {
    /*!
        \brief The class for a configuration base.
    */
    class config_base : private boost::noncopyable
    {
    public:
        // types

        //! The string type.
        using string_type = type_list::string_type;

        //! The unsigned integer type.
        using uint_type = type_list::size_type;

        //! The value type.
        using value_type = boost::variant<string_type, uint_type>;


        // constructors and destructor

        /*!
            \brief Creates a configuration base.
        */
        config_base();

        /*!
            \brief Destroys the configuration base.
        */
        virtual ~config_base();


        // functions

        /*!
            \brief Returns the value.

            \param key A key.

            \return The value or boost::none when no corresponding value to the key.
        */
        boost::optional<value_type> get(const string_type& key) const;

        /*!
            \brief Sets a string value.

            \param key   A key.
            \param value A value.
        */
        void set(const string_type& key, value_type value);

        /*!
            \brief Clears the configuration.
        */
        void clear();


    private:
        // types

        class impl;


        // variables

        const std::unique_ptr<impl> m_p_impl;


        // virtual functions

        virtual boost::optional<value_type> get_impl(const string_type& key) const = 0;

        virtual void set_impl(const string_type& key, value_type value) = 0;

        virtual void clear_impl() = 0;
    };
}


#endif
