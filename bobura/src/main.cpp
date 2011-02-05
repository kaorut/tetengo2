/*! \file
    \brief The definition of the main function.

    Copyright (C) 2007-2011 kaoru

    $Id$
*/

//#include <cassert>
//#include <cstddef>
//#include <exception>
//#include <locale>
//#include <stdexcept>
//#include <string>
//#include <utility>
//#include <vector>

//#include <boost/exception/all.hpp>
//#define BOOST_FILESYSTEM_VERSION 3
//#include <boost/filesystem.hpp>
//#include <boost/mpl/at.hpp>
//#include <boost/program_options.hpp>
//#include <boost/scoped_array.hpp>
//#include <boost/throw_exception.hpp>

//#define NOMINMAX
//#define OEMRESOURCE
//#include <Windows.h>

#include <tetengo2.cpp0x_keyword.h>
#include <tetengo2.text.h>

#include "bobura.type_list.h"


namespace
{
    // types

    typedef
        boost::mpl::at<bobura::type_list, bobura::type::settings>::type
        settings_type;


    // functions

    std::string locale_info(const ::LCID id, const ::LCTYPE type)
    {
        const int length = ::GetLocaleInfoA(id, type, NULL, 0);
        if (length == 0)
        {
            BOOST_THROW_EXCEPTION(
                std::runtime_error("Can't get locale info.")
            );
        }

        boost::scoped_array<char> p_info(new char[length]);
        ::GetLocaleInfoA(id, type, p_info.get(), length);

        return std::string(p_info.get());
    }

    std::string ui_locale_name()
    {
        const ::LANGID language_id = ::GetUserDefaultLangID();
        const ::LCID locale_id = MAKELCID(language_id, SORT_DEFAULT);

        return locale_info(locale_id, LOCALE_SENGLANGUAGE) +
            "_" +
            locale_info(locale_id, LOCALE_SENGCOUNTRY);
    }

    void set_locale(const boost::filesystem::path& message_directory_path)
    {
        const std::locale global_locale(
            std::locale(""),
            new boost::mpl::at<
                bobura::type_list, bobura::type::messages_facet
            >::type(
                message_directory_path, std::locale(ui_locale_name().c_str())
            )
        );

        std::locale::global(global_locale);
    }

    int run_application(const settings_type& settings)
    {
        return boost::mpl::at<
            bobura::type_list, bobura::type::application
        >::type(settings).run();
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
TETENGO2_CPP0X_NOEXCEPT
{
    try
    {
        std::vector<std::wstring> command_line_arguments =
            boost::program_options::split_winmain(::GetCommandLineW());
        assert(!command_line_arguments.empty());
        boost::filesystem::path base_path =
            boost::filesystem::path(command_line_arguments[0]).parent_path();
        const settings_type settings(
            std::move(command_line_arguments), std::move(base_path)
        );

        set_locale(settings.message_directory_path());

        return ::run_application(settings);
    }
    catch (const boost::exception& e)
    {
        boost::mpl::at<bobura::type_list, bobura::type::alert>::type()(e);
        return 1;
    }
    catch (const std::exception& e)
    {
        boost::mpl::at<bobura::type_list, bobura::type::alert>::type()(e);
        return 1;
    }
    catch (...)
    {
        boost::mpl::at<bobura::type_list, bobura::type::alert>::type()();
        return 2;
    }
}
