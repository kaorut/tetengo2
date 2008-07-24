/*! \file
    \brief The definition of concept_tetengo2::gui::MainMenu.

    Copyright (C) 2007-2008 kaoru

    $Id$
*/

#if !defined(CONCEPTTETENGO2_GUI_MAINMENU_H)
#define CONCEPTTETENGO2_GUI_MAINMENU_H

//#include <boost/concept_check.hpp>


namespace concept_tetengo2 { namespace gui
{
    /*!
        \brief The concept check class template for a main menu.

        \tparam Type A type.
    */
    template <typename Type>
    class MainMenu : private boost::DefaultConstructible<Type>
    {
#if !defined(DOCUMENTATION)
    public:
        // typedef checks

        typedef typename Type::handle_type handle_type;


        // usage checks

        BOOST_CONCEPT_USAGE(MainMenu)
        {
            const_constraints(m_object);
        }

        void const_constraints(const Type& object)
        {
            const handle_type handle = object.handle();
            boost::ignore_unused_variable_warning(handle);
        }

        
    private:
        // variables

        Type m_object;


#endif
    };


}}

#endif
