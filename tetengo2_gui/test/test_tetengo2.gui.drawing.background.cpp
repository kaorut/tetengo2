/*! \file
    \brief Test of class tetengo2::gui::drawing::background.

    Copyright (C) 2007-2018 kaoru

    $Id$
*/

#include <memory>
#include <sstream>

#include <boost/preprocessor.hpp>
#include <boost/test/unit_test.hpp>

#include <tetengo2/gui/drawing/background.h>


namespace {
    // types

    using background_type = tetengo2::gui::drawing::background;

    struct concrete_background : public background_type
    {
        concrete_background() : background_type{}, m_details{} {}


    private:
        background_type::details_type m_details;

        virtual std::unique_ptr<background_type> clone_impl() const override
        {
            return std::make_unique<concrete_background>();
        }

        virtual const background_type::details_type& details_impl() const override
        {
            return m_details;
        }

        virtual background_type::details_type& details_impl() override
        {
            return m_details;
        }
    };
}


BOOST_AUTO_TEST_SUITE(test_tetengo2)
    BOOST_AUTO_TEST_SUITE(gui)
        BOOST_AUTO_TEST_SUITE(drawing)
            BOOST_AUTO_TEST_SUITE(background)
                // test cases

                BOOST_AUTO_TEST_CASE(construction)
                {
                    BOOST_TEST_PASSPOINT();

                    const concrete_background background;

                    background.clone();
                }

                BOOST_AUTO_TEST_CASE(clone)
                {
                    BOOST_TEST_PASSPOINT();

                    const concrete_background background;

                    background.details();
                }

                BOOST_AUTO_TEST_CASE(details)
                {
                    BOOST_TEST_PASSPOINT();

                    {
                        const concrete_background background;

                        background.details();
                    }
                    {
                        concrete_background background;

                        background.details();
                    }
                }


            BOOST_AUTO_TEST_SUITE_END()
        BOOST_AUTO_TEST_SUITE_END()
    BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()
