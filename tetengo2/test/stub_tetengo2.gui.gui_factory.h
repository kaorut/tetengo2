/*! \file
    \brief The definition of stub_tetengo2::gui::gui_factory.

    Copyright (C) 2007-2008 kaoru

    $Id$
*/

#if !defined(STUBTETENGO2_GUI_GUIFACTORY_H)
#define STUBTETENGO2_GUI_GUIFACTORY_H

#include <string>

#include "tetengo2.gui.gui_factory.h"
#include "tetengo2.gui.paint_observer.h"
#include "tetengo2.gui.window_observer.h"

#include "stub_tetengo2.gui.alert.h"
#include "stub_tetengo2.gui.canvas.h"
#include "stub_tetengo2.gui.gui_initializer_finalizer.h"
#include "stub_tetengo2.gui.window.h"
#include "stub_tetengo2.encode.h"


namespace stub_tetengo2 { namespace gui
{
    namespace
    {
        typedef
            canvas<
                int,
                int,
                std::wstring,
                stub_tetengo2::encode,
                int
            >
            canvas_type;

        typedef alert<int, stub_tetengo2::encode> alert_type;

        typedef
            window<
                int,
                canvas_type,
                alert_type,
                std::wstring,
                stub_tetengo2::encode,
                tetengo2::gui::paint_observer<canvas_type>,
                tetengo2::gui::window_observer
            >
            window_type;


    }

    typedef
        tetengo2::gui::gui_factory<
            stub_tetengo2::gui::gui_initializer_finalizer,
            window_type
        >
        gui_factory;


}}

#endif
