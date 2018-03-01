/*! \file
    \brief Test of class tetengo2::gui::position.

    Copyright (C) 2007-2018 kaoru

    $Id$
*/

#include <sstream>

#include <boost/operators.hpp>
#include <boost/preprocessor.hpp>
#include <boost/test/unit_test.hpp>

#include <tetengo2/gui/position.h>
#include <tetengo2/gui/unit/em.h>
#include <tetengo2/gui/unit/unit.h>


namespace {
    using unit_type = tetengo2::gui::unit::em_for_test;

    using position_type = tetengo2::gui::position<unit_type>;
}


BOOST_AUTO_TEST_SUITE(test_tetengo2)
    BOOST_AUTO_TEST_SUITE(gui)
        BOOST_AUTO_TEST_SUITE(position)
            // test cases

            BOOST_AUTO_TEST_CASE(construction)
            {
                BOOST_TEST_PASSPOINT();

                {
                    const position_type position{};
                }
                {
                    const position_type position{ unit_type{ 42 }, unit_type{ 24 } };
                }
            }

            BOOST_AUTO_TEST_CASE(operator_equal)
            {
                BOOST_TEST_PASSPOINT();

                const position_type position1{ unit_type{ 42 }, unit_type{ 24 } };
                const position_type position2{ unit_type{ 42 }, unit_type{ 24 } };
                const position_type position3{ unit_type{ 42 }, unit_type{ 42 } };
                const position_type position4{ unit_type{ 24 }, unit_type{ 42 } };
                const position_type position5{ unit_type{ 24 }, unit_type{ 24 } };

                BOOST_CHECK(position1 == position2);
                BOOST_CHECK(position1 != position3);
                BOOST_CHECK(position1 != position4);
                BOOST_CHECK(position1 != position5);
            }

            BOOST_AUTO_TEST_CASE(left)
            {
                BOOST_TEST_PASSPOINT();

                {
                    const position_type position{};

                    BOOST_CHECK((position.left() == unit_type{}));
                }
                {
                    const position_type position{ unit_type{ 42 }, unit_type{ 24 } };

                    BOOST_CHECK((position.left() == unit_type{ 42 }));
                }
            }

            BOOST_AUTO_TEST_CASE(top)
            {
                BOOST_TEST_PASSPOINT();

                {
                    const position_type position{};

                    BOOST_CHECK((position.top() == unit_type{}));
                }
                {
                    const position_type position{ unit_type{ 42 }, unit_type{ 24 } };

                    BOOST_CHECK((position.top() == unit_type{ 24 }));
                }
            }


        BOOST_AUTO_TEST_SUITE_END()
    BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()
