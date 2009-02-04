/*! \file
    \brief The definition of stub_tetengo2::gui::widget.

    Copyright (C) 2007-2009 kaoru

    $Id$
*/

#if !defined(STUBTETENGO2_GUI_WIDGET_H)
#define STUBTETENGO2_GUI_WIDGET_H

#include <exception>
#include <memory>
#include <stdexcept>
#include <string>
#include <utility>

#include <boost/concept_check.hpp>
#include <boost/noncopyable.hpp>

#include "concept_tetengo2.String.h"
#include "concept_tetengo2.gui.Canvas.h"
#include "concept_tetengo2.gui.Handle.h"
#include "concept_tetengo2.gui.PaintObserver.h"


namespace stub_tetengo2 { namespace gui
{
    template <
        typename Handle,
        typename Canvas,
        typename Alert,
        typename Difference,
        typename Size,
        typename String,
        template <typename Target, typename Source> class Encode,
        typename PaintObserver
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
        struct concept_check_Encode
        {
            typedef std::wstring native_string_type;
            typedef Encode<String, std::wstring> encode_from_native_type;
            typedef Encode<std::wstring, String> encode_to_native_type;
            BOOST_CONCEPT_ASSERT((
                boost::UnaryFunction<
                    encode_from_native_type, String, native_string_type
                >
            ));
            BOOST_CONCEPT_ASSERT((
                boost::UnaryFunction<
                    encode_to_native_type, native_string_type, String
                >
            ));
        };
        BOOST_CONCEPT_ASSERT((
            concept_tetengo2::gui::PaintObserver<PaintObserver>
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

        typedef Encode<String, String> encode_from_native_type;

        typedef Encode<String, String> encode_to_native_type;

        typedef PaintObserver paint_observer_type;


        // constructors and destructor

        widget()
        :
        m_enabled(false),
        m_visible(false),
        m_position(std::make_pair(0, 0)),
        m_dimension(std::make_pair(100, 100)),
        m_text()
        {}

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
                throw std::invalid_argument("Dimension has zero value.");

            m_dimension = dimension;
        }

        virtual const dimension_type& dimension()
        const
        {
            return m_dimension;
        }

        virtual void set_text(const string_type& text)
        {
            m_text = text;
        }

        virtual const string_type text()
        const
        {
            return m_text;
        }

        void add_paint_observer(
            std::auto_ptr<paint_observer_type> p_paint_observer
        )
        {}


    private:
        // variables

        bool m_enabled;

        bool m_visible;

        position_type m_position;

        dimension_type m_dimension;

        string_type m_text;


    };


}}

#endif
