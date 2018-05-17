/*! \file
    \brief Test of class tetengo2::gui::icon.

    Copyright (C) 2007-2018 kaoru

    $Id$
*/

#include <sstream>

#include <boost/preprocessor.hpp>
#include <boost/test/unit_test.hpp>

#include <tetengo2/gui/dimension.h>
#include <tetengo2/gui/icon.h>
#include <tetengo2/gui/unit/em.h>
#include <tetengo2/stdalt.h>
#include <tetengo2/text.h>

#include "test_tetengo2.gui.detail_type_list.h"
#include "test_tetengo2.gui.type_list.h"


namespace {
    // types

    using detail_type_list_type = test_tetengo2::gui::type_list::detail_for_test;

    using common_type_list_type = test_tetengo2::gui::type_list::common<detail_type_list_type>;

    using dimension_type = common_type_list_type::dimension_type;

    using dimension_unit_type = dimension_type::unit_type;

    using icon_type = tetengo2::gui::icon<dimension_type, detail_type_list_type::icon_type>;

    using path_type = tetengo2::stdalt::filesystem::path;

    using path_string_type = path_type::string_type;


    // functions

    dimension_type make_dimension(const std::size_t width, const std::size_t height)
    {
        return { dimension_unit_type{ width }, dimension_unit_type{ height } };
    }
}


BOOST_AUTO_TEST_SUITE(test_tetengo2)
    BOOST_AUTO_TEST_SUITE(gui)
        BOOST_AUTO_TEST_SUITE(icon)
            // test cases

            BOOST_AUTO_TEST_CASE(construction)
            {
                BOOST_TEST_PASSPOINT();

                {
                    const icon_type icon{ path_type{ path_string_type{ TETENGO2_TEXT("hoge.ico") } } };
                }
                {
                    const icon_type icon{ path_type{ path_string_type{ TETENGO2_TEXT("hoge.ico") } },
                                          make_dimension(42, 42) };
                }
            }

            BOOST_AUTO_TEST_CASE(path)
            {
                BOOST_TEST_PASSPOINT();

                const icon_type icon{ path_type{ path_string_type{ TETENGO2_TEXT("hoge.ico") } } };

                BOOST_CHECK(icon.path() == path_type{ path_string_type{ TETENGO2_TEXT("hoge.ico") } });
            }

            BOOST_AUTO_TEST_CASE(dimension)
            {
                BOOST_TEST_PASSPOINT();

                const icon_type icon{ path_type{ path_string_type{ TETENGO2_TEXT("hoge.ico") } },
                                      make_dimension(42, 42) };

                BOOST_CHECK(icon.dimension() == make_dimension(42, 42));
            }

            BOOST_AUTO_TEST_CASE(details)
            {
                BOOST_TEST_PASSPOINT();

                {
                    const icon_type icon{ path_type{ path_string_type{ TETENGO2_TEXT("hoge.ico") } } };

                    icon.details();
                }
                {
                    icon_type icon{ path_type{ path_string_type{ TETENGO2_TEXT("hoge.ico") } } };

                    icon.details();
                }
            }


        BOOST_AUTO_TEST_SUITE_END()
    BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()
