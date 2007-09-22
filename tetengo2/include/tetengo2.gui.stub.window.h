/*! \file
    \brief The definition of tetengo2::gui::stub::window.

    Copyright (C) 2007 kaoru

    $Id$
*/

#if !defined(TETENGO2_GUI_STUB_WINDOW_H)
#define TETENGO2_GUI_STUB_WINDOW_H

#include <memory>

#include <boost/concept_check.hpp>
#include <boost/noncopyable.hpp>

#include "tetengo2.gui.WindowObserverConcept.h"
#include "tetengo2.gui.stub.widget.h"


namespace tetengo2 { namespace gui { namespace stub
{
    /*!
        \brief The class template for a window for testing.
 
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
        \param WindowObserver        A window observer type. It must conform
                                     to
                                     tetengo2::gui::WindowObserverConcept<WindowObserver>.
   */
    template <
        typename Handle,
        typename Canvas,
        typename Alert,
        typename String,
        template <typename Target, typename Source> class Encode,
        typename PaintObserver,
        typename WindowObserver
    >
    class window :
        public widget<
            Handle,
            Canvas,
            Alert,
            String,
            Encode,
            PaintObserver
        >
    {
    private:
        // concept checks

        BOOST_CLASS_REQUIRE(
            WindowObserver, tetengo2::gui, WindowObserverConcept
        );


    public:
        // types

        //! The window observer type.
        typedef WindowObserver window_observer_type;


        // constructors and destructor

        /*!
            \brief Creates a window.
        */
        window()
        {}

        /*!
            \brief Destroys the window.
        */
        virtual ~window()
        throw ()
        {}


        // functions

        // The document will be derived from tetengo2::gui::stub::widget.
        virtual handle_type handle()
        const
        {
            return 0;
        }

        /*!
            \brief Adds a window observer.

            Do nothing actually.

            \param p_window_observer An auto pointer to a window observer.
        */
        void add_window_observer(
            std::auto_ptr<window_observer_type> p_window_observer
        )
        {}


    };


}}}

#endif
