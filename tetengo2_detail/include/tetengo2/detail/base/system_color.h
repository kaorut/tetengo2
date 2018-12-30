/*! \file
    \brief The definition of tetengo2::detail::base::system_color.

    Copyright (C) 2007-2019 kaoru

    $Id$
*/

#if !defined(TETENGO2_DETAIL_BASE_SYSTEMCOLOR_H)
#define TETENGO2_DETAIL_BASE_SYSTEMCOLOR_H

#include <memory>

#include <boost/core/noncopyable.hpp>

#include <tetengo2/gui/drawing/color.h>


namespace tetengo2::detail::base {
    /*!
        \brief The class for a detail implementation of a system color.
    */
    class system_color : private boost::noncopyable
    {
    public:
        // types

        //! The color type.
        using color_type = tetengo2::gui::drawing::color;

        //! The index type.
        enum class index_type
        {
            title_bar_text, //!< Title bar text.
            title_bar_background, //!< Title bar background.
            dialog_background, //!< Dialog background.
            control_background, //!< Control background.
            control_text, //!< Control text.
            selected_background, //!< Selected background.
            selected_text, //!< Selected text.
            hyperlink_text, //!< Hyperlink text.
        };


        // constructors and destructor

        /*!
            \brief Dstroys the detail implementation.
        */
        virtual ~system_color();


        // functions

        /*!
            \brief Returns the system color.

            \param index An index;

            \return The system color.
        */
        color_type get_system_color(index_type index) const;


    protected:
        // constructors

        /*!
            \brief Creates a detail implementation.
        */
        system_color();


    private:
        // types

        class impl;


        // variables

        const std::unique_ptr<impl> m_p_impl;


        // virtual functions

        virtual color_type get_system_color_impl(index_type index) const = 0;
    };
}


#endif
