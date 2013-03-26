/*! \file
    \brief The definition of the main function.

    Copyright (C) 2007-2013 kaoru

    $Id$
*/

//#include <exception>
//#include <locale>
//#include <memory>
//#include <stdexcept>
//#include <string>
//#include <vector>

//#include <boost/exception/all.hpp>
//#include <boost/filesystem.hpp>
//#include <boost/mpl/at.hpp>
//#include <boost/program_options.hpp>
//#include <boost/throw_exception.hpp>

//#define NOMINMAX
//#define OEMRESOURCE
//#include <Windows.h>

#include <tetengo2.cpp11.h>
#include <tetengo2.unique.h>
#include <tetengo2.utility.h>

#include "bobura.application.h"
#include "bobura.type_list.h"


namespace
{
    // types

    typedef boost::mpl::at<bobura::setting_type_list, bobura::type::setting::settings>::type settings_type;


    // functions

    std::string locale_info(const ::LCID id, const ::LCTYPE type)
    {
        const auto length = ::GetLocaleInfoA(id, type, nullptr, 0);
        if (length == 0)
            BOOST_THROW_EXCEPTION(std::runtime_error("Can't get locale info."));

        std::vector<char> info(length, '\0');
        ::GetLocaleInfoA(id, type, info.data(), length);

        return std::string(info.data());
    }

    std::string ui_locale_name()
    {
        const auto language_id = ::GetUserDefaultLangID();
        const ::LCID locale_id = MAKELCID(language_id, SORT_DEFAULT);

        return locale_info(locale_id, LOCALE_SENGLANGUAGE) + "_" + locale_info(locale_id, LOCALE_SENGCOUNTRY);
    }

    void set_locale(const boost::filesystem::path& message_directory_path)
    {
        typedef
            boost::mpl::at<bobura::locale_type_list, bobura::type::locale::messages_facet>::type messages_facet_type;
        auto p_messages_facet =
            tetengo2::make_unique<messages_facet_type>(message_directory_path, std::locale(ui_locale_name().c_str()));
        const std::locale global_locale(std::locale(""), p_messages_facet.release());

        std::locale::global(global_locale);
    }

    int run_application(settings_type& settings)
    {
        return bobura::application(settings).run();
    }


}


/*!
    \brief The entry point of the application.

    \param hInstance     Not used.
    \param hPrevInstance Not used.
    \param lpCmdLine     Not used.
    \param nCmdShow      Not used.

    \return The exit status code.
*/
int WINAPI wWinMain(
    const ::HINSTANCE hInstance,
    const ::HINSTANCE hPrevInstance,
    const ::LPWSTR    lpCmdLine,
    const int         nCmdShow
)
TETENGO2_CPP11_NOEXCEPT
{
    tetengo2::suppress_unused_variable_warning(hInstance, hPrevInstance, lpCmdLine, nCmdShow);

    typedef boost::mpl::at<bobura::ui_type_list, bobura::type::ui::alert>::type alsert_type;

    try
    {
        settings_type settings(boost::program_options::split_winmain(::GetCommandLineW()));

        set_locale(settings.message_directory_path());

        return ::run_application(settings);
    }
    catch (const boost::exception& e)
    {
        alsert_type()(e);
        return 1;
    }
    catch (const std::exception& e)
    {
        alsert_type()(e);
        return 1;
    }
    catch (...)
    {
        alsert_type()();
        return 2;
    }
}
