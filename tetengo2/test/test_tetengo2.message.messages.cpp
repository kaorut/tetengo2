/*! \file
    \brief Test of class tetengo2::message::messages.

    Copyright (C) 2007-2017 kaoru

    $Id$
*/

#include <ios>
#include <locale>
#include <stdexcept>
#include <string>

#include <boost/filesystem.hpp>
#include <boost/predef.h>
#include <boost/scope_exit.hpp>
#include <boost/test/unit_test.hpp>

#include <tetengo2/message/messages.h>
#include <tetengo2/stdalt.h>
#include <tetengo2/text.h>


namespace
{
    // types

    using messages_type = tetengo2::message::messages;

    using string_type = messages_type::string_type;

    using internal_encoding_type = tetengo2::text::encoding::locale<string_type>;

    using std_messages_type = std::messages<string_type::value_type>;

    struct set_global_locale
    {
        const std::locale m_initial_locale;

        explicit set_global_locale(const std::locale& locale)
        :
        m_initial_locale(
            std::locale::global(
                std::locale{
                    locale,
                    tetengo2::stdalt::make_unique<messages_type>(
                        boost::filesystem::path{ "messages.test" }, locale
                    ).release()
                }
            )
        )
        {}

        ~set_global_locale()
        noexcept
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
BOOST_AUTO_TEST_SUITE(messages)
    // test cases

    BOOST_AUTO_TEST_CASE(remove_namespace)
    {
        BOOST_TEST_PASSPOINT();

        {
            const auto namespace_removed = messages_type::remove_namespace(string_type{ TETENGO2_TEXT("hoge") });

            BOOST_CHECK(namespace_removed == string_type{ TETENGO2_TEXT("hoge") });
        }
        {
            const auto namespace_removed = messages_type::remove_namespace(string_type{ TETENGO2_TEXT("hoge:fuga") });

            BOOST_CHECK(namespace_removed == string_type{ TETENGO2_TEXT("fuga") });
        }
        {
            const auto namespace_removed =
                messages_type::remove_namespace(string_type{ TETENGO2_TEXT("hoge:fuga:piyo") });

            BOOST_CHECK(namespace_removed == string_type{ TETENGO2_TEXT("piyo") });
        }
    }

    BOOST_AUTO_TEST_CASE(construction)
    {
        BOOST_TEST_PASSPOINT();

        if (locale_supported())
        {
            const messages_type messages{ boost::filesystem::path{ "messages.test" }, std::locale{} };

            BOOST_CHECK_THROW((messages_type{ boost::filesystem::path{ "" }, std::locale{} }), std::ios_base::failure);

            BOOST_CHECK_THROW(
                (messages_type{ boost::filesystem::path{ "messages.test" } / "English.txt", std::locale{} }),
                std::ios_base::failure
            );
        }
        else
        {
            BOOST_WARN_MESSAGE(false, "Locale not supported.");
        }
    }

