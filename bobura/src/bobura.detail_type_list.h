/*! \file
    \brief The definition of bobura::detail_type_list.

    Copyright (C) 2007-2012 kaoru

    $Id$
*/

#if !defined(BOBURA_DETAILTYPELIST_H)
#define BOBURA_DETAILTYPELIST_H

#include <tetengo2.detail.windows.alert.h>
#include <tetengo2.detail.windows.common_dialog.h>
#include <tetengo2.detail.windows.cursor.h>
#include <tetengo2.detail.windows.encoding.h>
#include <tetengo2.detail.windows.gdiplus.drawing.h>
#include <tetengo2.detail.windows.gdiplus.gui_fixture.h>
#include <tetengo2.detail.windows.gui_fixture.h>
#include <tetengo2.detail.windows.menu.h>
#include <tetengo2.detail.windows.message_handler.h>
#include <tetengo2.detail.windows.message_loop.h>
#include <tetengo2.detail.windows.unit.h>
#include <tetengo2.detail.windows.virtual_key.h>
#include <tetengo2.detail.windows.widget.h>


namespace bobura
{
    /**** Detail Implementation *********************************************/

    namespace type { namespace detail
    {
        //struct difference;     //!< The difference type.
    }}

#if !defined(DOCUMENTATION)
    namespace detail { namespace detail
    {
        //typedef std::ptrdiff_t difference_type;
    }}
#endif

    //! The common type list.
    //typedef
    //    tetengo2::meta::assoc_list<
    //        boost::mpl::pair<type::difference, detail::difference_type>,
    //    tetengo2::meta::assoc_list_end
    //    >
    //    detail_type_list;


}


#endif
