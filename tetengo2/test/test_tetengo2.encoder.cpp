/*! \file
    \brief Test of class tetengo2::encoder.

    Copyright (C) 2007-2010 kaoru

    $Id$
*/

#include <boost/test/unit_test.hpp>

//#include <locale>
//#include <stdexcept>
//#include <string>

#include "tetengo2.text.h"
#include "tetengo2.encoding.locale.h"

#include "tetengo2.encoder.h"


namespace
{
    // types

    typedef tetengo2::encoding::locale<std::string> m_encoding_type;

    typedef tetengo2::encoding::locale<std::wstring> w_encoding_type;

    typedef 
        tetengo2::encoder<m_encoding_type, m_encoding_type> m_m_encoder_type;

    typedef 
        tetengo2::encoder<m_encoding_type, w_encoding_type> m_w_encoder_type;

    typedef 
        tetengo2::encoder<w_encoding_type, m_encoding_type> w_m_encoder_type;

    typedef 
        tetengo2::encoder<w_encoding_type, w_encoding_type> w_w_encoder_type;


    // functions

    bool locale_supported()
    {
        try
        {
            std::locale locale("");
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
            return std::locale(name.c_str());
        }
        catch (const std::runtime_error&)
        {
            return std::locale::classic();
        }
    }


    // data

#if defined(_WIN32)
    const std::locale locale_en = make_locale("English");

    const std::locale locale_ja = make_locale("Japanese_Japan");
#else
    const std::locale locale_en = make_locale("en_US");

    const std::locale locale_ja = make_locale("ja_JP.UTF-8");
#endif


}


