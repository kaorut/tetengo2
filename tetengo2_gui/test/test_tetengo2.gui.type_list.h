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

#include <boost/mpl/at.hpp>
#include <boost/mpl/pair.hpp>

#include <tetengo2.h>
#include <tetengo2.gui.h>

#include "test_tetengo2.gui.detail_type_list.h"


namespace test_tetengo2 { namespace gui
{
    namespace type
    {
        struct size;           //!< The size type.
        struct difference;     //!< The difference type.
        struct position;       //!< The position type.
        struct dimension;      //!< The dimension type.
        struct string;         //!< The string type.
        struct ui_encoder;     //!< The UI encoder type.
        struct exception_encoder; //!< The exception encoder type.
        struct widget_traits;  //!< The widget traits type.
        struct widget_details_traits; //!< The widget details traits type.
    }

#if !defined(DOCUMENTATION)
    namespace detail
    {
        using size_type = std::size_t;

        using difference_type = std::ptrdiff_t;

        using position_type =
            std::pair<tetengo2::gui::unit::pixel<difference_type>, tetengo2::gui::unit::pixel<difference_type>>;

        using dimension_type = std::pair<tetengo2::gui::unit::pixel<size_type>, tetengo2::gui::unit::pixel<size_type>>;

        using string_type = std::string;

        template <typename DetailTypeList>
        using widget_details_type = typename boost::mpl::at<DetailTypeList, type::detail::widget>::type;

        using exception_string_type = std::string;

        template <typename DetailTypeList>
        using encoding_details_type = typename boost::mpl::at<DetailTypeList, type::detail::encoding>::type;

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
                typename boost::mpl::at<DetailTypeList, type::detail::drawing>::type,
                typename boost::mpl::at<DetailTypeList, type::detail::icon>::type,
                typename boost::mpl::at<DetailTypeList, type::detail::alert>::type,
                typename boost::mpl::at<DetailTypeList, type::detail::cursor>::type,
                typename boost::mpl::at<DetailTypeList, type::detail::scroll>::type,
                typename boost::mpl::at<DetailTypeList, type::detail::message_handler>::type,
                typename boost::mpl::at<DetailTypeList, type::detail::virtual_key>::type
            >;

    }
#endif

    //! The type list.
    template <typename DetailTypeList>
    using type_list =
        tetengo2::meta::assoc_list<boost::mpl::pair<type::size, detail::size_type>,
        tetengo2::meta::assoc_list<boost::mpl::pair<type::difference, detail::difference_type>,
        tetengo2::meta::assoc_list<boost::mpl::pair<type::position, detail::position_type>,
        tetengo2::meta::assoc_list<boost::mpl::pair<type::dimension, detail::dimension_type>,
        tetengo2::meta::assoc_list<boost::mpl::pair<type::string, detail::string_type>,
        tetengo2::meta::assoc_list<boost::mpl::pair<type::ui_encoder, detail::ui_encoder_type<DetailTypeList>>,
        tetengo2::meta::assoc_list<boost::mpl::pair<type::exception_encoder, detail::exception_encoder_type<DetailTypeList>>,
        tetengo2::meta::assoc_list<boost::mpl::pair<type::widget_traits, detail::widget_traits_type<DetailTypeList>>,
        tetengo2::meta::assoc_list<boost::mpl::pair<type::widget_details_traits, detail::widget_details_traits_type<DetailTypeList>>,
        tetengo2::meta::assoc_list_end
        >>>>>>>>>;


}}


#endif
