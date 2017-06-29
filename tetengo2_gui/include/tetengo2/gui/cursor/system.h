/*! \file
    \brief The definition of tetengo2::gui::cursor::system.

    Copyright (C) 2007-2017 kaoru

    $Id$
*/

#if !defined(TETENGO2_GUI_CURSOR_SYSTEMCURSOR_H)
#define TETENGO2_GUI_CURSOR_SYSTEMCURSOR_H

#include <tetengo2/detail/base/cursor.h>
#include <tetengo2/gui/cursor/cursor_base.h>


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

        //! The detail implemetation type of a cursor.
        using cursor_details_type = detail::base::cursor;

        //! The style type.
        enum class style_type
        {
            default_,          //!< A default style.
            hand,              //!< A hand style.
            horizontal_resize, //!< A horizontal resize style.
            vertical_resize,   //!< A vertical resize style.
        };


        // constructors and destructor

        /*!
            \brief Creates a system cursor.

            \param style          A style.
            \param cursor_details A cursor details type.
        */
        system(const style_type style, const cursor_details_type& cursor_details)
        :
        m_style(style),
        m_p_details(cursor_details.create_system_cursor(static_cast<int>(style)))
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
        // types

        using details_ptr_type = typename cursor_details_type::cursor_details_ptr_type;


        // variables

        style_type m_style;

        details_ptr_type m_p_details;


    };


}}}


#endif
