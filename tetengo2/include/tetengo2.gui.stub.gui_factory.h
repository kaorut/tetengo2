/*! \file
    \brief The definition of tetengo2::gui::stub::gui_factory.

    Copyright (C) 2007 kaoru

    $Id$
*/

#if !defined(TETENGO2_GUI_STUB_GUIFACTORY_H)
#define TETENGO2_GUI_STUB_GUIFACTORY_H

#include <string>

#include "tetengo2.gui.gui_factory.h"
#include "tetengo2.gui.paint_observer.h"
#include "tetengo2.gui.window_observer.h"
#include "tetengo2.gui.stub.alert.h"
#include "tetengo2.gui.stub.canvas.h"
#include "tetengo2.gui.stub.gui_initializer_finalizer.h"
#include "tetengo2.gui.stub.window.h"
#include "tetengo2.stub.encode.h"


namespace tetengo2 { namespace gui { namespace stub
{
    namespace
    {
        typedef
            canvas<
                int,
                int,
                std::wstring,
                tetengo2::stub::encode,
                int
            >
            canvas_type;

        typedef alert<int, tetengo2::stub::encode> alert_type;

        typedef
            window<
                int,
                canvas_type,
                alert_type,
                std::wstring,
                tetengo2::stub::encode,
                tetengo2::gui::paint_observer<canvas_type>,
                tetengo2::gui::window_observer
            >
            window_type;


    }

    //! The GUI object factory type for testing.
    typedef
        tetengo2::gui::gui_factory<
            tetengo2::gui::stub::gui_initializer_finalizer,
            window_type
        >
        gui_factory;


}}}

#endif
