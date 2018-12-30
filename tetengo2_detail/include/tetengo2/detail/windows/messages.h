/*! \file
    \brief The definition of tetengo2::detail::windows::messages.

    Copyright (C) 2007-2019 kaoru

    $Id$
*/

#if !defined(TETENGO2_DETAIL_WINDOWS_MESSAGES_H)
#define TETENGO2_DETAIL_WINDOWS_MESSAGES_H

#include <memory>

#include <tetengo2/detail/base/messages.h>


namespace tetengo2::detail::windows {
    /*!
        \brief The class for a detail implementation of a messages facet.
    */
    class messages : public base::messages
    {
    public:
        // types

        //! The string type.
        using string_type = base::messages::string_type;


        // static functions

        /*!
            \brief Returns the instance.

            \return The instance.
        */
        static const messages& instance();


        // constructors and destructor

        /*!
            \brief Creates a detail implementation.
        */
        messages();

        /*!
            \brief Destroys the detail implementaion.
        */
        virtual ~messages();


    private:
        // types

        class impl;


        // variables

        const std::unique_ptr<impl> m_p_impl;


        // virtual functions

        virtual const string_type& locale_name_prefix_impl() const override;
    };
}


#endif
