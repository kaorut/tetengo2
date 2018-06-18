/*! \file
    \brief The definition of tetengo2::gui::icon.

    Copyright (C) 2007-2018 kaoru

    $Id$
*/

#if !defined(TETENGO2_GUI_ICON_H)
#define TETENGO2_GUI_ICON_H

#include <memory>

#include <boost/core/noncopyable.hpp>

#include <tetengo2/detail/base/icon.h>
#include <tetengo2/gui/dimension.h>
#include <tetengo2/stdalt.h>


namespace tetengo2::gui {
    /*!
        \brief The class for an icon.
    */
    class icon : private boost::noncopyable
    {
    public:
        // types

        //! The dimension type.
        using dimension_type = gui::em_dimension;

        //! The details type.
        using details_type = detail::base::icon;

        //! The icon details type.
        using icon_details_type = typename details_type::icon_details_type;


        // constructors and destructor

        /*!
            \brief Creates an icon.

            The dimension is determined by the system.

            \param path A path.
        */
        explicit icon(tetengo2::stdalt::filesystem::path path);

        /*!
            \brief Creates an icon.

            \param path      A path.
            \param dimension A dimension.
        */
        icon(tetengo2::stdalt::filesystem::path path, dimension_type dimension);

        /*!
            \brief Destroys the icon.
        */
        ~icon();


        // functions

        /*!
            \brief Returns the path.

            \return The path.
        */
        const tetengo2::stdalt::filesystem::path& path() const;

        /*!
            \brief Returns the dimension.

            \return The dimension.
        */
        const dimension_type& dimension() const;

        /*!
            \brief Returns the detail implementation.

            \return The detail implementation.
        */
        const icon_details_type& details() const;

        /*!
            \brief Returns the detail implementation.

            \return The detail implementation.
        */
        icon_details_type& details();


    private:
        // types

        class impl;


        // variables

        const std::unique_ptr<impl> m_p_impl;
    };
}

#endif
