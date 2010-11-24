/*! \file
    \brief The definition of stub_tetengo2::gui::widget.

    Copyright (C) 2007-2010 kaoru

    $Id$
*/

#if !defined(STUBTETENGO2_GUI_WIDGET_H)
#define STUBTETENGO2_GUI_WIDGET_H

#include <cstddef>
#include <memory>
#include <stdexcept>
//#include <utility>
#include <vector>

#include <boost/noncopyable.hpp>
#include <boost/throw_exception.hpp>

#include "tetengo2.cpp0x_keyword.h"
#include "tetengo2.text.h"
#include "tetengo2.gui.widget_traits.h"


namespace stub_tetengo2 { namespace gui
{
    template <typename Traits>
    class widget : private boost::noncopyable
    {
    public:
        // types

        typedef Traits traits_type;

        typedef typename traits_type::handle_type handle_type;

        typedef typename traits_type::canvas_type canvas_type;

        typedef typename traits_type::alert_type alert_type;

        typedef typename traits_type::difference_type difference_type;

        typedef typename traits_type::size_type size_type;

        typedef typename traits_type::position_type position_type;

        typedef typename traits_type::dimension_type dimension_type;

        typedef typename traits_type::string_type string_type;

        typedef typename traits_type::encoder_type encoder_type;

        typedef typename traits_type::font_type font_type;

        typedef
            typename traits_type::paint_observer_set_type
            paint_observer_set_type;

        typedef
            typename traits_type::mouse_observer_set_type
            mouse_observer_set_type;

        typedef widget child_type;


        // constructors and destructor

        virtual ~widget()
        TETENGO2_NOEXCEPT
        {}


        // functions

        handle_type handle()
        const
        {
            return handle_impl();
        }

        bool has_parent()
        const
        {
            return m_p_parent != NULL;
        }

        widget& parent()
        {
            if (!has_parent())
                BOOST_THROW_EXCEPTION(std::runtime_error("Has no parent."));

            return *m_p_parent;
        }

        const widget& parent()
        const
        {
            if (!has_parent())
                BOOST_THROW_EXCEPTION(std::runtime_error("Has no parent."));

            return *m_p_parent;
        }

        widget& root_ancestor()
        {
            if (!has_parent())
                BOOST_THROW_EXCEPTION(std::runtime_error("Has no parent."));

            return *m_p_parent;
        }

        const widget& root_ancestor()
        const
        {
            if (!has_parent())
                BOOST_THROW_EXCEPTION(std::runtime_error("Has no parent."));

            return *m_p_parent;
        }

        void set_enabled(const bool enabled)
        {
            m_enabled = enabled;
        }

        bool enabled()
        const
        {
            return m_enabled;
        }

        void set_visible(const bool visible)
        {
            m_visible = visible;
        }

        bool visible()
        const
        {
            return m_visible;
        }

        std::auto_ptr<canvas_type> create_canvas()
        {
            return std::auto_ptr<canvas_type>(
                new canvas_type(handle(), false)
            );
        }

        std::auto_ptr<const canvas_type> create_canvas()
        const
        {
            return std::auto_ptr<const canvas_type>(
                new canvas_type(handle(), false)
            );
        }

        template <typename P>
        void set_position(P&& position)
        {
            m_position = std::forward<P>(position);
        }

        const position_type& position()
        const
        {
            return m_position;
        }

        template <typename D>
        void set_dimension(D&& dimension)
        {
            if (dimension.first == 0 || dimension.second == 0)
            {
                BOOST_THROW_EXCEPTION(
                    std::invalid_argument("Dimension has zero value.")
                );
            }

            m_dimension = std::forward<D>(dimension);
        }

        const dimension_type& dimension()
        const
        {
            return m_dimension;
        }

        template <typename D>
        void set_client_dimension(D&& client_dimension)
        {
            if (client_dimension.first == 0 || client_dimension.second == 0)
            {
                BOOST_THROW_EXCEPTION(
                    std::invalid_argument("Client dimension has zero value.")
                );
            }

            m_client_dimension = std::forward<D>(client_dimension);
        }

        const dimension_type& client_dimension()
        const
        {
            return m_client_dimension;
        }

        template <typename S>
        void set_text(S&& text)
        {
            m_text = std::forward<S>(text);
        }

        string_type text()
        const
        {
            return m_text;
        }

        template <typename F>
        void set_font(F&& font)
        {}

        font_type font()
        const
        {
            return font_type(
                string_type(TETENGO2_TEXT("MS UI Gothic")),
                12,
                false,
                false,
                false,
                false
            );
        }

        std::vector<child_type*> children()
        {
            return std::vector<child_type*>();
        }

        std::vector<const child_type*> children()
        const
        {
            return std::vector<const child_type*>();
        }

        void click()
        {}

        const paint_observer_set_type& paint_observer_set()
        const
        {
            static const paint_observer_set_type dummy;
            return dummy;
        }

        paint_observer_set_type& paint_observer_set()
        {
            static paint_observer_set_type dummy;
            return dummy;
        }

        const mouse_observer_set_type& mouse_observer_set()
        const
        {
            static const mouse_observer_set_type dummy;
            return dummy;
        }

        mouse_observer_set_type& mouse_observer_set()
        {
            static mouse_observer_set_type dummy;
            return dummy;
        }

        bool destroyed()
        const
        {
            return false;
        }


    protected:
        // static functions

        static const encoder_type& encoder()
        {
            static const encoder_type singleton;
            return singleton;
        }


        // constructors

        widget()
        :
        m_p_parent(NULL),
        m_enabled(false),
        m_visible(false),
        m_position(std::make_pair(0, 0)),
        m_dimension(std::make_pair(100, 100)),
        m_client_dimension(std::make_pair(80, 80)),
        m_text()
        {}


    private:
        // variables

        widget* const m_p_parent;

        bool m_enabled;

        bool m_visible;

        position_type m_position;

        dimension_type m_dimension;

        dimension_type m_client_dimension;

        string_type m_text;


        // virtual functions

        virtual handle_type handle_impl()
        const = 0;


    };


}}

#endif
