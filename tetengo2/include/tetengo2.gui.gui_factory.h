/*! \file
    \brief The definition of tetengo2::gui::gui_factory.

    Copyright (C) 2007-2008 kaoru

    $Id$
*/

#if !defined(TETENGO2_GUI_GUIFACTORY_H)
#define TETENGO2_GUI_GUIFACTORY_H

//#include <memory>

//#include <boost/concept_check.hpp>
#include <boost/noncopyable.hpp>
#include <boost/scoped_ptr.hpp>

#include "concept_tetengo2.gui.Window.h"


namespace tetengo2 { namespace gui
{
    /*!
        \brief The class template for a GUI object factory.

        \tparam GuiInitializerFinalizer A initalization and finalization
                                        manager type.
        \tparam Window                  A window type. It must conform to
                                        concept_tetengo2::gui::Window<Window>.
    */
    template <
        typename GuiInitializerFinalizer,
        typename Window
    >
    class gui_factory : private boost::noncopyable
    {
    private:
        // concept checks

        BOOST_CONCEPT_ASSERT((concept_tetengo2::gui::Window<Window>));


    public:
        // types

        //! The GUI initialization and finalization manager type.
        typedef GuiInitializerFinalizer gui_initializer_finalizer_type;

        //! The window type
        typedef Window window_type;


        // constructors and destructor

        /*!
            \brief Creates a GUI object factory.

            \param p_gui_initializer_finalizer An auto pointer to a GUI
                                               initalization and finalization
                                               manager.
        */
        explicit gui_factory(
            std::auto_ptr<const gui_initializer_finalizer_type>
            p_gui_initializer_finalizer    
        )
        :
        m_p_gui_initializer_finalizer(p_gui_initializer_finalizer)
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

        const boost::scoped_ptr<const gui_initializer_finalizer_type>
        m_p_gui_initializer_finalizer;


    };


}}

#endif
