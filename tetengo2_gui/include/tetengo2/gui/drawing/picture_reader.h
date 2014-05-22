/*! \file
    \brief The definition of tetengo2::gui::drawing::picture_reader.

    Copyright (C) 2007-2014 kaoru

    $Id$
*/

#if !defined(TETENGO2_GUI_DRAWING_PICTUREREADER_H)
#define TETENGO2_GUI_DRAWING_PICTUREREADER_H

#include <memory>
#include <utility>

#include <boost/noncopyable.hpp>

#include <tetengo2/stdalt.h>


namespace tetengo2 { namespace gui { namespace drawing
{
    /*!
        \brief The class template for a picture reader.

        \tparam Picture        A picture type.
        \tparam Path           A path type.
        \tparam DrawingDetails A detail implementation type of a drawing.
    */
    template <typename Picture, typename Path, typename DrawingDetails>
    class picture_reader : private boost::noncopyable
    {
    public:
        // types

        //! The picture type.
        using picture_type = Picture;

        //! The path type.
        using path_type = Path;

        //! The detail implementation type of a drawing.
        using drawing_details_type = DrawingDetails;


        // constructors and destructor

        /*!
            \brief Creates a picture reader.

            \param path A path.
        */
        explicit picture_reader(path_type path)
        :
        m_path(std::move(path))
        {}


        // functions

        /*!
            \brief Reads a picture.

            \return A unique pointer to a picture.
        */
        std::unique_ptr<picture_type> read()
        {
            picture_details_ptr_type p_picture{ drawing_details_type::read_picture(m_path) };
            return stdalt::make_unique<picture_type>(std::move(p_picture));
        }


    private:
        // types

        using picture_details_ptr_type = typename drawing_details_type::picture_details_ptr_type;


        // variables

        const path_type m_path;


    };


}}}


#endif
