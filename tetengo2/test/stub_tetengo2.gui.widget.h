/*! \file
    \brief The definition of stub_tetengo2::gui::widget.

    Copyright (C) 2007-2008 kaoru

    $Id$
*/

#if !defined(STUBTETENGO2_GUI_WIDGET_H)
#define STUBTETENGO2_GUI_WIDGET_H

#include <exception>
#include <memory>
#include <string>

#include <boost/concept_check.hpp>
#include <boost/noncopyable.hpp>

#include "tetengo2.StringConcept.h"
#include "tetengo2.gui.CanvasConcept.h"
#include "tetengo2.gui.HandleConcept.h"
#include "tetengo2.gui.PaintObserverConcept.h"


namespace stub_tetengo2 { namespace gui
{
    template <
        typename Handle,
        typename Canvas,
        typename Alert,
        typename String,
        template <typename Target, typename Source> class Encode,
        typename PaintObserver
    >
    class widget : private boost::noncopyable
    {
    private:
        // concept checks

        BOOST_CONCEPT_ASSERT((tetengo2::gui::HandleConcept<Handle>));
        BOOST_CONCEPT_ASSERT((tetengo2::gui::CanvasConcept<Canvas>));
        struct concept_check_Alert
        {
            typedef std::exception exception_type;
            BOOST_CONCEPT_ASSERT((
                boost::UnaryFunctionConcept<Alert, void, exception_type>
            ));
        };
        BOOST_CONCEPT_ASSERT((tetengo2::StringConcept<String>));
        struct concept_check_Encode
        {
            typedef std::wstring native_string_type;
            typedef Encode<String, std::wstring> encode_from_native_type;
            typedef Encode<std::wstring, String> encode_to_native_type;
            BOOST_CONCEPT_ASSERT((
                boost::UnaryFunctionConcept<
                    encode_from_native_type, String, native_string_type
                >
            ));
            BOOST_CONCEPT_ASSERT((
                boost::UnaryFunctionConcept<
                    encode_to_native_type, native_string_type, String
                >
            ));
        };
        BOOST_CONCEPT_ASSERT((
            tetengo2::gui::PaintObserverConcept<PaintObserver>
        ));


    public:
        // types

        typedef Handle handle_type;

        typedef Canvas canvas_type;

        typedef Alert alert_type;

        typedef String string_type;

        typedef Encode<String, String> encode_from_native_type;

        typedef Encode<String, String> encode_to_native_type;

        typedef PaintObserver paint_observer_type;


        // constructors and destructor

        widget()
        :
        m_visible(false),
        m_text()
        {}

        virtual ~widget()
        throw ()
        {}


        // functions

        virtual handle_type handle()
        const = 0;

        virtual void set_visible(const bool visible)
        {
            m_visible = visible;
        }

        virtual bool visible()
        const
        {
            return m_visible;
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

        bool m_visible;

        string_type m_text;


    };


}}

#endif
