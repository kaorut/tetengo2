/*! \file
    \brief Test of class tetengo2::gui::drawing::picture_reader.

    Copyright (C) 2007-2011 kaoru

    $Id$
*/

#include <boost/filesystem.hpp>
#include <boost/scoped_ptr.hpp>
#include <boost/test/unit_test.hpp>

#include "stub_tetengo2.gui.drawing.picture.h"
#include "tetengo2.detail.stub.drawing.h"

#include "tetengo2.gui.drawing.picture_reader.h"


namespace
{
    // types

    typedef stub_tetengo2::gui::drawing::picture<std::size_t> picture_type;

    typedef
        tetengo2::gui::drawing::picture_reader<
            picture_type,
            boost::filesystem::path,
            tetengo2::detail::stub::drawing
        >
        picture_reader_type;


}


BOOST_AUTO_TEST_SUITE(test_tetengo2)
BOOST_AUTO_TEST_SUITE(gui)
BOOST_AUTO_TEST_SUITE(drawing)
BOOST_AUTO_TEST_SUITE(picture_reader)
    // test cases

    BOOST_AUTO_TEST_CASE(construction)
    {
        BOOST_TEST_PASSPOINT();

        const boost::filesystem::path path;
        const picture_reader_type reader(path);
    }

    BOOST_AUTO_TEST_CASE(read)
    {
        BOOST_TEST_PASSPOINT();

        const boost::filesystem::path path;
        picture_reader_type reader(path);

        const boost::scoped_ptr<picture_type> p_picture(reader.read());
    }


BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()
