/*! \file
    \brief The definition of stub_tetengo2::gui::window.

    Copyright (C) 2007-2008 kaoru

    $Id$
*/

#if !defined(STUBTETENGO2_GUI_WINDOW_H)
#define STUBTETENGO2_GUI_WINDOW_H

#include <memory>

#include <boost/concept_check.hpp>

#include "tetengo2.gui.WindowObserverConcept.h"

#include "stub_tetengo2.gui.widget.h"


namespace stub_tetengo2 { namespace gui
{
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

        typedef WindowObserver window_observer_type;


        // constructors and destructor

        window()
        {}

        virtual ~window()
        throw ()
        {}


        // functions

        virtual handle_type handle()
        const
        {
            return 0;
        }

        void add_window_observer(
            std::auto_ptr<window_observer_type> p_window_observer
        )
        {}


    };


}}

#endif
