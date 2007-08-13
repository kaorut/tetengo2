/*!
	\file The definition of the main function.

	Copyright (C) 2007 kaoru
*/

#include <exception>

#include <boost/program_options.hpp>

#define OEMRESOURCE
#include <windows.h>

#include "bobura.configuration.h"


namespace
{
	template <typename Char, typename InstanceHandle>
	int run_application(
		const InstanceHandle instance_handle,
		const boost::program_options::basic_parsed_options<Char>&
		parsed_options
	)
	{
		boost::program_options::variables_map option_values;
		boost::program_options::store(parsed_options, option_values);
		boost::program_options::notify(option_values);

		return bobura::configuration<Char, InstanceHandle>(
			option_values
		).create_bobura(instance_handle)->run();
	}
}

int WINAPI wWinMain(
	const ::HINSTANCE hInstance,
	const ::HINSTANCE /* hPrevInstance */,
	const ::LPWSTR    lpCmdLine,
	const int         /* nCmdShow */
)
throw ()
{
	typedef bobura::configuration<wchar_t, ::HINSTANCE> configuration_type;

	try
	{
		return ::run_application(
			hInstance,
			boost::program_options::wcommand_line_parser(
				boost::program_options::split_winmain(lpCmdLine)
			).options(configuration_type::options()).run()
		);
	}
	catch (const std::exception& e)
	{
		configuration_type::gui_factory_type::show_fatal_error(NULL, e);
		return 1;
	}
	catch (...)
	{
		configuration_type::gui_factory_type::show_fatal_error(NULL);
		return 2;
	}
}
