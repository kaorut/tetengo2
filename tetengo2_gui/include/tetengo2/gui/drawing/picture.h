/*! \file
    \brief The definition of tetengo2::gui::drawing::picture.

    Copyright (C) 2007-2018 kaoru

    $Id$
*/

#if !defined(TETENGO2_GUI_DRAWING_PICTURE_H)
#define TETENGO2_GUI_DRAWING_PICTURE_H

#include <algorithm>
#include <cassert>
#include <stdexcept>

#include <boost/core/noncopyable.hpp>
#include <boost/throw_exception.hpp>

#include <tetengo2/detail/base/drawing.h>
#include <tetengo2/detail/base/gui_impl_set.h>
#include <tetengo2/gui/type_list.h>


namespace tetengo2::gui::drawing {
    /*!
        \brief The class for a picture.
    */
    class picture : private boost::noncopyable
    {
    public:
        // types

        //! The dimension type.
        using dimension_type = gui::type_list::dimension_type;

        //! The drawing details type.
        using drawing_details_type = detail::base::drawing;

        //! The details type.
        using details_type = drawing_details_type::picture_details_type;

        //! The detail implementation pointer type.
        using details_ptr_type = drawing_details_type::picture_details_ptr_type;


        // constructors and destructor

        /*!
            \brief Creates an empty picture.

            \param drawing_details A detail implementation of a drawing.
            \param dimension       A dimension.
        */
        picture(const drawing_details_type& drawing_details, const dimension_type& dimension)
        : m_drawing_details{ drawing_details }, m_p_details{ m_drawing_details.create_picture(dimension) }
        {}

        /*!
            \brief Creates an empty picture.

            Creates a picture for widgets.

            \param dimension A dimension.
        */
        explicit picture(const dimension_type& dimension)
        : m_drawing_details{ detail::gui_detail_impl_set().drawing_() }, m_p_details{ m_drawing_details.create_picture(
                                                                             dimension) }
        {}

        /*!
            \brief Creates a picture with a detail implementation.

            \param drawing_details A detail implementation of a drawing.
            \param p_details       A unique pointer to a detail implementation.

            \throw std::invalid_argument When p_details is nullptr.
        */
        picture(const drawing_details_type& drawing_details, details_ptr_type p_details)
        : m_drawing_details{ drawing_details }, m_p_details{ std::move(p_details) }
        {
            if (!m_p_details)
                BOOST_THROW_EXCEPTION((std::invalid_argument{ "The detail implementation is nullptr." }));
        }

        /*!
            \brief Creates a picture with a detail implementation.

            Creates a picture for widgets.

            \param p_details A unique pointer to a detail implementation.

            \throw std::invalid_argument When p_details is nullptr.
        */
        explicit picture(details_ptr_type p_details)
        : m_drawing_details{ detail::gui_detail_impl_set().drawing_() }, m_p_details{ std::move(p_details) }
        {
            if (!m_p_details)
                BOOST_THROW_EXCEPTION((std::invalid_argument{ "The detail implementation is nullptr." }));
        }


        // functions

        /*!
            \brief Returns the dimension.

            \return The dimension.
        */
        dimension_type dimension() const
        {
            return m_drawing_details.picture_dimension(*m_p_details);
        }

        /*!\
            \brief Returns the detail implentation of a drawing.

            \return The detail implementation of a drawing.
        */
        const drawing_details_type& drawing_details() const
        {
            return m_drawing_details;
        }

        /*!
            \brief Returns the detail implementation.

            \return The detail implementation.
        */
        const details_type& details() const
        {
            assert(m_p_details);
            return *m_p_details;
        }

        /*!
            \brief Returns the detail implementation.

            \return The detail implementation.
        */
        details_type& details()
        {
            assert(m_p_details);
            return *m_p_details;
        }


    private:
        // variables

        const drawing_details_type& m_drawing_details;

        const details_ptr_type m_p_details;
    };
}


#endif
