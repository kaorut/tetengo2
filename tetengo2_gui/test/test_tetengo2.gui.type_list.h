/*! \file
    \brief The definition of test_tetengo2::gui::type_list.

    Copyright (C) 2007-2012 kaoru

    $Id$
*/

#if !defined(TESTTETENGO2_GUI_TYPELIST_H)
#define TESTTETENGO2_GUI_TYPELIST_H

//#include <string>

//#include <boost/mpl/at.hpp>
#include <boost/mpl/pair.hpp>

#include "tetengo2.detail.stub.alert.h"
#include "tetengo2.detail.stub.cursor.h"
#include "tetengo2.detail.stub.encoding.h"
#include "tetengo2.detail.stub.virtual_key.h"
#include "tetengo2.gui.alert.h"
#include "tetengo2.gui.cursor.cursor_base.h"
#include "tetengo2.gui.cursor.system.h"
#include "tetengo2.gui.virtual_key.h"
#include "tetengo2.meta.assoc_list.h"
#include "tetengo2.text.encoder.h"
#include "tetengo2.text.encoding.locale.h"


namespace test_tetengo2 { namespace gui
{
    /**** Common ************************************************************/

    namespace type
    {
        struct string;         //!< The string type.
        struct exception_string; //!< The exception string type.
    }

    //! The common type list.
    typedef
        tetengo2::meta::assoc_list<
            boost::mpl::pair<type::string, std::string>,
        tetengo2::meta::assoc_list<
            boost::mpl::pair<type::exception_string, std::string>,
        tetengo2::meta::assoc_list_end
        >>
        type_list;


    /**** GUI Common ********************************************************/

    namespace type { namespace gui_common
    {
        struct alert;          //!< The alert type.
        struct virtual_key;    //!< The virtual key type.
    }}

#if !defined(DOCUMENTATION)
    namespace detail { namespace gui_common
    {
        typedef tetengo2::detail::stub::encoding encoding_details_type;
        typedef
            tetengo2::text::encoding::locale<
                boost::mpl::at<type_list, type::string>::type,
                encoding_details_type
            >
            internal_encoding_type;
        typedef
            tetengo2::text::encoding::locale<
                boost::mpl::at<type_list, type::string>::type,
                encoding_details_type
            >
            ui_encoding_type;
        typedef
            tetengo2::text::encoder<internal_encoding_type, ui_encoding_type>
            ui_encoder_type;
        typedef
            tetengo2::text::encoding::locale<
                boost::mpl::at<type_list, type::exception_string>::type,
                encoding_details_type
            >
            exception_encoding_type;
        typedef
            tetengo2::text::encoder<
                internal_encoding_type, exception_encoding_type
            >
            exception_encoder_type;
        typedef tetengo2::detail::stub::alert alert_details_type;
        typedef tetengo2::detail::stub::virtual_key virtual_key_details_type;
    }}
#endif

    //! The GUI common type list.
    typedef
        tetengo2::meta::assoc_list<
            boost::mpl::pair<
                type::gui_common::alert,
                tetengo2::gui::alert<
                    detail::gui_common::ui_encoder_type,
                    detail::gui_common::exception_encoder_type,
                    detail::gui_common::alert_details_type
                >
            >,
        tetengo2::meta::assoc_list<
            boost::mpl::pair<
                type::gui_common::virtual_key,
                tetengo2::gui::virtual_key<
                    boost::mpl::at<type_list, type::string>::type,
                    detail::gui_common::virtual_key_details_type
                >
            >,
        tetengo2::meta::assoc_list_end
        >>
        gui_common_type_list;


    /**** Cursor ********************************************************/

    namespace type { namespace cursor
    {
        struct cursor_base;    //!< The cursor base type.
        struct system;         //!< The system cursor type.
    }}

#if !defined(DOCUMENTATION)
    namespace detail { namespace cursor
    {
        typedef tetengo2::detail::stub::cursor cursor_details_type;
    }}
#endif

    //! The cursor type list.
    typedef
        tetengo2::meta::assoc_list<
            boost::mpl::pair<
                type::cursor::cursor_base,
                tetengo2::gui::cursor::cursor_base<
                    detail::cursor::cursor_details_type
                >
            >,
        tetengo2::meta::assoc_list<
            boost::mpl::pair<
                type::cursor::system,
                tetengo2::gui::cursor::system<
                    detail::cursor::cursor_details_type
                >
            >,
        tetengo2::meta::assoc_list_end
        >>
        cursor_type_list;


}}


#endif
