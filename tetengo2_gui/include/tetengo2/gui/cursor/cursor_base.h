/*! \file
    \brief The definition of tetengo2::gui::cursor::cursor_base.

    Copyright (C) 2007-2014 kaoru

    $Id$
*/

#if !defined(TETENGO2_GUI_CURSOR_CURSOR_H)
#define TETENGO2_GUI_CURSOR_CURSOR_H

#include <boost/noncopyable.hpp>

#include <tetengo2/stdalt.h>


namespace tetengo2 { namespace gui { namespace cursor
{
    /*!
        \brief The class template for a cursor base.

        \tparam CursorDetails A detail implementation type of a cursor.
    */
    template <typename CursorDetails>
    class cursor_base : private boost::noncopyable
    {
    public:
        // types

        //! The detail implementation type of a cursor.
        using cursor_details_type = CursorDetails;

        //! The detail implementation type.
        using details_type = typename cursor_details_type::cursor_details_type;


        // constructors and destructor

        /*!
            \brief Destroys the cursor_base.
        */
        virtual ~cursor_base()
        TETENGO2_STDALT_DESTRUCTOR_DEFAULT_IMPLEMENTATION;


        // functions

        /*!
            \brief Returns the detail implementation.

            \return The detail implementation.
        */
        const details_type& details()
        const
        {
            return details_impl();
        }

        /*!
            \brief Returns the detail implementation.

            \return The detail implementation.
        */
        details_type& details()
        {
            return details_impl();
        }


    protected:
        // constructors and destructor

        /*!
            \brief Creates a cursor base.
        */
        cursor_base()
        {}


    private:
        // virtual functions

        virtual const details_type& details_impl()
        const = 0;

        virtual details_type& details_impl()
        = 0;


    };


}}}


#endif
