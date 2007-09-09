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


namespace tetengo2 { namespace gui
{
    /*!
        \brief The class template for a GUI object factory.

        \param Canvas      A canvas type. It must conform to
                           tetengo2::gui::concept::CanvasConcept.
        \param Window      A window type. It must conform to
                           tetengo2::gui::concept::WindowConcept.
        \param MessageLoop A message loop type. It must conform to
                           tetengo2::gui::concept::MessageLoop.
        \param Alert       An alerting binary functor type. It must conform to
                           boost::AdaptableBinaryFunctionConcept<Alert, void, Window::handle_type, std::exception>.
    */
    template <
        typename Canvas,
        typename Window,
        typename MessageLoop,
        typename Alert
    >
    class gui_factory : private boost::noncopyable
    {
    private:
        // concept checks

        struct concept_check_alert
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

        //! The canvas type.
        typedef Canvas canvas_type;

        //! The window type
        typedef Window window_type;

        //! The message loop type;
        typedef MessageLoop message_loop_type;

        //! The alerting binary functor type.
        typedef Alert alert_type;


        // constructors and destructor

        /*!
            \brief Creates a GUI object factory.
        */
        gui_factory()
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

        /*!
            \brief Creates a message loop.

            \return An auto pointer to a message loop.
        */
        std::auto_ptr<const message_loop_type> create_message_loop()
        const
        {
            return std::auto_ptr<const message_loop_type>(
                new message_loop_type()
            );
        }


    };
}}

#endif
