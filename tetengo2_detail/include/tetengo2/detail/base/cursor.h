/*! \file
    \brief The definition of tetengo2::detail::base::cursor.

    Copyright (C) 2007-2018 kaoru

    $Id$
*/

#if !defined(TETENGO2_DETAIL_BASE_CURSOR_H)
#define TETENGO2_DETAIL_BASE_CURSOR_H

#include <functional>
#include <memory>

#include <boost/core/noncopyable.hpp>

#include <tetengo2/gui/cursor/system_cursor_style.h>


namespace tetengo2 { namespace detail { namespace base
{
    /*!
        \brief The class for a detail implementation of a cursor.
    */
    class cursor : private boost::noncopyable
    {
    public:
        // types

        //! The cursor details type.
        struct cursor_details_type {};

        //! The cursor details pointer type.
        using cursor_details_ptr_type =
            std::unique_ptr<cursor_details_type, std::function<void (cursor_details_type*)>>;

        //! The system cursor style type.
        using system_cursor_style_type = gui::cursor::system_cursor_style;


        // constructors and destructor

        /*!
            \brief Destroys the detail implementation.
        */
        virtual ~cursor();


        // functions

        /*!
            \brief Creates a system cursor.

            \param style A style.

            \return A unique pointer to a system cursor.

            \throw std::system_error When a system cursor cannot be created.
        */
        cursor_details_ptr_type create_system_cursor(system_cursor_style_type style)
        const;


    protected:
        // constructors

        /*!
            \brief Creates a detail implementation.
        */
        cursor();


    private:
        // types

        class impl;


        // variables

        const std::unique_ptr<impl> m_p_impl;


        // virtual functions

        virtual cursor_details_ptr_type create_system_cursor_impl(system_cursor_style_type style)
        const = 0;


    };




}}}


#endif
