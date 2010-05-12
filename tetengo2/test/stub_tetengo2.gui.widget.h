/*! \file
    \brief The definition of stub_tetengo2::gui::widget.

    Copyright (C) 2007-2010 kaoru

    $Id$
*/

#if !defined(STUBTETENGO2_GUI_WIDGET_H)
#define STUBTETENGO2_GUI_WIDGET_H

//#include <cstddef>
#include <exception>
#include <memory>
#include <stdexcept>
#include <utility>
#include <vector>

//#include <boost/concept_check.hpp>
#include <boost/noncopyable.hpp>
#include <boost/throw_exception.hpp>

#include "concept_tetengo2.Encoder.h"
#include "concept_tetengo2.String.h"
#include "concept_tetengo2.gui.Canvas.h"
#include "concept_tetengo2.gui.Font.h"
#include "concept_tetengo2.gui.Handle.h"
#include "concept_tetengo2.gui.MouseObserver.h"
#include "concept_tetengo2.gui.PaintObserver.h"
#include "tetengo2.text.h"


namespace stub_tetengo2 { namespace gui
{
    template <
        typename Handle,
        typename Canvas,
        typename Alert,
        typename Difference,
        typename Size,
        typename String,
        typename Encoder,
        typename Font,
        typename PaintObserver,
        typename MouseObserver
    >
    class widget : private boost::noncopyable
    {
    private:
        // concept checks

        BOOST_CONCEPT_ASSERT((concept_tetengo2::gui::Handle<Handle>));
        BOOST_CONCEPT_ASSERT((concept_tetengo2::gui::Canvas<Canvas>));
        struct concept_check_Alert
        {
            typedef std::exception exception_type;
            BOOST_CONCEPT_ASSERT((
                boost::UnaryFunction<Alert, void, exception_type>
            ));
        };
        BOOST_CONCEPT_ASSERT((boost::SignedInteger<Difference>));
        BOOST_CONCEPT_ASSERT((boost::UnsignedInteger<Size>));
        BOOST_CONCEPT_ASSERT((concept_tetengo2::String<String>));
        BOOST_CONCEPT_ASSERT((concept_tetengo2::Encoder<Encoder>));
        BOOST_CONCEPT_ASSERT((concept_tetengo2::gui::Font<Font>));
        BOOST_CONCEPT_ASSERT((
            concept_tetengo2::gui::PaintObserver<PaintObserver>
        ));
        BOOST_CONCEPT_ASSERT((
            concept_tetengo2::gui::MouseObserver<MouseObserver>
        ));



    public:
        // types

        typedef Handle handle_type;

        typedef Canvas canvas_type;

        typedef Alert alert_type;

        typedef Difference difference_type;

        typedef Size size_type;

        typedef std::pair<difference_type, difference_type> position_type;

        typedef std::pair<size_type, size_type> dimension_type;

        typedef String string_type;

        typedef Encoder encoder_type;

        typedef Font font_type;

        typedef widget child_type;

        typedef PaintObserver paint_observer_type;

        typedef MouseObserver mouse_observer_type;


        // constructors and destructor

        virtual ~widget()
        throw ()
        {}


        // functions

        virtual handle_type handle()
        const = 0;

        virtual void set_enabled(const bool enabled)
        {
            m_enabled = enabled;
        }

        virtual bool has_parent()
        const
        {
            return m_p_parent != NULL;
        }

        virtual widget& parent()
        {
            if (!has_parent())
                BOOST_THROW_EXCEPTION(std::runtime_error("Has no parent."));

            return *m_p_parent;
        }

        virtual const widget& parent()
        const
        {
            if (!has_parent())
                BOOST_THROW_EXCEPTION(std::runtime_error("Has no parent."));

            return *m_p_parent;
        }

        virtual widget& root_ancestor()
        {
            if (!has_parent())
                BOOST_THROW_EXCEPTION(std::runtime_error("Has no parent."));

            return *m_p_parent;
        }

        virtual const widget& root_ancestor()
        const
        {
            if (!has_parent())
                BOOST_THROW_EXCEPTION(std::runtime_error("Has no parent."));

            return *m_p_parent;
        }

        virtual bool enabled()
        const
        {
            return m_enabled;
        }

        virtual void set_visible(const bool visible)
        {
            m_visible = visible;
        }

        virtual bool visible()
        const
        {
            return m_visible;
        }

        virtual std::auto_ptr<canvas_type> create_canvas()
        {
            return std::auto_ptr<canvas_type>(
                new canvas_type(this->handle(), false)
            );
        }

        virtual std::auto_ptr<const canvas_type> create_canvas()
        const
        {
            return std::auto_ptr<const canvas_type>(
                new canvas_type(this->handle(), false)
            );
        }

        virtual void set_position(const position_type& position)
        {
            m_position = position;
        }

        virtual const position_type& position()
        const
        {
            return m_position;
        }

        virtual void set_dimension(const dimension_type& dimension)
        {
            if (dimension.first == 0 || dimension.second == 0)
            {
                BOOST_THROW_EXCEPTION(
                    std::invalid_argument("Dimension has zero value.")
                );
            }

            m_dimension = dimension;
        }

        virtual const dimension_type& dimension()
        const
        {
            return m_dimension;
        }

        virtual void set_client_dimension(
            const dimension_type& client_dimension
        )
        {
            if (client_dimension.first == 0 || client_dimension.second == 0)
            {
                BOOST_THROW_EXCEPTION(
                    std::invalid_argument("Client dimension has zero value.")
                );
            }

            m_client_dimension = client_dimension;
        }

        virtual const dimension_type& client_dimension()
        const
        {
            return m_client_dimension;
        }

        virtual void set_text(const string_type& text)
        {
            m_text = text;
        }

        virtual string_type text()
        const
        {
            return m_text;
        }

        virtual void set_font(const font_type& font)
        {}

        virtual font_type font()
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

        virtual void add_paint_observer(
            std::auto_ptr<paint_observer_type> p_paint_observer
        )
        {}

        virtual void add_mouse_observer(
            std::auto_ptr<mouse_observer_type> p_mouse_observer
        )
        {}

        virtual bool destroyed()
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

        explicit widget()
        :
        m_p_parent(NULL),
        m_enabled(false),
        m_visible(false),
        m_position(std::make_pair(0, 0)),
        m_dimension(std::make_pair(100, 100)),
        m_client_dimension(std::make_pair(80, 80)),
        m_text()
        {}

        explicit widget(widget& parent)
        :
        m_p_parent(&parent),
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


    };


}}

#endif
