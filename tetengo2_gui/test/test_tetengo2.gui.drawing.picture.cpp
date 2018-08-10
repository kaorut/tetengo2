/*! \file
    \brief Test of class tetengo2::gui::drawing::picture.

    Copyright (C) 2007-2018 kaoru

    $Id$
*/

#include <sstream>
#include <stdexcept>
#include <utility>

#include <boost/preprocessor.hpp>
#include <boost/test/unit_test.hpp>

#include <tetengo2/detail/base/drawing.h>
#include <tetengo2/detail/base/gui_impl_set.h>
#include <tetengo2/gui/dimension.h>
#include <tetengo2/gui/drawing/picture.h>
#include <tetengo2/gui/unit/em.h>

#include "test_tetengo2.gui.detail_type_list.h"
#include "test_tetengo2.gui.type_list.h"


namespace {
    // types

    using detail_type_list_type = test_tetengo2::gui::type_list::detail_for_test;

    using common_type_list_type = test_tetengo2::gui::type_list::common<detail_type_list_type>;

    using drawing_details_type = detail_type_list_type::drawing_type;

    using dimension_type = common_type_list_type::dimension_type;

    using dimension_unit_type = dimension_type::unit_type;

    using picture_type = tetengo2::gui::drawing::picture;
}


BOOST_AUTO_TEST_SUITE(test_tetengo2)
    BOOST_AUTO_TEST_SUITE(gui)
        BOOST_AUTO_TEST_SUITE(drawing)
            BOOST_AUTO_TEST_SUITE(picture)
                // test cases

                BOOST_AUTO_TEST_CASE(construction)
                {
                    BOOST_TEST_PASSPOINT();

                    {
                        const picture_type picture{ tetengo2::detail::gui_detail_impl_set().drawing_(),
                                                    dimension_type{ dimension_unit_type{ 123 },
                                                                    dimension_unit_type{ 456 } } };
                    }
                    {
                        picture_type::details_ptr_type p_details{
                            tetengo2::detail::gui_detail_impl_set().drawing_().create_picture(
                                dimension_type{ dimension_unit_type{ 123 }, dimension_unit_type{ 456 } })
                        };
                        const picture_type picture2{ tetengo2::detail::gui_detail_impl_set().drawing_(),
                                                     std::move(p_details) };
                    }
                    {
                        picture_type::details_ptr_type p_details;

                        auto exception_thrown = false;
                        try
                        {
                            picture_type picture{ tetengo2::detail::gui_detail_impl_set().drawing_(),
                                                  std::move(p_details) };
                        }
                        catch (const std::invalid_argument&)
                        {
                            exception_thrown = true;
                        }
                        BOOST_TEST(exception_thrown);
                    }
                }

                BOOST_AUTO_TEST_CASE(dimension)
                {
                    BOOST_TEST_PASSPOINT();

                    const picture_type picture{ tetengo2::detail::gui_detail_impl_set().drawing_(),
                                                dimension_type{ dimension_unit_type{ 123 },
                                                                dimension_unit_type{ 456 } } };

                    BOOST_CHECK(
                        (picture.dimension() ==
                         dimension_type{ dimension_unit_type{ 123 }, dimension_unit_type{ 456 } }));
                }

                BOOST_AUTO_TEST_CASE(details)
                {
                    BOOST_TEST_PASSPOINT();

                    {
                        const picture_type picture{ tetengo2::detail::gui_detail_impl_set().drawing_(),
                                                    dimension_type{ dimension_unit_type{ 123 },
                                                                    dimension_unit_type{ 456 } } };

                        picture.details();
                    }
                    {
                        picture_type picture{ tetengo2::detail::gui_detail_impl_set().drawing_(),
                                              dimension_type{ dimension_unit_type{ 123 },
                                                              dimension_unit_type{ 456 } } };

                        picture.details();
                    }
                }


            BOOST_AUTO_TEST_SUITE_END()
        BOOST_AUTO_TEST_SUITE_END()
    BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()
