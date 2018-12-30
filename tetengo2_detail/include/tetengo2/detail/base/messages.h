/*! \file
    \brief The definition of tetengo2::detail::base::messages.

    Copyright (C) 2007-2019 kaoru

    $Id$
*/

#if !defined(TETENGO2_DETAIL_BASE_MESSAGES_H)
#define TETENGO2_DETAIL_BASE_MESSAGES_H

#include <memory>

#include <boost/core/noncopyable.hpp>

#include <tetengo2/type_list.h>


namespace tetengo2::detail::base {
    /*!
        \brief The class for a detail implementation of a messages facet.
    */
    class messages : private boost::noncopyable
    {
    public:
        // types

        //! The string type.
        using string_type = type_list::string_type;


        // constructors and destructor

        /*!
            \brief Destroys the detail implementaion.
        */
        virtual ~messages();


        // functions

        /*!
            \brief Returns the locale name prefix for the catalog file mapping.

            \return The locale name prefix.
        */
        const string_type& locale_name_prefix() const;


    protected:
        // constructors

        /*!
            \brief Creates a detail implementation.
        */
        messages();


    private:
        // types

        class impl;


        // variables

        const std::unique_ptr<impl> m_p_impl;


        // virtual functions

        virtual const string_type& locale_name_prefix_impl() const = 0;
    };
}


#endif
