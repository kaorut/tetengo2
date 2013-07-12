/*! \file
    \brief The definition of tetengo2::detail::stub::cursor.

    Copyright (C) 2007-2013 kaoru

    $Id$
*/

#if !defined(TETENGO2_DETAIL_STUB_CURSOR_H)
#define TETENGO2_DETAIL_STUB_CURSOR_H

//#include <memory>
#include <system_error>

#include <boost/noncopyable.hpp>

#include "tetengo2.stdalt.h"
#include "tetengo2.utility.h"


namespace tetengo2 { namespace detail { namespace stub
{
    /*!
        \brief The class for a detail implementation of a cursor.
    */
    class cursor : private boost::noncopyable
    {
    public:
        // types

        //! The cursor details type.
        typedef int cursor_details_type;

        //! The cursor details pointer type.
        typedef std::unique_ptr<cursor_details_type> cursor_details_ptr_type;


        // static functions

        /*!
            \brief Creates a system cursor.

            \tparam SystemCursor A system cursor type.

            \param style A style.

            \return A unique pointer to a system cursor.

            \throw std::system_error When a system cursor cannot be created.
        */
        template <typename SystemCursor>
        static cursor_details_ptr_type create_system_cursor(const typename SystemCursor::style_type style)
        {
            suppress_unused_variable_warning(style);

            return stdalt::make_unique<cursor_details_type>();
        }


    };


}}}


#endif
