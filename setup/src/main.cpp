/*! \file
    \brief The definition of the main function.

    Copyright (C) 2007-2013 kaoru

    $Id$
*/

#include <exception>
#include <string>

#define NOMINMAX
#define OEMRESOURCE
#include <Windows.h>
#include <CommCtrl.h>

#include <tetengo2.stdalt.h>
#include <tetengo2.utility.h>


namespace
{
    void show_error_message(const ::HINSTANCE instance_handle, const std::string& message = std::string())
    TETENGO2_STDALT_NOEXCEPT
    {
        try
        {
            ::TaskDialog(NULL, instance_handle, L"Setup", L"Cannot setup.", NULL, TDCBF_CLOSE_BUTTON, NULL, NULL);
        }
        catch (...){}
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
TETENGO2_STDALT_NOEXCEPT
{
    tetengo2::suppress_unused_variable_warning(hInstance, hPrevInstance, lpCmdLine, nCmdShow);

    try
    {
        return 0;
    }
    catch (const std::exception& e)
    {
        show_error_message(hInstance, e.what());
        return 1;
    }
    catch (...)
    {
        show_error_message(hInstance);
        return 1;
    }
}
