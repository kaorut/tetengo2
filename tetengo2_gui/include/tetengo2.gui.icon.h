/*! \file
    \brief The definition of tetengo2::gui::icon.

    Copyright (C) 2007-2013 kaoru

    $Id$
*/

#if !defined(TETENGO2_GUI_ICON_H)
#define TETENGO2_GUI_ICON_H

#include <boost/noncopyable.hpp>


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

        //! The icon details pointer type.
        typedef typename details_type::icon_details_ptr_type icon_details_ptr_type;


        // constructors and destructor

        /*!
            \brief Creates an icon.

            \param path A path.
        */
        explicit icon(const path_type& path)
        :
        m_p_icon_details(details_type::create(path))
        {}


    private:
        // variables

        const icon_details_ptr_type m_p_icon_details;


    };


}}

#endif
