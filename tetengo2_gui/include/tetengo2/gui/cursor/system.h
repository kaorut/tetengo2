/*! \file
    \brief The definition of tetengo2::gui::cursor::system.

    Copyright (C) 2007-2018 kaoru

    $Id$
*/

#if !defined(TETENGO2_GUI_CURSOR_SYSTEM_H)
#define TETENGO2_GUI_CURSOR_SYSTEM_H

#include <memory>

#include <tetengo2/gui/cursor/cursor_base.h>
#include <tetengo2/gui/cursor/system_cursor_style.h>


namespace tetengo2 { namespace gui { namespace cursor {
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
        system(const style_type style, const cursor_details_type& cursor_details);

        /*!
            \brief Destroys the system cursor.
        */
        virtual ~system();


        // functions

        /*!
            \brief Returns the style.

            \return The style.
        */
        style_type style() const;


    private:
        // class

        class impl;


        // variables

        const std::unique_ptr<impl> m_p_impl;


        // virtual functions

        virtual const details_type& details_impl() const override;

        virtual details_type& details_impl() override;
    };


}}}


#endif
