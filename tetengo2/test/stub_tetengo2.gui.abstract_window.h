/*! \file
    \brief The definition of stub_tetengo2::gui::abstract_window.

    Copyright (C) 2007-2011 kaoru

    $Id$
*/

#if !defined(STUBTETENGO2_GUI_ABSTRACTWINDOW_H)
#define STUBTETENGO2_GUI_ABSTRACTWINDOW_H

//#include <memory>

#include "stub_tetengo2.gui.widget.h"
#include "tetengo2.cpp0x_keyword.h"


namespace stub_tetengo2 { namespace gui
{
    template <typename Traits>
    class abstract_window : public widget<typename Traits::base_type>
    {
    public:
        // types

        typedef Traits traits_type;

        typedef widget<typename traits_type::base_type> base_type;

        typedef typename traits_type::main_menu_type main_menu_type;

        typedef
            typename traits_type::window_observer_set_type
            window_observer_set_type;


        // constructors and destructor

        virtual ~abstract_window()
        TETENGO2_CPP0X_NOEXCEPT
        {}


        // functions

        void activate()
        {}

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

        const window_observer_set_type& window_observer_set()
        const
        {
            static const window_observer_set_type dummy;
            return dummy;
        }

        window_observer_set_type& window_observer_set()
        {
            static window_observer_set_type dummy;
            return dummy;
        }

        void close()
        const
        {}


    protected:
        // constructors

        abstract_window()
        :
        base_type()
        {}


    };


}}

#endif
