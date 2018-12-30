/*! \file
    \brief The definition of tetengo2::detail::stub::icon.

    Copyright (C) 2007-2019 kaoru

    $Id$
*/

#if !defined(TETENGO2_DETAIL_STUB_ICON_H)
#define TETENGO2_DETAIL_STUB_ICON_H

#include <memory>

#include <tetengo2/detail/base/icon.h>
#include <tetengo2/stdalt.h>


namespace tetengo2::detail::stub {
    /*!
        \brief The class for a detail implementation of an icon.
    */
    class icon : public base::icon
    {
    public:
        // types

        //! The dimension type.
        using dimension_type = base::icon::dimension_type;

        //! The icon details type.
        using icon_details_type = base::icon::icon_details_type;

        //! The icon details pointer type.
        using icon_details_ptr_type = base::icon::icon_details_ptr_type;


        // static functions

        /*!
            \brief Returns the instance.

            \return The instance.
        */
        static const icon& instance();


        // constructors and destructor

        /*!
            \brief Destroys the instance.
        */
        virtual ~icon();


    private:
        // types

        class impl;


        // variables

        const std::unique_ptr<impl> m_p_impl;


        // constructors

        icon();


        // virtual functions

        virtual dimension_type default_dimension_impl() const override;

        virtual icon_details_ptr_type
        create_impl(const tetengo2::stdalt::filesystem::path& path, const dimension_type& dimension) const override;
    };
}


#endif
