/*! \file
    \brief The definition of stub_tetengo2::gui::window.

    Copyright (C) 2007-2009 kaoru

    $Id$
*/

#if !defined(STUBTETENGO2_GUI_WINDOW_H)
#define STUBTETENGO2_GUI_WINDOW_H

//#include <memory>

//#include <boost/concept_check.hpp>

#include "concept_tetengo2.gui.MainMenu.h"
#include "concept_tetengo2.gui.WindowObserver.h"
#include "concept_tetengo2.gui.Widget.h"


namespace stub_tetengo2 { namespace gui
{
    template <typename Widget, typename MainMenu, typename WindowObserver>
    class window : public Widget
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

        typedef Widget widget_type;

        typedef typename widget_type::handle_type handle_type;

        typedef typename widget_type::canvas_type canvas_type;

        typedef typename widget_type::alert_type alert_type;

        typedef typename widget_type::difference_type difference_type;

        typedef typename widget_type::size_type size_type;

        typedef typename widget_type::position_type position_type;

        typedef typename widget_type::dimension_type dimension_type;

        typedef typename widget_type::string_type string_type;

        typedef
            typename widget_type::encode_from_native_type
            encode_from_native_type;

        typedef
            typename widget_type::encode_to_native_type
            encode_to_native_type;

        typedef typename widget_type::child_type child_type;

        typedef
            typename widget_type::paint_observer_type paint_observer_type;

        typedef MainMenu main_menu_type;

        typedef WindowObserver window_observer_type;

        enum style_type
        {
            style_flat,
            style_frame,
            style_dialog,
        };


        // constructors and destructor

        window(const style_type style = style_frame)
        :
        widget_type()
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

        window(const window& parent, const style_type style = style_frame)
        :
        widget_type(parent)
        {}


    };


}}

#endif
