/*! \file
    \brief The definition of stub_tetengo2::gui::abstract_window.

    Copyright (C) 2007-2010 kaoru

    $Id$
*/

#if !defined(STUBTETENGO2_GUI_ABSTRACTWINDOW_H)
#define STUBTETENGO2_GUI_ABSTRACTWINDOW_H

#include <memory>


namespace stub_tetengo2 { namespace gui
{
    template <typename Widget, typename MainMenu, typename WindowObserverSet>
    class abstract_window : public Widget
    {
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

        typedef typename base_type::encoder_type encoder_type;

        typedef typename base_type::font_type font_type;

        typedef typename base_type::child_type child_type;

        typedef
            typename base_type::paint_observer_set_type
            paint_observer_set_type;

        typedef typename base_type::mouse_observer_type mouse_observer_type;

        typedef MainMenu main_menu_type;

        typedef WindowObserverSet window_observer_set_type;


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

        virtual const window_observer_set_type& window_observer_set()
        const
        {
            static const window_observer_set_type dummy;
            return dummy;
        }

        virtual window_observer_set_type& window_observer_set()
        {
            static window_observer_set_type dummy;
            return dummy;
        }

        virtual void close()
        const
        {}


    protected:
        // constructors

        abstract_window()
        :
        base_type()
        {}

        explicit abstract_window(base_type& parent)
        :
        base_type(parent)
        {}


    };


}}

#endif
