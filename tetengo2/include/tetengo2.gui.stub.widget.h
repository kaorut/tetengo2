/*! \file
    \brief The definition of tetengo2::gui::stub::widget.

    Copyright (C) 2007 kaoru

    $Id$
*/

#if !defined(TETENGO2_GUI_STUB_WIDGET_H)
#define TETENGO2_GUI_STUB_WIDGET_H

#include <memory>

#include <boost/concept_check.hpp>
#include <boost/noncopyable.hpp>

#include "tetengo2.StringConcept.h"
#include "tetengo2.gui.CanvasConcept.h"
#include "tetengo2.gui.HandleConcept.h"
#include "tetengo2.gui.PaintObserverConcept.h"


namespace tetengo2 { namespace gui { namespace stub
{
    /*!
        \brief The base class template for a GUI widget for testing.

        \param Handle                A handle type to the native interface. It
                                     must conform to
                                     tetengo2::gui::HandleConcept<Handle>.
        \param Canvas                A canvas type. It must conform to
                                     tetengo2::gui::CanvasConcept<Canvas>.
        \param Alert                 An alerting unary functor type. It must
                                     conform to
                                     boost::UnaryFunctionConcept<Alert, void, Handle, std::exception>.
        \param String                A string type. It must conform to
                                     tetengo2::StringConcept<String>.
        \param Encode                An encoding unary functor type. The types
                                     Encode<String, std::wstring> and
                                     Encode<std::wstring, String> must conform
                                     to
                                     boost::UnaryFunctionConcept<Encode, String, std::wstring>
                                     and
                                     boost::UnaryFunctionConcept<Encode, std::wstring, String>.
        \param PaintObserver         A paint observer type. It must conform to
                                     tetengo2::gui::PaintObserverConcept<PaintObserver>.
    */
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

        BOOST_CLASS_REQUIRE(Handle, tetengo2::gui, HandleConcept);
        BOOST_CLASS_REQUIRE(Canvas, tetengo2::gui, CanvasConcept);
        struct concept_check_Alert
        {
            typedef std::exception exception_type;
            BOOST_CLASS_REQUIRE3(
                Alert,
                void,
                exception_type,
                boost,
                UnaryFunctionConcept
            );
        };
        BOOST_CLASS_REQUIRE(String, tetengo2, StringConcept);
        struct concept_check_Encode
        {
            typedef std::wstring native_string_type;
            typedef Encode<String, std::wstring> encode_from_native_type;
            typedef Encode<std::wstring, String> encode_to_native_type;
            BOOST_CLASS_REQUIRE3(
                encode_from_native_type,
                String,
                native_string_type,
                boost,
                UnaryFunctionConcept
            );
            BOOST_CLASS_REQUIRE3(
                encode_to_native_type,
                native_string_type,
                String,
                boost,
                UnaryFunctionConcept
            );
        };
        BOOST_CLASS_REQUIRE(
            PaintObserver, tetengo2::gui, PaintObserverConcept
        );


    public:
        // types

        //! The handle type.
        typedef Handle handle_type;

        //! The canvas type.
        typedef Canvas canvas_type;

        //! The alerting unary functor type.
        typedef Alert alert_type;

        //! The string type
        typedef String string_type;

        //! The unary functor type for encoding from the native.
        typedef Encode<String, String> encode_from_native_type;

        //! The unary functor type for encoding to the native.
        typedef Encode<String, String> encode_to_native_type;

        //! The paint observer type.
        typedef PaintObserver paint_observer_type;


        // constructors and destructor

        /*!
            \brief Creates a widget.
        */
        widget()
        :
        m_visible(false),
        m_text()
        {}

        /*!
            \brief Destroys the widget.
        */
        virtual ~widget()
        throw ()
        {}


        // functions

        /*!
            \brief Returns the handle.
            
            \return The handle. Always 0.
        */
        virtual handle_type handle()
        const = 0;

        /*!
            \brief Sets the visible status.

            \param visible A visible status.
        */
        virtual void set_visible(const bool visible)
        {
            m_visible = visible;
        }

        /*!
            \brief Returns the visible status.

            \param The visible status.
        */
        virtual bool visible()
        const
        {
            return m_visible;
        }

        /*!
            \brief Sets the text.

            \param text A text.
        */
        virtual void set_text(const string_type& text)
        {
            m_text = text;
        }

        /*!
            \brief Retuns the text.

            \return The text.
        */
        virtual const string_type text()
        const
        {
            return m_text;
        }

        /*!
            \brief Adds a paint observer.

            Do nothing actually.

            \param p_paint_observer An auto pointer to a paint observer.
        */
        void add_paint_observer(
            std::auto_ptr<paint_observer_type> p_paint_observer
        )
        {}


    private:
        // variables

        bool m_visible;

        string_type m_text;


    };


}}}

#endif
