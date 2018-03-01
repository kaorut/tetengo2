/*! \file
    \brief The definition of tetengo2::config::config_list.

    Copyright (C) 2007-2018 kaoru

    $Id$
*/

#if !defined(TETENGO2_CONFIG_CONFIGLIST_H)
#define TETENGO2_CONFIG_CONFIGLIST_H

#include <memory>
#include <vector>

#include <boost/optional.hpp>

#include <tetengo2/config/config_base.h>
#include <tetengo2/type_list.h>


namespace tetengo2 { namespace config {
    /*!
        \brief The class for a configuration list.
    */
    class config_list : public config_base
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
            \brief Creates a configuration list.

            \param p_configs A vector of unique pointers to configurations.
        */
        explicit config_list(std::vector<std::unique_ptr<base_type>> p_configs);

        /*!
            \brief Destroys the configuration list.
        */
        virtual ~config_list();


    private:
        // types

        class impl;


        // variables

        const std::unique_ptr<impl> m_p_impl;


        // virtual functions

        virtual boost::optional<value_type> get_impl(const string_type& key) const override;

        virtual void set_impl(const string_type& key, value_type value) override;

        virtual void clear_impl() override;
    };


}}


#endif
