/*! \file
    \brief The definition of stub_tetengo2::gui::win32::dialog.

    Copyright (C) 2007-2010 kaoru

    $Id$
*/

#if !defined(STUBTETENGO2_GUI_DIALOG_H)
#define STUBTETENGO2_GUI_DIALOG_H //!< !! Include Guard !!

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

        typedef MessageLoop message_loop_type;

        typedef QuitMessageLoop quit_message_loop_type;

        enum result_type
        {
            result_undecided,
            result_accepted,
            result_canceled,
        };


        // constructors and destructor

        dialog(base_type& parent)
        :
        base_type(parent)
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

        virtual void set_result(const result_type result)
        {}

        virtual result_type result()
        const
        {
            return result_undecided;
        }

        virtual result_type do_modal()
        {
            return result_canceled;
        }


    };


}}

#endif
