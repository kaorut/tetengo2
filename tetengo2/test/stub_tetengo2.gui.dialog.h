/*! \file
    \brief The definition of stub_tetengo2::gui::win32::dialog.

    Copyright (C) 2007-2009 kaoru

    $Id$
*/

#if !defined(STUBTETENGO2_GUI_DIALOG_H)
#define STUBTETENGO2_GUI_DIALOG_H

//#include <boost/concept_check.hpp>

#include "concept_tetengo2.gui.Window.h"


namespace stub_tetengo2 { namespace gui
{
    template <typename Window, typename MessageLoop, typename QuitMessageLoop>
    class dialog : public Window
    {
    private:
        // concept checks

        BOOST_CONCEPT_ASSERT((concept_tetengo2::gui::Window<Window>));
        BOOST_CONCEPT_ASSERT((boost::Generator<MessageLoop, int>));
        BOOST_CONCEPT_ASSERT((
            boost::UnaryFunction<QuitMessageLoop, void, int>
        ));


    public:
        // types

        typedef Window window_type;

        typedef typename window_type::handle_type handle_type;

        typedef typename window_type::canvas_type canvas_type;

        typedef typename window_type::alert_type alert_type;

        typedef typename window_type::difference_type difference_type;

        typedef typename window_type::size_type size_type;

        typedef typename window_type::position_type position_type;

        typedef typename window_type::dimension_type dimension_type;

        typedef typename window_type::string_type string_type;

        typedef
            typename window_type::encode_from_native_type
            encode_from_native_type;

        typedef
            typename window_type::encode_to_native_type
            encode_to_native_type;

        typedef
            typename window_type::paint_observer_type paint_observer_type;

        typedef typename window_type::main_menu_type main_menu_type;

        typedef
            typename window_type::window_observer_type window_observer_type;

        typedef typename window_type::style_type style_type;

        typedef MessageLoop message_loop_type;

        typedef QuitMessageLoop quit_message_loop_type;


        // constructors and destructor

        dialog(
            const window_type& parent,
            const style_type   style = style_dialog
        )
        :
        window_type(parent, style)
        {}

        virtual ~dialog()
        throw ()
        {}


        // functions

        void do_modal()
        {}


    };


}}

#endif
