/*! \file
    \brief Test of class tetengo2::gui::common_dialog::message_box.

    Copyright (C) 2007-2018 kaoru

    $Id$
*/

#include <sstream>
#include <string>
#include <utility>

#include <boost/preprocessor.hpp>
#include <boost/test/unit_test.hpp>

#include <tetengo2/gui/common_dialog/message_box.h>
#include <tetengo2/gui/widget/window.h>
#include <tetengo2/stdalt.h>
#include <tetengo2/text.h>

#include "test_tetengo2.gui.detail_type_list.h"
#include "test_tetengo2.gui.type_list.h"


namespace {
    // types

    using detail_type_list_type = test_tetengo2::gui::type_list::detail_for_test;

    using common_type_list_type = test_tetengo2::gui::type_list::common<detail_type_list_type>;

    using string_type = common_type_list_type::string_type;

    using menu_details_type = detail_type_list_type::menu_type;

    using window_type = tetengo2::gui::widget::window;

    using button_style_type = tetengo2::gui::common_dialog::message_box_style::button_style;

    using common_dialog_details_type = detail_type_list_type::common_dialog_type;

    using message_box_type = tetengo2::gui::common_dialog::message_box<
        common_dialog_details_type,
        common_type_list_type::widget_details_type,
        common_type_list_type::drawing_details_type,
        common_type_list_type::scroll_details_type,
        common_type_list_type::message_handler_details_type,
        menu_details_type>;
}


