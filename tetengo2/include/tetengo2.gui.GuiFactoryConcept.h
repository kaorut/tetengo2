/*! \file
    \brief The definition of tetengo2::gui::GuiFactoryConcept.

    Copyright (C) 2007-2008 kaoru

    $Id$
*/

#if !defined(TETENGO2_GUI_GUIFACTORYCONCEPT_H)
#define TETENGO2_GUI_GUIFACTORYCONCEPT_H

#include <memory>


namespace tetengo2 { namespace gui
{
    /*!
        \brief The concept check class template for GUI object factories.

        \tparam GuiFactory A GUI object factory type.
    */
    template <typename GuiFactory>
    class GuiFactoryConcept
    {
    public:
        // functions

        /*!
            \brief Checks the constraints on a GUI object factory.
        */
        void constraints()
        {
            typedef
                typename GuiFactory::gui_initializer_finalizer_type
                gui_initializer_finalizer_type;
            typedef typename GuiFactory::window_type window_type;

            std::auto_ptr<const gui_initializer_finalizer_type> p;
            const GuiFactory gui_factory(p);

            const_constraints(*m_p_gui_factory);
        }

        /*!
            \brief Checks the const constraints on a GUI object factory.

            \param gui_factory A constant object.
        */
        void const_constraints(const GuiFactory& gui_factory)
        {
            const std::auto_ptr<typename GuiFactory::window_type> p_window =
                gui_factory.create_window();
        }


    private:
        // variables

        GuiFactory* m_p_gui_factory;


    };


}}

#endif
