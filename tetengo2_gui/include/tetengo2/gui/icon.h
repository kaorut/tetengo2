/*! \file
    \brief The definition of tetengo2::gui::icon.

    Copyright (C) 2007-2017 kaoru

    $Id$
*/

#if !defined(TETENGO2_GUI_ICON_H)
#define TETENGO2_GUI_ICON_H

#include <cassert>
#include <utility>

#include <boost/core/noncopyable.hpp>
#include <boost/filesystem.hpp>


namespace tetengo2 { namespace gui
{
    /*!
        \brief The class template for an icon.

        \tparam Dimension A dimension type.
        \tparam Details   A detail implementation type.
    */
    template <typename Dimension, typename Details>
    class icon : private boost::noncopyable
    {
    public:
        // types

        //! The dimension type.
        using dimension_type = Dimension;

        //! The details type.
        using details_type = Details;

        //! The icon details type.
        using icon_details_type = typename details_type::icon_details_type;

        //! The icon details pointer type.
        using icon_details_ptr_type = typename details_type::icon_details_ptr_type;


        // constructors and destructor

        /*!
            \brief Creates an icon.

            The dimension is determined by the system.

            \param path A path.
        */
        explicit icon(boost::filesystem::path path)
        :
        m_path(std::move(path)),
        m_dimension(details_type::template default_dimension<dimension_type>()),
        m_p_icon_details(details_type::create(m_path, m_dimension))
        {}

        /*!
            \brief Creates an icon.

            \param path      A path.
            \param dimension A dimension.
        */
        icon(boost::filesystem::path path, dimension_type dimension)
        :
        m_path(std::move(path)),
        m_dimension(std::move(dimension)),
        m_p_icon_details(details_type::create(m_path, m_dimension))
        {}


        // functions

        /*!
            \brief Returns the path.

            \return The path.
        */
        const boost::filesystem::path& path()
        const
        {
            return m_path;
        }

        /*!
            \brief Returns the dimension.

            \return The dimension.
        */
        const dimension_type& dimension()
        const
        {
            return m_dimension;
        }

        /*!
            \brief Returns the detail implementation.

            \return The detail implementation.
        */
        const icon_details_type& details()
        const
        {
            assert(m_p_icon_details);
            return *m_p_icon_details;
        }

        /*!
            \brief Returns the detail implementation.

            \return The detail implementation.
        */
        icon_details_type& details()
        {
            assert(m_p_icon_details);
            return *m_p_icon_details;
        }


    private:
        // variables

        const boost::filesystem::path m_path;

        const dimension_type m_dimension;

        const icon_details_ptr_type m_p_icon_details;


    };


}}

#endif
