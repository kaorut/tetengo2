/*! \file
    \brief The definition of tetengo2::gui::drawing::picture_reader.

    Copyright (C) 2007-2018 kaoru

    $Id$
*/

#if !defined(TETENGO2_GUI_DRAWING_PICTUREREADER_H)
#define TETENGO2_GUI_DRAWING_PICTUREREADER_H

#include <memory>

#include <boost/core/noncopyable.hpp>

#include <tetengo2/detail/base/drawing.h>
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
        picture_reader(const drawing_details_type& drawing_details, tetengo2::stdalt::filesystem::path path);

        /*!
            \brief Creates a picture reader.

            Creates a picture reader for widgets.

            \param path A path.
        */
        explicit picture_reader(tetengo2::stdalt::filesystem::path path);

        /*!
            \brief Destroys the picture reader.
        */
        ~picture_reader();


        // functions

        /*!
            \brief Reads a picture.

            \return A unique pointer to a picture.
        */
        std::unique_ptr<picture_type> read();

        /*!\
            \brief Returns the detail implentation of a drawing.

            \return The detail implementation of a drawing.
        */
        const drawing_details_type& drawing_details() const;


    private:
        // types

        class impl;


        // variables

        const std::unique_ptr<impl> m_p_impl;
    };
}


#endif
