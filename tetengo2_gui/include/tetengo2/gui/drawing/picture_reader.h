/*! \file
    \brief The definition of tetengo2::gui::drawing::picture_reader.

    Copyright (C) 2007-2018 kaoru

    $Id$
*/

#if !defined(TETENGO2_GUI_DRAWING_PICTUREREADER_H)
#define TETENGO2_GUI_DRAWING_PICTUREREADER_H

#include <memory>
#include <utility>

#include <boost/core/noncopyable.hpp>

#include <tetengo2/detail/base/drawing.h>
#include <tetengo2/gui/drawing/picture.h>
#include <tetengo2/stdalt.h>


namespace tetengo2::gui::drawing {
    /*!
        \brief The class for a picture reader.
    */
    class picture_reader : private boost::noncopyable
    {
    public:
        // types

        //! The drawing details type.
        using drawing_details_type = detail::base::drawing;

        //! The picture type.
        using picture_type = picture;


        // constructors and destructor

        /*!
            \brief Creates a picture reader.

            \param drawing_details A detail implementation of a drawing.
            \param path            A path.
        */
        picture_reader(const drawing_details_type& drawing_details, tetengo2::stdalt::filesystem::path path)
        : m_drawing_details{ drawing_details }, m_path{ std::move(path) }
        {}


        // functions

        /*!
            \brief Reads a picture.

            \return A unique pointer to a picture.
        */
        std::unique_ptr<picture_type> read()
        {
            picture_details_ptr_type p_picture{ m_drawing_details.read_picture(m_path) };
            return std::make_unique<picture_type>(m_drawing_details, std::move(p_picture));
        }

        /*!\
            \brief Returns the detail implentation of a drawing.

            \return The detail implementation of a drawing.
        */
        const drawing_details_type& drawing_details() const
        {
            return m_drawing_details;
        }


    private:
        // types

        using picture_details_ptr_type = typename drawing_details_type::picture_details_ptr_type;


        // variables

        const drawing_details_type& m_drawing_details;

        const tetengo2::stdalt::filesystem::path m_path;
    };
}


#endif
