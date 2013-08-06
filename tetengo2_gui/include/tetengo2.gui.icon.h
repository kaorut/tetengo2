/*! \file
    \brief The definition of tetengo2::gui::icon.

    Copyright (C) 2007-2013 kaoru

    $Id$
*/

#if !defined(TETENGO2_GUI_ICON_H)
#define TETENGO2_GUI_ICON_H

#include <utility>

#include <boost/noncopyable.hpp>
#include <boost/optional.hpp>


namespace tetengo2 { namespace gui
{
    /*!
        \brief The class template for an icon.

        \tparam Path    A path type.
        \tparam Details A detail implementation type.
    */
    template <typename Path, typename Details>
    class icon : private boost::noncopyable
    {
    public:
        // types

        //! The path type.
        typedef Path path_type;

        //! The detail implementation type.
        typedef Details details_type;

        //! The icon details type.
        typedef typename details_type::icon_details_type icon_details_type;

        //! The icon details pointer type.
        typedef typename details_type::icon_details_ptr_type icon_details_ptr_type;


        // constructors and destructor

        /*!
            \brief Creates an icon.

            \param path A path.
        */
        explicit icon(path_type path)
        :
        m_path(std::move(path)),
        m_p_icon_details(details_type::create(m_path))
        {}


        // functions

        /*!
            \brief Returns the path.

            \return The path.
        */
        const path_type& path()
        const
        {
            return m_path;
        }

        /*!
            \brief Returns the detail implementation.

            \return The detail implementation.
        */
        boost::optional<const icon_details_type&> details()
        const
        {
            if (!m_p_icon_details)
                return boost::none;
            return boost::make_optional<const icon_details_type&>(*m_p_icon_details);
        }

        /*!
            \brief Returns the detail implementation.

            \return The detail implementation.
        */
        boost::optional<icon_details_type&> details()
        {
            if (!m_p_icon_details)
                return boost::none;
            return boost::make_optional<icon_details_type&>(*m_p_icon_details);
        }


    private:
        // variables

        const path_type m_path;

        const icon_details_ptr_type m_p_icon_details;


    };


}}

#endif
