/*! \file
    \brief The definition of stub_tetengo2::gui::abstract_window.

    Copyright (C) 2007-2010 kaoru

    $Id$
*/

#if !defined(STUBTETENGO2_GUI_ABSTRACTWINDOW_H)
#define STUBTETENGO2_GUI_ABSTRACTWINDOW_H

//#include <memory>

//#include <boost/concept_check.hpp>

#include "concept_tetengo2.gui.MainMenu.h"
#include "concept_tetengo2.gui.WindowObserver.h"
#include "concept_tetengo2.gui.Widget.h"


namespace stub_tetengo2 { namespace gui
{
    template <typename Widget, typename MainMenu, typename WindowObserver>
    class abstract_window : public Widget
    {
    private:
        // concept checks

        BOOST_CONCEPT_ASSERT((concept_tetengo2::gui::Widget<Widget>));
        BOOST_CONCEPT_ASSERT((concept_tetengo2::gui::MainMenu<MainMenu>));
        BOOST_CONCEPT_ASSERT((
            concept_tetengo2::gui::WindowObserver<WindowObserver>
        ));


    public:
        // types

        typedef Widget base_type;

        typedef typename base_type::handle_type handle_type;

        typedef typename base_type::canvas_type canvas_type;

        typedef typename base_type::alert_type alert_type;

        typedef typename base_type::difference_type difference_type;

        typedef typename base_type::size_type size_type;

        typedef typename base_type::position_type position_type;

        typedef typename base_type::dimension_type dimension_type;

        typedef typename base_type::string_type string_type;

        typedef
            typename base_type::encode_from_native_type
            encode_from_native_type;

        typedef
            typename base_type::encode_to_native_type encode_to_native_type;

        typedef typename base_type::font_type font_type;

        typedef typename base_type::child_type child_type;

        typedef typename base_type::paint_observer_type paint_observer_type;

        typedef typename base_type::mouse_observer_type mouse_observer_type;

        typedef MainMenu main_menu_type;

        typedef WindowObserver window_observer_type;


        // constructors and destructor

        virtual ~abstract_window()
        throw ()
        {}


        // functions

        virtual void activate()
        {}

        virtual bool has_main_menu()
        const
        {
            return false;
        }

        virtual main_menu_type& main_menu()
        {
            static main_menu_type dummy;
            return dummy;
        }

        virtual void set_main_menu(std::auto_ptr<main_menu_type> p_main_menu)
        {}

        virtual void add_window_observer(
            std::auto_ptr<window_observer_type> p_window_observer
        )
        {}

        virtual void close()
        const
        {}


    protected:
        // constructors

        abstract_window()
        :
        base_type()
        {}

        abstract_window(abstract_window& parent)
        :
        base_type(parent)
        {}


    };


}}

#endif
