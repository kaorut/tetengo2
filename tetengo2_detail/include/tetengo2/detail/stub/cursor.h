/*! \file
    \brief The definition of tetengo2::detail::stub::cursor.

    Copyright (C) 2007-2017 kaoru

    $Id$
*/

#if !defined(TETENGO2_DETAIL_STUB_CURSOR_H)
#define TETENGO2_DETAIL_STUB_CURSOR_H

#include <memory>

#include <tetengo2/detail/base/cursor.h>
#include <tetengo2/stdalt.h>


namespace tetengo2 { namespace detail { namespace stub
{
    /*!
        \brief The class for a detail implementation of a cursor.
    */
    class cursor : public base::cursor
    {
    public:
        // types

        //! The cursor details type.
        using cursor_details_type = base::cursor::cursor_details_type;

        //! The cursor details pointer type.
        using cursor_details_ptr_type = base::cursor::cursor_details_ptr_type;

        //! The system cursor style type.
        using system_cursor_style_type = base::cursor::system_cursor_style_type;


        // static functions

        /*!
            \brief Returns the instance.

            \return The instance.
        */
        static const cursor& instance();


        // constructors and destructor

        /*!
            \brief Destroy the detail implementation.
        */
        virtual ~cursor();


    private:
        // types

        class impl;


        // variables

        const std::unique_ptr<impl> m_p_impl;


        // constructors and destructor

        cursor();


        // virtual functions

        virtual cursor_details_ptr_type create_system_cursor_impl(system_cursor_style_type style)
        const override;


    };


}}}


#endif
