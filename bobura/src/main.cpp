/*! \file
    \brief The definition of the main function.

    Copyright (C) 2007-2009 kaoru

    $Id$
*/

//#include <exception>
//#include <string>
//#include <vector>

//#include <boost/program_options.hpp>

#include "bobura.type_list.h"


namespace
{
    /*!
        \brief Creates the application and runs it.

        \tparam CommandLineArgumentInputIterator A input iterator type for a
                                                 command line arguments.

        \param command_line_argument_first The first iterator for a command
                                           line arguments.
        \param command_line_argument_last  The last iterator for a command
                                           line arguments.

        \return The exit status code.
    */
    template <typename CommandLineArgumentInputIterator>
    int run_application(
        CommandLineArgumentInputIterator command_line_argument_first,
        CommandLineArgumentInputIterator command_line_argument_last
    )
    {
        const bobura::type_list::settings_type settings(
            command_line_argument_first, command_line_argument_last
        );

        return bobura::type_list::bobura_type().run();
    }


}

/*!
    \brief The entry point of the application.

    \param hInstance     Not used.
    \param hPrevInstance Not used.
    \param lpCmdLine     The command line arguments.
    \param nCmdShow      Not used.

    \return The exit status code.
*/
int WINAPI wWinMain(
    const ::HINSTANCE hInstance,
    const ::HINSTANCE hPrevInstance,
    const ::LPWSTR    lpCmdLine,
    const int         nCmdShow
)
throw ()
{
    try
    {
        const std::vector<std::wstring> command_line_arguments =
            boost::program_options::split_winmain(lpCmdLine);
        return ::run_application(
            command_line_arguments.begin(), command_line_arguments.end()
        );
    }
    catch (const std::exception& e)
    {
        bobura::type_list::alert_type()(e);
        return 1;
    }
    catch (...)
    {
        bobura::type_list::alert_type()();
        return 2;
    }
}
