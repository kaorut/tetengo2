/*! \file
    \brief The definition of tetengo2::gui::drawing::picture.

    Copyright (C) 2007-2014 kaoru

    $Id$
*/

#if !defined(TETENGO2_GUI_DRAWING_PICTURE_H)
#define TETENGO2_GUI_DRAWING_PICTURE_H

#include <cassert>
#include <stdexcept>
#include <utility>

#include <boost/noncopyable.hpp>
#include <boost/throw_exception.hpp>


namespace tetengo2 { namespace gui { namespace drawing
{
    /*!
        \brief The class template for a picture.

        \tparam Dimension      A dimension type.
        \tparam DrawingDetails A detail implementation type of a drawing.
    */
    template <typename Dimension, typename DrawingDetails>
    class picture : private boost::noncopyable
    {
    public:
        // types

        //! The dimension type.
        using dimension_type = Dimension;

        //! The detail implementation type of a drawing.
        using drawing_details_type = DrawingDetails;

        //! The detail implementation type.
        using details_type = typename drawing_details_type::picture_details_type;

        //! The detail implementation pointer type.
        using details_ptr_type = typename drawing_details_type::picture_details_ptr_type;


        // constructors and destructor

        /*!
            \brief Creates an empty picture.

            \param dimension A dimension.
        */
        explicit picture(const dimension_type& dimension)
        :
        m_p_details(drawing_details_type::create_picture(dimension))
        {}

        /*!
            \brief Creates a picture with a detail implementation.

            \param p_details A unique pointer to a detail implementation.

            \throw std::invalid_argument When p_details is nullptr.
        */
        explicit picture(details_ptr_type p_details)
        :
        m_p_details(std::move(p_details))
        {
            if (!m_p_details)
                BOOST_THROW_EXCEPTION(std::invalid_argument{ "The detail implementation is nullptr." });
        }


        // functions

        /*!
            \brief Returns the dimension.

            \return The dimension.
        */
        dimension_type dimension()
        const
        {
            return drawing_details_type::template picture_dimension<dimension_type>(*m_p_details);
        }

        /*!
            \brief Returns the detail implementation.

            \return The detail implementation.
        */
        const details_type& details()
        const
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

        const details_ptr_type m_p_details;


    };


}}}


#endif
