/*! \file
    \brief The definition of tetengo2::gui::widget::image.

    Copyright (C) 2007-2013 kaoru

    $Id$
*/

#if !defined(TETENGO2_GUI_WIDGET_IMAGE_H)
#define TETENGO2_GUI_WIDGET_IMAGE_H

//#include <memory>
//#include <stdexcept>
//#include <utility>

//#include <boost/throw_exception.hpp>

#include "tetengo2.gui.measure.h"
#include "tetengo2.gui.widget.control.h"
#include "tetengo2.stdalt.h"


namespace tetengo2 { namespace gui { namespace widget
{
    /*!
        \brief The class template for an image.

        \tparam Traits                A traits type.
        \tparam WidgetDetails         A detail implementation type of a widget.
        \tparam MessageHandlerDetails A detail implementation type of a message handler.
   */
    template <typename Traits, typename WidgetDetails, typename MessageHandlerDetails>
    class image : public control<typename Traits::base_type, WidgetDetails, MessageHandlerDetails>
    {
    public:
        // types

        //! The traits type.
        typedef Traits traits_type;

        //! The detail implementation type of a widget.
        typedef WidgetDetails widget_details_type;

        //! The detail implementation type of a message handler.
        typedef MessageHandlerDetails message_handler_details_type;

        //! The base type.
        typedef control<typename traits_type::base_type, widget_details_type, message_handler_details_type> base_type;

        //! The widget type.
        typedef typename base_type::base_type widget_type;

        //! The picture type.
        typedef typename traits_type::picture_type picture_type;
        
        //! The icon type.
        typedef typename traits_type::icon_type icon_type;

        //! The detail implementation type.
        typedef typename widget_details_type::widget_details_type details_type;


        // constructors and destructor

        /*!
            \brief Creates an image.

            \param parent A parent widget.
        */
        explicit image(widget_type& parent)
        :
#if defined(_MSC_VER)
#   pragma warning(push)
#   pragma warning(disable: 4355)
#endif
        base_type(
            base_type::scroll_bar_style_type::none,
            message_handler_details_type::make_image_message_handler_map(*this, message_handler_map_type()),
            widget_details_type::create_image(parent)
        ),
#if defined(_MSC_VER)
#   pragma warning(pop)
#endif
        m_p_picture(),
        m_p_icon()
        {
            initialize_image(this);
        }

        /*!
            \brief Destroys the image.
        */
        virtual ~image()
        TETENGO2_STDALT_NOEXCEPT
        {}


        // functions

        /*!
            \brief Checks whether a picture is set.

            \retval true  When a picture is set.
            \retval false Otherwise.
        */
        bool has_picture()
        const
        {
            return static_cast<bool>(m_p_picture);
        }

        /*!
            \brief Returns the picture.

            \return The picture.

            \throw std::logic_error When no picture is set.
        */
        const picture_type& picture()
        const
        {
            if (!m_p_picture)
                BOOST_THROW_EXCEPTION(std::logic_error("No picture is set."));

            return *m_p_picture;
        }

        /*!
            \brief Returns the picture.

            \return The picture.

            \throw std::logic_error When no picture is set.
        */
        picture_type& picture()
        {
            if (!m_p_picture)
                BOOST_THROW_EXCEPTION(std::logic_error("No picture is set."));

            return *m_p_picture;
        }

        /*!
            \brief Sets a picture.

            \param p_picture A unique pointer to a picture.
        */
        void set_picture(std::unique_ptr<picture_type> p_picture)
        {
            m_p_picture = std::move(p_picture);
            m_p_icon.reset();
        }

        /*!
            \brief Checks whether an icon is set.

            \retval true  When an icon is set.
            \retval false Otherwise.
        */
        bool has_icon()
        const
        {
            return static_cast<bool>(m_p_icon);
        }

        /*!
            \brief Returns the icon.

            \return The icon.

            \throw std::logic_error When no icon is set.
        */
        const icon_type& icon()
        const
        {
            if (!m_p_icon)
                BOOST_THROW_EXCEPTION(std::logic_error("No icon is set."));

            return *m_p_icon;
        }

        /*!
            \brief Returns the icon.

            \return The icon.

            \throw std::logic_error When no icon is set.
        */
        icon_type& icon()
        {
            if (!m_p_icon)
                BOOST_THROW_EXCEPTION(std::logic_error("No icon is set."));

            return *m_p_icon;
        }

        /*!
            \brief Sets an icon.

            \param p_icon A unique pointer to an icon.
        */
        void set_icon(std::unique_ptr<icon_type> p_icon)
        {
            m_p_icon = std::move(p_icon);
            m_p_picture.reset();
        }

        /*!
            \brief Fit the dimension to the dimension of the picture or the icon.
        */
        void fit_to_content()
        {
            if (m_p_picture)
                this->set_client_dimension(m_p_picture->dimension());
            else if (m_p_icon)
                this->set_client_dimension(m_p_icon->dimension());
        }


    private:
        // types

        typedef typename base_type::canvas_type canvas_type;

        typedef typename base_type::position_type position_type;

        typedef typename gui::position<position_type>::left_type left_type;

        typedef typename gui::position<position_type>::top_type top_type;

        typedef typename message_handler_details_type::message_handler_map_type message_handler_map_type;


        // static functions

        static void initialize_image(image* const p_image)
        {
            p_image->initialize(p_image);

            p_image->paint_observer_set().paint().connect(
                [p_image](canvas_type& canvas) { p_image->paint_image(canvas); }
            );
        }


        // variables

        std::unique_ptr<picture_type> m_p_picture;

        std::unique_ptr<icon_type> m_p_icon;


        // functions

        void paint_image(canvas_type& canvas)
        const
        {
            if (!m_p_picture) return;

            canvas.paint_picture(*m_p_picture, position_type(left_type(0), top_type(0)), this->client_dimension());
        }


    };


}}}


#endif
