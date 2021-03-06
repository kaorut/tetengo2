/*! \file
    \brief Test of class tetengo2::gui::common_dialog::file_save.

    Copyright (C) 2007-2019 kaoru

    $Id$
*/

#include <sstream>
#include <string>

#include <boost/preprocessor.hpp>
#include <boost/shared_ptr.hpp>
#include <boost/signals2.hpp>
#include <boost/test/unit_test.hpp>

#include <tetengo2/gui/common_dialog/file_save.h>
#include <tetengo2/gui/menu/abstract_popup.h>
#include <tetengo2/gui/menu/menu_bar.h>
#include <tetengo2/gui/widget/window.h>
#include <tetengo2/stdalt.h>
#include <tetengo2/text.h>
#include <tetengo2/type_list.h>


namespace {
    // types

    using string_type = tetengo2::type_list::string_type;

    using window_type = tetengo2::gui::widget::window;

    using file_save_dialog_type = tetengo2::gui::common_dialog::file_save;


    // functions

    file_save_dialog_type::file_filters_type make_file_filters()
    {
        return { { string_type{ TETENGO2_TEXT("All Files") }, string_type{ TETENGO2_TEXT("*.*") } } };
    }
}


BOOST_AUTO_TEST_SUITE(test_tetengo2)
    BOOST_AUTO_TEST_SUITE(gui)
        BOOST_AUTO_TEST_SUITE(common_dialog)
            BOOST_AUTO_TEST_SUITE(file_save)
                // test cases

                BOOST_AUTO_TEST_CASE(construction)
                {
                    BOOST_TEST_PASSPOINT();

                    {
                        window_type                 parent{};
                        const file_save_dialog_type file_save{
                            string_type{}, TETENGO2_STDALT_NULLOPT, make_file_filters(), parent
                        };
                    }
                    {
                        window_type                 parent{};
                        const file_save_dialog_type file_save{ string_type{ TETENGO2_TEXT("hoge") },
                                                               TETENGO2_STDALT_NULLOPT,
                                                               file_save_dialog_type::file_filters_type{},
                                                               parent };
                    }
                    {
                        window_type                 parent{};
                        const file_save_dialog_type file_save{
                            string_type{ TETENGO2_TEXT("hoge") }, TETENGO2_STDALT_NULLOPT, make_file_filters(), parent
                        };
                    }
                }

                BOOST_AUTO_TEST_CASE(result)
                {
                    BOOST_TEST_PASSPOINT();

                    {
                        window_type                 parent{};
                        const file_save_dialog_type file_save{
                            string_type{ TETENGO2_TEXT("hoge") }, TETENGO2_STDALT_NULLOPT, make_file_filters(), parent
                        };

                        BOOST_TEST(file_save.result().empty());
                    }
                    {
                        window_type           parent{};
                        file_save_dialog_type file_save{
                            string_type{ TETENGO2_TEXT("hoge") }, TETENGO2_STDALT_NULLOPT, make_file_filters(), parent
                        };

                        file_save.do_modal();

                        BOOST_TEST(!file_save.result().empty());
                    }
                    {
                        window_type                 parent{};
                        const file_save_dialog_type file_save{ string_type{ TETENGO2_TEXT("hoge") },
                                                               tetengo2::stdalt::make_optional(
                                                                   tetengo2::stdalt::filesystem::path{ "fuga.jpg" }),
                                                               make_file_filters(),
                                                               parent };

                        BOOST_CHECK(file_save.result() == tetengo2::stdalt::filesystem::path{ "fuga.jpg" });
                    }
                    {
                        window_type           parent{};
                        file_save_dialog_type file_save{ string_type{ TETENGO2_TEXT("hoge") },
                                                         tetengo2::stdalt::make_optional(
                                                             tetengo2::stdalt::filesystem::path{ "fuga.jpg" }),
                                                         make_file_filters(),
                                                         parent };

                        file_save.do_modal();

                        BOOST_CHECK(file_save.result() != tetengo2::stdalt::filesystem::path{ "fuga.jpg" });
                    }
                }

                BOOST_AUTO_TEST_CASE(do_modal)
                {
                    BOOST_TEST_PASSPOINT();

                    window_type           parent{};
                    file_save_dialog_type file_save{
                        string_type{ TETENGO2_TEXT("hoge") }, TETENGO2_STDALT_NULLOPT, make_file_filters(), parent
                    };

                    file_save.do_modal();
                }

                BOOST_AUTO_TEST_CASE(details)
                {
                    BOOST_TEST_PASSPOINT();

                    {
                        window_type                 parent{};
                        const file_save_dialog_type file_save{
                            string_type{ TETENGO2_TEXT("hoge") }, TETENGO2_STDALT_NULLOPT, make_file_filters(), parent
                        };

                        file_save.details();
                    }
                    {
                        window_type           parent{};
                        file_save_dialog_type file_save{
                            string_type{ TETENGO2_TEXT("hoge") }, TETENGO2_STDALT_NULLOPT, make_file_filters(), parent
                        };

                        file_save.details();
                    }
                }


            BOOST_AUTO_TEST_SUITE_END()
        BOOST_AUTO_TEST_SUITE_END()
    BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()
