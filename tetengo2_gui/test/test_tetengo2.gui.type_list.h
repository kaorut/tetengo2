/*! \file
    \brief The definition of test_tetengo2::gui::type_list.

    Copyright (C) 2007-2018 kaoru

    $Id$
*/

#if !defined(TESTTETENGO2_GUI_TYPELIST_H)
#define TESTTETENGO2_GUI_TYPELIST_H

#include <cstddef>
#include <string>

#include <tetengo2/gui/dimension.h>
#include <tetengo2/gui/position.h>
#include <tetengo2/gui/widget/widget_details_traits.h>
#include <tetengo2/message/message_catalog.h>


namespace test_tetengo2::gui::type_list {
/**** Common *****************************************************************************************************/

#if !defined(DOCUMENTATION)
    namespace detail::common {
        using size_type = std::size_t;

        using difference_type = std::ptrdiff_t;

        using string_type = std::wstring;

        using position_type = tetengo2::gui::em_position;

        using dimension_type = tetengo2::gui::em_dimension;

        template <typename DetailTypeList>
        using widget_details_type = typename DetailTypeList::widget_type;

        using exception_string_type = std::string;

        template <typename DetailTypeList>
        using widget_details_traits_type = tetengo2::gui::widget::widget_details_traits<
            widget_details_type<DetailTypeList>,
            typename DetailTypeList::drawing_type,
            typename DetailTypeList::icon_type,
            typename DetailTypeList::scroll_type,
            typename DetailTypeList::message_handler_type>;

        using message_catalog_type = tetengo2::message::message_catalog;
    }
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

        //! The widget details traits type.
        using widget_details_traits_type = detail::common::widget_details_traits_type<DetailTypeList>;

        //! The message catalog type.
        using message_catalog_type = detail::common::message_catalog_type;
    };
}


#endif
