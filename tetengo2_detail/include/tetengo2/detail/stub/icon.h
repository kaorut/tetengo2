/*! \file
    \brief The definition of tetengo2::detail::stub::icon.

    Copyright (C) 2007-2018 kaoru

    $Id$
*/

#if !defined(TETENGO2_DETAIL_STUB_ICON_H)
#define TETENGO2_DETAIL_STUB_ICON_H

#include <memory>

#include <boost/core/ignore_unused.hpp>
#include <boost/core/noncopyable.hpp>
#include <boost/filesystem.hpp>

#include <tetengo2/stdalt.h>


namespace tetengo2 { namespace detail { namespace stub {
    /*!
        \brief The class for a detail implementation of an icon.
    */
    class icon : private boost::noncopyable
    {
    public:
        // types

        //! The icon details type.
        struct icon_details_type
        {
        };

        //! The icon details pointer type.
        using icon_details_ptr_type = std::unique_ptr<icon_details_type>;


        // static functions

        /*!
            \brief Returns the default dimension.

            \tparam Dimension A dimension type.

            \return The default dimension.
        */
        template <typename Dimension>
        static Dimension default_dimension()
        {
            using dimension_unit_type = typename Dimension::unit_type;
            return { dimension_unit_type{ 42 }, dimension_unit_type{ 42 } };
        }

        /*!
            \brief Creates an icon.

            \tparam Dimension A dimension type.

            \param path      A path.
            \param dimension A dimension.

            \return A unique pointer to an icon.
        */
        template <typename Dimension>
        static icon_details_ptr_type create(const boost::filesystem::path& path, const Dimension& dimension)
        {
            boost::ignore_unused(path, dimension);
            return stdalt::make_unique<icon_details_type>();
        }
    };


}}}


#endif
