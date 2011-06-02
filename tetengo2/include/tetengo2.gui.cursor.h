/*! \file
    \brief The definition of tetengo2::gui::cursor.

    Copyright (C) 2007-2011 kaoru

    $Id$
*/

#if !defined(TETENGO2_GUI_CURSOR_H)
#define TETENGO2_GUI_CURSOR_H

#include <boost/noncopyable.hpp>
#include <boost/optional.hpp>

#include "tetengo2.cpp0x.h"


namespace tetengo2 { namespace gui
{
    /*!
        \brief The class template for a cursor.

        \tparam CursorDetails A detail implementation type of a cursor.
    */
    template <typename CursorDetails>
    class cursor : private boost::noncopyable
    {
    public:
        // types

        //! The detail implementation type of a cursor.
        typedef CursorDetails cursor_details_type;

        //! The detail implementation type.
        typedef
            typename cursor_details_type::cursor_details_type details_type;


        // constructors and destructor

        /*!
            \brief Destroys the cursor.
        */
        virtual ~cursor()
        TETENGO2_CPP0X_NOEXCEPT
        {}


        // functions

        /*!
            \brief Returns the detail implementation.

            \return The detail implementation.
        */
        boost::optional<const details_type&> details()
        const
        {
            return details_impl();
        }

        /*!
            \brief Returns the detail implementation.

            \return The detail implementation.
        */
        boost::optional<details_type&> details()
        {
            return details_impl();
        }


    protected:
        // constructors and destructor

        /*!
            \brief Creates a cursor.
        */
        cursor()
        {}


    private:
        // virtual functions

        virtual boost::optional<const details_type&> details_impl()
        const = 0;

        virtual boost::optional<details_type&> details_impl()
        = 0;


    };


}}


#endif
