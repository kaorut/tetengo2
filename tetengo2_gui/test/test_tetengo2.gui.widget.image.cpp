/*! \file
    \brief Test of class tetengo2::gui::widget::image.

    Copyright (C) 2007-2017 kaoru

    $Id$
*/

#include <memory>
#include <stdexcept>
#include <utility>

#include <boost/filesystem.hpp>
#include <boost/test/unit_test.hpp>

#include <tetengo2/gui/drawing/picture.h>
#include <tetengo2/gui/drawing/picture_reader.h>
#include <tetengo2/gui/icon.h>
#include <tetengo2/gui/widget/image.h>
#include <tetengo2/gui/widget/window.h>
#include <tetengo2/stdalt.h>

#include "test_tetengo2.gui.detail_type_list.h"
#include "test_tetengo2.gui.type_list.h"


namespace
{
    // types

    using detail_type_list_type = test_tetengo2::gui::type_list::detail_for_test;

    using common_type_list_type = test_tetengo2::gui::type_list::common<detail_type_list_type>;

    using widget_traits_type = common_type_list_type::widget_traits_type;

    using widget_details_traits_type = common_type_list_type::widget_details_traits_type;

    using menu_details_type = detail_type_list_type::menu_type;

    using window_type =
        tetengo2::gui::widget::window<widget_traits_type, widget_details_traits_type, menu_details_type>;

    using drawing_details_type = detail_type_list_type::drawing_type;

    using dimension_type = common_type_list_type::dimension_type;

    using dimension_unit_type = dimension_type::unit_type;

    using picture_type = tetengo2::gui::drawing::picture<dimension_type, drawing_details_type>;

    using picture_reader_type = tetengo2::gui::drawing::picture_reader<dimension_type, drawing_details_type>;

    using icon_type = tetengo2::gui::icon<dimension_type, detail_type_list_type::icon_type>;

    using image_type = tetengo2::gui::widget::image<widget_traits_type, widget_details_traits_type>;


}


BOOST_AUTO_TEST_SUITE(test_tetengo2)
BOOST_AUTO_TEST_SUITE(gui)
BOOST_AUTO_TEST_SUITE(widget)
BOOST_AUTO_TEST_SUITE(image)
    // test cases

    BOOST_AUTO_TEST_CASE(construction)
    {
        BOOST_TEST_PASSPOINT();

        window_type parent{};
        const image_type image{ parent };
    }

    BOOST_AUTO_TEST_CASE(has_picture)
    {
        BOOST_TEST_PASSPOINT();

        window_type parent{};
        image_type image{ parent };

        BOOST_TEST(!image.has_picture());

        picture_reader_type picture_reader{ "image_file" };
        image.set_picture(picture_reader.read());

        BOOST_TEST(image.has_picture());
    }

    BOOST_AUTO_TEST_CASE(picture)
    {
        BOOST_TEST_PASSPOINT();

        window_type parent{};
        image_type image{ parent };
        const auto& const_image = image;

        BOOST_CHECK_THROW(image.picture(), std::logic_error);
        BOOST_CHECK_THROW(const_image.picture(), std::logic_error);

        picture_reader_type picture_reader{ "image_file" };
        image.set_picture(picture_reader.read());
        image.picture();
        const_image.picture();
    }

    BOOST_AUTO_TEST_CASE(set_picture)
    {
        BOOST_TEST_PASSPOINT();

        {
            window_type parent{};
            image_type image{ parent };

            picture_reader_type picture_reader{ "image_file" };
            image.set_picture(picture_reader.read());

            BOOST_TEST(image.has_picture());

            image.set_picture(std::unique_ptr<picture_type>{});

            BOOST_TEST(!image.has_picture());
        }
        {
            window_type parent{};
            image_type image{ parent };

            auto p_icon =
                tetengo2::stdalt::make_unique<icon_type>(boost::filesystem::path{ TETENGO2_TEXT("hoge.ico") });
            image.set_icon(std::move(p_icon));

            picture_reader_type picture_reader{ "image_file" };
            image.set_picture(picture_reader.read());

            BOOST_TEST(image.has_picture());
            BOOST_TEST(!image.has_icon());
        }
    }

    BOOST_AUTO_TEST_CASE(has_icon)
    {
        BOOST_TEST_PASSPOINT();

        window_type parent{};
        image_type image{ parent };

        BOOST_TEST(!image.has_icon());

        auto p_icon = tetengo2::stdalt::make_unique<icon_type>(boost::filesystem::path{ TETENGO2_TEXT("hoge.ico") });
        image.set_icon(std::move(p_icon));

        BOOST_TEST(image.has_icon());
    }

    BOOST_AUTO_TEST_CASE(icon)
    {
        BOOST_TEST_PASSPOINT();

        window_type parent{};
        image_type image{ parent };
        const auto& const_image = image;

        BOOST_CHECK_THROW(image.icon(), std::logic_error);
        BOOST_CHECK_THROW(const_image.icon(), std::logic_error);

        auto p_icon = tetengo2::stdalt::make_unique<icon_type>(boost::filesystem::path{ TETENGO2_TEXT("hoge.ico") });
        image.set_icon(std::move(p_icon));
        image.icon();
        const_image.icon();
    }

    BOOST_AUTO_TEST_CASE(set_icon)
    {
        BOOST_TEST_PASSPOINT();

        {
            window_type parent{};
            image_type image{ parent };

            auto p_icon =
                tetengo2::stdalt::make_unique<icon_type>(boost::filesystem::path{ TETENGO2_TEXT("hoge.ico") });
            image.set_icon(std::move(p_icon));

            BOOST_TEST(image.has_icon());

            image.set_icon(std::unique_ptr<icon_type>{});

            BOOST_TEST(!image.has_icon());
        }
        {
            window_type parent{};
            image_type image{ parent };

            picture_reader_type picture_reader{ "image_file" };
            image.set_picture(picture_reader.read());

            auto p_icon =
                tetengo2::stdalt::make_unique<icon_type>(boost::filesystem::path{ TETENGO2_TEXT("hoge.ico") });
            image.set_icon(std::move(p_icon));

            BOOST_TEST(image.has_icon());
            BOOST_TEST(!image.has_picture());
        }
    }

    BOOST_AUTO_TEST_CASE(fit_to_content)
    {
        BOOST_TEST_PASSPOINT();

        window_type parent{};
        image_type image{ parent };

        {
            picture_reader_type picture_reader{ "image_file" };
            image.set_picture(picture_reader.read());

            image.fit_to_content();

            const auto dimension = image.client_dimension();
            const dimension_type answer_dimension{ dimension_unit_type{ 123 }, dimension_unit_type{ 456 } };
            BOOST_CHECK(dimension == answer_dimension);
        }
        {
            auto p_icon =
                tetengo2::stdalt::make_unique<icon_type>(boost::filesystem::path{ TETENGO2_TEXT("hoge.ico") });
            image.set_icon(std::move(p_icon));

            image.fit_to_content();

            const auto dimension = image.client_dimension();
            const dimension_type answer_dimension{ dimension_unit_type{ 42 }, dimension_unit_type{ 42 } };
            BOOST_CHECK(dimension == answer_dimension);
        }
    }


BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()
