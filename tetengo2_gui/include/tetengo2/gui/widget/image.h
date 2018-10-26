/*! \file
    \brief The definition of tetengo2::gui::widget::image.

    Copyright (C) 2007-2018 kaoru

    $Id$
*/

#if !defined(TETENGO2_GUI_WIDGET_IMAGE_H)
#define TETENGO2_GUI_WIDGET_IMAGE_H

#include <memory>

#include <tetengo2/gui/drawing/picture.h>
#include <tetengo2/gui/icon.h>
#include <tetengo2/gui/widget/control.h>


namespace tetengo2::gui::widget {
    class widget;


    /*!
        \brief The class for an image.
    */
    class image : public control
    {
    public:
        // types

        //! The picture type.
        using picture_type = gui::drawing::picture;

        //! The icon type.
        using icon_type = gui::icon;


        // constructors and destructor

        /*!
            \brief Creates an image.

            \param parent A parent widget.
        */
        explicit image(widget& parent);

        /*!
            \brief Destroys the image.
        */
        virtual ~image() noexcept;


        // functions

        /*!
            \brief Checks whether a picture is set.

            \retval true  When a picture is set.
            \retval false Otherwise.
        */
        bool has_picture() const;

        /*!
            \brief Returns the picture.

            \return The picture.

            \throw std::logic_error When no picture is set.
        */
        const picture_type& picture() const;

        /*!
            \brief Returns the picture.

            \return The picture.

            \throw std::logic_error When no picture is set.
        */
        picture_type& picture();

        /*!
            \brief Sets a picture.

            \param p_picture A unique pointer to a picture.
        */
        void set_picture(std::unique_ptr<picture_type> p_picture);

        /*!
            \brief Checks whether an icon is set.

            \retval true  When an icon is set.
            \retval false Otherwise.
        */
        bool has_icon() const;

        /*!
            \brief Returns the icon.

            \return The icon.

            \throw std::logic_error When no icon is set.
        */
        const icon_type& icon() const;

        /*!
            \brief Returns the icon.

            \return The icon.

            \throw std::logic_error When no icon is set.
        */
        icon_type& icon();

        /*!
            \brief Sets an icon.

            \param p_icon A unique pointer to an icon.
        */
        void set_icon(std::unique_ptr<icon_type> p_icon);

        /*!
            \brief Fit the dimension to the dimension of the picture or the icon.
        */
        void fit_to_content();


    private:
        // types

        class impl;


        // variables

        const std::unique_ptr<impl> m_p_impl;
    };
}


#endif
