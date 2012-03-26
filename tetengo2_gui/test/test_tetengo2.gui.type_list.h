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
#include "tetengo2.detail.stub.drawing.h"
#include "tetengo2.detail.stub.encoding.h"
#include "tetengo2.detail.stub.unit.h"
#include "tetengo2.detail.stub.virtual_key.h"
#include "tetengo2.gui.alert.h"
#include "tetengo2.gui.cursor.cursor_base.h"
#include "tetengo2.gui.cursor.system.h"
#include "tetengo2.gui.drawing.background.h"
#include "tetengo2.gui.drawing.canvas.h"
#include "tetengo2.gui.drawing.color.h"
#include "tetengo2.gui.drawing.font.h"
#include "tetengo2.gui.drawing.picture.h"
#include "tetengo2.gui.drawing.transparent_background.h"
#include "tetengo2.gui.unit.em.h"
#include "tetengo2.gui.unit.pixel.h"
#include "tetengo2.gui.virtual_key.h"
#include "tetengo2.meta.assoc_list.h"
#include "tetengo2.text.encoder.h"
#include "tetengo2.text.encoding.locale.h"


namespace test_tetengo2 { namespace gui
{
    /**** Common ************************************************************/

    namespace type
    {
        struct size;           //!< The size type.
        struct difference;     //!< The difference type.
        struct string;         //!< The string type.
        struct exception_string; //!< The exception string type.
    }

    //! The common type list.
    typedef
        tetengo2::meta::assoc_list<
            boost::mpl::pair<type::size, std::size_t>,
        tetengo2::meta::assoc_list<
            boost::mpl::pair<type::difference, std::ptrdiff_t>,
        tetengo2::meta::assoc_list<
            boost::mpl::pair<type::string, std::string>,
        tetengo2::meta::assoc_list<
            boost::mpl::pair<type::exception_string, std::string>,
        tetengo2::meta::assoc_list_end
        >>>>
        type_list;


    /**** GUI Common ********************************************************/

    namespace type { namespace gui_common
    {
        struct alert;          //!< The alert type.
        struct virtual_key;    //!< The virtual key type.
        struct dimension;      //!< The dimmension type.
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


    /**** Cursor ************************************************************/

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


    /**** Unit **************************************************************/

    namespace type { namespace unit
    {
        struct em;             //!< The em unit type.
        struct pixel;          //!< The pixel unit type.
    }}

#if !defined(DOCUMENTATION)
    namespace detail { namespace unit
    {
        typedef tetengo2::detail::stub::unit unit_details_type;
    }}
#endif

    //! The unit type list.
    typedef
        tetengo2::meta::assoc_list<
            boost::mpl::pair<
                type::unit::em,
                 tetengo2::gui::unit::em<
                    int, int, detail::unit::unit_details_type
                 >
            >,
        tetengo2::meta::assoc_list<
            boost::mpl::pair<
                type::unit::pixel,
                 tetengo2::gui::unit::pixel<int, int>
            >,
        tetengo2::meta::assoc_list_end
        >>
        unit_type_list;


    /**** Drawing ***********************************************************/

    namespace type { namespace drawing
    {
        struct dimension;
        struct canvas_details; //!< The canvas details type.
        struct canvas_details_ptr; //!< The canvas details pointer type.
        struct canvas;         //!< The canvas type.
        struct color;          //!< The color type.
        struct background;     //!< The background type.
        struct transparent_background; //!< The transparent background type.
        struct font;           //!< The font type.
        struct picture;        //!< The picture type.
    }}

#if !defined(DOCUMENTATION)
    namespace detail { namespace drawing
    {
        typedef tetengo2::detail::stub::drawing drawing_details_type;
        typedef
            std::pair<
                boost::mpl::at<type_list, type::size>::type,
                boost::mpl::at<type_list, type::size>::type
            >
            dimension_type;
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
            tetengo2::gui::drawing::transparent_background<
                drawing_details_type
            >
            transparent_background_type;
        typedef
            tetengo2::gui::drawing::font<
                boost::mpl::at<type_list, type::string>::type,
                boost::mpl::at<type_list, type::size>::type,
                drawing_details_type
            >
            font_type;
        typedef
            tetengo2::gui::drawing::picture<
                boost::mpl::at<type_list, type::size>::type,
                drawing_details_type
            >
            picture_type;
        typedef drawing_details_type::canvas_details_type canvas_details_type;
        typedef
            drawing_details_type::canvas_details_ptr_type
            canvas_details_ptr_type;
    }}
#endif

    //! The drawing type list.
    typedef
        tetengo2::meta::assoc_list<
            boost::mpl::pair<
                type::drawing::dimension, detail::drawing::dimension_type
            >,
        tetengo2::meta::assoc_list<
            boost::mpl::pair<
                type::drawing::canvas_details,
                detail::drawing::canvas_details_type
            >,
        tetengo2::meta::assoc_list<
            boost::mpl::pair<
                type::drawing::canvas_details_ptr,
                detail::drawing::canvas_details_ptr_type
            >,
        tetengo2::meta::assoc_list<
            boost::mpl::pair<
                type::drawing::canvas,
                tetengo2::gui::drawing::canvas<
                    boost::mpl::at<type_list, type::size>::type,
                    boost::mpl::at<type_list, type::string>::type,
                    detail::drawing::dimension_type,
                    detail::drawing::ui_encoder_type,
                    detail::drawing::transparent_background_type,
                    detail::drawing::font_type,
                    detail::drawing::picture_type,
                    detail::drawing::drawing_details_type
                >
            >,
        tetengo2::meta::assoc_list<
            boost::mpl::pair<
                type::drawing::color,
                tetengo2::gui::drawing::color<unsigned char>
            >,
        tetengo2::meta::assoc_list<
            boost::mpl::pair<
                type::drawing::background,
                tetengo2::gui::drawing::background<
                    detail::drawing::drawing_details_type
                >
            >,
        tetengo2::meta::assoc_list<
            boost::mpl::pair<
                type::drawing::transparent_background,
                detail::drawing::transparent_background_type
            >,
        tetengo2::meta::assoc_list<
            boost::mpl::pair<
                type::drawing::font, detail::drawing::font_type
            >,
        tetengo2::meta::assoc_list<
            boost::mpl::pair<
                type::drawing::picture, detail::drawing::picture_type
            >,
        tetengo2::meta::assoc_list_end
        >>>>>>>>>
        drawing_type_list;


}}


#endif
