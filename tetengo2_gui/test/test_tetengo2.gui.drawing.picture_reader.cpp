/*! \file
    \brief Test of class tetengo2::gui::drawing::picture_reader.

    Copyright (C) 2007-2018 kaoru

    $Id$
*/

#include <sstream>
#include <utility>

#include <boost/preprocessor.hpp>
#include <boost/test/unit_test.hpp>

#include <tetengo2/detail/base/gui_impl_set.h>
#include <tetengo2/gui/drawing/picture.h>
#include <tetengo2/gui/drawing/picture_reader.h>
#include <tetengo2/stdalt.h>


namespace {
    // types

    using picture_type = tetengo2::gui::drawing::picture;

    using picture_reader_type = tetengo2::gui::drawing::picture_reader;
}


BOOST_AUTO_TEST_SUITE(test_tetengo2)
    BOOST_AUTO_TEST_SUITE(gui)
        BOOST_AUTO_TEST_SUITE(drawing)
            BOOST_AUTO_TEST_SUITE(picture_reader)
                // test cases

                BOOST_AUTO_TEST_CASE(construction)
                {
                    BOOST_TEST_PASSPOINT();

                    tetengo2::stdalt::filesystem::path path{};
                    const picture_reader_type          reader{ tetengo2::detail::gui_detail_impl_set().drawing_(),
                                                      std::move(path) };
                }

                BOOST_AUTO_TEST_CASE(read)
                {
                    BOOST_TEST_PASSPOINT();

                    tetengo2::stdalt::filesystem::path path{};
                    picture_reader_type reader{ tetengo2::detail::gui_detail_impl_set().drawing_(), std::move(path) };

                    const auto p_picture = reader.read();
                }


            BOOST_AUTO_TEST_SUITE_END()
        BOOST_AUTO_TEST_SUITE_END()
    BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()
