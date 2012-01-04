/*! \file
    \brief The definition of tetengo2::gui::drawing::picture_reader.

    Copyright (C) 2007-2012 kaoru

    $Id$
*/

#if !defined(TETENGO2_GUI_DRAWING_PICTUREREADER_H)
#define TETENGO2_GUI_DRAWING_PICTUREREADER_H

//#include <memory>
#include <stdexcept>
//#include <utility>

#include <boost/noncopyable.hpp>

#include "tetengo2.unique.h"


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
        typedef Picture picture_type;

        //! The path type.
        typedef Path path_type;

        //! The detail implementation type of a drawing.
        typedef DrawingDetails drawing_details_type;


        // constructors and destructor

        /*!
            \brief Creates a picture reader.

            \tparam P A path type.

            \param path A path.
        */
        template <typename P>
        explicit picture_reader(P&& path)
        :
        m_path(std::forward<P>(path))
        {}


        // functions

        /*!
            \brief Reads a picture.

            \return A unique pointer to a picture.

            \throw std::runtime_error When a picture cannot be read.
        */
        std::unique_ptr<picture_type> read()
        {
            std::unique_ptr<picture_details_type> p_picture(
                drawing_details_type::read_picture(m_path)
            );
            return make_unique<picture_type>(std::move(p_picture));
        }


    private:
        // types

        typedef
            typename drawing_details_type::picture_details_type
            picture_details_type;


        // variables

        const path_type m_path;


    };


}}}


#endif
