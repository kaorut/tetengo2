/*! \file
    \brief Test of class tetengo2::gui::common_dialog::file_open.

    Copyright (C) 2007-2018 kaoru

    $Id$
*/

#include <sstream>
#include <string>

#include <boost/preprocessor.hpp>
#include <boost/test/unit_test.hpp>

#include <tetengo2/gui/common_dialog/file_open.h>
#include <tetengo2/gui/widget/window.h>
#include <tetengo2/stdalt.h>
#include <tetengo2/text.h>
#include <tetengo2/type_list.h>


namespace {
    // types

    using string_type = tetengo2::type_list::string_type;

    using window_type = tetengo2::gui::widget::window;

    using file_open_dialog_type = tetengo2::gui::common_dialog::file_open;


    // functions

    file_open_dialog_type::file_filters_type make_file_filters()
    {
        return { { string_type{ TETENGO2_TEXT("All Files") }, string_type{ TETENGO2_TEXT("*.*") } } };
    }
}


BOOST_AUTO_TEST_SUITE(test_tetengo2)
    BOOST_AUTO_TEST_SUITE(gui)
        BOOST_AUTO_TEST_SUITE(common_dialog)
            BOOST_AUTO_TEST_SUITE(file_open)
                // test cases

                BOOST_AUTO_TEST_CASE(construction)
                {
                    BOOST_TEST_PASSPOINT();

                    {
                        window_type                 parent{};
                        const file_open_dialog_type file_open{ string_type{}, make_file_filters(), parent };
                    }
                    {
                        window_type                 parent{};
                        const file_open_dialog_type file_open{ string_type{ TETENGO2_TEXT("hoge") },
                                                               file_open_dialog_type::file_filters_type{},
                                                               parent };
                    }
                    {
                        window_type                 parent{};
                        const file_open_dialog_type file_open{ string_type{ TETENGO2_TEXT("hoge") },
                                                               make_file_filters(),
                                                               parent };
                    }
                }

                BOOST_AUTO_TEST_CASE(result)
                {
                    BOOST_TEST_PASSPOINT();

                    {
                        window_type                 parent{};
                        const file_open_dialog_type file_open{ string_type{ TETENGO2_TEXT("hoge") },
                                                               make_file_filters(),
                                                               parent };

                        BOOST_TEST(file_open.result().empty());
                    }
                    {
                        window_type           parent{};
                        file_open_dialog_type file_open{ string_type{ TETENGO2_TEXT("hoge") },
                                                         make_file_filters(),
                                                         parent };

                        file_open.do_modal();

                        BOOST_TEST(!file_open.result().empty());
                    }
                }

                BOOST_AUTO_TEST_CASE(do_modal)
                {
                    BOOST_TEST_PASSPOINT();

                    window_type           parent{};
                    file_open_dialog_type file_open{ string_type{ TETENGO2_TEXT("hoge") },
                                                     make_file_filters(),
                                                     parent };

                    file_open.do_modal();
                }

                BOOST_AUTO_TEST_CASE(details)
                {
                    BOOST_TEST_PASSPOINT();

                    {
                        window_type                 parent{};
                        const file_open_dialog_type file_open{ string_type{ TETENGO2_TEXT("hoge") },
                                                               make_file_filters(),
                                                               parent };


                        file_open.details();
                    }
                    {
                        window_type           parent{};
                        file_open_dialog_type file_open{ string_type{ TETENGO2_TEXT("hoge") },
                                                         make_file_filters(),
                                                         parent };

                        file_open.details();
                    }
                }


            BOOST_AUTO_TEST_SUITE_END()
        BOOST_AUTO_TEST_SUITE_END()
    BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()
