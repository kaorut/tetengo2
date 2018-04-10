/*! \file
    \brief The definition of tetengo2::config::cached_config.

    Copyright (C) 2007-2018 kaoru

    $Id$
*/

#if !defined(TETENGO2_CONFIG_CACHEDCONFIG_H)
#define TETENGO2_CONFIG_CACHEDCONFIG_H

#include <memory>

#include <tetengo2/config/config_base.h>
#include <tetengo2/stdalt.h>
#include <tetengo2/type_list.h>


namespace tetengo2::config {
    /*!
        \brief The class for a cached configuration.
    */
    class cached_config : public config_base
    {
    public:
        // types

        //! The string type.
        using string_type = type_list::string_type;

        //! The unsigned integer type.
        using uint_type = type_list::size_type;

        //! The base type.
        using base_type = config_base;

        //! The value type.
        using value_type = base_type::value_type;


        // constructors and destructor

        /*!
            \brief Creates a cached configuration.

            \param p_config A unique pointer to a configuration.
        */
        explicit cached_config(std::unique_ptr<base_type> p_config);

        /*!
            \brief Destroys the cached configuration.
        */
        virtual ~cached_config();


    private:
        // types

        class impl;


        // variables

        const std::unique_ptr<impl> m_p_impl;


        // virtual functions

        virtual tetengo2::stdalt::optional<value_type> get_impl(const string_type& key) const override;

        virtual void set_impl(const string_type& key, value_type value) override;

        virtual void clear_impl() override;
    };
}


#endif
