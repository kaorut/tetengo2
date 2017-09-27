/*! \file
    \brief The definition of test_tetengo2::gui::type_list.

    Copyright (C) 2007-2017 kaoru

    $Id$
*/

#if !defined(TESTTETENGO2_GUI_TYPELIST_H)
#define TESTTETENGO2_GUI_TYPELIST_H

#include <cstddef>
#include <string>

#include <boost/rational.hpp>

#include <tetengo2/gui/dimension.h>
#include <tetengo2/gui/position.h>
#include <tetengo2/gui/unit/pixel.h>
#include <tetengo2/gui/widget/widget_details_traits.h>
#include <tetengo2/gui/widget/widget_traits.h>
#include <tetengo2/message/message_catalog.h>
#include <tetengo2/text/encoder.h>
#include <tetengo2/text/encoding/locale.h>

#include "test_tetengo2.gui.detail_type_list.h"


namespace test_tetengo2 { namespace gui { namespace type_list
{
    /**** Common *****************************************************************************************************/

#if !defined(DOCUMENTATION)
    namespace detail { namespace common
    {
        using size_type = std::size_t;

        using difference_type = std::ptrdiff_t;

        using string_type = std::wstring;

        using position_type = tetengo2::gui::position<tetengo2::gui::unit::pixel<boost::rational<difference_type>>>;

        using dimension_type = tetengo2::gui::dimension<tetengo2::gui::unit::pixel<boost::rational<size_type>>>;

        template <typename DetailTypeList>
        using widget_details_type = typename DetailTypeList::widget_type;

        using exception_string_type = std::string;

        template <typename DetailTypeList>
        using internal_encoding_type =
            tetengo2::text::encoding::locale<string_type>;

        template <typename DetailTypeList>
        using ui_encoding_type =
            tetengo2::text::encoding::locale<string_type>;

        template <typename DetailTypeList>
        using ui_encoder_type =
            tetengo2::text::encoder<internal_encoding_type<DetailTypeList>, ui_encoding_type<DetailTypeList>>;

        template <typename DetailTypeList>
        using widget_traits_type =
            tetengo2::gui::widget::widget_traits<
                size_type,
                difference_type,
                string_type,
                position_type,
                dimension_type,
                ui_encoder_type<DetailTypeList>
            >;

        template <typename DetailTypeList>
        using widget_details_traits_type =
            tetengo2::gui::widget::widget_details_traits<
                widget_details_type<DetailTypeList>,
                typename DetailTypeList::drawing_type,
                typename DetailTypeList::icon_type,
                typename DetailTypeList::unit_type,
                typename DetailTypeList::scroll_type,
                typename DetailTypeList::message_handler_type,
                typename DetailTypeList::virtual_key_type
            >;

        using message_catalog_type = tetengo2::message::message_catalog;

    }}
#endif

    /*!
        \brief The common type list.

        \tparam DetailTypeList A detail type list.
    */
    template <typename DetailTypeList>
    struct common
    {
        //! The size type.
        using size_type = detail::common::size_type;

        //! The difference type.
        using difference_type = detail::common::difference_type;

        //! The string_type.
        using string_type = detail::common::string_type;

        //! The position type.
        using position_type = detail::common::position_type;

        //! The dimension type.
        using dimension_type = detail::common::dimension_type;

        //! The UI encoder_type.
        using ui_encoder_type = detail::common::ui_encoder_type<DetailTypeList>;

        //! The widget traits type.
        using widget_traits_type = detail::common::widget_traits_type<DetailTypeList>;

        //! The widget details traits type.
        using widget_details_traits_type = detail::common::widget_details_traits_type<DetailTypeList>;

        //! The message catalog type.
        using message_catalog_type = detail::common::message_catalog_type;

    };

}}}


#endif
