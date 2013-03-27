/*! \file
    \brief Test of class tetengo2::gui::widget::image.

    Copyright (C) 2007-2013 kaoru

    $Id$
*/

//#include <memory>
//#include <stdexcept>

//#include <boost/mpl/at.hpp>
#include <boost/test/unit_test.hpp>

#include "test_tetengo2.gui.type_list.h"


namespace
{
    // types

    typedef
        boost::mpl::at<test_tetengo2::gui::widget_type_list, test_tetengo2::gui::type::widget::window>::type
        window_type;

    typedef
        boost::mpl::at<test_tetengo2::gui::drawing_type_list, test_tetengo2::gui::type::drawing::picture>::type
        picture_type;

    typedef
        boost::mpl::at<test_tetengo2::gui::drawing_type_list, test_tetengo2::gui::type::drawing::picture_reader>::type
        picture_reader_type;

    typedef boost::mpl::at<test_tetengo2::gui::type_list, test_tetengo2::gui::type::dimension>::type dimension_type;

    typedef
        boost::mpl::at<test_tetengo2::gui::widget_type_list, test_tetengo2::gui::type::widget::image>::type image_type;


}


BOOST_AUTO_TEST_SUITE(test_tetengo2)
BOOST_AUTO_TEST_SUITE(gui)
BOOST_AUTO_TEST_SUITE(widget)
BOOST_AUTO_TEST_SUITE(image)
    // test cases

    BOOST_AUTO_TEST_CASE(construction)
    {
        BOOST_TEST_PASSPOINT();

        window_type parent;
        const image_type image(parent);
    }

    BOOST_AUTO_TEST_CASE(has_picture)
    {
        BOOST_TEST_PASSPOINT();

        window_type parent;
        image_type image(parent);

        BOOST_CHECK(!image.has_picture());

        picture_reader_type picture_reader("image_file");
        image.set_picture(picture_reader.read());

        BOOST_CHECK(image.has_picture());
    }

    BOOST_AUTO_TEST_CASE(picture)
    {
        BOOST_TEST_PASSPOINT();

        window_type parent;
        image_type image(parent);
        const auto& const_image = image;

        BOOST_CHECK_THROW(image.picture(), std::logic_error);
        BOOST_CHECK_THROW(const_image.picture(), std::logic_error);

        picture_reader_type picture_reader("image_file");
        image.set_picture(picture_reader.read());
        image.picture();
        const_image.picture();

    }

    BOOST_AUTO_TEST_CASE(set_picture)
    {
        BOOST_TEST_PASSPOINT();

        window_type parent;
        image_type image(parent);

        picture_reader_type picture_reader("image_file");
        image.set_picture(picture_reader.read());

        BOOST_CHECK(image.has_picture());

        image.set_picture(std::unique_ptr<picture_type>());

        BOOST_CHECK(!image.has_picture());
    }

    BOOST_AUTO_TEST_CASE(fit_to_content)
    {
        BOOST_TEST_PASSPOINT();

        window_type parent;
        image_type image(parent);
        picture_reader_type picture_reader("image_file");
        image.set_picture(picture_reader.read());

        image.fit_to_content();

        const auto dimension = image.client_dimension();
        const dimension_type answer_dimension(123, 456);
        BOOST_CHECK(dimension == answer_dimension);
    }


BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()