    BOOST_AUTO_TEST_CASE(open)
    {
        BOOST_TEST_PASSPOINT();

        if (locale_supported())
        {
            {
                const set_global_locale global_locale{ locale_en };
                const auto& messages = std::use_facet<std_messages_type>(std::locale{});
                BOOST_TEST(dynamic_cast<const messages_type*>(&messages));

                const auto catalog_id = messages.open("", std::locale{});
                BOOST_SCOPE_EXIT((&messages)(catalog_id))
                {
                    messages.close(catalog_id);
                } BOOST_SCOPE_EXIT_END;

                BOOST_TEST(catalog_id >= 0);

                BOOST_CHECK_THROW(messages.open("", std::locale{}), std::runtime_error);
            }
            {
                const set_global_locale global_locale{ locale_ja };
                const auto& messages = std::use_facet<std_messages_type>(std::locale{});
                BOOST_TEST(dynamic_cast<const messages_type*>(&messages));

                const auto catalog_id = messages.open("", std::locale{});
                BOOST_SCOPE_EXIT((&messages)(catalog_id))
                {
                    messages.close(catalog_id);
                } BOOST_SCOPE_EXIT_END;

                BOOST_TEST(catalog_id >= 0);

                BOOST_CHECK_THROW(messages.open("", std::locale{}), std::runtime_error);
            }
            {
                const set_global_locale global_locale{ locale_zh };
                const auto& messages = std::use_facet<std_messages_type>(std::locale{});
                BOOST_TEST(dynamic_cast<const messages_type*>(&messages));

                const auto catalog_id = messages.open("", std::locale{});
                BOOST_TEST(catalog_id < 0);
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
                const auto& messages = std::use_facet<std_messages_type>(std::locale{});
                BOOST_TEST(dynamic_cast<const messages_type*>(&messages));

                BOOST_CHECK_THROW(messages.get(0, 0, 0, string_type{ TETENGO2_TEXT("Language") }), std::runtime_error);

                BOOST_CHECK(
                    messages.get(-1, 0, 0, string_type{ TETENGO2_TEXT("Language") }) ==
                    string_type{ TETENGO2_TEXT("Language") }
                );

                const auto catalog_id = messages.open("", std::locale{});
                BOOST_SCOPE_EXIT((&messages)(catalog_id))
                {
                    messages.close(catalog_id);
                } BOOST_SCOPE_EXIT_END;

                BOOST_CHECK(
                    messages.get(catalog_id, 0, 0, string_type{ TETENGO2_TEXT("Language") }) ==
                    string_type{ TETENGO2_TEXT("English") }
                );
                BOOST_CHECK(
                    messages.get(catalog_id, 0, 0, string_type{ TETENGO2_TEXT("Name:Space:Hello") }) ==
                    string_type{ TETENGO2_TEXT("Hi") }
                );
                BOOST_CHECK(
                    messages.get(catalog_id, 0, 0, string_type{ TETENGO2_TEXT("Name:Space:ByeBye") }) ==
                    string_type{ TETENGO2_TEXT("ByeBye") }
                );
                BOOST_CHECK(
                    messages.get(catalog_id, 0, 0, string_type{ TETENGO2_TEXT("Name:Space:Colon:") }) ==
                    string_type{ TETENGO2_TEXT("Colon:") }
                );
            }
            {
                const set_global_locale global_locale{ locale_ja };
                const auto& messages = std::use_facet<std_messages_type>(std::locale{});
                BOOST_TEST(dynamic_cast<const messages_type*>(&messages));

                BOOST_CHECK_THROW(messages.get(0, 0, 0, string_type{ TETENGO2_TEXT("Language") }), std::runtime_error);

                BOOST_CHECK(
                    messages.get(-1, 0, 0, string_type{ TETENGO2_TEXT("Language") }) ==
                    string_type{ TETENGO2_TEXT("Language") }
                );

                const auto catalog_id = messages.open("", std::locale{});
                BOOST_SCOPE_EXIT((&messages)(catalog_id))
                {
                    messages.close(catalog_id);
                } BOOST_SCOPE_EXIT_END;

                BOOST_CHECK(
                    messages.get(catalog_id, 0, 0, string_type{ TETENGO2_TEXT("Language") }) ==
                    string_type{ TETENGO2_TEXT("Japanese") }
                );
                BOOST_CHECK(
                    messages.get(catalog_id, 0, 0, string_type{ TETENGO2_TEXT("Name:Space:Hello") }) ==
                    string_type{ TETENGO2_TEXT("Konnichiwa") }
                );
                BOOST_CHECK(
                    messages.get(catalog_id, 0, 0, string_type{ TETENGO2_TEXT("Name:Space:ByeBye") }) ==
                    string_type{ TETENGO2_TEXT("ByeBye") }
                );
                BOOST_CHECK(
                    messages.get(catalog_id, 0, 0, string_type{ TETENGO2_TEXT("Name:Space:Colon:") }) ==
                    string_type{ TETENGO2_TEXT("Colon:") }
                );
            }
            {
                const set_global_locale global_locale{ locale_zh };
                const auto& messages = std::use_facet<std_messages_type>(std::locale{});
                BOOST_TEST(dynamic_cast<const messages_type*>(&messages));

                const auto catalog_id = messages.open("", std::locale{});

                BOOST_CHECK(
                    messages.get(catalog_id, 0, 0, string_type{ TETENGO2_TEXT("Language") }) ==
                    string_type{ TETENGO2_TEXT("Language") }
                );
                BOOST_CHECK(
                    messages.get(catalog_id, 0, 0, string_type{ TETENGO2_TEXT("Name:Space:Hello") }) ==
                    string_type{ TETENGO2_TEXT("Hello") }
                );
                BOOST_CHECK(
                    messages.get(catalog_id, 0, 0, string_type{ TETENGO2_TEXT("Name:Space:ByeBye") }) ==
                    string_type{ TETENGO2_TEXT("ByeBye") }
                );
                BOOST_CHECK(
                    messages.get(catalog_id, 0, 0, string_type{ TETENGO2_TEXT("Name:Space:Colon:") }) ==
                    string_type{ TETENGO2_TEXT("Colon:") }
                );
            }
        }
        else
        {
            BOOST_WARN_MESSAGE(false, "Locale not supported.");
        }
    }

    BOOST_AUTO_TEST_CASE(close)
    {
        BOOST_TEST_PASSPOINT();

        if (locale_supported())
        {
            {
                const set_global_locale global_locale{ locale_en };
                const auto& messages = std::use_facet<std_messages_type>(std::locale{});
                BOOST_TEST(dynamic_cast<const messages_type*>(&messages));

                BOOST_CHECK_THROW(messages.close(0), std::runtime_error);

                BOOST_CHECK_NO_THROW(messages.close(-1));

                const auto catalog_id = messages.open("", std::locale{});
                BOOST_SCOPE_EXIT((&messages)(catalog_id))
                {
                    messages.close(catalog_id);

                    BOOST_CHECK_THROW(messages.close(catalog_id), std::runtime_error);
                } BOOST_SCOPE_EXIT_END;
            }
            {
                const set_global_locale global_locale{ locale_ja };
                const auto& messages = std::use_facet<std_messages_type>(std::locale{});
                BOOST_TEST(dynamic_cast<const messages_type*>(&messages));

                BOOST_CHECK_THROW(messages.close(0), std::runtime_error);

                BOOST_CHECK_NO_THROW(messages.close(-1));

                const auto catalog_id = messages.open("", std::locale{});
                BOOST_SCOPE_EXIT((&messages)(catalog_id))
                {
                    messages.close(catalog_id);

                    BOOST_CHECK_THROW(messages.close(catalog_id), std::runtime_error);
                } BOOST_SCOPE_EXIT_END;
            }
            {
                const set_global_locale global_locale{ locale_zh };
                const auto& messages = std::use_facet<std_messages_type>(std::locale{});
                BOOST_TEST(dynamic_cast<const messages_type*>(&messages));

                const auto catalog_id = messages.open("", std::locale{});
                BOOST_CHECK_NO_THROW(messages.close(catalog_id));
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
