/*! \file
    \brief The definition of stub_tetengo2::gui::window.

    Copyright (C) 2007-2008 kaoru

    $Id$
*/

#if !defined(STUBTETENGO2_GUI_WINDOW_H)
#define STUBTETENGO2_GUI_WINDOW_H

//#include <memory>

//#include <boost/concept_check.hpp>

#include "concept_tetengo2.gui.Menu.h"
#include "concept_tetengo2.gui.WindowObserver.h"

#include "stub_tetengo2.gui.widget.h"


namespace stub_tetengo2 { namespace gui
{
    template <
        typename Handle,
        typename Canvas,
        typename Alert,
        typename String,
        template <typename Target, typename Source> class Encode,
        typename MainMenu,
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

        BOOST_CONCEPT_ASSERT((concept_tetengo2::gui::Menu<MainMenu>));
        BOOST_CONCEPT_ASSERT((
            concept_tetengo2::gui::WindowObserver<WindowObserver>
        ));


    public:
        // types

        typedef MainMenu main_menu_type;

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

        bool has_main_menu()
        const
        {
            return false;
        }

        main_menu_type& main_menu()
        {
            static main_menu_type dummy;
            return dummy;
        }

        void set_main_menu(std::auto_ptr<main_menu_type> p_main_menu)
        {}

        void add_window_observer(
            std::auto_ptr<window_observer_type> p_window_observer
        )
        {}


    };


}}

#endif
