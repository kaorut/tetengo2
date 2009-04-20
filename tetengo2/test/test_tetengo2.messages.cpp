/*! \file
    \brief Test of class tetengo2::messages.

    Copyright (C) 2007-2009 kaoru

    $Id$
*/

#include <locale>
#include <string>

#include <boost/filesystem.hpp>
#include <boost/test/unit_test.hpp>

#include "tetengo2.messages.h"


namespace
{
    // types

    typedef
        tetengo2::messages<std::wstring, boost::filesystem::wpath>
        messages_type;

    struct set_locale_to_ja
    {
        const std::locale m_initial_locale;

        set_locale_to_ja()
        :
        m_initial_locale(std::locale::global(std::locale("")))
        {}

        ~set_locale_to_ja()
        {
            std::locale::global(m_initial_locale);
        }

    };

    struct set_locale_to_en
    {
        const std::locale m_initial_locale;

        set_locale_to_en()
        :
        m_initial_locale(std::locale::global(std::locale("")))
        {}

        ~set_locale_to_en()
        {
            std::locale::global(m_initial_locale);
        }

    };

};


BOOST_AUTO_TEST_SUITE(test_tetengo2)
BOOST_AUTO_TEST_SUITE(messages)
    // test cases

    BOOST_AUTO_TEST_CASE(construction)
    {
        BOOST_CHECKPOINT("");

        const messages_type messages(boost::filesystem::wpath(L""));
    }

    BOOST_FIXTURE_TEST_CASE(do_open, set_locale_to_en)
    {
        BOOST_CHECKPOINT("");
    }

    BOOST_FIXTURE_TEST_CASE(do_get, set_locale_to_en)
    {
        BOOST_CHECKPOINT("");
    }

    BOOST_FIXTURE_TEST_CASE(do_close, set_locale_to_en)
    {
        BOOST_CHECKPOINT("");
    }


BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()
