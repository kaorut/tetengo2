/*! \file
    \brief The definition of the main function.

    Copyright (C) 2007-2013 kaoru

    $Id$
*/

#include <cstdint>
#include <exception>
#include <locale>
#include <string>

#include <boost/filesystem.hpp>

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
    const std::wstring& application_name()
    {
        static const std::wstring singleton(L"Bobura");
        return singleton;
    }

    const std::string& application_name_narrow()
    {
        static const std::string singleton("Bobura");
        return singleton;
    }

    const std::wstring& message_box_title()
    {
        static const std::wstring singleton(application_name() + L" Setup");
        return singleton;
    }

    const std::wstring& msi_prefix()
    {
        static const std::wstring singleton(L"bobura.");
        return singleton;
    }

    const std::wstring& msi_suffix()
    {
        static const std::wstring singleton(L".msi");
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

    boost::filesystem::path msi_path(const boost::filesystem::path& base_path_, const std::wstring& platform)
    {
        return base_path_ / boost::filesystem::path(msi_prefix() + platform + msi_suffix());
    }

    std::wstring build_parameters(
        const std::wstring&            language,
        const std::wstring&            platform,
        const boost::filesystem::path& base_path_
    )
    {
        std::wstring parameters;

        parameters += L"/i ";
        parameters += std::wstring(L"\"") + msi_path(base_path_, platform).c_str() + L"\" ";
        if (!language.empty())
            parameters += L"TRANSFORMS=\":" + language + L".mst\"";

        return parameters;
    }

    boost::filesystem::path base_path()
    {
        std::vector<wchar_t> path_buffer(MAX_PATH, 0);
        const ::DWORD path_length = ::GetModuleFileNameW(NULL, path_buffer.data(), path_buffer.size());
        if (path_length == 0)
            throw std::runtime_error("Cannot get the path where the installer exists.");

        boost::filesystem::path path(path_buffer.begin(), path_buffer.begin() + path_length);
        
        return path.parent_path();
    }

    void launch_msi(const std::wstring& language, const std::wstring& platform, const int window_state)
    {
        if (platform.empty())
        {
            throw
                std::runtime_error(std::string("Cannot install ") + application_name_narrow() + " to this platform.");
        }

        const boost::filesystem::path base_path_ = base_path();

        const std::wstring parameters = build_parameters(language, platform, base_path_);

        const ::HINSTANCE instance_handle =
            ::ShellExecuteW(NULL, NULL, L"msiexec", parameters.c_str(), base_path_.c_str(), window_state);
        if (reinterpret_cast<std::intptr_t>(instance_handle) <= 32)
            throw std::runtime_error("Cannot launch the msi file.");
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

        launch_msi(language, platform, nCmdShow);

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
