/*! \file
    \brief The definition of stub_tetengo2::gui::main_menu.

    Copyright (C) 2007-2010 kaoru

    $Id$
*/

#if !defined(STUBTETENGO2_GUI_MAINMENU_H)
#define STUBTETENGO2_GUI_MAINMENU_H

#include <cstddef>


namespace stub_tetengo2 { namespace gui
{
    template <typename Menu>
    class main_menu : public Menu
    {
    public:
        // types

        typedef Menu base_type;

        typedef typename base_type::id_type id_type;

        typedef typename base_type::handle_type handle_type;

        typedef typename base_type::string_type string_type;

        typedef typename base_type::encoder_type encoder_type;

        typedef
            typename base_type::menu_observer_set_type menu_observer_set_type;

        typedef typename base_type::iterator iterator;

        typedef typename base_type::const_iterator const_iterator;

        typedef typename base_type::recursive_iterator recursive_iterator;

        typedef
            typename base_type::const_recursive_iterator
            const_recursive_iterator;


        // constructors and destructor

        main_menu()
        :
        base_type(NULL, string_type())
        {}

        virtual ~main_menu()
        throw ()
        {}


    };


}}

#endif
