/*! \file
    \brief The definition of tetengo2::gui::cursor::system.

    Copyright (C) 2007-2017 kaoru

    $Id$
*/

#if !defined(TETENGO2_GUI_CURSOR_SYSTEM_H)
#define TETENGO2_GUI_CURSOR_SYSTEM_H

#include <cassert>

#include <tetengo2/gui/cursor/cursor_base.h>
#include <tetengo2/gui/cursor/system_cursor_style.h>


namespace tetengo2 { namespace gui { namespace cursor
{
    /*!
        \brief The class for a system cursor.

        \tparam CursorDetails A detail implementation type of a cursor.
    */
    class system : public cursor_base
    {
    public:
        // types

        //! The base type.
        using base_type = cursor_base;

        //! The details type.
        using details_type = cursor_base::details_type;

        //! The detail pointer type.
        using details_ptr_type = cursor_base::details_ptr_type;

        //! The style type.
        using style_type = system_cursor_style;


        // constructors and destructor

        /*!
            \brief Creates a system cursor.

            \param style          A style.
            \param cursor_details A cursor details type.
        */
        system(const style_type style, const cursor_details_type& cursor_details)
        :
        m_style(style),
        m_p_details(cursor_details.create_system_cursor(style))
        {}

        /*!
            \brief Destroys the system cursor.
        */
        virtual ~system()
        = default;


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

        virtual const details_type& details_impl()
        const override
        {
            assert(m_p_details);
            return *m_p_details;
        }

        virtual details_type& details_impl()
        override
        {
            assert(m_p_details);
            return *m_p_details;
        }


    };


}}}


#endif