BOOST_AUTO_TEST_SUITE(test_tetengo2)
    BOOST_AUTO_TEST_SUITE(gui)
        BOOST_AUTO_TEST_SUITE(common_dialog)
            BOOST_AUTO_TEST_SUITE(message_box_style)
                BOOST_AUTO_TEST_SUITE(button_style)
                    // test cases

                    BOOST_AUTO_TEST_CASE(construction)
                    {
                        BOOST_TEST_PASSPOINT();

                        button_style_type style1{ button_style_type::ok(false) };
                        BOOST_CHECK(style1.style() == button_style_type::style_type::ok);

                        const button_style_type style2{ style1 };
                        BOOST_CHECK(style2.style() == button_style_type::style_type::ok);

                        const button_style_type style3{ std::move(style1) };
                        BOOST_CHECK(style3.style() == button_style_type::style_type::ok);
                    }

                    BOOST_AUTO_TEST_CASE(ok)
                    {
                        BOOST_TEST_PASSPOINT();

                        button_style_type::ok(false);
                        button_style_type::ok(true, string_type{ TETENGO2_TEXT("hoge") });
                        button_style_type::ok(false);
                        button_style_type::ok(true, string_type{ TETENGO2_TEXT("hoge") });
                    }

                    BOOST_AUTO_TEST_CASE(yes_no)
                    {
                        BOOST_TEST_PASSPOINT();

                        button_style_type::yes_no(false);
                        button_style_type::yes_no(
                            true, string_type{ TETENGO2_TEXT("hoge") }, string_type{ TETENGO2_TEXT("fuga") });
                        button_style_type::yes_no(false);
                        button_style_type::yes_no(
                            true, string_type{ TETENGO2_TEXT("hoge") }, string_type{ TETENGO2_TEXT("fuga") });
                    }

                    BOOST_AUTO_TEST_CASE(style)
                    {
                        BOOST_TEST_PASSPOINT();

                        {
                            const auto style = button_style_type::ok(false);

                            BOOST_CHECK(style.style() == button_style_type::style_type::ok);
                        }
                        {
                            const auto style = button_style_type::ok(false, string_type{ TETENGO2_TEXT("hoge") });

                            BOOST_CHECK(style.style() == button_style_type::style_type::ok);
                        }
                        {
                            const auto style = button_style_type::ok(true);

                            BOOST_CHECK(style.style() == button_style_type::style_type::ok);
                        }
                        {
                            const auto style = button_style_type::ok(true, string_type{ TETENGO2_TEXT("hoge") });

                            BOOST_CHECK(style.style() == button_style_type::style_type::ok);
                        }
                        {
                            const auto style = button_style_type::yes_no(false);

                            BOOST_CHECK(style.style() == button_style_type::style_type::yes_no);
                        }
                        {
                            const auto style = button_style_type::yes_no(
                                false, string_type{ TETENGO2_TEXT("hoge") }, string_type{ TETENGO2_TEXT("fuga") });

                            BOOST_CHECK(style.style() == button_style_type::style_type::yes_no);
                        }
                        {
                            const auto style = button_style_type::yes_no(true);

                            BOOST_CHECK(style.style() == button_style_type::style_type::yes_no);
                        }
                        {
                            const auto style = button_style_type::yes_no(
                                true, string_type{ TETENGO2_TEXT("hoge") }, string_type{ TETENGO2_TEXT("fuga") });

                            BOOST_CHECK(style.style() == button_style_type::style_type::yes_no);
                        }
                    }

                    BOOST_AUTO_TEST_CASE(cancellable)
                    {
                        BOOST_TEST_PASSPOINT();

                        {
                            const auto style = button_style_type::ok(false);

                            BOOST_TEST(!style.cancellable());
                        }
                        {
                            const auto style = button_style_type::ok(true);

                            BOOST_TEST(style.cancellable());
                        }
                        {
                            const auto style = button_style_type::yes_no(false);

                            BOOST_TEST(!style.cancellable());
                        }
                        {
                            const auto style = button_style_type::yes_no(true);

                            BOOST_TEST(style.cancellable());
                        }
                    }

                    BOOST_AUTO_TEST_CASE(ok_button_label)
                    {
                        BOOST_TEST_PASSPOINT();

                        {
                            const auto style = button_style_type::ok(false);

                            BOOST_TEST_REQUIRE(!tetengo2::stdalt::has_value(style.ok_button_label()));
                        }
                        {
                            const auto style = button_style_type::ok(false, string_type{ TETENGO2_TEXT("hoge") });

                            BOOST_TEST_REQUIRE(tetengo2::stdalt::has_value(style.ok_button_label()));
                            BOOST_CHECK(*style.ok_button_label() == string_type{ TETENGO2_TEXT("hoge") });
                        }
                        {
                            const auto style = button_style_type::yes_no(false);

                            BOOST_TEST_REQUIRE(!tetengo2::stdalt::has_value(style.ok_button_label()));
                        }
                        {
                            const auto style = button_style_type::yes_no(
                                false, string_type{ TETENGO2_TEXT("hoge") }, string_type{ TETENGO2_TEXT("fuga") });

                            BOOST_TEST_REQUIRE(!tetengo2::stdalt::has_value(style.ok_button_label()));
                        }
                    }

                    BOOST_AUTO_TEST_CASE(yes_no_button_labels)
                    {
                        BOOST_TEST_PASSPOINT();

                        {
                            const auto style = button_style_type::ok(false);

                            BOOST_TEST_REQUIRE(!tetengo2::stdalt::has_value(style.yes_no_button_labels()));
                        }
                        {
                            const auto style = button_style_type::ok(false, string_type{ TETENGO2_TEXT("hoge") });

                            BOOST_TEST_REQUIRE(!tetengo2::stdalt::has_value(style.yes_no_button_labels()));
                        }
                        {
                            const auto style = button_style_type::yes_no(false);

                            BOOST_TEST_REQUIRE(!tetengo2::stdalt::has_value(style.yes_no_button_labels()));
                        }
                        {
                            const auto style = button_style_type::yes_no(
                                false, string_type{ TETENGO2_TEXT("hoge") }, string_type{ TETENGO2_TEXT("fuga") });

                            BOOST_TEST_REQUIRE(tetengo2::stdalt::has_value(style.yes_no_button_labels()));
                            BOOST_CHECK(style.yes_no_button_labels()->first == string_type{ TETENGO2_TEXT("hoge") });
                            BOOST_CHECK(style.yes_no_button_labels()->second == string_type{ TETENGO2_TEXT("fuga") });
                        }
                    }


                BOOST_AUTO_TEST_SUITE_END()
            BOOST_AUTO_TEST_SUITE_END()
            BOOST_AUTO_TEST_SUITE(message_box)
                // test cases

                BOOST_AUTO_TEST_CASE(construction)
                {
                    BOOST_TEST_PASSPOINT();

                    window_type            parent{};
                    const string_type      title{};
                    const string_type      main_content{};
                    const string_type      sub_content{};
                    const message_box_type message_box{ parent,
                                                        title,
                                                        main_content,
                                                        sub_content,
                                                        button_style_type::ok(true),
                                                        message_box_type::icon_style_type::warning };
                }

                BOOST_AUTO_TEST_CASE(do_modal)
                {
                    BOOST_TEST_PASSPOINT();

                    window_type       parent{};
                    const string_type title{};
                    const string_type main_content{};
                    const string_type sub_content{};
                    message_box_type  message_box{ parent,
                                                  title,
                                                  main_content,
                                                  sub_content,
                                                  button_style_type::ok(true),
                                                  message_box_type::icon_style_type::warning };

                    message_box.do_modal();
                }

                BOOST_AUTO_TEST_CASE(details)
                {
                    BOOST_TEST_PASSPOINT();

                    {
                        window_type            parent{};
                        const string_type      title{};
                        const string_type      main_content{};
                        const string_type      sub_content{};
                        const message_box_type message_box{ parent,
                                                            title,
                                                            main_content,
                                                            sub_content,
                                                            button_style_type::ok(true),
                                                            message_box_type::icon_style_type::warning };

                        message_box.details();
                    }
                    {
                        window_type       parent{};
                        const string_type title{};
                        const string_type main_content{};
                        const string_type sub_content{};
                        message_box_type  message_box{ parent,
                                                      title,
                                                      main_content,
                                                      sub_content,
                                                      button_style_type::ok(true),
                                                      message_box_type::icon_style_type::warning };

                        message_box.details();
                    }
                }


            BOOST_AUTO_TEST_SUITE_END()
        BOOST_AUTO_TEST_SUITE_END()
    BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()
