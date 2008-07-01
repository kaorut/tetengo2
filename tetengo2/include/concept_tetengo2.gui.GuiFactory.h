/*! \file
    \brief The definition of concept_tetengo2::gui::GuiFactory.

    Copyright (C) 2007-2008 kaoru

    $Id$
*/

#if !defined(CONCEPTTETENGO2_GUI_GUIFACTORY_H)
#define CONCEPTTETENGO2_GUI_GUIFACTORY_H

#include <memory>

#include <boost/concept_check.hpp>


namespace concept_tetengo2 { namespace gui
{
    /*!
        \brief The concept check class template for a GUI object factory.

        \tparam Type A type.
    */
    template <typename Type>
    class GuiFactory
    {
#if !defined(DOCUMENTATION)
    public:
        // typedef checks

        typedef
            typename Type::gui_initializer_finalizer_type
            gui_initializer_finalizer_type;

        typedef typename Type::window_type window_type;


        // usage checks

        BOOST_CONCEPT_USAGE(GuiFactory)
        {
            std::auto_ptr<const gui_initializer_finalizer_type> p;
            const Type object(p);

            const_constraints(m_object);
        }

        void const_constraints(const Type& object)
        {
            const std::auto_ptr<window_type> p_window =
                object.create_window();
        }

        
    private:
        // variables

        Type m_object;


#endif
    };


}}

#endif
