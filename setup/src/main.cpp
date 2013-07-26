/*! \file
    \brief The definition of the main function.

    Copyright (C) 2007-2013 kaoru

    $Id$
*/

#include <exception>
#include <locale>
#include <string>

#define NOMINMAX
#define OEMRESOURCE
#include <Windows.h>
#include <CommCtrl.h>

#include <tetengo2.detail.windows.encoding.h>
#include <tetengo2.stdalt.h>
#include <tetengo2.text.encoder.h>
#include <tetengo2.text.encoding.ascii.h>
#include <tetengo2.text.encoding.locale.h>
#include <tetengo2.utility.h>


namespace
{
    const std::wstring& message_box_title()
    {
        static const std::wstring singleton(L"Bobura Setup");
        return singleton;
    }

    std::wstring detect_language()
    {
        if (std::locale() == std::locale("Japanese"))
            return L"ja";
        else
            return std::wstring();
    }

    std::wstring detect_platform()
    {
        ::SYSTEM_INFO info = {};
        ::GetNativeSystemInfo(&info);
        if (info.wProcessorArchitecture == PROCESSOR_ARCHITECTURE_AMD64)
            return L"x64";
        else if (info.wProcessorArchitecture == PROCESSOR_ARCHITECTURE_INTEL)
            return L"Win32";
        else
            return std::wstring();
    }

    typedef tetengo2::detail::windows::encoding encoding_details_type;

    typedef
        tetengo2::text::encoder<
            tetengo2::text::encoding::ascii<encoding_details_type>,
            tetengo2::text::encoding::locale<std::wstring, encoding_details_type>
        >
        encoder_type;

    const encoder_type& encoder()
    {
        static const encoder_type singleton;
        return singleton;
    }

    void show_error_message(const ::HINSTANCE instance_handle, const std::string& message = std::string())
    TETENGO2_STDALT_NOEXCEPT
    {
        try
        {
            ::TaskDialog(
                NULL,
                instance_handle,
                message_box_title().c_str(),
                encoder().encode(message).c_str(),
                NULL,
                TDCBF_CLOSE_BUTTON,
                NULL,
                NULL
            );
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
        std::locale::global(std::locale(""));

        const std::wstring language = detect_language();
        const std::wstring platform = detect_platform();

        throw std::exception("hoge");
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
