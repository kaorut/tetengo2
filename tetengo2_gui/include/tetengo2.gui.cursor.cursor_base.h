/*! \file
    \brief The definition of tetengo2::gui::cursor::cursor_base.

    Copyright (C) 2007-2013 kaoru

    $Id$
*/

#if !defined(TETENGO2_GUI_CURSOR_CURSOR_H)
#define TETENGO2_GUI_CURSOR_CURSOR_H

#include <boost/noncopyable.hpp>
#include <boost/optional.hpp>


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
        typedef CursorDetails cursor_details_type;

        //! The detail implementation type.
        typedef typename cursor_details_type::cursor_details_type details_type;

        //! The detail implementation pointer type.
        typedef typename cursor_details_type::cursor_details_ptr_type details_ptr_type;


        // constructors and destructor

        /*!
            \brief Destroys the cursor_base.
        */
        virtual ~cursor_base()
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
            \brief Creates a cursor base.
        */
        cursor_base()
        {}


    private:
        // virtual functions

        virtual boost::optional<const details_type&> details_impl()
        const = 0;

        virtual boost::optional<details_type&> details_impl()
        = 0;


    };


}}}


#endif
