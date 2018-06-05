/*! \file
    \brief The definition of tetengo2::gui::drawing::system_color_set.

    Copyright (C) 2007-2018 kaoru

    $Id$
*/

#if !defined(TETENGO2_GUI_DRAWING_SYSTEMCOLORSET_H)
#define TETENGO2_GUI_DRAWING_SYSTEMCOLORSET_H

#include <memory>

#include <boost/core/noncopyable.hpp>

#include <tetengo2/gui/drawing/color.h>


namespace tetengo2::gui::drawing {
    /*!
        \brief The class for a system color set.
    */
    class system_color_set : private boost::noncopyable
    {
    public:
        // types

        //! The color type.
        using color_type = color;


        // static functions

        /*!
            \brief Returns the instance.

            \return The instance.
        */
        static const system_color_set& instance();


        // functions

        /*!
            \brief Returns the color of title bar backgrounds.

            \return The color.
        */
        const color_type& title_bar_background() const;

        /*!
            \brief Returns the color of title bar texts.

            \return The color.
        */
        const color_type& title_bar_text() const;

        /*!
            \brief Returns the color of dialog backgrounds.

            \return The color.
        */
        const color_type& dialog_background() const;

        /*!
            \brief Returns the color of control backgrounds.

            \return The color.
        */
        const color_type& control_background() const;

        /*!
            \brief Returns the color of control texts.

            \return The color.
        */
        const color_type& control_text() const;

        /*!
            \brief Returns the color of selected backgrounds.

            \return The color.
        */
        const color_type& selected_background() const;

        /*!
            \brief Returns the color of selected texts.

            \return The color.
        */
        const color_type& selected_text() const;

        /*!
            \brief Returns the color of hyperlink texts.

            \return The color.
        */
        const color_type& hyperlink_text() const;


    private:
        // types

        class impl;


        // variables

        const std::unique_ptr<impl> m_p_impl;


        // constructors

        system_color_set();
    };
}


#endif