BOOST_AUTO_TEST_SUITE(test_tetengo2)
BOOST_AUTO_TEST_SUITE(encoder)
    // test cases

    BOOST_AUTO_TEST_CASE(construction)
    {
        {
            const m_m_encoder_type encoder =
                m_m_encoder_type(
                    m_encoding_type(std::locale::classic()),
                    m_encoding_type(std::locale::classic())
                );
        }
        {
            const m_w_encoder_type encoder =
                m_w_encoder_type(
                    m_encoding_type(std::locale::classic()),
                    w_encoding_type(std::locale::classic())
                );
        }
        {
            const w_m_encoder_type encoder =
                w_m_encoder_type(
                    w_encoding_type(std::locale::classic()),
                    m_encoding_type(std::locale::classic())
                );
        }
        {
            const w_w_encoder_type encoder =
                w_w_encoder_type(
                    w_encoding_type(std::locale::classic()),
                    w_encoding_type(std::locale::classic())
                );
        }
    }

    BOOST_AUTO_TEST_CASE(swap)
    {
        if (locale_supported())
        {
            {
                m_m_encoder_type encoder1 =
                    m_m_encoder_type(
                        m_encoding_type(locale_en), m_encoding_type(locale_en)
                    );
                m_m_encoder_type encoder2 =
                    m_m_encoder_type(
                        m_encoding_type(locale_ja), m_encoding_type(locale_ja)
                    );

                encoder1.swap(encoder2);

                BOOST_CHECK(
                    encoder1.internal_encoding().locale_based_on() ==
                    locale_ja
                );
                BOOST_CHECK(
                    encoder1.external_encoding().locale_based_on() ==
                    locale_ja
                );
                BOOST_CHECK(
                    encoder2.internal_encoding().locale_based_on() ==
                    locale_en
                );
                BOOST_CHECK(
                    encoder2.external_encoding().locale_based_on() ==
                    locale_en
                );
            }
            {
                m_w_encoder_type encoder1 =
                    m_w_encoder_type(
                        m_encoding_type(locale_en), w_encoding_type(locale_en)
                    );
                m_w_encoder_type encoder2 =
                    m_w_encoder_type(
                        m_encoding_type(locale_ja), w_encoding_type(locale_ja)
                    );

                encoder1.swap(encoder2);

                BOOST_CHECK(
                    encoder1.internal_encoding().locale_based_on() ==
                    locale_ja
                );
                BOOST_CHECK(
                    encoder1.external_encoding().locale_based_on() ==
                    locale_ja
                );
                BOOST_CHECK(
                    encoder2.internal_encoding().locale_based_on() ==
                    locale_en
                );
                BOOST_CHECK(
                    encoder2.external_encoding().locale_based_on() ==
                    locale_en
                );
            }
            {
                w_m_encoder_type encoder1 =
                    w_m_encoder_type(
                        w_encoding_type(locale_en), m_encoding_type(locale_en)
                    );
                w_m_encoder_type encoder2 =
                    w_m_encoder_type(
                        w_encoding_type(locale_ja), m_encoding_type(locale_ja)
                    );

                encoder1.swap(encoder2);

                BOOST_CHECK(
                    encoder1.internal_encoding().locale_based_on() ==
                    locale_ja
                );
                BOOST_CHECK(
                    encoder1.external_encoding().locale_based_on() ==
                    locale_ja
                );
                BOOST_CHECK(
                    encoder2.internal_encoding().locale_based_on() ==
                    locale_en
                );
                BOOST_CHECK(
                    encoder2.external_encoding().locale_based_on() ==
                    locale_en
                );
            }
            {
                w_w_encoder_type encoder1 =
                    w_w_encoder_type(
                        w_encoding_type(locale_en), w_encoding_type(locale_en)
                    );
                w_w_encoder_type encoder2 =
                    w_w_encoder_type(
                        w_encoding_type(locale_ja), w_encoding_type(locale_ja)
                    );

                encoder1.swap(encoder2);

                BOOST_CHECK(
                    encoder1.internal_encoding().locale_based_on() ==
                    locale_ja
                );
                BOOST_CHECK(
                    encoder1.external_encoding().locale_based_on() ==
                    locale_ja
                );
                BOOST_CHECK(
                    encoder2.internal_encoding().locale_based_on() ==
                    locale_en
                );
                BOOST_CHECK(
                    encoder2.external_encoding().locale_based_on() ==
                    locale_en
                );
            }
        }
        else
        {
            BOOST_WARN_MESSAGE(false, "Locale not supported.");
        }
    }

    BOOST_AUTO_TEST_CASE(operator_assign)
    {
        if (locale_supported())
        {
            {
                m_m_encoder_type encoder1 =
                    m_m_encoder_type(
                        m_encoding_type(locale_en), m_encoding_type(locale_en)
                    );
                const m_m_encoder_type encoder2 =
                    m_m_encoder_type(
                        m_encoding_type(locale_ja), m_encoding_type(locale_ja)
                    );

                encoder1 = encoder2;

                BOOST_CHECK(
                    encoder1.internal_encoding().locale_based_on() ==
                    encoder2.internal_encoding().locale_based_on()
                );
                BOOST_CHECK(
                    encoder1.external_encoding().locale_based_on() ==
                    encoder2.external_encoding().locale_based_on()
                );
            }
            {
                m_w_encoder_type encoder1 =
                    m_w_encoder_type(
                        m_encoding_type(locale_en), w_encoding_type(locale_en)
                    );
                const m_w_encoder_type encoder2 =
                    m_w_encoder_type(
                        m_encoding_type(locale_ja), w_encoding_type(locale_ja)
                    );

                encoder1 = encoder2;

                BOOST_CHECK(
                    encoder1.internal_encoding().locale_based_on() ==
                    encoder2.internal_encoding().locale_based_on()
                );
                BOOST_CHECK(
                    encoder1.external_encoding().locale_based_on() ==
                    encoder2.external_encoding().locale_based_on()
                );
            }
            {
                w_m_encoder_type encoder1 =
                    w_m_encoder_type(
                        w_encoding_type(locale_en), m_encoding_type(locale_en)
                    );
                const w_m_encoder_type encoder2 =
                    w_m_encoder_type(
                        w_encoding_type(locale_ja), m_encoding_type(locale_ja)
                    );

                encoder1 = encoder2;

                BOOST_CHECK(
                    encoder1.internal_encoding().locale_based_on() ==
                    encoder2.internal_encoding().locale_based_on()
                );
                BOOST_CHECK(
                    encoder1.external_encoding().locale_based_on() ==
                    encoder2.external_encoding().locale_based_on()
                );
            }
            {
                w_w_encoder_type encoder1 =
                    w_w_encoder_type(
                        w_encoding_type(locale_en), w_encoding_type(locale_en)
                    );
                const w_w_encoder_type encoder2 =
                    w_w_encoder_type(
                        w_encoding_type(locale_ja), w_encoding_type(locale_ja)
                    );

                encoder1 = encoder2;

                BOOST_CHECK(
                    encoder1.internal_encoding().locale_based_on() ==
                    encoder2.internal_encoding().locale_based_on()
                );
                BOOST_CHECK(
                    encoder1.external_encoding().locale_based_on() ==
                    encoder2.external_encoding().locale_based_on()
                );
            }
        }
        else
        {
            BOOST_WARN_MESSAGE(false, "Locale not supported.");
        }
    }

    BOOST_AUTO_TEST_CASE(internal_encoding)
    {
        if (locale_supported())
        {
            {
                {
                    const m_m_encoder_type encoder =
                        m_m_encoder_type(
                            m_encoding_type(locale_en),
                            m_encoding_type(locale_ja)
                        );

                    BOOST_CHECK(
                        encoder.internal_encoding().locale_based_on() ==
                        locale_en
                    );
                }
                {
                    const m_m_encoder_type encoder =
                        m_m_encoder_type(
                            m_encoding_type(locale_ja),
                            m_encoding_type(locale_en)
                        );

                    BOOST_CHECK(
                        encoder.internal_encoding().locale_based_on() ==
                        locale_ja
                    );
                }
            }
            {
                {
                    const m_w_encoder_type encoder =
                        m_w_encoder_type(
                            m_encoding_type(locale_en),
                            w_encoding_type(locale_ja)
                        );

                    BOOST_CHECK(
                        encoder.internal_encoding().locale_based_on() ==
                        locale_en
                    );
                }
                {
                    const m_w_encoder_type encoder =
                        m_w_encoder_type(
                            m_encoding_type(locale_ja),
                            w_encoding_type(locale_en)
                        );

                    BOOST_CHECK(
                        encoder.internal_encoding().locale_based_on() ==
                        locale_ja
                    );
                }
            }
            {
                {
                    const w_m_encoder_type encoder =
                        w_m_encoder_type(
                            w_encoding_type(locale_en),
                            m_encoding_type(locale_ja)
                        );

                    BOOST_CHECK(
                        encoder.internal_encoding().locale_based_on() ==
                        locale_en
                    );
                }
                {
                    const w_m_encoder_type encoder =
                        w_m_encoder_type(
                            w_encoding_type(locale_ja),
                            m_encoding_type(locale_en)
                        );

                    BOOST_CHECK(
                        encoder.internal_encoding().locale_based_on() ==
                        locale_ja
                    );
                }
            }
            {
                {
                    const w_w_encoder_type encoder =
                        w_w_encoder_type(
                            w_encoding_type(locale_en),
                            w_encoding_type(locale_ja)
                        );

                    BOOST_CHECK(
                        encoder.internal_encoding().locale_based_on() ==
                        locale_en
                    );
                }
                {
                    const w_w_encoder_type encoder =
                        w_w_encoder_type(
                            w_encoding_type(locale_ja),
                            w_encoding_type(locale_en)
                        );

                    BOOST_CHECK(
                        encoder.internal_encoding().locale_based_on() ==
                        locale_ja
                    );
                }
            }
        }
        else
        {
            BOOST_WARN_MESSAGE(false, "Locale not supported.");
        }
    }

    BOOST_AUTO_TEST_CASE(external_encoding)
    {
        if (locale_supported())
        {
            {
                {
                    const m_m_encoder_type encoder =
                        m_m_encoder_type(
                            m_encoding_type(locale_en),
                            m_encoding_type(locale_ja)
                        );

                    BOOST_CHECK(
                        encoder.external_encoding().locale_based_on() ==
                        locale_ja
                    );
                }
                {
                    const m_m_encoder_type encoder =
                        m_m_encoder_type(
                            m_encoding_type(locale_ja),
                            m_encoding_type(locale_en)
                        );

                    BOOST_CHECK(
                        encoder.external_encoding().locale_based_on() ==
                        locale_en
                    );
                }
            }
            {
                {
                    const m_w_encoder_type encoder =
                        m_w_encoder_type(
                            m_encoding_type(locale_en),
                            w_encoding_type(locale_ja)
                        );

                    BOOST_CHECK(
                        encoder.external_encoding().locale_based_on() ==
                        locale_ja
                    );
                }
                {
                    const m_w_encoder_type encoder =
                        m_w_encoder_type(
                            m_encoding_type(locale_ja),
                            w_encoding_type(locale_en)
                        );

                    BOOST_CHECK(
                        encoder.external_encoding().locale_based_on() ==
                        locale_en
                    );
                }
            }
            {
                {
                    const w_m_encoder_type encoder =
                        w_m_encoder_type(
                            w_encoding_type(locale_en),
                            m_encoding_type(locale_ja)
                        );

                    BOOST_CHECK(
                        encoder.external_encoding().locale_based_on() ==
                        locale_ja
                    );
                }
                {
                    const w_m_encoder_type encoder =
                        w_m_encoder_type(
                            w_encoding_type(locale_ja),
                            m_encoding_type(locale_en)
                        );

                    BOOST_CHECK(
                        encoder.external_encoding().locale_based_on() ==
                        locale_en
                    );
                }
            }
            {
                {
                    const w_w_encoder_type encoder =
                        w_w_encoder_type(
                            w_encoding_type(locale_en),
                            w_encoding_type(locale_ja)
                        );

                    BOOST_CHECK(
                        encoder.external_encoding().locale_based_on() ==
                        locale_ja
                    );
                }
                {
                    const w_w_encoder_type encoder =
                        w_w_encoder_type(
                            w_encoding_type(locale_ja),
                            w_encoding_type(locale_en)
                        );

                    BOOST_CHECK(
                        encoder.external_encoding().locale_based_on() ==
                        locale_en
                    );
                }
            }
        }
        else
        {
            BOOST_WARN_MESSAGE(false, "Locale not supported.");
        }
    }

    BOOST_AUTO_TEST_CASE(encode)
    {
        {
            const m_m_encoder_type::internal_string_type internal_string(
                TETENGO2_TEXT("Tetengo2")
            );
            const m_m_encoder_type::external_string_type external_string(
                TETENGO2_TEXT("Tetengo2")
            );

            const m_m_encoder_type encoder =
                m_m_encoder_type(
                    m_encoding_type(std::locale::classic()),
                    m_encoding_type(std::locale::classic())
                );

            BOOST_CHECK(encoder.encode(internal_string) == external_string);
        }
        {
            const m_w_encoder_type::internal_string_type internal_string(
                TETENGO2_TEXT("Tetengo2")
            );
            const m_w_encoder_type::external_string_type external_string(
                TETENGO2_TEXT("Tetengo2")
            );

            const m_w_encoder_type encoder =
                m_w_encoder_type(
                    m_encoding_type(std::locale::classic()),
                    w_encoding_type(std::locale::classic())
                );

            BOOST_CHECK(encoder.encode(internal_string) == external_string);
        }
        {
            const w_m_encoder_type::internal_string_type internal_string(
                TETENGO2_TEXT("Tetengo2")
            );
            const w_m_encoder_type::external_string_type external_string(
                TETENGO2_TEXT("Tetengo2")
            );

            const w_m_encoder_type encoder =
                w_m_encoder_type(
                    w_encoding_type(std::locale::classic()),
                    m_encoding_type(std::locale::classic())
                );

            BOOST_CHECK(encoder.encode(internal_string) == external_string);
        }
        {
            const w_w_encoder_type::internal_string_type internal_string(
                TETENGO2_TEXT("Tetengo2")
            );
            const w_w_encoder_type::external_string_type external_string(
                TETENGO2_TEXT("Tetengo2")
            );

            const w_w_encoder_type encoder =
                w_w_encoder_type(
                    w_encoding_type(std::locale::classic()),
                    w_encoding_type(std::locale::classic())
                );

            BOOST_CHECK(encoder.encode(internal_string) == external_string);
        }
    }

    BOOST_AUTO_TEST_CASE(decode)
    {
        {
            const m_m_encoder_type::internal_string_type internal_string(
                TETENGO2_TEXT("Tetengo2")
            );
            const m_m_encoder_type::external_string_type external_string(
                TETENGO2_TEXT("Tetengo2")
            );

            const m_m_encoder_type encoder =
                m_m_encoder_type(
                    m_encoding_type(std::locale::classic()),
                    m_encoding_type(std::locale::classic())
                );

            BOOST_CHECK(encoder.decode(external_string) == internal_string);
        }
        {
            const m_w_encoder_type::internal_string_type internal_string(
                TETENGO2_TEXT("Tetengo2")
            );
            const m_w_encoder_type::external_string_type external_string(
                TETENGO2_TEXT("Tetengo2")
            );

            const m_w_encoder_type encoder =
                m_w_encoder_type(
                    m_encoding_type(std::locale::classic()),
                    w_encoding_type(std::locale::classic())
                );

            BOOST_CHECK(encoder.decode(external_string) == internal_string);
        }
        {
            const w_m_encoder_type::internal_string_type internal_string(
                TETENGO2_TEXT("Tetengo2")
            );
            const w_m_encoder_type::external_string_type external_string(
                TETENGO2_TEXT("Tetengo2")
            );

            const w_m_encoder_type encoder =
                w_m_encoder_type(
                    w_encoding_type(std::locale::classic()),
                    m_encoding_type(std::locale::classic())
                );

            BOOST_CHECK(encoder.decode(external_string) == internal_string);
        }
        {
            const w_w_encoder_type::internal_string_type internal_string(
                TETENGO2_TEXT("Tetengo2")
            );
            const w_w_encoder_type::external_string_type external_string(
                TETENGO2_TEXT("Tetengo2")
            );

            const w_w_encoder_type encoder =
                w_w_encoder_type(
                    w_encoding_type(std::locale::classic()),
                    w_encoding_type(std::locale::classic())
                );

            BOOST_CHECK(encoder.decode(external_string) == internal_string);
        }
    }


BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()
