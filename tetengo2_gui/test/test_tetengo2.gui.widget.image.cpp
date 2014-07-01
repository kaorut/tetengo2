/*! \file
    \brief Test of class tetengo2::gui::widget::image.

    Copyright (C) 2007-2014 kaoru

    $Id$
*/

#include <memory>
#include <stdexcept>
#include <utility>

#include <boost/mpl/at.hpp>
#include <boost/test/unit_test.hpp>

#include <tetengo2.h>
#include <tetengo2.gui.h>

#include "test_tetengo2.gui.type_list.h"


namespace
{
    // types

    using window_type =
        boost::mpl::at<test_tetengo2::gui::widget_type_list, test_tetengo2::gui::type::widget::window>::type;

    using picture_type =
        boost::mpl::at<test_tetengo2::gui::drawing_type_list, test_tetengo2::gui::type::drawing::picture>::type;

    using picture_reader_type =
        boost::mpl::at<test_tetengo2::gui::drawing_type_list, test_tetengo2::gui::type::drawing::picture_reader>::type;

    using icon_type =
        tetengo2::gui::icon<
            boost::mpl::at<test_tetengo2::gui::type_list, test_tetengo2::gui::type::path>::type,
            boost::mpl::at<test_tetengo2::gui::type_list, test_tetengo2::gui::type::dimension>::type,
            boost::mpl::at<test_tetengo2::gui::detail_type_list, test_tetengo2::gui::type::detail::icon>::type
        >;

    using path_type = boost::mpl::at<test_tetengo2::gui::type_list, test_tetengo2::gui::type::path>::type;

    using dimension_type = boost::mpl::at<test_tetengo2::gui::type_list, test_tetengo2::gui::type::dimension>::type;

    using width_type = tetengo2::gui::dimension<dimension_type>::width_type;

    using height_type = tetengo2::gui::dimension<dimension_type>::height_type;

    using image_type =
        boost::mpl::at<test_tetengo2::gui::widget_type_list, test_tetengo2::gui::type::widget::image>::type;


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

        BOOST_CHECK(!image.has_picture());

        picture_reader_type picture_reader{ "image_file" };
        image.set_picture(picture_reader.read());

        BOOST_CHECK(image.has_picture());
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

            BOOST_CHECK(image.has_picture());

            image.set_picture(std::unique_ptr<picture_type>{});

            BOOST_CHECK(!image.has_picture());
        }
        {
            window_type parent{};
            image_type image{ parent };

            auto p_icon = tetengo2::stdalt::make_unique<icon_type>(path_type{ TETENGO2_TEXT("hoge.ico") });
            image.set_icon(std::move(p_icon));

            picture_reader_type picture_reader{ "image_file" };
            image.set_picture(picture_reader.read());

            BOOST_CHECK(image.has_picture());
            BOOST_CHECK(!image.has_icon());
        }
    }

    BOOST_AUTO_TEST_CASE(has_icon)
    {
        BOOST_TEST_PASSPOINT();

        window_type parent{};
        image_type image{ parent };

        BOOST_CHECK(!image.has_icon());

        auto p_icon = tetengo2::stdalt::make_unique<icon_type>(path_type{ TETENGO2_TEXT("hoge.ico") });
        image.set_icon(std::move(p_icon));

        BOOST_CHECK(image.has_icon());
    }

    BOOST_AUTO_TEST_CASE(icon)
    {
        BOOST_TEST_PASSPOINT();

        window_type parent{};
        image_type image{ parent };
        const auto& const_image = image;

        BOOST_CHECK_THROW(image.icon(), std::logic_error);
        BOOST_CHECK_THROW(const_image.icon(), std::logic_error);

        auto p_icon = tetengo2::stdalt::make_unique<icon_type>(path_type{ TETENGO2_TEXT("hoge.ico") });
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

            auto p_icon = tetengo2::stdalt::make_unique<icon_type>(path_type{ TETENGO2_TEXT("hoge.ico") });
            image.set_icon(std::move(p_icon));

            BOOST_CHECK(image.has_icon());

            image.set_icon(std::unique_ptr<icon_type>{});

            BOOST_CHECK(!image.has_icon());
        }
        {
            window_type parent{};
            image_type image{ parent };

            picture_reader_type picture_reader{ "image_file" };
            image.set_picture(picture_reader.read());

            auto p_icon = tetengo2::stdalt::make_unique<icon_type>(path_type{ TETENGO2_TEXT("hoge.ico") });
            image.set_icon(std::move(p_icon));

            BOOST_CHECK(image.has_icon());
            BOOST_CHECK(!image.has_picture());
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
            const dimension_type answer_dimension{ width_type{ 123 }, height_type{ 456 } };
            BOOST_CHECK(dimension == answer_dimension);
        }
        {
            auto p_icon = tetengo2::stdalt::make_unique<icon_type>(path_type{ TETENGO2_TEXT("hoge.ico") });
            image.set_icon(std::move(p_icon));

            image.fit_to_content();

            const auto dimension = image.client_dimension();
            const dimension_type answer_dimension{ width_type{ 42 }, height_type{ 42 } };
            BOOST_CHECK(dimension == answer_dimension);
        }
    }


BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()
