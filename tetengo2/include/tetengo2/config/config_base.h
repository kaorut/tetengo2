/*! \file
    \brief The definition of tetengo2::config::config_base.

    Copyright (C) 2007-2015 kaoru

    $Id$
*/

#if !defined(TETENGO2_CONFIG_CONFIGBASE_H)
#define TETENGO2_CONFIG_CONFIGBASE_H

#include <utility>

#include <boost/core/noncopyable.hpp>
#include <boost/optional.hpp>
#include <boost/variant.hpp>


namespace tetengo2 { namespace config
{
    /*!
        \brief The class template for a configuration base.

        \tparam String A string type.
        \tparam UInt   An unsigned integer type.
    */
    template <typename String, typename UInt>
    class config_base : private boost::noncopyable
    {
    public:
        // types

        //! The string type.
        using string_type = String;

        //! The unsigned integer type.
        using uint_type = UInt;

        //! The value type.
        using value_type = boost::variant<string_type, uint_type>;


        // constructors and destructor

        /*!
            \brief Destroys the configuration base.
        */
        virtual ~config_base()
        = default;


        // functions
        
        /*!
            \brief Returns the value.

            \param key A key.

            \return The value.
        */
        boost::optional<value_type> get(const string_type& key)
        const
        {
            return get_impl(key);
        }

        /*!
            \brief Sets a string value.

            \param key   A key.
            \param value A value.
        */
        void set(const string_type& key, value_type value)
        {
            set_impl(key, std::move(value));
        }

        /*!
            \brief Clears the configuration.
        */
        void clear()
        {
            clear_impl();
        }


    private:
        // virtual functions

        virtual boost::optional<value_type> get_impl(const string_type& key)
        const = 0;

        virtual void set_impl(const string_type& key, value_type value)
        = 0;

        virtual void clear_impl()
        = 0;


    };


}}


#endif
