/*! \file
    \brief The definition of stub_tetengo2::gui::window.

    Copyright (C) 2007-2009 kaoru

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

        typedef AbstractWindow abstract_window_type;

        typedef typename abstract_window_type::handle_type handle_type;

        typedef typename abstract_window_type::canvas_type canvas_type;

        typedef typename abstract_window_type::alert_type alert_type;

        typedef
            typename abstract_window_type::difference_type difference_type;

        typedef typename abstract_window_type::size_type size_type;

        typedef typename abstract_window_type::position_type position_type;

        typedef typename abstract_window_type::dimension_type dimension_type;

        typedef typename abstract_window_type::string_type string_type;

        typedef
            typename abstract_window_type::encode_from_native_type
            encode_from_native_type;

        typedef
            typename abstract_window_type::encode_to_native_type
            encode_to_native_type;

        typedef typename abstract_window_type::font_type font_type;

        typedef typename abstract_window_type::child_type child_type;

        typedef
            typename abstract_window_type::paint_observer_type
            paint_observer_type;

        typedef
            typename abstract_window_type::mouse_observer_type
            mouse_observer_type;

        typedef typename abstract_window_type::main_menu_type main_menu_type;

        typedef
            typename abstract_window_type::window_observer_type
            window_observer_type;

        enum style_type
        {
            style_flat,
            style_frame,
            style_dialog,
        };


        // constructors and destructor

        window(const style_type style = style_frame)
        :
        abstract_window_type()
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


    protected:
        // constructors

        window(const window& parent, const style_type style = style_frame)
        :
        abstract_window_type(parent)
        {}


    };


}}

#endif
