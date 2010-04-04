/*! \file
    \brief The definition of stub_tetengo2::gui::window.

    Copyright (C) 2007-2010 kaoru

    $Id$
*/

#if !defined(STUBTETENGO2_GUI_WINDOW_H)
#define STUBTETENGO2_GUI_WINDOW_H

//#include <boost/concept_check.hpp>

#include "concept_tetengo2.gui.AbstractWindow.h"


namespace stub_tetengo2 { namespace gui
{
    template <typename AbstractWindow>
    class window : public AbstractWindow
    {
    private:
        // concept checks

        BOOST_CONCEPT_ASSERT((
            concept_tetengo2::gui::AbstractWindow<AbstractWindow>
        ));


    public:
        // types

        typedef AbstractWindow base_type;

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

        typedef typename base_type::paint_observer_type paint_observer_type;

        typedef typename base_type::mouse_observer_type mouse_observer_type;

        typedef typename base_type::main_menu_type main_menu_type;

        typedef typename base_type::window_observer_type window_observer_type;


        // constructors and destructor

        window()
        :
        base_type()
        {}

        explicit window(const base_type& parent)
        :
        base_type(parent)
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


    };


}}

#endif
