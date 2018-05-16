/*! \file
    \brief The definition of tetengo2::detail::base::icon.

    Copyright (C) 2007-2018 kaoru

    $Id$
*/

#if !defined(TETENGO2_DETAIL_BASE_ICON_H)
#define TETENGO2_DETAIL_BASE_ICON_H

#include <memory>

#include <boost/core/noncopyable.hpp>

#include <tetengo2/gui/dimension.h>
#include <tetengo2/stdalt.h>


namespace tetengo2::detail::base {
    /*!
        \brief The class for a detail implementation of an icon.
    */
    class icon : private boost::noncopyable
    {
    public:
        // types

        //! The dimension type.
        using dimension_type = gui::em_dimension;

        //! The icon details type.
        struct icon_details_type
        {
        };

        //! The icon details pointer type.
        using icon_details_ptr_type = std::unique_ptr<icon_details_type>;


        // constructors and destructor

        /*!
            \brief Destroys the detail implementation of an icon.
        */
        ~icon();


        // functions

        /*!
            \brief Returns the default dimension.

            \return The default dimension.
        */
        dimension_type default_dimension() const;

        /*!
            \brief Creates an icon.

            \param path      A path.
            \param dimension A dimension.

            \return A unique pointer to an icon.
        */
        icon_details_ptr_type
        create(const tetengo2::stdalt::filesystem::path& path, const dimension_type& dimension) const;


    protected:
        // constructors

        /*!
            \brief Creates a detail implementation of an icon.
        */
        icon();


    private:
        // types

        class impl;


        // variables

        const std::unique_ptr<impl> m_p_impl;


        // virtual functions

        virtual dimension_type default_dimension_impl() const;

        virtual icon_details_ptr_type
        create_impl(const tetengo2::stdalt::filesystem::path& path, const dimension_type& dimension) const;
    };
}


#endif
