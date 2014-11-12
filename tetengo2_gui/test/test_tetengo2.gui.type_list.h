/*! \file
    \brief The definition of test_tetengo2::gui::type_list.

    Copyright (C) 2007-2014 kaoru

    $Id$
*/

#if !defined(TESTTETENGO2_GUI_TYPELIST_H)
#define TESTTETENGO2_GUI_TYPELIST_H

#include <cstddef>
#include <string>
#include <utility>

#include <tetengo2.h>
#include <tetengo2.gui.h>

#include "test_tetengo2.gui.detail_type_list.h"


namespace test_tetengo2 { namespace gui { namespace type_list
{
    /**** Common *****************************************************************************************************/

#if !defined(DOCUMENTATION)
    namespace detail { namespace common
    {
        using size_type = std::size_t;

        using difference_type = std::ptrdiff_t;

        using string_type = std::string;

        using position_type =
            std::pair<tetengo2::gui::unit::pixel<difference_type>, tetengo2::gui::unit::pixel<difference_type>>;

        using dimension_type = std::pair<tetengo2::gui::unit::pixel<size_type>, tetengo2::gui::unit::pixel<size_type>>;

        template <typename DetailTypeList>
        using widget_details_type = typename DetailTypeList::widget_type;

        using exception_string_type = std::string;

        template <typename DetailTypeList>
        using encoding_details_type = typename DetailTypeList::encoding_type;

        template <typename DetailTypeList>
        using internal_encoding_type =
            tetengo2::text::encoding::locale<string_type, encoding_details_type<DetailTypeList>>;

        template <typename DetailTypeList>
        using ui_encoding_type =
            tetengo2::text::encoding::locale<string_type, encoding_details_type<DetailTypeList>>;

        template <typename DetailTypeList>
        using ui_encoder_type =
            tetengo2::text::encoder<internal_encoding_type<DetailTypeList>, ui_encoding_type<DetailTypeList>>;

        template <typename DetailTypeList>
        using exception_encoding_type =
            tetengo2::text::encoding::locale<exception_string_type, encoding_details_type<DetailTypeList>>;

        template <typename DetailTypeList>
        using exception_encoder_type =
            tetengo2::text::encoder<internal_encoding_type<DetailTypeList>, exception_encoding_type<DetailTypeList>>;

        template <typename DetailTypeList>
        using widget_traits_type =
            tetengo2::gui::widget::widget_traits<
                size_type,
                size_type,
                difference_type,
                string_type,
                position_type,
                dimension_type,
                ui_encoder_type<DetailTypeList>,
                exception_encoder_type<DetailTypeList>
            >;

        template <typename DetailTypeList>
        using widget_details_traits_type =
            tetengo2::gui::widget::widget_details_traits<
                widget_details_type<DetailTypeList>,
                typename DetailTypeList::drawing_type,
                typename DetailTypeList::icon_type,
                typename DetailTypeList::alert_type,
                typename DetailTypeList::cursor_type,
                typename DetailTypeList::scroll_type,
                typename DetailTypeList::message_handler_type,
                typename DetailTypeList::virtual_key_type
            >;

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

        //! The exception encoder type.
        using exception_encoder_type = detail::common::exception_encoder_type<DetailTypeList>;

        //! The widget traits type.
        using widget_traits_type = detail::common::widget_traits_type<DetailTypeList>;

        //! The widget details traits type.
        using widget_details_traits_type = detail::common::widget_details_traits_type<DetailTypeList>;

    };

}}}


#endif
