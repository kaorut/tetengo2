/*! \file
    \brief The definition of tetengo2::gui::GuiFactoryConcept.

    Copyright (C) 2007-2008 kaoru

    $Id$
*/

#if !defined(TETENGO2_GUI_GUIFACTORYCONCEPT_H)
#define TETENGO2_GUI_GUIFACTORYCONCEPT_H

#include <memory>

#include <boost/concept_check.hpp>


namespace tetengo2 { namespace gui
{
    /*!
        \brief The concept check class template for GUI object factories.

        \tparam GuiFactory A GUI object factory type.
    */
    template <typename GuiFactory>
    class GuiFactoryConcept
    {
#if !defined(DOCUMENTATION)
    public:
        // typedef checks

        typedef
            typename GuiFactory::gui_initializer_finalizer_type
            gui_initializer_finalizer_type;

        typedef typename GuiFactory::window_type window_type;


        // usage checks

        BOOST_CONCEPT_USAGE(GuiFactoryConcept)
        {
            std::auto_ptr<const gui_initializer_finalizer_type> p;
            const GuiFactory gui_factory(p);

            const_constraints(m_gui_factory);
        }

        void const_constraints(const GuiFactory& gui_factory)
        {
            const std::auto_ptr<window_type> p_window =
                gui_factory.create_window();
        }

        
    private:
        // variables

        GuiFactory m_gui_factory;


#endif
    };


}}

#endif
