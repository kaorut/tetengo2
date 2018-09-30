/*! \file
    \brief The definition of tetengo2::gui::widget::image.

    Copyright (C) 2007-2018 kaoru

    $Id$
*/

#include <algorithm>
#include <memory>
#include <stdexcept>

#include <boost/core/noncopyable.hpp>
#include <boost/predef.h>
#include <boost/throw_exception.hpp>

#include <tetengo2/detail/base/gui_impl_set.h>
#include <tetengo2/detail/base/message_handler.h>
#include <tetengo2/detail/base/widget.h>
#include <tetengo2/gui/drawing/picture.h> // IWYU pragma: keep
#include <tetengo2/gui/icon.h> // IWYU pragma: keep
#include <tetengo2/gui/message/child_observer_set.h> // IWYU pragma: keep
#include <tetengo2/gui/message/paint_observer_set.h> // IWYU pragma: keep
#include <tetengo2/gui/widget/control.h>
#include <tetengo2/gui/widget/image.h>
#include <tetengo2/gui/widget/widget.h>


namespace tetengo2::gui::widget {
    class image::impl : private boost::noncopyable
    {
    public:
        // types

        using picture_type = image::picture_type;

        using icon_type = image::icon_type;


        // constructors and destructor

        impl() : m_p_picture{}, m_p_icon{} {}


        // functions

        bool has_picture() const
        {
            return static_cast<bool>(m_p_picture);
        }

        const picture_type& picture() const
        {
            if (!m_p_picture)
                BOOST_THROW_EXCEPTION((std::logic_error{ "No picture is set." }));

            return *m_p_picture;
        }

        picture_type& picture()
        {
            if (!m_p_picture)
                BOOST_THROW_EXCEPTION((std::logic_error{ "No picture is set." }));

            return *m_p_picture;
        }

        void set_picture(std::unique_ptr<picture_type> p_picture)
        {
            m_p_picture = std::move(p_picture);
            m_p_icon.reset();
        }

        bool has_icon() const
        {
            return static_cast<bool>(m_p_icon);
        }

        const icon_type& icon() const
        {
            if (!m_p_icon)
                BOOST_THROW_EXCEPTION((std::logic_error{ "No icon is set." }));

            return *m_p_icon;
        }

        icon_type& icon()
        {
            if (!m_p_icon)
                BOOST_THROW_EXCEPTION((std::logic_error{ "No icon is set." }));

            return *m_p_icon;
        }

        void set_icon(std::unique_ptr<icon_type> p_icon)
        {
            m_p_icon = std::move(p_icon);
            m_p_picture.reset();
        }

        void fit_to_content(image& self)
        {
            if (m_p_picture)
                self.set_client_dimension(m_p_picture->dimension());
            else if (m_p_icon)
                self.set_client_dimension(m_p_icon->dimension());
        }

        void paint_image(canvas_type& canvas, const image& self) const
        {
            if (m_p_picture)
                canvas.paint_picture(*m_p_picture, position_type{}, self.client_dimension());
            else if (m_p_icon)
                canvas.paint_icon(*m_p_icon, position_type{});
        }


    private:
        // variables

        std::unique_ptr<picture_type> m_p_picture;

        std::unique_ptr<icon_type> m_p_icon;
    };


    image::image(widget& parent)
    :
#if BOOST_COMP_MSVC
#pragma warning(push)
#pragma warning(disable : 4355)
#endif
      control{ control::scroll_bar_style_type::none,
               detail::gui_detail_impl_set().message_handler_().make_image_message_handler_map(
                   *this,
                   message_handler_map_type{}),
               widget_details().create_image(parent) },
#if BOOST_COMP_MSVC
#pragma warning(pop)
#endif
      m_p_impl{ std::make_unique<impl>() }
    {
        control::initialize(this);

        this->paint_observer_set().paint().connect(
            [this](canvas_type& canvas) { m_p_impl->paint_image(canvas, *this); });

        parent.child_observer_set().created()(*this);
    }

    image::~image() noexcept
    {
        try
        {
            if (this->has_parent())
                this->parent().child_observer_set().destroying()(*this);
        }
        catch (...)
        {
        }
    }

    bool image::has_picture() const
    {
        return m_p_impl->has_picture();
    }

    const image::picture_type& image::picture() const
    {
        return m_p_impl->picture();
    }

    image::picture_type& image::picture()
    {
        return m_p_impl->picture();
    }

    void image::set_picture(std::unique_ptr<picture_type> p_picture)
    {
        m_p_impl->set_picture(std::move(p_picture));
    }

    bool image::has_icon() const
    {
        return m_p_impl->has_icon();
    }

    const image::icon_type& image::icon() const
    {
        return m_p_impl->icon();
    }

    image::icon_type& image::icon()
    {
        return m_p_impl->icon();
    }

    void image::set_icon(std::unique_ptr<icon_type> p_icon)
    {
        m_p_impl->set_icon(std::move(p_icon));
    }

    void image::fit_to_content()
    {
        m_p_impl->fit_to_content(*this);
    }
}
