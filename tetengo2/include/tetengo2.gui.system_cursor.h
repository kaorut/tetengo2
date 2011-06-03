/*! \file
    \brief The definition of tetengo2::gui::system_cursor.

    Copyright (C) 2007-2011 kaoru

    $Id$
*/

#if !defined(TETENGO2_GUI_SYSTEMCURSOR_H)
#define TETENGO2_GUI_SYSTEMCURSOR_H

#include "tetengo2.cpp0x.h"
#include "tetengo2.gui.cursor.h"


namespace tetengo2 { namespace gui
{
    /*!
        \brief The class template for a system cursor.

        \tparam CursorDetails A detail implementation type of a cursor.
    */
    template <typename CursorDetails>
    class system_cursor : public cursor<CursorDetails>
    {
    public:
        // types

        //! The detail implemetation type of a cursor.
        typedef CursorDetails cursor_details_type;

        //! The detail implementation type.
        typedef
            typename cursor_details_type::cursor_details_type details_type;

        //! The detail implementation pointer type.
        typedef
            typename cursor_details_type::cursor_details_ptr_type
            details_ptr_type;

        //! The style type.
        enum style_type
        {
            style_default, //!< A default style.
            style_hand,    //!< A hand style.
        };


        // constructors and destructor

        /*!
            \brief Creates a system cursor.

            \param style A style.
        */
        system_cursor(const style_type style)
        :
        m_style(style),
        m_p_details(
            cursor_details_type::create_system_cursor<system_cursor>(style)
        )
        {}

        /*!
            \brief Destroys the system cursor.
        */
        virtual ~system_cursor()
        TETENGO2_CPP0X_NOEXCEPT
        {}


        // functions

        /*!
            \brief Returns the style.

            \return The style.
        */
        style_type style()
        const
        {
            return m_style;
        }


    private:
        // variables

        style_type m_style;

        details_ptr_type m_p_details;


        // virtual functions

        virtual boost::optional<const details_type&> details_impl()
        const
        {
            return *m_p_details;
        }

        virtual boost::optional<details_type&> details_impl()
        {
            return *m_p_details;
        }


    };


}}


#endif
