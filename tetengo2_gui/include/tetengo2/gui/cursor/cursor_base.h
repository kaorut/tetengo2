/*! \file
    \brief The definition of tetengo2::gui::cursor::cursor_base.

    Copyright (C) 2007-2018 kaoru

    $Id$
*/

#if !defined(TETENGO2_GUI_CURSOR_CURSORBASE_H)
#define TETENGO2_GUI_CURSOR_CURSORBASE_H

#include <memory>

#include <boost/core/noncopyable.hpp>

#include <tetengo2/detail/base/cursor.h>


namespace tetengo2::gui::cursor {
    /*!
        \brief The class for a cursor base.
    */
    class cursor_base : private boost::noncopyable
    {
    public:
        // types

        //! The detail implemetation type of a cursor.
        using cursor_details_type = detail::base::cursor;

        //! The details type.
        using details_type = cursor_details_type::cursor_details_type;

        //! The detail pointer type.
        using details_ptr_type = cursor_details_type::cursor_details_ptr_type;


        // constructors and destructor

        /*!
            \brief Destroys the cursor_base.
        */
        virtual ~cursor_base();


        // functions

        /*!
            \brief Returns the details.

            \return The details.
        */
        const details_type& details() const;

        /*!
            \brief Returns the details.

            \return The details.
        */
        details_type& details();


    protected:
        // constructors and destructor

        /*!
            \brief Creates a cursor base.
        */
        cursor_base();


    private:
        // types

        class impl;


        // variables

        const std::unique_ptr<impl> m_p_impl;


        // virtual functions

        virtual const details_type& details_impl() const = 0;

        virtual details_type& details_impl() = 0;
    };
}


#endif
