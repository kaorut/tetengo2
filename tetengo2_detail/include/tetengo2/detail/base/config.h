/*! \file
    \brief The definition of tetengo2::detail::base::config.

    Copyright (C) 2007-2018 kaoru

    $Id$
*/

#if !defined(TETENGO2_DETAIL_BASE_CONFIG_H)
#define TETENGO2_DETAIL_BASE_CONFIG_H

#include <boost/core/noncopyable.hpp>
#include <boost/optional.hpp>
#include <boost/variant.hpp>

#include <tetengo2/type_list.h>


namespace tetengo2::detail::base {
    /*!
        \brief The class for a detail implementation of a configuration.
    */
    class config : private boost::noncopyable
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
            \brief Destroys the detail implementation.
        */
        virtual ~config();


        // functions

        /*!
            \brief Returns the configuration value.

            \param group_name A group name.
            \param key        A key.

            \return The pointer to the value. Or nullptr when no corresponding value to the key.
        */
        boost::optional<value_type> get(const string_type& group_name, const string_type& key) const;

        /*!
            \brief Sets a configuration value.

            \param group_name A group_name.
            \param key        A key.
            \param value      A value.
        */
        void set(const string_type& group_name, const string_type& key, value_type value) const;

        /*!
            \brief Clears the configuration.

            \param group_name A group_name.
        */
        void clear(const string_type& group_name) const;


    protected:
        // constructors

        /*!
            \brief Creates a detail implementation.
        */
        config();


    private:
        // virtual functions

        virtual boost::optional<value_type> get_impl(const string_type& group_name, const string_type& key) const = 0;

        virtual void set_impl(const string_type& group_name, const string_type& key, value_type value) const = 0;

        virtual void clear_impl(const string_type& group_name) const = 0;
    };
}


#endif
