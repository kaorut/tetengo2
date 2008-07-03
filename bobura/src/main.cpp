/*! \file
    \brief The definition of the main function.

    Copyright (C) 2007-2008 kaoru

    $Id$
*/

//#include <exception>

#include <boost/program_options.hpp>

#include "bobura.configuration.h"


namespace
{
    /*!
        \brief Creates the application and runs it.

        \param parsed_options The parsed command line options.

        \return The exit status code.
    */
    int run_application(
        const boost::program_options::wparsed_options& parsed_options
    )
    {
        boost::program_options::variables_map option_values;
        boost::program_options::store(parsed_options, option_values);
        boost::program_options::notify(option_values);

        return bobura::configuration(option_values).create_bobura()->run();
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
        return ::run_application(
            boost::program_options::wcommand_line_parser(
                boost::program_options::split_winmain(lpCmdLine)
            ).options(bobura::configuration::options()).run()
        );
    }
    catch (const std::exception& e)
    {
        bobura::configuration::alert()(e);
        return 1;
    }
    catch (...)
    {
        bobura::configuration::alert()();
        return 2;
    }
}
