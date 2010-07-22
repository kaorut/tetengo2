/*! \file
    \brief The definition of stub_tetengo2::gui::menu_separator.

    Copyright (C) 2007-2010 kaoru

    $Id$
*/

#if !defined(STUBTETENGO2_GUI_MENUSEPARATOR_H)
#define STUBTETENGO2_GUI_MENUSEPARATOR_H

#include <cstddef>


namespace stub_tetengo2 { namespace gui
{
    template <typename Menu>
    class menu_separator : public Menu
    {
    private:
    public:
        // types

        typedef Menu base_type;

        typedef typename base_type::id_type id_type;

        typedef typename base_type::handle_type handle_type;

        typedef typename base_type::string_type string_type;

        typedef typename base_type::encoder_type encoder_type;

        typedef typename base_type::menu_observer_type menu_observer_type;

        typedef typename base_type::iterator iterator;

        typedef typename base_type::const_iterator const_iterator;


        // constructors and destructor

        menu_separator()
        :
        base_type(string_type())
        {}

        virtual ~menu_separator()
        throw ()
        {}


    };


}}

#endif
