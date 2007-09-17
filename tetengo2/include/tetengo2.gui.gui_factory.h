/*! \file
    \brief The definition of tetengo2::gui::gui_factory.

    Copyright (C) 2007 kaoru

    $Id$
*/

#if !defined(TETENGO2_GUI_GUIFACTORY_H)
#define TETENGO2_GUI_GUIFACTORY_H

#include <exception>
#include <memory>
#include <stdexcept>

#include <boost/concept_check.hpp>
#include <boost/scoped_ptr.hpp>


namespace tetengo2 { namespace gui
{
    /*!
        \brief The class template for a GUI object factory.

        \param InitializerFinalizer A initalization and finalization manager
                                    type. It must conform to
                                    tetengo2::gui::InitalizerFinalizerConcept.
        \param Canvas               A canvas type. It must conform to
                                    tetengo2::gui::concept::CanvasConcept.
        \param Window               A window type. It must conform to
                                    tetengo2::gui::concept::WindowConcept.
        \param MessageLoop          A message loop type. It must conform to
                                    tetengo2::gui::concept::MessageLoop.
        \param QuitMessageLoop      A unary functor type for quitting the
                                    message loop. It must conform to
                                    boost::AdaptableUnaryFunctionConcept<QuitMessageLoop, void, int>.
        \param Alert                An alerting binary functor type. It must
                                    conform to
                                    boost::AdaptableBinaryFunctionConcept<Alert, void, Window::handle_type, std::exception>.
    */
    template <
        typename InitializerFinalizer,
        typename Canvas,
        typename Window,
        typename MessageLoop,
        typename QuitMessageLoop,
        typename Alert
    >
    class gui_factory : private boost::noncopyable
    {
    private:
        // concept checks

        struct concept_check_Alert
        {
            typedef typename Window::handle_type window_handle_type;
            typedef std::exception exception_type;
            BOOST_CLASS_REQUIRE4(
                Alert,
                void,
                window_handle_type,
                exception_type,
                boost,
                AdaptableBinaryFunctionConcept
            );
        };


    public:
        // types

        //! The initialization and finalization manager type.
        typedef InitializerFinalizer initializer_finalizer_type;

        //! The canvas type.
        typedef Canvas canvas_type;

        //! The window type
        typedef Window window_type;

        //! The message loop type;
        typedef MessageLoop message_loop_type;

        //! The unary functor type for quitting the message loop.
        typedef QuitMessageLoop quit_message_loop_type;

        //! The alerting binary functor type.
        typedef Alert alert_type;


        // constructors and destructor

        /*!
            \brief Creates a GUI object factory.

            \param p_initializer_finalizer An auto pointer to an initalization
                                           and finalization manager.
        */
        gui_factory(
            std::auto_ptr<const initializer_finalizer_type>
            p_initializer_finalizer    
        )
        :
        m_p_initializer_finalizer(p_initializer_finalizer)
        {}

        /*!
            \brief Destroys the GUI object factory.
        */
        ~gui_factory()
        throw ()
        {}


        // functions

        /*!
            \brief Creates a window.

            \return An auto pointer to a window.
        */
        std::auto_ptr<window_type> create_window()
        const
        {
            return std::auto_ptr<window_type>(new window_type());
        }


    private:
        // variables

        const boost::scoped_ptr<const initializer_finalizer_type>
        m_p_initializer_finalizer;


    };


}}

#endif
