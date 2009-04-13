/*! \file
    \brief The definition of stub_tetengo2::gui::win32::dialog.

    Copyright (C) 2007-2009 kaoru

    $Id$
*/

#if !defined(STUBTETENGO2_GUI_DIALOG_H)
#define STUBTETENGO2_GUI_DIALOG_H

//#include <boost/concept_check.hpp>

#include "concept_tetengo2.gui.AbstractWindow.h"


namespace stub_tetengo2 { namespace gui
{
    template <
        typename AbstractWindow,
        typename MessageLoop,
        typename QuitMessageLoop
    >
    class dialog : public AbstractWindow
    {
    private:
        // concept checks

        BOOST_CONCEPT_ASSERT((
            concept_tetengo2::gui::AbstractWindow<AbstractWindow>
        ));
        BOOST_CONCEPT_ASSERT((boost::Generator<MessageLoop, int>));
        BOOST_CONCEPT_ASSERT((
            boost::UnaryFunction<QuitMessageLoop, void, int>
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

        typedef MessageLoop message_loop_type;

        typedef QuitMessageLoop quit_message_loop_type;


        // constructors and destructor

        dialog(
            const abstract_window_type& parent,
            const style_type            style = style_dialog
        )
        :
        abstract_window_type(parent)
        {}

        virtual ~dialog()
        throw ()
        {}


        // functions

        virtual handle_type handle()
        const
        {
            return 0;
        }

        void do_modal()
        {}


    };


}}

#endif
