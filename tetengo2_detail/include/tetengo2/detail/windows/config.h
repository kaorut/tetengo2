/*! \file
    \brief The definition of tetengo2::detail::windows::config.

    Copyright (C) 2007-2018 kaoru

    $Id$
*/

#if !defined(TETENGO2_DETAIL_WINDOWS_CONFIG_H)
#define TETENGO2_DETAIL_WINDOWS_CONFIG_H

#include <memory>

#include <tetengo2/detail/base/config.h>
#include <tetengo2/stdalt.h>
#include <tetengo2/type_list.h>


namespace tetengo2::detail::windows {
    /*!
        \brief The class for a detail implementation of a config.
    */
    class config : public base::config
    {
    public:
        // types

        //! The string type.
        using string_type = type_list::string_type;

        //! The unsigned integer type.
        using uint_type = type_list::size_type;

        //! The value type.
        using value_type = tetengo2::stdalt::variant<string_type, uint_type>;


        // static functions

        /*!
            \brief Returns the instance.

            \return The instance.
        */
        static const config& instance();


        // constructors and destructor

        /*!
            \brief Destroys the detail implementation.
        */
        virtual ~config();


    private:
        // types

        class impl;


        // variables

        const std::unique_ptr<impl> m_p_impl;


        // constructors

        config();


        // virtual functions

        virtual tetengo2::stdalt::optional<value_type>
        get_impl(const string_type& group_name, const string_type& key) const override;

        virtual void set_impl(const string_type& group_name, const string_type& key, value_type value) const override;

        virtual void clear_impl(const string_type& group_name) const override;
    };
}


#endif
