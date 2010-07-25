/*! \file
    \brief The definition of bobura::message::type_list.

    Copyright (C) 2007-2010 kaoru

    $Id$
*/

#if !defined(BOBURA_MESSAGE_TYPELISTIMPL_H)
#define BOBURA_MESSAGE_TYPELISTIMPL_H

#include <boost/mpl/pair.hpp>

#include <tetengo2.meta.assoc_list.h>

#include "bobura.message.about_dialog.h"
#include "bobura.message.main_window_observers.h"
#include "bobura.message.type_list.h"


namespace bobura { namespace message
{
    namespace main_window
    {
        /*!
            \brief The meta function for the type list of the main window
                   messages.

            \tparam Command         A command type.
            \tparam Canvas          A canvas type of the main window.
            \tparam QuitMessageLoop A unary functor type for quitting the message
                                    loop.
        */
        template <typename Command, typename Canvas, typename QuitMessageLoop>
        class type_list
        {
        public:
            // types

            //! \return The type list for the main window.
            typedef
                tetengo2::meta::assoc_list<
                    boost::mpl::pair<
                        type::menu_observer,
                        main_window_menu_observer<Command>
                    >,
                tetengo2::meta::assoc_list<
                    boost::mpl::pair<
                        type::paint_observer,
                        main_window_paint_observer<Canvas>
                    >,
                tetengo2::meta::assoc_list<
                    boost::mpl::pair<
                        type::window_observer,
                        main_window_window_observer<QuitMessageLoop>
                    >,
                tetengo2::meta::assoc_list_end
                > > >
                type;
                

        };
    }

    namespace about_dialog
    {
        /*!
            \brief The meta function for the type list of the about dialog
                   messages.

            \tparam Dialog A dialog type.
        */
        template <typename Dialog>
        class type_list
        {
        public:
            // types

            //! \return The type list for the about dialog.
            typedef
                tetengo2::meta::assoc_list<
                    boost::mpl::pair<
                        type::ok_button_mouse_observer,
                        ok_button_mouse_observer<Dialog>
                    >,
                tetengo2::meta::assoc_list_end
                >
                type;
                

        };
    }


}}


#endif
