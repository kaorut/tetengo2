/*! \file
    \brief Test of class tetengo2::message::message_catalog.

    Copyright (C) 2007-2018 kaoru

    $Id$
*/

#include <memory>
#include <sstream>
#include <stdexcept>
#include <string>

#include <boost/predef.h>
#include <boost/preprocessor.hpp>
#include <boost/test/unit_test.hpp>

#include <tetengo2/message/message_catalog.h>
#include <tetengo2/message/messages.h>
#include <tetengo2/stdalt.h>
#include <tetengo2/text.h>


namespace {
    // types

    using message_catalog_type = tetengo2::message::message_catalog;

    using string_type = message_catalog_type::string_type;

    struct set_global_locale
    {
        using messages_type = tetengo2::message::messages;

        const std::locale m_initial_locale;

        explicit set_global_locale(const std::locale& locale)
        : m_initial_locale{ std::locale::global(std::locale{
              locale,
              std::make_unique<messages_type>(tetengo2::stdalt::filesystem::path{ "messages.test" }, locale)
                  .release() }) }
        {}

        ~set_global_locale() noexcept
        {
            std::locale::global(m_initial_locale);
        }
    };


    // functions

    bool locale_supported()
    {
        try
        {
            std::locale locale{ "" };
            return true;
        }
        catch (const std::runtime_error&)
        {
            return false;
        }
    }

    std::locale make_locale(const std::string& name)
    {
        try
        {
            return std::locale{ name.c_str() };
        }
        catch (const std::runtime_error&)
        {
            return std::locale::classic();
        }
    }


        // data

#if BOOST_OS_WINDOWS
    const std::locale locale_en = make_locale("English");

    const std::locale locale_ja = make_locale("Japanese_Japan");

    const std::locale locale_zh = make_locale("Chinese");
#else
    const std::locale locale_en = make_locale("en_US");

    const std::locale locale_ja = make_locale("ja_JP.UTF-8");

    const std::locale locale_zh = make_locale("zh_CN");
#endif
}


BOOST_AUTO_TEST_SUITE(test_tetengo2)
    BOOST_AUTO_TEST_SUITE(message)
        BOOST_AUTO_TEST_SUITE(message_catalog)
            // test cases

            BOOST_AUTO_TEST_CASE(construction)
            {
                BOOST_TEST_PASSPOINT();

                if (locale_supported())
                {
                    {
                        const set_global_locale global_locale{ locale_en };

                        const message_catalog_type message_catalog{};
                    }
                    {
                        const set_global_locale global_locale{ locale_ja };

                        const message_catalog_type message_catalog{};
                    }
                    {
                        const set_global_locale global_locale{ locale_zh };

                        const message_catalog_type message_catalog{};
                    }
                }
                else
                {
                    BOOST_WARN_MESSAGE(false, "Locale not supported.");
                }
            }

            BOOST_AUTO_TEST_CASE(get)
            {
                BOOST_TEST_PASSPOINT();

                if (locale_supported())
                {
                    {
                        const set_global_locale global_locale{ locale_en };

                        const message_catalog_type message_catalog{};

                        BOOST_CHECK(
                            message_catalog.get(TETENGO2_TEXT("Language")) == string_type{ TETENGO2_TEXT("English") });
                        BOOST_CHECK(
                            message_catalog.get(TETENGO2_TEXT("Name:Space:Hello")) ==
                            string_type{ TETENGO2_TEXT("Hi") });
                        BOOST_CHECK(
                            message_catalog.get(TETENGO2_TEXT("Name:Space:ByeBye")) ==
                            string_type{ TETENGO2_TEXT("ByeBye") });
                        BOOST_CHECK(
                            message_catalog.get(TETENGO2_TEXT("Name:Space:Colon:")) ==
                            string_type{ TETENGO2_TEXT("Colon:") });
                        BOOST_CHECK(
                            message_catalog.get(TETENGO2_TEXT("Name:Space:Esc\\:ape")) ==
                            string_type{ TETENGO2_TEXT("Esc:ape") });
                    }
                    {
                        const set_global_locale global_locale{ locale_ja };

                        const message_catalog_type message_catalog{};

                        BOOST_CHECK(
                            message_catalog.get(TETENGO2_TEXT("Language")) == string_type{ TETENGO2_TEXT("Japanese") });
                        BOOST_CHECK(
                            message_catalog.get(TETENGO2_TEXT("Name:Space:Hello")) ==
                            string_type{ TETENGO2_TEXT("Konnichiwa") });
                        BOOST_CHECK(
                            message_catalog.get(TETENGO2_TEXT("Name:Space:ByeBye")) ==
                            string_type{ TETENGO2_TEXT("ByeBye") });
                        BOOST_CHECK(
                            message_catalog.get(TETENGO2_TEXT("Name:Space:Colon:")) ==
                            string_type{ TETENGO2_TEXT("Colon:") });
                        BOOST_CHECK(
                            message_catalog.get(TETENGO2_TEXT("Name:Space:Esc\\:ape")) ==
                            string_type{ TETENGO2_TEXT("Esc:ape") });
                    }
                    {
                        const set_global_locale global_locale{ locale_zh };

                        const message_catalog_type message_catalog{};

                        BOOST_CHECK(
                            message_catalog.get(TETENGO2_TEXT("Language")) == string_type{ TETENGO2_TEXT("Language") });
                        BOOST_CHECK(
                            message_catalog.get(TETENGO2_TEXT("Name:Space:Hello")) ==
                            string_type{ TETENGO2_TEXT("Hello") });
                        BOOST_CHECK(
                            message_catalog.get(TETENGO2_TEXT("Name:Space:ByeBye")) ==
                            string_type{ TETENGO2_TEXT("ByeBye") });
                        BOOST_CHECK(
                            message_catalog.get(TETENGO2_TEXT("Name:Space:Colon:")) ==
                            string_type{ TETENGO2_TEXT("Colon:") });
                        BOOST_CHECK(
                            message_catalog.get(TETENGO2_TEXT("Name:Space:Esc\\:ape")) ==
                            string_type{ TETENGO2_TEXT("Esc:ape") });
                    }
                }
                else
                {
                    BOOST_WARN_MESSAGE(false, "Locale not supported.");
                }
            }


        BOOST_AUTO_TEST_SUITE_END()
    BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()
