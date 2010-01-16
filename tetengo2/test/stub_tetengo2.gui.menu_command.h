/*! \file
    \brief The definition of stub_tetengo2::gui::menu_command.

    Copyright (C) 2007-2010 kaoru

    $Id$
*/

#if !defined(STUBTETENGO2_GUI_MENUCOMMAND_H)
#define STUBTETENGO2_GUI_MENUCOMMAND_H

#include <cstddef>

//#include <boost/concept_check.hpp>

#include "concept_tetengo2.gui.Menu.h"


namespace stub_tetengo2 { namespace gui
{
    template <typename Menu>
    class menu_command : public Menu
    {
    private:
        // concept checks

        BOOST_CONCEPT_ASSERT((concept_tetengo2::gui::Menu<Menu>));


    public:
        // types

        typedef Menu base_type;

        typedef typename base_type::id_type id_type;

        typedef typename base_type::handle_type handle_type;

        typedef typename base_type::string_type string_type;

        typedef
            typename base_type::encode_from_native_type
            encode_from_native_type;

        typedef
            typename base_type::encode_to_native_type encode_to_native_type;

        typedef typename base_type::menu_observer_type menu_observer_type;

        typedef typename base_type::iterator iterator;

        typedef typename base_type::const_iterator const_iterator;


        // constructors and destructor

        explicit menu_command(const string_type& text)
        :
        base_type(NULL, text)
        {}

        virtual ~menu_command()
        throw ()
        {}


    };


}}

#endif
