/*! \file
    \brief The definition of picture utilities for tetengo2::detail::windows.

    Copyright (C) 2007-2018 kaoru

    $Id$
*/

#if !defined(TETENGO2_DETAIL_WINDOWS_PICTURE_H)
#define TETENGO2_DETAIL_WINDOWS_PICTURE_H

#include <memory>

#include <boost/core/noncopyable.hpp>
#include <tetengo2/detail/windows/com_ptr.h>
#include <tetengo2/gui/dimension.h>
#include <tetengo2/stdalt.h>

struct IWICImagingFactory;


namespace tetengo2::detail::windows {
    /*!
        \brief The class for a detail implementation of a picture.
    */
    class picture : private boost::noncopyable
    {
    public:
        // types

        //! The dimension type.
        using dimension_type = gui::em_dimension;

        //! The details type.
        using details_type = ::IWICBitmapSource;

        //! The details pointer type.
        using details_ptr_type = unique_com_ptr<details_type>;


        // static functions

        /*!
            \brief Returns the instance.

            \return The instance.
        */
        static const picture& instance();


        // functions

        /*!
            \brief Returns the WIC image factory.

            \return The WIC image factory.
        */
        ::IWICImagingFactory& wic_imaging_factory() const;

        /*!
            \brief Creates a picture.

            \param dimension A dimension.

            \return A unique pointer to a picture.
        */
        details_ptr_type create(const dimension_type& dimension) const;

        /*!
            \brief Reads a picture.

            \param path A path.

            \return A unique pointer to a picture.

            \throw std::system_error When the picture cannot be read.
        */
        details_ptr_type read(const tetengo2::stdalt::filesystem::path& path) const;

        /*!
            \brief Returns the dimension of a picture.

            \param picture A picture.

            \return The dimension of the picture.
        */
        dimension_type dimension(const details_type& picture) const;


    private:
        // types

        class impl;


        // variables

        const std::unique_ptr<impl> m_p_impl;


        // constructors

        picture();
    };
}


#endif
