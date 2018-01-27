/*! \file
    \brief The definition of tetengo2::gui::widget::image.

    Copyright (C) 2007-2018 kaoru

    $Id$
*/

#if !defined(TETENGO2_GUI_WIDGET_IMAGE_H)
#define TETENGO2_GUI_WIDGET_IMAGE_H

#include <memory>
#include <stdexcept>

#include <boost/predef.h>
#include <boost/throw_exception.hpp>

#include <tetengo2/gui/drawing/picture.h>
#include <tetengo2/gui/icon.h>
#include <tetengo2/gui/widget/control.h>


namespace tetengo2 { namespace gui { namespace widget
{
    /*!
        \brief The class template for an image.

        \tparam Traits        A traits type.
        \tparam DetailsTraits A detail implementation type traits.
    */
    template <typename Traits, typename DetailsTraits>
    class image : public control<Traits, DetailsTraits>
    {
    public:
        // types

        //! The traits type.
        using traits_type = Traits;

        //! The details traits type.
        using details_traits_type = DetailsTraits;

        //! The widget details type.
        using widget_details_type = typename details_traits_type::widget_details_type;

        //! The drawing details type.
        using drawing_details_type = typename details_traits_type::drawing_details_type;

        //! The icon details type.
        using icon_details_type = typename details_traits_type::icon_details_type;

        //! The message handler details type.
        using message_handler_details_type = typename details_traits_type::message_handler_details_type;

        //! The base type.
        using base_type = control<traits_type, details_traits_type>;

        //! The widget type.
        using widget_type = typename base_type::base_type;

        //! The dimension type.
        using dimension_type = typename base_type::dimension_type;

        //! The picture type.
        using picture_type = gui::drawing::picture<dimension_type, drawing_details_type>;
        
        //! The icon type.
        using icon_type = gui::icon<dimension_type, icon_details_type>;


        // constructors and destructor

        /*!
            \brief Creates an image.

            \param parent A parent widget.
        */
        explicit image(widget_type& parent)
        :
#if BOOST_COMP_MSVC
#   pragma warning(push)
#   pragma warning(disable: 4355)
#endif
        base_type(
            base_type::scroll_bar_style_type::none,
            message_handler_details_type::make_image_message_handler_map(*this, message_handler_map_type{}),
            widget_details_type::create_image(parent)
        ),
#if BOOST_COMP_MSVC
#   pragma warning(pop)
#endif
        m_p_picture(),
        m_p_icon()
        {
            initialize_image(this);

            parent.child_observer_set().created()(*this);
        }

        /*!
            \brief Destroys the image.
        */
        virtual ~image()
        noexcept
        {
            try
            {
                if (this->has_parent())
                    this->parent().child_observer_set().destroying()(*this);
            }
            catch (...)
            {}
        }


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
                BOOST_THROW_EXCEPTION((std::logic_error{ "No picture is set." }));

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
                BOOST_THROW_EXCEPTION((std::logic_error{ "No picture is set." }));

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
                BOOST_THROW_EXCEPTION((std::logic_error{ "No icon is set." }));

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
                BOOST_THROW_EXCEPTION((std::logic_error{ "No icon is set." }));

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

        using canvas_type = typename base_type::canvas_type;

        using position_type = typename base_type::position_type;

        using message_handler_map_type = typename message_handler_details_type::message_handler_map_type;


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
            if (m_p_picture)
                canvas.paint_picture(*m_p_picture, position_type{}, this->client_dimension());
            else if (m_p_icon)
                canvas.paint_icon(*m_p_icon, position_type{});
        }


    };


}}}


#endif
